/**
    @file        sample_app_mcal_uart_console.c
    @version     2.0.0

    @brief       AUTOSAR - Autosar  Sample Application.
    @details     The standard C library routine printf() over serial , but without all the garbage

    Project      : AUTOSAR 3.0 MCAL
    Platform     : PA
    Peripheral   : 
    Dependencies : Base Det Dem Port Dio Mcu SchM Wdg WdgIf CanIf LinIf EcuM

    Autosar Version       : 1.9.0
    Autosar Revision      : ASR_REL_1_9_REV_0003
    Autosar Conf. Variant :
    Software Version      : 2.0.0
    Build Version         : MPC563xMxM_MCAL_2_0_0_RTM_ASR_REL_1_9_REV_0003_20110214

    (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
    All Rights Reserved.

    You can use this example for any purpose on any computer system with the following restrictions:
    1. This example is provided "as is", without warranty.
    2. You do not remove this copyright notice from this example or any direct derivation thereof.

*/
/*==================================================================================================
==================================================================================================*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/

#include "sample_app_mcal_uart_console.h"
#include "Reg_Macros.h"
#include "Reg_eSys.h"
#include "Reg_eSys_ESCI.h"
#include "Mcal.h"

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

#define ESCI_PORT       0U
/* ESCI IPG Clock in Hz */
#define ESCI_IPG_CLK        60000000UL
/* ESCI Baudrate */
#define ESCI_BAUDRATE   115200UL
/* Calculate SBR value by the formula */
#define ESCI_SBR        ((ESCI_IPG_CLK / 16UL ) / ESCI_BAUDRATE)

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/


/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/

#define TX_BUF_SIZE     0x200U
#define TX_ON           0x1U
#define TX_OFF          0x0U
/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/


/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/**
@brief This is the TX buffer used as a FIFO
*/
STATIC char uart_tx_buf[TX_BUF_SIZE] = {0};
/**
@brief head index points to the location from the uart_tx_buf for the next char to send
*/
STATIC volatile uint16_t head = 0U;
/**
@brief tail index points to the location from the uart_tx_buf for the next char to put in the buffer
*/
STATIC volatile uint16_t tail = 0U;
/**
@brief Represents the state of the UART. TX_ON if the UART is busy, TX_OFF if the UART is idle
*/
STATIC volatile uint8_t tx_state = TX_OFF;


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/
ISR(ESCI_SCI_Isr_UART_TX);

/********************************************************************/
static void printk_putc (int c, int *count, PRINTK_INFO *info)
{
    switch (info->dest)
    {
        case DEST_CONSOLE:
            info->func((char)c);
            break;

        case DEST_STRING:
            *(info->loc) = (unsigned char)c;
            ++(info->loc);
            break;

        default:
            break;
    }

    *count += 1;
}


/********************************************************************/
static int printk_mknumstr (char *numstr, void *nump, int neg, int radix)
{
    int a,b,c;
    unsigned int ua,ub,uc;

    int nlen;
    char *nstrp;

    nlen = 0;
    nstrp = numstr;
    *nstrp++ = '\0';

    if (neg)
    {
        a = *(int *)nump;
        if (a == 0)
        {
            *nstrp = '0';
            ++nlen;
            goto done;
        }

        while (a != 0)
        {
            b = (int)a / (int)radix;
            c = (int)a - ((int)b * (int)radix);

            if (c < 0)
            {
                c = ~c + 1 + '0';
            }
            else
            {
                c = c + '0';
            }

            a = b;
            *nstrp++ = (char)c;
            ++nlen;
        }
    }
    else
    {
        ua = *(unsigned int *)nump;

        if (ua == 0)
        {
            *nstrp = '0';
            ++nlen;
            goto done;
        }

        while (ua != 0)
        {
            ub = (unsigned int)ua / (unsigned int)radix;
            uc = (unsigned int)ua - ((unsigned int)ub * (unsigned int)radix);

            if (uc < 10)
            {
                uc = uc + '0';
            }
            else
            {
                uc = uc - 10 + 'A';
            }

            ua = ub;
            *nstrp++ = (char)uc;
            ++nlen;
        }
    }

    done:
    return nlen;
}

