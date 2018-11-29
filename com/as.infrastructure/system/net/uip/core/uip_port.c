/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2018  AS <parai@foxmail.com>
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
#include "Os.h"
#include "net/ip/uip.h"
#include "net/ipv4/uip_arp.h"
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */
#if defined(__LINUX__)
#define ethernet_process tapdev_process
#elif defined(__WINDOWS__)
#define ethernet_process wpcap_process
#endif

#define AS_LOG_UIP 1
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
#if defined(__LINUX__)
extern struct process tapdev_process;
#elif defined(__WINDOWS__)
extern struct process wpcap_process;
#else
extern struct process ethernet_process;
#endif
extern struct process tcpip_process;
extern struct process tcp_socket_process;
/* ============================ [ DATAS     ] ====================================================== */
PROCESS(protoUIPMain,"protoUIPMain");
PROTO_AUTOSTART_PROCESS_EXPORT(protoUIPMain);
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
PROCESS_THREAD(protoUIPMain, ev, data)
{
	uip_ipaddr_t ipaddr;

	PROCESS_BEGIN();

	ASLOG(UIP, "startup uip!\n");

	process_start(&tcpip_process, NULL);
	uip_ipaddr(&ipaddr, 172, 18, 0, 200);
	uip_sethostaddr(&ipaddr);
	uip_ipaddr(&ipaddr, 255, 255, 255, 0);
	uip_setnetmask(&ipaddr);
	uip_ipaddr(&ipaddr, 172, 18, 0, 1);
	uip_setdraddr(&ipaddr);

	process_start(&ethernet_process, NULL);

	process_start(&tcp_socket_process, NULL);

	for(;;) {
		process_poll(&ethernet_process);
		process_poll(&protoUIPMain);
		PROCESS_YIELD();
	}
	PROCESS_END();
}
