#define OSTRG_C
/******************************************************************************
*
*   Freescale(TM) and the Freescale logo are trademarks of Freescale Semiconductor, Inc. 
*   All other product or service names are the property of their respective owners. 
*   (C) Freescale Semiconductor, Inc. 2006-2010
*
*   THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
*   BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
*   Freescale Semiconductor, Inc.
*
* Filename:     $Source: /u/OSEK/src/autosar/src/osmpc56xxAMv3/ssc/src/ostrg.c,v $
* Author:       $Author: b00355 $
* Revision:     $Revision: 1.5 $
*
* Functions:    
*
* History:      Use the CVS command rlog to display revision history
*               information.
*
* Description:  OS/MPC target-specific functions
*
* Notes:        1.  This file should be preprocessed with osprop.h
*                   and ostarget.h.
*
******************************************************************************/

#define OS_INTERNAL 1
#include    <os.h>
#undef OS_INTERNAL

#define OSTEXT_START_SEC_CODE
#include "ossections.h"
#define OS_START_SEC_VAR_UNSPECIFIED
#include "ossections.h"
#define OS_START_ONCE_SEC_VAR_FAST_UNSPECIFIED
#include "ossections.h"
#define OS_START_SEC_CONST_UNSPECIFIED
#include "ossections.h"

#ifndef _lint

#if defined(OSGHSPPC)
OSASM("    .section    \".ostext\", \"vax\" ");
OSASM("    .vle                             ");
#endif

#if defined(OSCWPPC)
#pragma require_prototypes off   /* to suppress redundant warnings for asm functions */
extern char _f_ostext[];
extern char _e_ostext[];
#if defined(OSMEMPROTECTION)
extern  void  OSTLBException( OSDWORD srr0, OSDWORD srr1 );
#endif
extern  void  OSExceptionError( OSDWORD srr0, OSDWORD srr1 );
#endif

#define OSEXCEPTIONTOS (OsExceptionStack+(OSEXCEPTIONSTACKSIZE-OSSTKADDS)*4) /* TOS for exception handlers */

#if (defined(OSE200Z0) && !defined(OSMPC5660)) || defined(OSE200Z1) || defined(OSE200Z3) || defined(OSE200Z4)
/******************************************************************************
 * Function: OSInterruptDispatcher
 *
 * Description: wrapper for OSInterruptDispatcher1
 *
 * Returns:
 *
 * Notes: CPU context saving and loading
 *
 ******************************************************************************/
#if defined(OSCWPPC)

extern  void  OSInterruptDispatcher1( void );