/********************************************************************/

static int printk_strlen(char *s)
{
    char *p=s;

    while (*p!='\0')
        p++;

    return(p-s);
}

/********************************************************************/
static void printk_pad_zero (int curlen, int field_width, int *count, PRINTK_INFO *info)
{
    int i;

    for (i = curlen; i < field_width; i++)
    {
        printk_putc('0',count, info);
    }
}


/********************************************************************/
static void printk_pad_space (int curlen, int field_width, int *count, PRINTK_INFO *info)
{
    int i;

    for (i = curlen; i < field_width; i++)
    {
        printk_putc(' ',count, info);
    }
}


/********************************************************************/
int printk (PRINTK_INFO *info, const char *fmt, va_list ap)
{
    char *p;
    int c;

    char vstr[33];
    char *vstrp;
    int vlen;

    int done;
    int count = 0;

    int flags_used;
    int field_width;
#if 0
    int precision_used;
    int precision_width;
    int length_modifier;
#endif

    int ival;
    int schar, dschar;
    int *ivalp;
    char *sval;
    int cval;
    unsigned int uval;

    /*
     * Start parsing apart the format string and display appropriate
     * formats and data.
     */
    for (p = (char *)fmt; (c = *p); p++)
    {
        /*
         * All formats begin with a '%' marker.  Special chars like
         * '\n' or '\t' are normally converted to the appropriate
         * character by the __compiler__.  Thus, no need for this
         * routine to account for the '\' character.
         */
        if (c != '%')
        {
            /*
             * This needs to be replaced with something like
             * 'out_char()' or call an OS routine.
             */
#ifndef UNIX_DEBUG
            if (c != '\n')
            {
                printk_putc(c, &count, info);
            }
            else
            {
                printk_putc(0x0D /* CR */, &count, info);
                printk_putc(0x0A /* LF */, &count, info);
            }
#else
            printk_putc(c, &count, info);
#endif

            /*
             * By using 'continue', the next iteration of the loop
             * is used, skipping the code that follows.
             */
            continue;
        }

        /*
         * First check for specification modifier flags.
         */
        flags_used = 0;
        done = FALSE;
        while (!done)
        {
            switch (/* c = */ *++p)
            {
                case '-':
                    flags_used |= FLAGS_MINUS;
                    break;

                case '+':
                    flags_used |= FLAGS_PLUS;
                    break;

                case ' ':
                    flags_used |= FLAGS_SPACE;
                    break;

                case '0':
                    flags_used |= FLAGS_ZERO;
                    break;

                case '#':
                    flags_used |= FLAGS_POUND;
                    break;

                default:
                    /* we've gone one char too far */
                    --p;
                    done = TRUE;
                    break;
            }
        }

        /*
         * Next check for minimum field width.
         */
        field_width = 0;
        done = FALSE;
        while (!done)
        {
            switch (c = *++p)
            {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    field_width = (field_width * 10) + (c - '0');
                    break;
                default:
                    /* we've gone one char too far */
                    --p;
                    done = TRUE;
                    break;
            }
        }

        /*
         * Next check for the width and precision field separator.
         */
        if (/* (c = *++p) */ *++p == '.')
        {
            /* precision_used = TRUE; */

            /*
             * Must get precision field width, if present.
             */
            /* precision_width = 0; */
            done = FALSE;
            while (!done)
            {
                switch (/* c = uncomment if used below */ *++p)
                {
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
#if 0
                        precision_width = (precision_width * 10) +
                        (c - '0');
#endif
                        break;
                    default:
                        /* we've gone one char too far */
                        --p;
                        done = TRUE;
                        break;
                }
            }
        }
        else
        {
            /* we've gone one char too far */
            --p;
#if 0
            precision_used = FALSE;
            precision_width = 0;
#endif
        }

        /*
         * Check for the length modifier.
         */
        /* length_modifier = 0; */
        switch (/* c = */ *++p)
        {
            case 'h':
                /* length_modifier |= LENMOD_h; */
                break;
            case 'l':
                /* length_modifier |= LENMOD_l; */
                break;
            case 'L':
                /* length_modifier |= LENMOD_L; */
                break;
            default:
                /* we've gone one char too far */
                --p;
                break;
        }

        /*
         * Now we're ready to examine the format.
         */
        switch (c = *++p)
        {
            case 'd':
            case 'i':
                ival = (int)va_arg(ap, int);
                vlen = printk_mknumstr(vstr,&ival,TRUE,10);
                vstrp = &vstr[vlen];

                if (ival < 0)
                {
                    schar = '-';
                    ++vlen;
                }
                else
                {
                    if (IS_FLAG_PLUS(flags_used))
                    {
                        schar = '+';
                        ++vlen;
                    }
                    else
                    {
                        if (IS_FLAG_SPACE(flags_used))
                        {
                            schar = ' ';
                            ++vlen;
                        }
                        else
                        {
                            schar = 0;
                        }
                    }
                }
                dschar = FALSE;

                /*
                 * do the ZERO pad.
                 */
                if (IS_FLAG_ZERO(flags_used))
                {
                    if (schar)
                        printk_putc(schar, &count, info);
                    dschar = TRUE;

                    printk_pad_zero (vlen, field_width, &count, info);
                    vlen = field_width;
                }
                else
                {
                    if (!IS_FLAG_MINUS(flags_used))
                    {
                        printk_pad_space (vlen, field_width, &count, info);

                        if (schar)
                            printk_putc(schar, &count, info);
                        dschar = TRUE;
                    }
                }

                /* the string was built in reverse order, now display in */
                /* correct order */
                if (!dschar && schar)
                {
                    printk_putc(schar, &count, info);
                }
                goto cont_xd;

            case 'x':
            case 'X':
                uval = (unsigned int)va_arg(ap, unsigned int);
                vlen = printk_mknumstr(vstr,&uval,FALSE,16);
                vstrp = &vstr[vlen];

                dschar = FALSE;
                if (IS_FLAG_ZERO(flags_used))
                {
                    if (IS_FLAG_POUND(flags_used))
                    {
                        printk_putc('0', &count, info);
                        printk_putc('x', &count, info);
                        dschar = TRUE;
                    }
                    printk_pad_zero (vlen, field_width, &count, info);
                    vlen = field_width;
                }
                else
                {
                    if (!IS_FLAG_MINUS(flags_used))
                    {
                        if (IS_FLAG_POUND(flags_used))
                        {
                            vlen += 2;
                        }
                        printk_pad_space (vlen, field_width, &count, info);
                        if (IS_FLAG_POUND(flags_used))
                        {
                            printk_putc('0', &count, info);
                            printk_putc('x', &count, info);
                            dschar = TRUE;
                        }
                    }
                }

                if ((IS_FLAG_POUND(flags_used)) && !dschar)
                {
                    printk_putc('0', &count, info);
                    printk_putc('x', &count, info);
                    vlen += 2;
                }
                goto cont_xd;

            case 'o':
                uval = (unsigned int)va_arg(ap, unsigned int);
                vlen = printk_mknumstr(vstr,&uval,FALSE,8);
                goto cont_u;
            case 'b':
                uval = (unsigned int)va_arg(ap, unsigned int);
                vlen = printk_mknumstr(vstr,&uval,FALSE,2);
                goto cont_u;
            case 'p':
                uval = (unsigned int)va_arg(ap, void *);
                vlen = printk_mknumstr(vstr,&uval,FALSE,16);
                goto cont_u;
            case 'u':
                uval = (unsigned int)va_arg(ap, unsigned int);
                vlen = printk_mknumstr(vstr,&uval,FALSE,10);

                cont_u:
                vstrp = &vstr[vlen];

                if (IS_FLAG_ZERO(flags_used))
                {
                    printk_pad_zero (vlen, field_width, &count, info);
                    vlen = field_width;
                }
                else
                {
                    if (!IS_FLAG_MINUS(flags_used))
                    {
                        printk_pad_space (vlen, field_width, &count, info);
                    }
                }

                cont_xd:
                while (*vstrp)
                    printk_putc(*vstrp--, &count, info);

                if (IS_FLAG_MINUS(flags_used))
                {
                    printk_pad_space (vlen, field_width, &count, info);
                }
                break;

            case 'c':
                cval = (char)va_arg(ap, unsigned int);
                printk_putc(cval,&count, info);
                break;

            case 's':
                sval = (char *)va_arg(ap, char *);
                if (sval)
                {

                    /* Create a strlen similar funtion */
                    vlen = printk_strlen(sval);

                    if (!IS_FLAG_MINUS(flags_used))
                    {
                        printk_pad_space (vlen, field_width, &count, info);
                    }
                    while (*sval)
                        printk_putc(*sval++,&count, info);
                    if (IS_FLAG_MINUS(flags_used))
                    {
                        printk_pad_space (vlen, field_width, &count, info);
                    }
                }
                break;
            case 'n':
                ivalp = (int *)va_arg(ap, int *);
                *ivalp = count;
                break;

            default:
                printk_putc(c,&count, info);
                break;
        }
    }
    return count;
}


