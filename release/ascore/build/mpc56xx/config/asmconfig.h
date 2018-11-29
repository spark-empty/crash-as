#ifndef _AS_MCONF_H_

#ifndef USE_ECUM
#define USE_ECUM 1
#endif

#ifndef USE_SCHM
#define USE_SCHM 1
#endif

#ifndef USE_MCU
#define USE_MCU 1
#endif

#ifndef USE_DET
#define USE_DET 1
#endif

#ifndef USE_TRACE
#define USE_TRACE 1
#endif

#ifndef USE_CLIB_STDIO_PRINTF
#define USE_CLIB_STDIO_PRINTF 1
#endif

#ifndef USE_ASKAR
#define USE_ASKAR 1
#endif

#ifndef USE_SHELL
#define USE_SHELL 1
#endif

#ifndef USE_CLIB_STRTOK_R
#define USE_CLIB_STRTOK_R 1
#endif

#ifndef USE_MPC5634M_MLQB80
#define USE_MPC5634M_MLQB80 1
#endif

#ifndef USE_PORT
#define USE_PORT 1
#endif

#ifndef USE_DIO
#define USE_DIO 1
#endif

#ifndef USE_CAN
#define USE_CAN 1
#endif

#ifndef USE_CANIF
#define USE_CANIF 1
#endif

#ifndef USE_PDUR
#define USE_PDUR 1
#endif

#ifndef USE_COM
#define USE_COM 1
#endif

#ifndef USE_COMM
#define USE_COMM 1
#endif

#ifndef USE_CANTP
#define USE_CANTP 1
#endif

#ifndef USE_DCM
#define USE_DCM 1
#endif

#ifndef USE_CANNM
#define USE_CANNM 1
#endif

#ifndef USE_CANSM
#define USE_CANSM 1
#endif

#ifndef USE_NM
#define USE_NM 1
#endif

#ifndef USE_OSEKNM
#define USE_OSEKNM 1
#endif

#ifndef USE_XCP
#define USE_XCP 1
#endif

#if defined(USE_RTTHREAD) && defined(USE_ARCH_X86)
#define _EXFUN(N,P) N P
#define _READ_WRITE_RETURN_TYPE int
#endif
#ifndef NOT_PYGEN_CAN
#define NOT_PYGEN_CAN
#endif
#ifndef ENABLE_SHELL_ECHO_BACK
#define ENABLE_SHELL_ECHO_BACK
#endif
#ifndef CFG_MPC563XM
#define CFG_MPC563XM
#endif
#ifndef CFG_MPC55XX
#define CFG_MPC55XX
#endif
#ifndef CPU_FREQUENCY
#define CPU_FREQUENCY 64
#endif
#ifndef CAN_LL_DL
#define CAN_LL_DL 8
#endif
#ifndef USE_FAST_LEAST_TYPE_DEF
#define USE_FAST_LEAST_TYPE_DEF
#endif
#ifndef VLE_IS_ON
#define VLE_IS_ON 1
#endif
#ifndef _G_va_list
#define _G_va_list va_list
#endif
#endif /* _AS_MCONF_H_ */
