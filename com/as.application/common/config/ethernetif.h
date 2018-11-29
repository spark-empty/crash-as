#ifdef USE_STDRT
#include_next "ethernetif.h"
#else
#ifndef __ETHERNETIF_H__
#define __ETHERNETIF_H__
#include "lwip/err.h"
#include "lwip/netif.h"

err_t ethernetif_init(struct netif *netif);
struct netif *ethernetif_register(void);
int ethernetif_poll(void);
void Set_MAC_Address(unsigned char* macadd);
void Ethernet_Configuration(void);
void EnableEthDMAIrq(void);
struct pbuf * low_level_input();

#endif 
#endif /* USE_STDRT */