OSASM void OSInterruptDispatcher( void ) 
{
    nofralloc
#else    
    OSASMF(     .globl OSInterruptDispatcher );
    OSASMF( OSInterruptDispatcher:           );
#endif /* defined(OSCWPPC) */  
    
    OSASMF2(    e_stwu      r1,-0x50(r1)     ); /* prepare frame and 8 additional bytes for EABI */

#if defined(OSDIABPPC) || defined(OSGHSPPC)    
    OSASMF4(    .byte 0x18, 0x01, 0x11, 0x0C ); /* e_stmvgprw  0xC(r1): save R0, R3-R12 */         
    OSASMF4(    .byte 0x18, 0x21, 0x11, 0x38 ); /* e_stmvsprw  0x38(r1): save CR, LR, CTR, XER */
    OSASMF4(    .byte 0x18, 0x81, 0x11, 0x48 ); /* e_stmvsrrw  0x48(r1): save SRR0, SRR1 */ 
#elif defined(OSCWPPC)  
    OSASMF(     opword  0x1801110C ); /* e_stmvgprw  0xC(r1): save R0, R3-R12 */         
    OSASMF(     opword  0x18211138 ); /* e_stmvsprw  0x38(r1): save CR, LR, CTR, XER */
    OSASMF(     opword  0x18811148 ); /* e_stmvsrrw  0x48(r1): save SRR0, SRR1 */     
#endif /* defined(OSDIABPPC) || defined(OSGHSPPC) */

    OSASMF(     e_bl    OSInterruptDispatcher1 );

#if defined(OSDIABPPC) || defined(OSGHSPPC)     
    OSASMF4(    .byte 0x18, 0x81, 0x10, 0x48 ); /* e_lmvsrrw   0x48(r1): load SRR0, SRR1 */   
    OSASMF4(    .byte 0x18, 0x21, 0x10, 0x38 ); /* e_lmvsprw   0x38(r1): load CR, LR, CTR, XER */
    OSASMF4(    .byte 0x18, 0x01, 0x10, 0x0C ); /* e_ldmvgprw  0xC(r1): load R0, R3-R12 */ 
#elif defined(OSCWPPC)
    OSASMF(     opword  0x18811048 ); /* e_lmvsrrw   0x48(r1): load SRR0, SRR1 */   
    OSASMF(     opword  0x18211038 ); /* e_lmvsprw   0x38(r1): load CR, LR, CTR, XER */
    OSASMF(     opword  0x1801100C ); /* e_ldmvgprw  0xC(r1): load R0, R3-R12 */ 
#endif /* defined(OSDIABPPC) || defined(OSGHSPPC) */

    OSASMF3(    e_addi      r1,r1,0x50       );
    OSASMF(     se_rfi                       );

#if defined(OSCWPPC)
}
#endif
#endif /* defined(OSMPC5510) || defined(OSE200Z0) || defined(OSE200Z4)... */

#if defined(OSNOFASTTERMINATE)
/******************************************************************************
* Function:    OSSetJmp
*
* Description: Save current execution environment into buffer
*
* Input:       r3  - pointer to environment buffer
*
* Return:      always 0 
*
* Notes:       The following registers are saved:
*              LR (return address), r1, CTR, r14 - r31
*
******************************************************************************/
#if defined(OSCWPPC)
#if defined(OSUSETCB)
OSASM OSSIGNEDDWORD OSSetJmp( OSJMP_BUF )  /**** check if proper ret.type and parameter can be put in here ****/
#else  /* OSUSETCB */
OSASM OSSIGNEDDWORD OSSetJmp( OSWORD )  /**** check if proper ret.type and parameter can be put in here ****/
#endif /* OSUSETCB */
{
	nofralloc
#endif /* defined(OSCWPPC) */
#if defined(OSDIABPPC) || defined(OSGHSPPC)    
    OSASMF(     .globl OSSetJmp      );
    OSASMF( OSSetJmp:                );
#endif /* defined(OSDIABPPC) || defined(OSGHSPPC) */    

    OSASMF(     se_mflr    r4        );
    OSASMF2(    se_stw     r1,0(r3)  );
    OSASMF2(    e_stwu     r4,4(r3)  );
    OSASMF(     mfctr      r4        );
    OSASMF2(    e_stwu     r4,4(r3)  );
    OSASMF2(    e_stmw     r14,4(r3) ); /* save r14 .. r31 */
    OSASMF2(    se_li      r3,0      );
    OSASMF(     se_blr               );
#if defined(OSCWPPC)
}
#endif /* defined(OSCWPPC) */
/******************************************************************************
* Function:    OSLongJmp
*
* Description: Restore execution environment from buffer
*
* Input:       r3  - pointer to environment buffer
*
* Return:      always 1 
*
* Notes:       The following registers are restored:
*              LR (return address), r1, CTR, r14 - r31
*
******************************************************************************/
#if defined(OSCWPPC)
#if defined(OSUSETCB)
OSASM OSSIGNEDDWORD OSLongJmp( OSJMP_BUF )
#else  /* OSUSETCB */
OSASM OSSIGNEDDWORD OSLongJmp( OSWORD )
#endif /* OSUSETCB */
{
    nofralloc
#else
    OSASMF(     .globl OSLongJmp      );
    OSASMF( OSLongJmp:                );
#endif /* defined(OSCWPPC) */
    OSASMF2(    se_lwz      r1,0(r3)  );
    OSASMF2(    e_lwzu      r5,4(r3)  );
    OSASMF(     se_mtlr     r5        );
    OSASMF2(    e_lwzu      r5,4(r3)  );
    OSASMF(     se_mtctr    r5        );
    OSASMF2(    e_lmw       r14,4(r3) ); /* restore r14 .. r31 */
    OSASMF2(    se_li       r3,1      );
    OSASMF(     se_blr                );
#if defined(OSCWPPC)
}
#endif  /* defined(OSCWPPC) */

