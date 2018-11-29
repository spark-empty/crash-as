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
#include <linux/err.h>
#include <linux/platform_device.h>
#include <linux/dma-mapping.h>
#include <linux/remoteproc.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/mutex.h>
#include <linux/semaphore.h>
#include "remoteproc_internal.h"

/* ============================ [ MACROS    ] ====================================================== */
#ifndef SLEEP_MILLI_SEC
#define SLEEP_MILLI_SEC(nMilliSec) \
    do { \
        long timeout = (nMilliSec) * HZ /1000; \
        while (timeout > 0) \
        { \
            timeout = schedule_timeout(timeout); \
        } \
    }while (0);
#endif

#define IPC_FIFO_SIZE 1024
/* ============================ [ TYPES     ] ====================================================== */
typedef struct
{
	u32 count;
	u32     idx[IPC_FIFO_SIZE];
}Ipc_FifoType;

/**
 * struct asvirt_rproc - asvirt remote processor state
 * @rproc: rproc handle
 */
struct asvirt_rproc {
	struct task_struct * task_linux;
	struct task_struct * task_mcu;

	/* r and w to linux */
	struct mutex r_lock;
	struct mutex w_lock;
	struct semaphore r_event;
	struct semaphore w_event;

	Ipc_FifoType* r_fifo;
	Ipc_FifoType* w_fifo;

	u32 r_pos;
	u32 w_pos;

	struct rproc *rproc;

	int table_loaded;
};
/* ============================ [ DECLARES  ] ====================================================== */
static int asvirt_rproc_probe(struct platform_device *pdev);
static int asvirt_rproc_remove(struct platform_device *pdev);
static void asvirt_rproc_kick(struct rproc *rproc, int vqid);
static struct resource_table *
asvirt_find_rsc_table(struct rproc *rproc, const struct firmware *fw,
		     int *tablesz);
static struct resource_table *
asvirt_find_loaded_rsc_table(struct rproc *rproc, const struct firmware *fw);
static int asvirt_rproc_stop(struct rproc *rproc);
static int asvirt_rproc_start(struct rproc *rproc);

extern void* Qt_GetRprocResourceTable(void);
extern unsigned int Qt_GetRprocResourceTableSize(void);
/* ============================ [ DATAS     ] ====================================================== */
static struct rproc_ops asvirt_rproc_ops = {
	.start		= asvirt_rproc_start,
	.stop		= asvirt_rproc_stop,
	.kick		= asvirt_rproc_kick,
};

/* ASVIRT firmware handler operations */
static const struct rproc_fw_ops asvirt_fw_ops = {
	.load = NULL,
	.find_rsc_table = asvirt_find_rsc_table,
	.find_loaded_rsc_table = asvirt_find_loaded_rsc_table,
};

static struct of_device_id asvirt_rproc_of_match[] = {
	{ .compatible = "as,virtual-rproc" },
};