/********************************************************************/
int my_printf (const char *fmt, ...)
{
    va_list ap;
    int rvalue;
    PRINTK_INFO info;


    info.dest = DEST_CONSOLE;
    info.func = &out_char;
    /*
     * Initialize the pointer to the variable length argument list.
     */
    va_start(ap, fmt);
    rvalue = printk(&info, fmt, ap);
    /*
     * Cleanup the variable length argument list.
     */
    va_end(ap);
    return rvalue;
}

/********************************************************************/
int my_sprintf (char *s, const char *fmt, ...)
{
    va_list ap;
    int rvalue = 0;
    PRINTK_INFO info;

    /*
     * Initialize the pointer to the variable length argument list.
     */
    if (s != 0)
    {
        info.dest = DEST_STRING;
        info.loc = s;
        va_start(ap, fmt);
        rvalue = printk(&info, fmt, ap);
        *info.loc = '\0';
        va_end(ap);
    }

    return rvalue;
}




/*================================================================================================*/
/**
@brief   Setup LINFlex1 for SCI/UART mode for 115200 bps
@details

@return None
@retval None

@pre None
@post None
*/
/*================================================================================================*/
void uart_console_init(void)
{
    tx_state = TX_OFF;

    /* Set SCI mode */
    REG_WRITE16(ESCI_LCR1(ESCI_PORT), 0x0UL);

    /* write Baudrate register */
    REG_WRITE16(ESCI_BRR(ESCI_PORT), ESCI_SBR);
    /* select receiver input mode */
    REG_WRITE16(ESCI_CR3(ESCI_PORT), 0x0UL);
    REG_WRITE16(ESCI_CR2(ESCI_PORT), 0x0UL);
    /* clear transmit complete status flag */
    REG_WRITE16(ESCI_IFSR1(ESCI_PORT), ESCI_IFSR1_TC_MASK);
    /* enable the transmitter and enable Tx complete interrupt */
    REG_WRITE16(ESCI_CR1(ESCI_PORT), ESCI_CR1_TE_MASK | ESCI_CR1_TCIE_MASK);
}

