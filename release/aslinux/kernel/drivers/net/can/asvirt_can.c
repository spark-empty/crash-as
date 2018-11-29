/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2016  AS <parai@foxmail.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */
/* ============================ [ INCLUDES  ] ====================================================== */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/rpmsg.h>
#include <linux/clk.h>
#include <linux/errno.h>
#include <linux/if_arp.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netdevice.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/rtnetlink.h>
#include <linux/skbuff.h>
#include <linux/spinlock.h>
#include <linux/string.h>
#include <linux/types.h>

#include <linux/can/dev.h>
#include <linux/can/error.h>
#include <linux/can/led.h>
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */

/**
 * struct ascan_priv - This definition define CAN driver instance
 * @can:			CAN private data structure.
 * @tx_head:			Tx CAN packets ready to send on the queue
 * @tx_tail:			Tx CAN packets successfully sended on the queue
 * @tx_max:			Maximum number packets the driver can send
 * @napi:			NAPI structure
 * @read_reg:			For reading data from CAN registers
 * @write_reg:			For writing data to CAN registers
 * @dev:			Network device data structure
 * @reg_base:			Ioremapped address to registers
 * @irq_flags:			For request_irq()
 * @bus_clk:			Pointer to struct clk
 * @can_clk:			Pointer to struct clk
 */
struct ascan_priv {
	struct can_priv can;
	struct napi_struct napi;
	struct net_device *dev;

	struct rpmsg_channel *rpdev;
};
/* ============================ [ DECLARES  ] ====================================================== */
static int rpmsg_can_probe(struct rpmsg_channel *rpdev);
static void rpmsg_can_cb(struct rpmsg_channel *rpdev, void *data, int len,
						void *priv, u32 src);
static void rpmsg_can_remove(struct rpmsg_channel *rpdev);

static int ascan_open(struct net_device *ndev);
static int ascan_close(struct net_device *ndev);
static int ascan_start_xmit(struct sk_buff *skb, struct net_device *ndev);
/* ============================ [ DATAS     ] ====================================================== */
static const struct net_device_ops ascan_netdev_ops = {
	.ndo_open	= ascan_open,
	.ndo_stop	= ascan_close,
	.ndo_start_xmit	= ascan_start_xmit,
	.ndo_change_mtu	= can_change_mtu,
};

static struct rpmsg_device_id rpmsg_driver_can_id_table[] = {
	{ .name	= "rpmsg-can-sample" },
	{ },
};
MODULE_DEVICE_TABLE(rpmsg, rpmsg_driver_can_id_table);
static struct rpmsg_driver rpmsg_can_client = {
	.drv.name	= KBUILD_MODNAME,
	.drv.owner	= THIS_MODULE,
	.id_table	= rpmsg_driver_can_id_table,
	.probe		= rpmsg_can_probe,
	.callback	= rpmsg_can_cb,
	.remove		= rpmsg_can_remove,
};
static const struct can_bittiming_const ascan_bittiming_const = {
	.name = KBUILD_MODNAME,
	.tseg1_min = 2,		/* Time segment 1 = prop_seg + phase_seg1 */
	.tseg1_max = 64,
	.tseg2_min = 1,		/* Time segment 2 = phase_seg2 */
	.tseg2_max = 16,
	.sjw_max = 16,
	.brp_min = 1,
	.brp_max = 1024,
	.brp_inc = 1,
};

static const struct can_bittiming_const ascan_data_bittiming_const = {
	.name = KBUILD_MODNAME,
	.tseg1_min = 2,		/* Time segment 1 = prop_seg + phase_seg1 */
	.tseg1_max = 16,
	.tseg2_min = 1,		/* Time segment 2 = phase_seg2 */
	.tseg2_max = 8,
	.sjw_max = 4,
	.brp_min = 1,
	.brp_max = 32,
	.brp_inc = 1,
};
/* ============================ [ LOCALS    ] ====================================================== */

/**
 * ascan_open - Driver open routine
 * @ndev:	Pointer to net_device structure
 *
 * This is the driver open routine.
 * Return: 0 on success and failure value on error
 */
static int ascan_open(struct net_device *ndev)
{
	struct ascan_priv *priv = netdev_priv(ndev);
	int ret;

	/* Common open */
	ret = open_candev(ndev);
	if (ret)
		return ret;

	can_led_event(ndev, CAN_LED_EVENT_OPEN);
	set_bit(NAPI_STATE_SCHED, &(priv->napi.state));
	napi_enable(&priv->napi);
	netif_start_queue(ndev);

	return 0;
}

/**
 * ascan_close - Driver close routine
 * @ndev:	Pointer to net_device structure
 *
 * Return: 0 always
 */
static int ascan_close(struct net_device *ndev)
{
	struct ascan_priv *priv = netdev_priv(ndev);

	netif_stop_queue(ndev);
	napi_disable(&priv->napi);
	close_candev(ndev);

	can_led_event(ndev, CAN_LED_EVENT_STOP);

	return 0;
}

/**
 * ascan_start_xmit - Starts the transmission
 * @skb:	sk_buff pointer that contains data to be Txed
 * @ndev:	Pointer to net_device structure
 *
 * This function is invoked from upper layers to initiate transmission. This
 * function uses the next available free txbuff and populates their fields to
 * start the transmission.
 *
 * Return: 0 on success and failure value on error
 */