static struct platform_driver asvirt_rproc_driver = {
	.probe = asvirt_rproc_probe,
	.remove = asvirt_rproc_remove,
	.driver = {
		.name = "asvirt-rproc",
		.owner = THIS_MODULE,
		.of_match_table = asvirt_rproc_of_match,
	},
};
/* ============================ [ LOCALS    ] ====================================================== */
static int fifo_read(struct asvirt_rproc *oproc, int *idx)
{
    int ercd;
    if(oproc->r_fifo->count > 0)
    {
        *idx = oproc->r_fifo->idx[oproc->r_pos];
        //printk("Kernel: Incoming message: 0x%X,pos=%d,count=%d from fifo@%p\n",
        //		*idx,oproc->r_pos,oproc->r_fifo->count,oproc->r_fifo);
        oproc->r_fifo->count -= 1;
        oproc->r_pos = (oproc->r_pos + 1)%(IPC_FIFO_SIZE);
        ercd = 0;
    }
    else
    {
        ercd  = -1;
    }
    return ercd;
}
static int fifo_write(struct asvirt_rproc *oproc, int idx)
{
	int ercd;

	mutex_lock(&oproc->w_lock);

	if(oproc->w_fifo->count < IPC_FIFO_SIZE)
	{
		oproc->w_fifo->idx[oproc->w_pos] = idx;
		oproc->w_fifo->count += 1;
		//printk("Kernel: Transmit message: 0x%X,pos=%d,count=%d through fifo@%p\n",
		//		idx,oproc->w_pos,oproc->w_fifo->count,oproc->w_fifo);
		oproc->w_pos = (oproc->w_pos + 1)%(IPC_FIFO_SIZE);
		ercd = 0;
	}
	else
	{
		ercd = -1;
	}

	mutex_unlock(&oproc->w_lock );
	up(&oproc->w_event);

	return ercd;
}
/* kick a virtqueue */
static void asvirt_rproc_kick(struct rproc *rproc, int vqid)
{
	struct asvirt_rproc *oproc = rproc->priv;
	struct device *dev = rproc->dev.parent;
	int ret;

	if(0 == oproc->table_loaded)
	{
		memcpy(Qt_GetRprocResourceTable(),rproc->cached_table,Qt_GetRprocResourceTableSize());
		oproc->table_loaded=1;
	}

	/* send the index of the triggered virtqueue in the mailbox payload */
	ret = fifo_write(oproc,vqid);
	if (ret)
		dev_err(dev, "fifo_write failed: %d\n", ret);
}

/* Find the resource table inside the remote processor's firmware. */
static struct resource_table *
asvirt_find_rsc_table(struct rproc *rproc, const struct firmware *fw,
		     int *tablesz)
{
	struct resource_table * rsc_tbl;

	rsc_tbl =  (struct resource_table *)Qt_GetRprocResourceTable();

	*tablesz = Qt_GetRprocResourceTableSize();
	return rsc_tbl;
}

/* Find the resource table inside the remote processor's firmware. */
static struct resource_table *
asvirt_find_loaded_rsc_table(struct rproc *rproc, const struct firmware *fw)
{
	struct resource_table * rsc_tbl;

	rsc_tbl =  (struct resource_table *)Qt_GetRprocResourceTable();

	return rsc_tbl;
}
/*
 * Power up the remote processor.
 *
 * This function will be invoked only after the firmware for this rproc
 * was loaded, parsed successfully, and all of its resource requirements
 * were met.
 */
static int asvirt_rproc_start(struct rproc *rproc)
{
	struct device *dev = rproc->dev.parent;
	struct platform_device *pdev = to_platform_device(dev);

	dev_info(&pdev->dev, " >>> rproc linux starting... <<<\n");

	//asvirt_rproc_kick(rproc,0xFFFFFFFF);

	return 0;
}

/* power off the remote processor */
static int asvirt_rproc_stop(struct rproc *rproc)
{
	struct device *dev = rproc->dev.parent;
	struct platform_device *pdev = to_platform_device(dev);

	dev_info(&pdev->dev, " >>> rproc linux stop... <<<\n");

	//asvirt_rproc_kick(rproc,0xFFFFFFFE);

	return 0;
}

static int thread_rproc_linux(void *data)
{
	int vqid=0,ercd;
	struct rproc *rproc =  (struct rproc *)data;
	struct device *dev = rproc->dev.parent;
	struct asvirt_rproc *oproc = rproc->priv;
	struct platform_device *pdev = to_platform_device(dev);

	/* sleep for a while make sure MCU thread run firstly */
	SLEEP_MILLI_SEC(100);
	dev_info(&pdev->dev, "rproc linux side thread is running...\n");

	while(1)
	{
		down(&oproc->r_event);

		mutex_lock(&oproc->r_lock);
		do {
			ercd = fifo_read(oproc,&vqid);

			if(!ercd)
			{
				if (rproc_vq_interrupt(rproc, vqid) == IRQ_NONE)
					dev_err(&pdev->dev, "no message was found in vqid %d\n", vqid);
			}
			else
			{

			}
		} while(ercd);
		mutex_unlock(&oproc->r_lock);
	}

	return 0;
}

