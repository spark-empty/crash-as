#define LWIP_AR_MAJOR_VERSION   1
#define LWIP_AR_MINOR_VERSION   0
#define LWIP_AR_PATCH_VERSION   0

#define LWIP_SW_MAJOR_VERSION   1
#define LWIP_SW_MINOR_VERSION   0
#define LWIP_SW_PATCH_VERSION   0

#ifndef LWIP_TIMEVAL_PRIVATE
#define LWIP_TIMEVAL_PRIVATE 0
#endif

#ifndef USE_STDRT
#include "LwIp_Cfg.h"
#endif

#ifndef RECV_BUFSIZE_DEFAULT
#define RECV_BUFSIZE_DEFAULT            8192
#endif

#ifdef USE_STDRT
#include_next "lwipopts.h"
#endif