#endif /* defined(OSNOFASTTERMINATE) */

#if defined(OSMEMPROTECTION)
#if defined(OSCWPPC)
extern ;
OSASM OSDWORD OSSystemCall0( OSDWORD ServiceId )
{
    nofralloc
#else
    OSASMF(     .globl OSSystemCall0 );
    OSASMF( OSSystemCall0:           );
#endif /* defined(OSCWPPC) */
    OSASMF2(    se_mr    r6,r3       );
    OSASMF(     se_sc                );
    OSASMF(     se_blr               );
#if defined(OSCWPPC)
}
#endif /* defined(OSCWPPC) */

#if defined(OSCWPPC)
OSASM OSDWORD OSSystemCall1( OSDWORD a, OSDWORD ServiceId )
{
    nofralloc
#else
    OSASMF(     .globl OSSystemCall1 );
    OSASMF( OSSystemCall1:           );
#endif /* defined(OSCWPPC) */
    OSASMF2(    se_mr    r6,r4       );
    OSASMF(     se_sc );
    OSASMF(     se_blr );
#if defined(OSCWPPC)
}
#endif /* defined(OSCWPPC) */

#if defined(OSCWPPC)
OSASM OSDWORD OSSystemCall2( OSDWORD a, OSDWORD b, OSDWORD ServiceId )
{
    nofralloc
#else
    OSASMF(     .globl OSSystemCall2 );
    OSASMF( OSSystemCall2:           );
#endif /* defined(OSCWPPC) */
    OSASMF2(    se_mr    r6,r5       );
    OSASMF(     se_sc                );
    OSASMF(     se_blr               );
#if defined(OSCWPPC)
}
#endif /* defined(OSCWPPC) */

#if defined(OSCWPPC)
OSASM OSDWORD OSSystemCall3( OSDWORD a, OSDWORD b, OSDWORD c, OSDWORD ServiceId )
{
    nofralloc
#else
    OSASMF(     .globl OSSystemCall3 );
    OSASMF( OSSystemCall3:           );
#endif /* defined(OSCWPPC) */
    OSASMF(     se_sc                );
    OSASMF(     se_blr               );
#if defined(OSCWPPC)
}
#endif

/******************************************************************************
 * Function:    Service dispatcher
 *
 * Description: Handles system calls (sc)
 *
 * Returns:     R3 - return value
 *
 * Notes:       R3, R4, R5 - arguments of service function
 *              R6, - number of service function
 *
 ******************************************************************************/
