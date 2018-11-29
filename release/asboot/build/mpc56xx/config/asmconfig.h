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

#ifndef USE_PORT
#define USE_PORT 1
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

#ifndef USE_CANTP
#define USE_CANTP 1
#endif

#ifndef USE_XCP
#define USE_XCP 1
#endif

#ifndef USE_DCM
#define USE_DCM 1
#endif

#ifndef USE_FLASH
#define USE_FLASH 1
#endif

#ifndef USE_TINYOS
#define USE_TINYOS 1
#endif

#ifndef USE_CLIB_STDIO_PRINTF
#define USE_CLIB_STDIO_PRINTF 1
#endif

#ifndef USE_CLIB_STRTOK_R
#define USE_CLIB_STRTOK_R 1
#endif

#ifndef USE_SHELL
#define USE_SHELL 1
#endif

#ifndef USE_FLASH_CMD
#define USE_FLASH_CMD 1
#endif

#ifndef USE_MEM_CMD
#define USE_MEM_CMD 1
#endif

#ifndef USE_JMP_CMD
#define USE_JMP_CMD 1
#endif

#ifndef USE_MPC5634M_MLQB80
#define USE_MPC5634M_MLQB80 1
#endif

#ifndef USE_MINIBLT
#define USE_MINIBLT 1
#endif

#if defined(USE_RTTHREAD) && defined(USE_ARCH_X86)
#define _EXFUN(N,P) N P
#define _READ_WRITE_RETURN_TYPE int
#endif
#ifndef CMDLINE_MAX
#define CMDLINE_MAX 4096
#endif
#ifndef FLASH_CMD_MAX_DATA
#define FLASH_CMD_MAX_DATA 2000
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
#ifndef FLASH_ERASE_SIZE
#define FLASH_ERASE_SIZE 0x20000
#endif
#ifndef FLASH_WRITE_SIZE
#define FLASH_WRITE_SIZE 8
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
#ifndef __AS_BOOTLOADER__
#define __AS_BOOTLOADER__
#endif
#ifndef NO_STDIO_RINGBUFFER
#define NO_STDIO_RINGBUFFER
#endif
#endif /* _AS_MCONF_H_ */