/*================================================================================================*/
/**
@brief   Wait until a character is received on UART and return it
@details

@return The Received char
@retval None

@pre None
@post None
*/
/*================================================================================================*/
char sci_a_getchar (void)
{
    char new_char;

    /* Wait until character has been received */
    /* RMB=1 - buffer ready to be read by software w1c */
    while ( ESCI_IFSR1_RDRF_MASK != (ESCI_IFSR1_RDRF_MASK & REG_READ16(ESCI_IFSR1(ESCI_PORT))) )
    {
        /* wait for a char */
    };

    /* char is present: read it and reset the flags */
    new_char = (char) (REG_READ16(ESCI_SDR(ESCI_PORT)) & 0xFFU);

    /* w1c */
    /* clear RMB and DRF flags */
    REG_WRITE16(ESCI_IFSR1(ESCI_PORT), ESCI_IFSR1_RDRF_MASK);

    return new_char;
}


/*================================================================================================*/
/**
@brief   Send a character on UART. If the tx is busy transmitting then put in the buffer.
@details

@return None
@retval None

@pre None
@post None
*/
/*================================================================================================*/
void sci_a_putchar (char ch)
{

    /* check if uart is  busy */
    if (TX_ON == tx_state)
    {
        /* Disable interrupts */
        SuspendAllInterrupts();

        /* Put a character in the circular buffer */
        /* save the char in to the buffer */
        uart_tx_buf[tail] = ch;
        /* increment the index */

        tail++;
        /* check the tail index from the buffer */
        if (TX_BUF_SIZE <= tail)
        {
            /* adjust if necessary  for overflow */
            if (0 == head)
            {
                tail = TX_BUF_SIZE - 1;
            }
            else
            {
                tail = 0;
            }
        }
        else
        {
            /* buffer full */
            if (head == tail)
            {
                tail--;
            }
        }
        /* Enable interrupts */
        ResumeAllInterrupts();

    }
    else
    {
        /* Send the character */
        tx_state = TX_ON;
        REG_WRITE16(ESCI_SDR(ESCI_PORT), (uint16_t)ch);
    }
}