#if defined(OSCWPPC)
OSASM void OSServiceDispatcher( void )
{                        
    nofralloc
#else
    OSASMF(     .globl OSServiceDispatcher           );
    OSASMF( OSServiceDispatcher:                     );
#endif /* defined(OSCWPPC) */

    OSASMF2(    e_lis       r7,OsLastServiceId@ha    );
    OSASMF2(    e_lbz       r7,OsLastServiceId@l(r7) );
    OSASMF2(    se_cmpl     r6,r7 );
    OSASMF(     se_bgt      OSServiceDispatcherExit  );

    OSASMF2(    e_stwu      r1,-24(r1)               ); /* 16 bytes to save SP, SRR0, SRR1, LR, and 8 reserved bytes */
    OSASMF(     mfsrr0      r7                       );
    OSASMF2(    se_stw      r7,12(r1)                ); /* save SRR0 */
    OSASMF(     mflr        r7                       );
    OSASMF2(    se_stw      r7,20(r1)                ); /* save LR */
    OSASMF(     mfsrr1      r7                       );
    OSASMF2(    se_stw      r7,16(r1)                ); /* save SRR1 */
                               
           /* enable interrupts if they were enabled */
    OSASMF(     mfmsr       r0                       );
    OSASMF5(    e_rlwinm    r7,r7,0,16,16            ); /* R7 &= 0x00008000 */
    OSASMF2(    se_or       r0,r7                    ); /* R0 |= R7 */
    OSASMF(     msync                                );
    OSASMF(     mtmsr       r0                       );

    OSASMF2(    e_lis       r7,OsServices@ha         );
    OSASMF3(    e_add16i    r7,r7,OsServices@l       );
                                                    /* R6 - index in OsServices table */
    OSASMF2(    se_slwi     r6,2                     ); /* R6 = R6 << 2 */
    OSASMF2(    se_add      r7,r6                    ); /* R7 = R7 + R6 */
    OSASMF2(    e_lwz       r7,0(r7)                 );
    OSASMF(     mtctr       r7                       );
    OSASMF(     se_bctrl                             );

    OSASMF2(    se_lwz      r6,16(r1)                ); /* load SRR1 from stack frame */
    OSASMF(     mfmsr       r7                       ); /* copy MSR to R7 */
    OSASMF2(    se_bclri    r6,16                    ); /* R6 &= 0xFFFF7FFF */
    OSASMF5(    e_rlwinm    r7,r7,0,16,16            ); /* R7 &= 0x00008000 */
    OSASMF2(    se_or       r6,r7                    ); /* R6 |= R7 */
                              
    OSASMF(     wrteei      0                        ); /* disable all interrupts, MSR[EE] = 0 */

    OSASMF2(    se_lwz      r7,20(r1)                ); /* load LR */
    OSASMF(     mtlr        r7                       );
    OSASMF2(    se_lwz      r7,12(r1)                ); /* load SRR0 */
    OSASMF(     mtsrr0      r7                       );
    OSASMF(     mtsrr1      r6                       ); /* load SRR1 */
    OSASMF3(    e_add16i    r1,r1,24                 );

    OSASMF( OSServiceDispatcherExit: );

    OSASMF(     se_rfi                               );
#if defined(OSCWPPC)
}
#endif /* defined(OSCWPPC) */
#endif /* defined(OSMEMPROTECTION) */

/******************************************************************************
 * Function:    OSCriticalException
 *
 * Description: Handles critical exception
 *
 * Returns:     
 *
 * Notes:       the processor uses CSRR0/CSRR1
 *
 ******************************************************************************/
#if defined(OSCWPPC)
OSASM void OSCriticalException( void )
{                        
    nofralloc
#else
    OSASMF(     .globl OSCriticalException         );
    OSASMF( OSCriticalException:                   );
#endif /* defined(OSCWPPC) */
#if defined(OSMEMPROTECTION)
           /* switch stack to exception stack and call OSExceptionError() */
    OSASMF2(    e_lis      r1,OSEXCEPTIONTOS@ha   );
    OSASMF3(    e_add16i   r1,r1,OSEXCEPTIONTOS@l );    
#endif
    OSASMF(     mfcsrr0    r3                      );
    OSASMF(     mfcsrr1    r4                      );
    OSASMF(     e_b        OSExceptionError        );
           /* This point is not reachable */
    OSASMF( OSCriticalExceptionEnd:                );
    OSASMF(     se_b       OSCriticalExceptionEnd  );
#if defined(OSCWPPC)
}
#endif /* defined(OSCWPPC) */

#if defined(OSE200Z4) || defined(OSE200Z7)
/******************************************************************************
 * Function:    OSMachineCheckException
 *
 * Description: Handles machine check exception
 *
 * Returns:     
 *
 * Notes:       the processor uses MCSRR0/MCSRR1
 *
 ******************************************************************************/
