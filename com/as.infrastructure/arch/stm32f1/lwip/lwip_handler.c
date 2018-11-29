/*-------------------------------- Arctic Core ------------------------------
 * Copyright (C) 2013, ArcCore AB, Sweden, www.arccore.com.
 * Contact: <contact@arccore.com>
 *
 * You may ONLY use this file:
 * 1)if you have a valid commercial ArcCore license and then in accordance with
 * the terms contained in the written license agreement between you and ArcCore,
 * or alternatively
 * 2)if you follow the terms found in GNU General Public License version 2 as
 * published by the Free Software Foundation and appearing in the file
 * LICENSE.GPL included in the packaging of this file or here
 * <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>
 *-------------------------------- Arctic Core -----------------------------*/


#include "lwip/opt.h"
#include "lwip/tcp.h"
#include "lwip/udp.h"
#include "lwip/mem.h"
#include "lwip/memp.h"
#include "lwip/tcpip.h"
#include "lwip/inet.h"
#include "netif/etharp.h"
#include "lwip/dhcp.h"
#include "lwip_handler.h"
#include <stdio.h>

#include "netbios.h"
#include "ethernetif.h"
#include "stm32_eth.h"

#include "Os.h"
#include "Mcu.h"

extern struct netif* sys_get_netif(void);
/* Eth Isr routine */
void knl_isr_eth_process(void)
{
	uint32_t res = 0;

	while((ETH_GetRxPktSize() != 0) && (res == 0))
	{
		struct netif* netif = sys_get_netif();
		/* move received packet into a new pbuf */
		struct pbuf *p = low_level_input();

		if(p!=NULL){
			tcpip_input(p, netif);
		}else{
			res = 1;
		}
	}

	/* Clear the Eth DMA Rx IT pending bits */
	ETH_DMAClearITPendingBit(ETH_DMA_IT_R);
	ETH_DMAClearITPendingBit(ETH_DMA_IT_NIS);
	ETH_DMAClearITPendingBit(ETH_DMA_IT_RO);
	ETH_DMAClearITPendingBit(ETH_DMA_IT_RBU);
	NVIC_ClearPendingIRQ(ETH_IRQn);
}


