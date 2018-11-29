/**
    @file    sample_app_mcal_uart_console.h
    @version 2.0.0

    @brief   AUTOSAR Sample_app - header file for the initialization task for platform reg file.
    @details .

    Project      : AUTOSAR 3.0 MCAL
    Platform     : PA
    Peripheral   : 
    Dependencies : Base Det Dem Port Dio Mcu SchM Wdg WdgIf CanIf LinIf EcuM

    ARVersion     : 1.9.0
    ARRevision    : ASR_REL_1_9_REV_0003
    ARConfVariant :
    SWVersion     : 2.0.0
    BuildVersion  : MPC563xMxM_MCAL_2_0_0_RTM_ASR_REL_1_9_REV_0003_20110214

    (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
    All Rights Reserved.

    You can use this example for any purpose on any computer system with the following restrictions:
    1. This example is provided "as is", without warranty.
    2. You do not remove this copyright notice from this example or any direct derivation thereof.

*/
/*==================================================================================================
==================================================================================================*/

#ifndef SAMPLE_APP_MCAL_UART_CONSOLE_H
#define SAMPLE_APP_MCAL_UART_CONSOLE_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
/**
@file        modules.h
@brief Include Standard types & defines
*/

#include "typedefs.h"
#include "Std_Types.h"

#include <stdarg.h>

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/

/**
@{
@brief Parameters that shall be published within the modules header file.
       The integration of incompatible files shall be avoided.
@remarks Covers
@remarks Implements
*/

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/* State machine constants*/

/* Other constants*/

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

#define DEST_CONSOLE    (1)
#define DEST_STRING     (2)

#define FLAGS_MINUS     (0x01)
#define FLAGS_PLUS      (0x02)
#define FLAGS_SPACE     (0x04)
#define FLAGS_ZERO      (0x08)
#define FLAGS_POUND     (0x10)

#define IS_FLAG_MINUS(a)    (a & FLAGS_MINUS)
#define IS_FLAG_PLUS(a)     (a & FLAGS_PLUS)
#define IS_FLAG_SPACE(a)    (a & FLAGS_SPACE)
#define IS_FLAG_ZERO(a)     (a & FLAGS_ZERO)
#define IS_FLAG_POUND(a)    (a & FLAGS_POUND)

#define LENMOD_h        (0x01)
#define LENMOD_l        (0x02)
#define LENMOD_L        (0x04)

#define IS_LENMOD_h(a)  (a & LENMOD_h)
#define IS_LENMOD_l(a)  (a & LENMOD_l)
#define IS_LENMOD_L(a)  (a & LENMOD_L)

#define FMT_d   (0x0001)
#define FMT_o   (0x0002)
#define FMT_x   (0x0004)
#define FMT_X   (0x0008)
#define FMT_u   (0x0010)
#define FMT_c   (0x0020)
#define FMT_s   (0x0040)
#define FMT_p   (0x0080)
#define FMT_n   (0x0100)

#define IS_FMT_d(a)     (a & FMT_d)
#define IS_FMT_o(a)     (a & FMT_o)
#define IS_FMT_x(a)     (a & FMT_x)
#define IS_FMT_X(a)     (a & FMT_X)
#define IS_FMT_u(a)     (a & FMT_u)
#define IS_FMT_c(a)     (a & FMT_c)
#define IS_FMT_s(a)     (a & FMT_s)
#define IS_FMT_p(a)     (a & FMT_p)
#define IS_FMT_n(a)     (a & FMT_n)




/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
typedef struct
{
    int   dest;
    void  (*func)(char);
    char  *loc;
} PRINTK_INFO;

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/


/* Console support specific functions */
void uart_console_init(void);
char sci_a_getchar(void);
void sci_a_putchar(char ch);
int  sci_a_getchar_present(void);
void sci_wait_tx(void);

static void printk_putc (int c, int *count, PRINTK_INFO *info);
static int  printk_mknumstr (char *numstr, void *nump, int neg, int radix);
static void printk_pad_zero (int curlen, int field_width, int *count, PRINTK_INFO *info);
static void printk_pad_space (int curlen, int field_width, int *count, PRINTK_INFO *info);
int         printk (PRINTK_INFO *info, const char *fmt, va_list ap);
int         my_printf (const char *fmt, ...);
int         my_sprintf (char *s, const char *fmt, ...);


#define out_char sci_a_putchar
#define in_char sci_a_getchar
#define CONSOLE_MESSAGE my_printf
#define CONSOLE_FLUSH sci_wait_tx


#ifdef __cplusplus
}
#endif

#endif /* SAMPLE_APP_MCAL_UART_CONSOLE_H */