#if defined(OSCWPPC)
OSASM void OSMachineCheckException( void )
{                        
    nofralloc
#else
    OSASMF(     .globl OSMachineCheckException     );
    OSASMF( OSMachineCheckException:               );
#endif /* defined(OSCWPPC) */
#if defined(OSMEMPROTECTION)
           /* switch stack to exception stack and call OSExceptionError() */
    OSASMF2(    e_lis      r1,OSEXCEPTIONTOS@ha   );
    OSASMF3(    e_add16i   r1,r1,OSEXCEPTIONTOS@l );    
#endif
    OSASMF(     mfmcsrr0   r3                      );
    OSASMF(     mfmcsrr1   r4                      );
    OSASMF(     e_b        OSExceptionError        );
           /* This point is not reachable */
    OSASMF( OSMachineCheckExceptionEnd:            );
    OSASMF(     se_b       OSMachineCheckExceptionEnd );
#if defined(OSCWPPC)
}
#endif /* defined(OSCWPPC) */
#endif /* defined(OSE200Z4) || defined(OSE200Z7) */

/******************************************************************************
 * Function:    OSNonCriticalException
 *
 * Description: Handles non-critical exception
 *
 * Returns:     
 *
 * Notes:       the processor uses SRR0/SRR1
 *
 ******************************************************************************/
#if defined(OSCWPPC)
OSASM void OSNonCriticalException( void )
{                        
    nofralloc
#else
    OSASMF(     .globl OSNonCriticalException     );
    OSASMF( OSNonCriticalException:               );
#endif /* defined(OSCWPPC) */
#if defined(OSMEMPROTECTION)
           /* switch stack to exception stack and call OSExceptionError() */
    OSASMF2(    e_lis      r1,OSEXCEPTIONTOS@ha   );
    OSASMF3(    e_add16i   r1,r1,OSEXCEPTIONTOS@l );    
#endif
    OSASMF(     mfsrr0    r3                      );
    OSASMF(     mfsrr1    r4                      );
    OSASMF(     e_b       OSExceptionError        );
           /* This point is not reachable */
    OSASMF( OSNonCriticalExceptionEnd:            );
    OSASMF(     se_b      OSNonCriticalExceptionEnd );
#if defined(OSCWPPC)
}
#endif /* defined(OSCWPPC) */

/******************************************************************************
 * Function:    OSDebugException
 *
 * Description: Handles debug exception
 *
 * Returns:     never
 *
 ******************************************************************************/
#if defined(OSCWPPC)
OSASM void OSDebugException( void )
{                        
    nofralloc
#else
    OSASMF(     .globl OSDebugException          );
    OSASMF( OSDebugException:                    );
#endif /* defined(OSCWPPC) */
#if defined(OSMEMPROTECTION)
           /* switch stack to exception stack and call OSExceptionError() */
    OSASMF2(    e_lis      r1,OSEXCEPTIONTOS@ha   );
    OSASMF3(    e_add16i   r1,r1,OSEXCEPTIONTOS@l );    
#endif
    OSASMF2(    se_li    r3,21                   ); /* set E_OS_SYS_FATAL */
    OSASMF(     e_b      OSShutdownOS            );
          /* This point is not reachable */
    OSASMF( OSDebugExceptionEnd:                 );
    OSASMF(     se_b     OSDebugExceptionEnd     );
#if defined(OSCWPPC)
}
#endif /* defined(OSCWPPC) */

#if defined(OSMEMPROTECTION)
/******************************************************************************
 * Function:    OSTLBErrorException
 *
 * Description: Handles both code and data TLB exceptions
 *
 * Returns:     
 *
 * Notes:       the processor uses SRR0/SRR1
 *
 ******************************************************************************/