static int ascan_start_xmit(struct sk_buff *skb, struct net_device *ndev)
{
	int ret;
	struct ascan_priv *priv = netdev_priv(ndev);
	struct net_device_stats *stats = &ndev->stats;
	struct can_frame *cf = (struct can_frame *)skb->data;
	struct rpmsg_channel *rpdev = priv->rpdev;

	if (can_dropped_invalid_skb(ndev, skb))
		return NETDEV_TX_OK;

	/* send a new message now */
	ret = rpmsg_send(rpdev, cf, sizeof(*cf));
	if (ret)
	{
		dev_err(&rpdev->dev, "CAN: rpmsg_send failed: %d\n", ret);

		return ret;
	}

	stats->tx_bytes += cf->can_dlc;

	return NETDEV_TX_OK;
}

static void rpmsg_can_cb(struct rpmsg_channel *rpdev, void *data, int len,
						void *priv, u32 src)
{
	struct net_device *ndev = (struct net_device *)priv;
	struct net_device_stats *stats = &ndev->stats;
	struct can_frame *cf;
	struct sk_buff *skb;

	/* dev_info(&rpdev->dev, "incoming can msg %d (src: 0x%x)\n", (int)stats->rx_packets+1, src); */

	print_hex_dump(KERN_DEBUG, "rpmsg_can_cb RX: ", DUMP_PREFIX_NONE, 16, 1,
		       data, len,  true);

	skb = alloc_can_skb(ndev, &cf);
	if (unlikely(!skb)) {
		stats->rx_dropped++;
		return;
	}

	if(sizeof(*cf) != len)
	{
		stats->rx_dropped++;
		dev_err(&rpdev->dev, "CAN: invalid length(%d != %d)\n", len,sizeof(*cf));
		return;
	}

	memcpy(cf,data,len);

	stats->rx_bytes += cf->can_dlc;
	stats->rx_packets++;
	netif_receive_skb(skb);
}

static void ascan_start(struct net_device *dev)
{
	/* TODO */
}
static int ascan_set_mode(struct net_device *dev, enum can_mode mode)
{
	switch (mode) {
	case CAN_MODE_START:
		ascan_start(dev);
		netif_wake_queue(dev);
		break;
	default:
		return -EOPNOTSUPP;
	}

	return 0;
}

static int __ascan_get_berr_counter(const struct net_device *dev,
				    struct can_berr_counter *bec)
{
	/* struct ascan_priv *priv = netdev_priv(dev); */

	bec->rxerr = 0;
	bec->txerr = 0;

	return 0;
}
static int ascan_get_berr_counter(const struct net_device *dev,
				  struct can_berr_counter *bec)
{
	/* struct ascan_priv *priv = netdev_priv(dev); */

	__ascan_get_berr_counter(dev, bec);

	return 0;
}

static int rpmsg_can_probe(struct rpmsg_channel *rpdev)
{
	int ret;
	struct can_frame cf;
	struct net_device *ndev;
	struct ascan_priv *priv;

	dev_info(&rpdev->dev, "new channel: 0x%x -> 0x%x!\n",
					rpdev->src, rpdev->dst);

	/* Create a CAN device instance */
	ndev = alloc_candev(sizeof(struct ascan_priv), 0x40);
	if (!ndev)
		return -ENOMEM;

	priv = netdev_priv(ndev);
	priv->dev = ndev;
	priv->rpdev = rpdev;

	rpdev->ept->priv = ndev;

	ndev->netdev_ops = &ascan_netdev_ops;

	/* set up bittiming */
	priv->can.bittiming.bitrate = 1000000; /* 1Mbps */
	priv->can.bittiming_const = &ascan_bittiming_const;
	priv->can.data_bittiming_const = &ascan_data_bittiming_const;
	priv->can.do_set_mode = ascan_set_mode;
	priv->can.do_get_berr_counter = ascan_get_berr_counter;
	priv->can.ctrlmode_supported = CAN_CTRLMODE_LOOPBACK |
					CAN_CTRLMODE_LISTENONLY |
					CAN_CTRLMODE_BERR_REPORTING;

	ret = register_candev(ndev);
	if (ret) {
		dev_err(&rpdev->dev, "rpmsg_send failed: %d\n", ret);
		return ret;
	}

	devm_can_led_init(ndev);

	cf.can_id = 0x777;
	cf.can_dlc = 0x8;
	for (ret=0;ret<8;ret++)
	{
		cf.data[ret] = (ret<<4)+(ret);
	}
	/* send a message to our remote processor */
	ret = rpmsg_send(rpdev, &cf, sizeof(cf));
	if (ret) {
		dev_err(&rpdev->dev, "rpmsg_send failed: %d\n", ret);
		return ret;
	}

	return 0;
}

static void rpmsg_can_remove(struct rpmsg_channel *rpdev)
{
	dev_info(&rpdev->dev, "rpmsg sample client driver is removed\n");
}


static int __init rpmsg_client_can_init(void)
{
	return register_rpmsg_driver(&rpmsg_can_client);
}
static void __exit rpmsg_client_can_fini(void)
{
	unregister_rpmsg_driver(&rpmsg_can_client);
}
/* ============================ [ FUNCTIONS ] ====================================================== */
module_init(rpmsg_client_can_init);
module_exit(rpmsg_client_can_fini);

MODULE_DESCRIPTION("Remote processor messaging sample client driver");
MODULE_LICENSE("GPL v2");