extern void Qt_SetIpcParam(int chl, void* r_lock, void* r_event, void* w_lock, void* w_event);
extern void Qt_GetIpcFifo(int chl, Ipc_FifoType** r_fifo, Ipc_FifoType** w_fifo);
extern void Qt_SetIpcBaseAddress(unsigned long base);
extern void aslinux_mcu_rproc_start(void);
static int thread_rproc_mcu(void *data)
{
	struct rproc *rproc =  (struct rproc *)data;
	struct device *dev = rproc->dev.parent;
	struct platform_device *pdev = to_platform_device(dev);
	//struct asvirt_rproc *oproc = rproc->priv;

	dev_info(&pdev->dev, "rproc MCU side thread is running...\n");

	aslinux_mcu_rproc_start();

	return 0;
}

static int asvirt_rproc_probe(struct platform_device *pdev)
{
	const char* firmware_name;
	struct device_node *np = pdev->dev.of_node;
	struct asvirt_rproc *oproc;
	struct rproc *rproc;
	int ret;

	ret = dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32));
	if (ret) {
		dev_err(&pdev->dev, "dma_set_coherent_mask: %d\n", ret);
		return ret;
	}

	ret = of_property_read_string(np,"fwname",&firmware_name);
	if (ret) {
		dev_err(&pdev->dev, "of_property_read_string: %d\n", ret);
		return ret;
	}

	rproc = rproc_alloc(&pdev->dev, firmware_name, &asvirt_rproc_ops,
				NULL, sizeof(*oproc));
	if (!rproc)
		return -ENOMEM;

	oproc = rproc->priv;
	oproc->rproc = rproc;

	/* Set the STE-modem specific firmware handler */
	rproc->fw_ops = &asvirt_fw_ops;

	atomic_inc(&rproc->power);

	platform_set_drvdata(pdev, rproc);

	Qt_SetIpcParam(0,&oproc->r_lock,&oproc->r_event,&oproc->w_lock,&oproc->w_event);
	Qt_GetIpcFifo(0,&oproc->r_fifo,&oproc->w_fifo);
	Qt_SetIpcBaseAddress(0);

	oproc->task_linux = kthread_run(&thread_rproc_linux,(void *)rproc,"rproc-linux");
	if(NULL == oproc->task_linux)
		goto free_rproc;

	oproc->task_mcu = kthread_run(&thread_rproc_mcu,(void *)rproc,"rproc-mcu");
	if(NULL == oproc->task_mcu)
		goto free_rproc;

	mutex_init(&oproc->r_lock);
	mutex_init(&oproc->w_lock);

	sema_init(&oproc->r_event,0);
	sema_init(&oproc->w_event,0);

	oproc->table_loaded = 0;

	ret = rproc_add(rproc);
	if (ret)
		goto free_rproc;

	dev_info(&pdev->dev, "initialized ASVIRT remote processor driver\n");

	return 0;

free_rproc:
	rproc_put(rproc);
	return ret;
}

static int asvirt_rproc_remove(struct platform_device *pdev)
{
	struct rproc *rproc = platform_get_drvdata(pdev);
	struct asvirt_rproc *oproc = rproc->priv;

	rproc_del(rproc);
	rproc_put(rproc);

	kthread_stop(oproc->task_linux);
	kthread_stop(oproc->task_mcu);

	return 0;
}
/* ============================ [ FUNCTIONS ] ====================================================== */
#include <linux/virtio.h>
#include <linux/virtio_ring.h>
#include <linux/virtio_config.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/hrtimer.h>
#include <linux/kmemleak.h>
unsigned long as_phys_to_virt(unsigned long addr)
{
	return (unsigned long)phys_to_virt(addr);
}

module_platform_driver(asvirt_rproc_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("ASVIRT Remote Processor control driver");