#if defined(OSCWPPC)
OSASM void OSTLBErrorException( void )
{                        
    nofralloc
#else
    OSASMF(     .globl OSTLBErrorException        );
    OSASMF( OSTLBErrorException:                  );
#endif /* defined(OSCWPPC) */
          /* switch stack to exception stack and call OSExceptionError() */
    OSASMF2(    e_lis      r1,OSEXCEPTIONTOS@ha   );
    OSASMF3(    e_add16i   r1,r1,OSEXCEPTIONTOS@l );    
    OSASMF(     mfsrr0    r3                      );
    OSASMF(     mfsrr1    r4                      );
    OSASMF(     e_b       OSTLBException          );
    /* This point is not reachable */
    OSASMF( OSTLBErrorExceptionEnd:               );
    OSASMF(     se_b      OSTLBErrorExceptionEnd  );
#if defined(OSCWPPC)
}
#endif /* defined(OSCWPPC) */

#if (OSNNOTTRUSTEDAPPS > 0)
/****************************************************************************************
 * Function:    OS_OS2SysMode
 *
 * Description: Returns from ServiceDispatcher always in superviser mode,
 *              call is allowed only from OS code
 *
 * Returns:     never
 *
 * Note:        it is reduced second part of ServiceDispacher
 *
 ****************************************************************************************/
#if defined(OSCWPPC)
OSASM void OS_OS2SysMode( void )
{                        
    nofralloc
#else
    OSASMF(     .globl OS_OS2SysMode                  );
    OSASMF( OS_OS2SysMode:                            );
#endif /* defined(OSCWPPC) */

    OSASMF2(    se_lwz      r6,20(r1)                 ); /* load call address */
#if defined(OSCWPPC)
    OSASMF2(    e_lis       r7, _f_ostext@ha          );
    OSASMF3(    e_add16i    r7, r7, _f_ostext@l       );
#endif
#if defined(OSDIABPPC)
    OSASMF2(    e_lis       r7,_f_ostext@ha           );
    OSASMF3(    e_add16i    r7,r7,_f_ostext@l         );
#endif
#if defined(OSGHSPPC)
    OSASMF2(    e_lis       r7,__ghsbegin_ostext@ha   );
    OSASMF3(    e_add16i    r7,r7,__ghsbegin_ostext@l );
#endif
    OSASMF2(    se_cmpl     r6,r7                     );
    OSASMF(     se_ble      OS2SysModeExit            );

#if defined(OSCWPPC)
    OSASMF2(    e_lis       r7, _e_ostext@ha           );
    OSASMF3(    e_add16i    r7, r7, _e_ostext@l        );
#endif
#if defined(OSDIABPPC)
    OSASMF2(    e_lis       r7,_e_ostext@ha           );
    OSASMF3(    e_add16i    r7,r7, _e_ostext@l        );
#endif
#if defined(OSGHSPPC)
    OSASMF2(    e_lis       r7,__ghsend_ostext@ha     );
    OSASMF3(    e_add16i    r7,r7,__ghsend_ostext@l   );
#endif
    OSASMF2(    se_cmpl     r6,r7                     );
    OSASMF(     se_bge      OS2SysModeExit            );

    OSASMF(     wrteei      0                         ); /* disable all interrupts, MSR[EE] = 0 */
    OSASMF2(    se_lwz      r7,12(r1)                 ); /* load SRR0 */
    OSASMF(     mtsrr0      r7                        );
    OSASMF(     mtlr        r6                        ); /* restore LR */
    OSASMF3(    e_add16i    r1,r1,24                  );
    OSASMF(     mfsrr1      r7                        );   
    OSASMF2(    se_bclri    r7,17                     ); /* clear 'pr' bit  in SRR1  */
    OSASMF(     mtsrr1      r7                        );

    OSASMF( OS2SysModeExit:                           );
    OSASMF(     se_rfi                                );
#if defined(OSCWPPC)
}
#endif /* defined(OSCWPPC) */

#endif /* (OSNNOTTRUSTEDAPPS > 0) */
#endif /* defined(OSMEMPROTECTION) */