/*================================================================================================*/
/**
@brief   Check if a char was received in the receive buffer.
@details

@return  - 1 if the char is present in UART buffer and 0 if none
@retval None

@pre None
@post None
*/
/*================================================================================================*/
int sci_a_getchar_present (void)
{
    return (0x0U != (ESCI_IFSR1_RDRF_MASK & REG_READ32(ESCI_IFSR1(ESCI_PORT))));
}

/*================================================================================================*/
/**
@brief   UART Tx ISR Process function.
@details

@return None
@retval None

@pre None
@post None
*/
/*================================================================================================*/
ISR(ESCI_SCI_Isr_UART_TX)
{
    uint32_t reg_temp;

    reg_temp = ESCI_IFSR1(ESCI_PORT);
    if ( ESCI_IFSR1_TC_MASK == (ESCI_IFSR1_TC_MASK & REG_READ16(reg_temp)) )
    {
        /* clear interrupt flag */
        /* w1c */
        REG_WRITE16(reg_temp, ESCI_IFSR1_TC_MASK);

        /* Disable interrupts */
        SuspendAllInterrupts();

        /* check for more chars to send */
        if (0x0U == (tail - head))
        {
            tx_state = TX_OFF;
            head = 0x0U;
            tail = 0x0U;
        }
        else
        {
            /* adjust the head index if necessary */
            if (TX_BUF_SIZE <= head)
            {
                head = 0x0U;
            }
            /* send the next char from buffer */
            REG_WRITE16(ESCI_SDR(ESCI_PORT), (uint16_t)uart_tx_buf[head]);
            /* increment the index */
            head++;
        }
        /* Enable interrupts */
        ResumeAllInterrupts();

    }
    EXIT_INTERRUPT();
}
/*================================================================================================*/

/*================================================================================================*/
/**
@brief   Wait for the uart to send.
@details

@return None
@retval None

@pre None
@post None
*/
/*================================================================================================*/

void sci_wait_tx(void)
{
    while (TX_ON == tx_state)
    {
        /* wait */
    }
}

/*================================================================================================*/
#ifdef __cplusplus
}
#endif