#if defined(OSDECISR) || defined(OSTIMDEC) || defined(OSTIM2DEC) || defined(OSTPTIMDEC)
/***************************************************************************
 * Function:    OSDECisr
 *
 * Description: redirects interrupt request to INTC 
 *
 * Notes:       
 *
 **************************************************************************/
#if defined(OSCWPPC)
OSASM void OSDECisr( void )
{                        
    nofralloc
#else
    OSASMF(     .globl OSDECisr                     );
    OSASMF( OSDECisr:                               );
#endif /* defined(OSCWPPC) */

    OSASMF2(    e_stwu      r1,-0x8(r1)             ); /* 8 bytes to save R0,R3  */
    OSASMF2(    se_stw      r0,0x0(r1)              ); /* save R0 */
    OSASMF2(    se_stw      r3,0x4(r1)              ); /* save R3 */

    OSASMF2(    e_lis       r3,0x800                ); /* OSTSR_DIS (0x8000000) -> TSR */
    OSASMF2(    mtspr       0x150,r3                );


    OSASMF2(    se_li       r0,0x2                  );/* OSDECSOFTINVOKE -> r0 */
    OSASMF2(    e_lis       r3,0xfff5               ); /* OSINTC_BASE_ADDR = 0xfff48000 for MCU5510, MCU5560 and MCU5633 */
    OSASMF2(    e_stw       r0,-0x7fdc(r3)          );  /* OSDECSOFTINVOKE -> (OSINTC_BASE_ADDR+0x24) */

    OSASMF2(    se_lwz      r3,0x4(r1)              );
    OSASMF2(    se_lwz      r0,0x0(r1)              );
    OSASMF2(    se_addi     r1,0x8                  );

    OSASMF(     se_rfi                              );
#if defined(OSCWPPC)
}
#endif
#endif /* defined(OSDECISR) || defined(OSTIMDEC) || defined(OSTIM2DEC) || defined(OSTP_TIMDEC) */

#if defined(OSFITISR)  || defined(OSTIMFIT)  || defined(OSTIM2FIT)
/***************************************************************************
 * Function:    OSFITisr
 *
 * Description: redirects interrupt request to INTC
 *
 * Notes:       
 *
 **************************************************************************/
#if defined(OSCWPPC)
OSASM void OSFITisr( void )
{                        
    nofralloc
#else
    OSASMF(     .globl OSFITisr            );
    OSASMF( OSFITisr:                      );
#endif /* defined(OSCWPPC) */

    OSASMF2(    e_stwu      r1,-0x8(r1)    ); /* 8 bytes to save R0,R3  */
    OSASMF2(    se_stw      r0,0x0(r1)     ); /* save R0 */
    OSASMF2(    se_stw      r3,0x4(r1)     ); /* save R3 */

    OSASMF2(    e_lis       r3,0x400       ); /* OSTSR_FIS (0x8000000) -> RTS */
    OSASMF2(    mtspr       0x150,r3       );       

    OSASMF2(    se_bgeni    r0,0x16        ); /* OSFITSOFTINVOKE (0x200) -> r0 */
    OSASMF2(    e_lis       r3,0xfff5      ); /* OSINTC_BASE_ADDR = 0xfff48000 for MCU5510, MCU5560 and MCU5633 */
    OSASMF2(    e_stw       r0,-0x7fdc(r3) ); /* OSFITSOFTINVOKE -> (OSINTC_BASE_ADDR+0x24) */

    OSASMF2(    se_lwz      r3,0x4(r1)     );
    OSASMF2(    se_lwz      r0,0x0(r1)     );
    OSASMF2(    se_addi     r1,0x8         );

    OSASMF(     se_rfi                     );
#if defined(OSCWPPC)
}
#endif

#endif /* defined(OSFITISR)  || defined(OSTIMFIT)  || defined(OSTIM2FIT) */

#endif  /*  ifndef _lint  */
