/**
@file    eMIOS_Pwm_LLD.c
@version 2.0.0

@brief   AUTOSAR Pwm - Pwm implementation using Emios.
@details Pwm implementation using Emios.

Project AUTOSAR 3.0 MCAL
Platform PA
Peripheral eMIOS200
Dependencies none

ARVersion 3.0.0
ARRevision ASR_REL_3_0_REV_0003
ARConfVariant
SWVersion 2.0.0
BuildVersion XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223

(c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
All Rights Reserved.
*/
/*===============================================================================================
===============================================================================================*/


/**
@page misra_violations MISRA-C:2004 violations

@section eMIOS_Pwm_LLD_C_REF_1
Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments
                                        before "#include"
MemMap.h included after each section define in order to set the current memory section

@section eMIOS_Pwm_LLD_C_REF_2
Violates MISRA 2004 Advisory Rule 10.1, Implicit conversion of integer to smaller type

@section eMIOS_Pwm_LLD_C_REF_3
Violates MISRA 2004 Advisory Rule 10.1, Prohibited Implicit Conversion:
                                        Non-constant argument to function

@section eMIOS_Pwm_LLD_C_REF_4
Violates MISRA 2004 Advisory Rule 10.1, Implicit conversion changes signedness

@section eMIOS_Pwm_LLD_C_REF_5
Violates MISRA 2004 Advisory Rule  14.6, more than one 'break' terminates loop

@section eMIOS_Pwm_LLD_C_REF_6
Violates MISRA 2004 Advisory Rule 10.3, Cast of complex integer expression to larger type

@section eMIOS_Pwm_LLD_C_REF_7
Violates MISRA 2004 Advisory Rule 11.1, Cast from unsigned long to pointer

@section eMIOS_Pwm_LLD_C_REF_8
Violates MISRA 2004 Advisory Rule 19.15 Precautions shall be taken in order to prevent the contents of a
header file being included twice.
This is not a violation since all header files are protected against multiple inclusions.

@section eMIOS_Pwm_LLD_C_REF_9
Violates MISRA 2004 Advisory Rule 1.2, 1.4 and 5.1 : Identifier clash
All compiler used to validate the code can make the difference between two symbols

@section eMIOS_Pwm_LLD_C_REF_10
Violates MISRA 2004 Advisory Rule 11.4 : cast from pointer to pointer
To typecast the pointer from one data type to other data type

@section eMIOS_Pwm_LLD_C_REF_11
Violates MISRA 2004 Advisory Rule  17.4 : pointer arithmetic other than array indexing used

*/



#ifdef __cplusplus
extern "C" {
#endif

/*===============================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
===============================================================================================*/

#include "Pwm.h"
#include "eMIOS_Pwm_LLD.h"
/*lint -save -e537 */
/** @file eMIOS_Pwm_LLD.c
    @note Violates MISRA 2004 Advisory Rule 19.1,19,15 : See @ref eMIOS_Pwm_LLD_C_REF_8 */
#include "eMIOS_Pwm_LLD_CfgEx.h"

#include "Reg_eSys_EMIOS.h"
/** @file eMIOS_Pwm_LLD.c
    @note Violates MISRA 2004 Advisory Rule 19.1,19,15 : See @ref eMIOS_Pwm_LLD_C_REF_8 */
#include "Reg_eSys_EMIOS_CfgEx.h"
/*lint -restore */

#include "SchM_Pwm.h"

#if (PWM_DEV_ERROR_DETECT == STD_ON)
    #include "Det.h"
#endif


/*===============================================================================================
                                        LOCAL MACROS
===============================================================================================*/
/**
@{
@brief Parameters that shall be published within the Pwm driver header file and also in the
       module's description file
@remarks Covers BSW00374, BSW00379, BSW00318
*/
#define PWM_VENDOR_ID_EMIOS_LLD_C         43
/*lint -e621 */
/** @file eMIOS_Pwm_LLD.c
    @note Violates MISRA 2004 Advisory Rule 1.2, 1.4 and 5.1 : See @ref eMIOS_Pwm_LLD_C_REF_9 */
#define PWM_AR_MAJOR_VERSION_EMIOS_LLD_C  3
#define PWM_AR_MINOR_VERSION_EMIOS_LLD_C  0
#define PWM_AR_PATCH_VERSION_EMIOS_LLD_C  0
#define PWM_SW_MAJOR_VERSION_EMIOS_LLD_C  2
#define PWM_SW_MINOR_VERSION_EMIOS_LLD_C  0
#define PWM_SW_PATCH_VERSION_EMIOS_LLD_C  0
/*lint -restore */
/**@}*/
/*===============================================================================================
                                      FILE VERSION CHECKS
===============================================================================================*/

/* Check if source file and PWM header file are of the same vendor */
#if (PWM_VENDOR_ID_EMIOS_LLD_C != PWM_VENDOR_ID)
    #error "eMIOS_Pwm_LLD.c and Pwm.h have different vendor ids"
#endif

/* Check if source file and PWM header file are of the same Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
    #if ((PWM_AR_MAJOR_VERSION_EMIOS_LLD_C != PWM_AR_MAJOR_VERSION) || \
         (PWM_AR_MINOR_VERSION_EMIOS_LLD_C != PWM_AR_MINOR_VERSION) || \
         (PWM_AR_PATCH_VERSION_EMIOS_LLD_C != PWM_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of eMIOS_Pwm_LLD.c and Pwm.h are different"
    #endif
#endif

/* Check if source file and PWM header file are of the same software version */
#if ((PWM_SW_MAJOR_VERSION_EMIOS_LLD_C != PWM_SW_MAJOR_VERSION) || \
     (PWM_SW_MINOR_VERSION_EMIOS_LLD_C != PWM_SW_MINOR_VERSION) || \
     (PWM_SW_PATCH_VERSION_EMIOS_LLD_C != PWM_SW_PATCH_VERSION))
#error "Software Version Numbers of eMIOS_Pwm_LLD.c and Pwm.h are different"
#endif



/* Check if source file and eMIOS_Pwm_LLD_IRQ.h are of the same vendor */
#if (PWM_VENDOR_ID_EMIOS_LLD_C != PWM_VENDOR_ID_EMIOS_LLD_H)
    #error "eMIOS_Pwm_LLD.c and eMIOS_Pwm_LLD.h have different vendor ids"
#endif

/* Check if source file and eMIOS_Pwm_LLD_IRQ.h are of the same Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
    #if ((PWM_AR_MAJOR_VERSION_EMIOS_LLD_C != PWM_AR_MAJOR_VERSION_EMIOS_LLD_H) || \
         (PWM_AR_MINOR_VERSION_EMIOS_LLD_C != PWM_AR_MINOR_VERSION_EMIOS_LLD_H) || \
         (PWM_AR_PATCH_VERSION_EMIOS_LLD_C != PWM_AR_PATCH_VERSION_EMIOS_LLD_H))
    #error "AutoSar Version Numbers of eMIOS_Pwm_LLD.c and eMIOS_Pwm_LLD.h are different"
    #endif
#endif

/* Check if source file and eMIOS_Pwm_LLD_IRQ.h are of the same software version */
#if ((PWM_SW_MAJOR_VERSION_EMIOS_LLD_C != PWM_SW_MAJOR_VERSION_EMIOS_LLD_H) || \
     (PWM_SW_MINOR_VERSION_EMIOS_LLD_C != PWM_SW_MINOR_VERSION_EMIOS_LLD_H) || \
     (PWM_SW_PATCH_VERSION_EMIOS_LLD_C != PWM_SW_PATCH_VERSION_EMIOS_LLD_H))
#error "Software Version Numbers of eMIOS_Pwm_LLD.c and eMIOS_Pwm_LLD.h are different"
#endif



/* Check if source file and eMIOS_Pwm_LLD_CfgEx.h are of the same vendor */
#if (PWM_VENDOR_ID_EMIOS_LLD_C != PWM_VENDOR_ID_EMIOS_LLD_CFGEX_H)
    #error "eMIOS_Pwm_LLD.c and eMIOS_Pwm_LLD_CfgEx.h have different vendor ids"
#endif

/* Check if source file and eMIOS_Pwm_LLD_CfgEx.h are of the same Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
    #if ((PWM_AR_MAJOR_VERSION_EMIOS_LLD_C != PWM_AR_MAJOR_VERSION_EMIOS_LLD_CFGEX_H) || \
         (PWM_AR_MINOR_VERSION_EMIOS_LLD_C != PWM_AR_MINOR_VERSION_EMIOS_LLD_CFGEX_H) || \
         (PWM_AR_PATCH_VERSION_EMIOS_LLD_C != PWM_AR_PATCH_VERSION_EMIOS_LLD_CFGEX_H))
    #error "AutoSar Version Numbers of eMIOS_Pwm_LLD.c and eMIOS_Pwm_LLD_CfgEx.h are different"
    #endif
#endif

/* Check if source file and eMIOS_Pwm_LLD_CfgEx.h are of the same software version */
#if ((PWM_SW_MAJOR_VERSION_EMIOS_LLD_C != PWM_SW_MAJOR_VERSION_EMIOS_LLD_CFGEX_H) || \
     (PWM_SW_MINOR_VERSION_EMIOS_LLD_C != PWM_SW_MINOR_VERSION_EMIOS_LLD_CFGEX_H)  || \
     (PWM_SW_PATCH_VERSION_EMIOS_LLD_C != PWM_SW_PATCH_VERSION_EMIOS_LLD_CFGEX_H))
#error "Software Version Numbers of eMIOS_Pwm_LLD.c and eMIOS_Pwm_LLD_CfgEx.h are different"
#endif



/* Check if source file and Reg_ESYS_EMIOS.h are of the same vendor */
#if (PWM_VENDOR_ID_EMIOS_LLD_C != REG_ESYS_EMIOS_H_VENDOR_ID)
    #error "eMIOS_Pwm_LLD.c and Reg_ESYS_EMIOS.h have different vendor ids"
#endif

/* Check if source file and Reg_ESYS_EMIOS_PWM.h are of the same Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
    #if ((PWM_AR_MAJOR_VERSION_EMIOS_LLD_C != REG_ESYS_EMIOS_H_AR_MAJOR_VERSION) || \
         (PWM_AR_MINOR_VERSION_EMIOS_LLD_C != REG_ESYS_EMIOS_H_AR_MINOR_VERSION) || \
         (PWM_AR_PATCH_VERSION_EMIOS_LLD_C != REG_ESYS_EMIOS_H_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of eMIOS_Pwm_LLD.c and Reg_ESYS_EMIOS.h are different"
    #endif
#endif

/* Check if source file and Reg_ESYS_EMIOS.h are of the same software version */
#if ((PWM_SW_MAJOR_VERSION_EMIOS_LLD_C != REG_ESYS_EMIOS_H_SW_MAJOR_VERSION) || \
     (PWM_SW_MINOR_VERSION_EMIOS_LLD_C != REG_ESYS_EMIOS_H_SW_MINOR_VERSION)  || \
     (PWM_SW_PATCH_VERSION_EMIOS_LLD_C != REG_ESYS_EMIOS_H_SW_PATCH_VERSION))
#error "Software Version Numbers of eMIOS_Pwm_LLD.c and Reg_ESYS_EMIOS.h are different"
#endif


/* Check if source file and Reg_eSys_EMIOS_CfgEx.h are of the same vendor */
#if (PWM_VENDOR_ID_EMIOS_LLD_C != REG_ESYS_EMIOS_CFGEX_H_VENDOR_ID)
    #error "eMIOS_Pwm_LLD.c and Reg_eSys_EMIOS_CfgEx.h have different vendor ids"
#endif

/* Check if source file and header file are of the same Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
    #if ((PWM_AR_MAJOR_VERSION_EMIOS_LLD_C != REG_ESYS_EMIOS_CFGEX_H_AR_MAJOR_VERSION) || \
         (PWM_AR_MINOR_VERSION_EMIOS_LLD_C != REG_ESYS_EMIOS_CFGEX_H_AR_MINOR_VERSION) || \
         (PWM_AR_PATCH_VERSION_EMIOS_LLD_C != REG_ESYS_EMIOS_CFGEX_H_AR_PATCH_VERSION))
        #error "AutoSar Version Numbers of eMIOS_Pwm_LLD.c and Reg_eSys_EMIOS_CfgEx.h differe"
    #endif
#endif

/* Check if source file and header file are of the same Software version */
#if ((PWM_SW_MAJOR_VERSION_EMIOS_LLD_C != REG_ESYS_EMIOS_CFGEX_H_SW_MAJOR_VERSION)  || \
     (PWM_SW_MINOR_VERSION_EMIOS_LLD_C != REG_ESYS_EMIOS_CFGEX_H_SW_MINOR_VERSION)  || \
     (PWM_SW_PATCH_VERSION_EMIOS_LLD_C != REG_ESYS_EMIOS_CFGEX_H_SW_PATCH_VERSION))
    #error "Software Version Numbers of eMIOS_Pwm_LLD.c and Reg_eSys_EMIOS_CfgEx.h are different"
#endif








/* Check if source file and header file are of the same Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
    #if ((PWM_AR_MAJOR_VERSION_EMIOS_LLD_C != SCHM_PWM_AR_MAJOR_VERSION) || \
         (PWM_AR_MINOR_VERSION_EMIOS_LLD_C != SCHM_PWM_AR_MINOR_VERSION))

        #error "AutoSar Version Numbers of eMIOS_Pwm_LLD.c and SchM_Pwm.h are different"
    #endif
#endif










/* Check if source file and DET header file are of the same version */
#if (PWM_DEV_ERROR_DETECT == STD_ON)
    #ifdef CHECK_AUTOSAR_VERSION
        #if ((PWM_AR_MAJOR_VERSION_EMIOS_LLD_C != DET_AR_MAJOR_VERSION) || \
             (PWM_AR_MINOR_VERSION_EMIOS_LLD_C != DET_AR_MINOR_VERSION))
            #error "AutoSar Version Numbers of eMIOS_Pwm_LLD.c and Det.h are different"
        #endif
    #endif
#endif


/*===============================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
===============================================================================================*/


/*===============================================================================================
                                       LOCAL CONSTANTS
===============================================================================================*/


/*===============================================================================================
                                       LOCAL VARIABLES
===============================================================================================*/

#define PWM_START_SEC_VAR_UNSPECIFIED
/*lint -save -e961 -e537 -e451 */
/** @file eMIOS_Pwm_LLD.c
    @note Violates MISRA 2004 Advisory Rule 19.1, 19.15 : See @ref eMIOS_Pwm_LLD_C_REF_1,
    eMIOS_Pwm_LLD_C_REF_8 */
#include "MemMap.h"
/*lint -restore */

#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
    /**
        @brief array used to store the notification status (enabled/disabled) and the
               type of notification if enabled for each channelindexed using
               the hardware channel ID
               \n PWM_RISING_EDGE,
               \n PWM_FALLING_EDGE,
               \n PWM_BOTH_EDGES,
               \n 0xFF for disabled
     */
    STATIC VAR(uint8, PWM_VAR)  Pwm_EMIOS_LLD_Notifications[ PWM_EMIOS_HW_CHANNELS ];
#endif


/*===============================================================================================
                                       GLOBAL VARIABLES
===============================================================================================*/

/**
    @brief   pointer to the top level configuration structure used by the EMIOS implementation
*/
/** @file Pwm.c
    @note Violates MISRA 2004 Advisory Rule 8.10 : See @ref Pwm_C_REF_1, Pwm_C_REF_2 */
P2CONST(Pwm_ConfigType, PWM_VAR, PWM_APPL_CONST) Pwm_EMIOS_Cfg = NULL_PTR;

/**
    @brief   array used to store the current period for each pwm channel, indexed using
             the hw channel id
*/
/** @file Pwm.c
    @note Violates MISRA 2004 Advisory Rule 8.10 : See @ref Pwm_C_REF_1, Pwm_C_REF_2 */
    VAR(Pwm_PeriodType, PWM_VAR) Pwm_EMIOS_LLD_Period[ PWM_EMIOS_HW_CHANNELS ];

#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)

    /**
        @brief array used for reverse translation between Hw channel and Logical channel
         used to call the logical channel notification in the hw channel ISR
    */
    VAR(Pwm_ChannelType, PWM_VAR)  Pwm_EMIOS_LLD_RevHardwareTable[ PWM_EMIOS_HW_CHANNELS ];


    /**
    @brief   array used to store the current dutycycle state
          \n 1 - dutycycle != 0%, 100% - signal toggling
          \n 0 - dutycycle == 0%, 100% - signal is stable state - no transition available
    */
    /** @file Pwm.c
    @note Violates MISRA 2004 Advisory Rule 8.10 : See @ref Pwm_C_REF_1, Pwm_C_REF_2 */
    VAR(uint8, PWM_VAR)  Pwm_EMIOS_LLD_DutyState[ PWM_EMIOS_HW_CHANNELS ];

#endif

#define PWM_STOP_SEC_VAR_UNSPECIFIED
/*lint -save -e961 -e537 -e451 */
/** @file eMIOS_Pwm_LLD.c
    @note Violates MISRA 2004 Advisory Rule 19.1, 19.15 : See @ref eMIOS_Pwm_LLD_C_REF_1,
    eMIOS_Pwm_LLD_C_REF_8 */
#include "MemMap.h"
/*lint -restore */


/*===============================================================================================
                                       GLOBAL CONSTANTS
===============================================================================================*/
#define EMIOS_CADR_OFFSET   0x00UL

#define EMIOS_CBDR_OFFSET   0x04UL

#define EMIOS_CCNTR_OFFSET  0x08UL

#define EMIOS_CCR_OFFSET    0x0CUL

#define EMIOS_CSR_OFFSET    0x10UL

#define EMIOS_ALTA_OFFSET   0x14UL

#define EMIOS_MCR_OFFSET             0x0000UL
#define EMIOS_OUDR_OFFSET            0x0008UL
#define EMIOS_UCDIS_OFFSET           0x000CUL

VAR(uint16, PWM_VAR) Pwm_Current_TriggerDelay[PWM_EMIOS_HW_CHANNELS];
VAR(uint16, PWM_VAR) Pwm_PeriodInit[PWM_EMIOS_HW_CHANNELS];
/*===============================================================================================
                                   LOCAL FUNCTION PROTOTYPES
===============================================================================================*/
/**
@brief   Function to update the A and B registers in a critical section
@details This function disable the transfer, updates the register A
         and register B and enables the transfer
@param[in] mIdx - eMIOS module index
@param[in] chIdx - the index of unified channel
@param[in] valA - The eMIOS Reg A value to be updated
@param[in] valB - The eMIOS Reg B value to be updated
*/

INLINE STATIC FUNC (void, PWM_CODE) EMIOS_LLD_UpdateChannel_AB
                                    (
                                        VAR(Pwm_ChannelType, AUTOMATIC) mIdx,
                                        VAR(Pwm_ChannelType, AUTOMATIC) chIdx,
                                        VAR(uint32, AUTOMATIC) valA,
                                        VAR(uint32, AUTOMATIC) valB,
                                        VAR(uint32, AUTOMATIC) ChannelAddr,
                                        VAR(uint32, AUTOMATIC) ModuleAddr
                                    );

/**
@brief   Function to compute the duty cycle
@details This function computes the dutycycle value in ticks
@param[in] Period - period of pulse
@param[in] Duty - duty cycle of pulse
@remarks Covers     PWM059
@return  Pwm_PeriodType - the computed dutycycle value in ticks
        - uint16 - 16bit EMIOS return value
        - uint32 - 24bit EMIOS return value
*/

INLINE STATIC FUNC (Pwm_PeriodType, PWM_CODE) EMIOS_PWM_LLD_ComputeDutycycle
                                              (
                                                  VAR(Pwm_PeriodType, AUTOMATIC) Period,
                                                  VAR(uint16,AUTOMATIC) Duty
                                              );
/**
@brief   Function to get the period of PWM channel
@details This function returns the channel period depending on the selected
         counter bus - BusA / Bus Diverse
@param[in] mIdx - eMIOS module index
@param[in] chIdx - the index of unified channel
@param[in] Bus - the bus selected by this unified channel
@return Pwm_PeriodType - the period of the selected counter bus
        - uint16 - 16bit EMIOS return value
        - uint32 - 24bit EMIOS return value
*/

STATIC FUNC (Pwm_PeriodType, PWM_CODE) EMIOS_PWM_LLD_GetCounterBusPeriod
                                       (
                                           VAR(Pwm_ChannelType, AUTOMATIC) mIdx,
                                           VAR(Pwm_ChannelType, AUTOMATIC) chIdx,
                                           VAR(Pwm_EmiosCtrlParamType, AUTOMATIC) Bus,
                                           VAR(uint32, AUTOMATIC) ChannelAddr,
                                           VAR(uint32, AUTOMATIC) ModuleAddr
                                       );



/*===============================================================================================
                                       LOCAL FUNCTIONS
===============================================================================================*/

/**
@brief   Function to update the A and B registers in a critical section
@details This function disable the transfer, updates the register A
         and register B and enables the transfer
@param[in] mIdx - eMIOS module index
@param[in] chIdx - the index of unified channel
@param[in] valA - The eMIOS Reg A value to be updated
@param[in] valB - The eMIOS Reg B value to be updated
*/

INLINE STATIC FUNC (void, PWM_CODE) EMIOS_LLD_UpdateChannel_AB
                                    (
                                        VAR(Pwm_ChannelType, AUTOMATIC) mIdx,
                                        VAR(Pwm_ChannelType, AUTOMATIC) chIdx,
                                        VAR(uint32, AUTOMATIC) valA,
                                        VAR(uint32, AUTOMATIC) valB,
                                        VAR(uint32, AUTOMATIC) ChannelAddr,
                                        VAR(uint32, AUTOMATIC) ModuleAddr
                                    )
{

/** @file eMIOS_Pwm_LLD.c
    @note Violates MISRA 2004 Advisory Rule 11.1 : See @ref eMIOS_Pwm_LLD_C_REF_7
    */
    /*lint -save -e923 */
    REG_BIT_SET32(   (ModuleAddr+EMIOS_OUDR_OFFSET), (uint32)((uint32)1<<(chIdx)) );
    REG_WRITE32(   ChannelAddr + EMIOS_CADR_OFFSET, (valA) );
    REG_WRITE32(   ChannelAddr + EMIOS_CBDR_OFFSET, (valB) );
    REG_BIT_CLEAR32( (ModuleAddr+EMIOS_OUDR_OFFSET), (uint32)((uint32)1<<(chIdx)) );
    /*lint -restore  */
}



/**
@brief   Function to compute the duty cycle
@details This function computes the dutycycle value in ticks
@param[in] Period - period of pulse
@param[in] Duty - duty cycle of pulse
@remarks Covers     PWM059
@return  Pwm_PeriodType - the computed dutycycle value in ticks
        - uint16 - 16bit EMIOS return value
        - uint32 - 24bit EMIOS return value
*/

INLINE STATIC FUNC (Pwm_PeriodType, PWM_CODE) EMIOS_PWM_LLD_ComputeDutycycle
                                              (
                                                  VAR(Pwm_PeriodType, AUTOMATIC) Period,
                                                  VAR(uint16,AUTOMATIC) Duty
                                              )
{

    VAR(Pwm_PeriodType, AUTOMATIC) dutycycle; /* 16bit or 32bit variable */
    VAR(uint32, AUTOMATIC) Calc_rounding; /* 16bit or 32bit variable */

#ifdef PWM_EMIOS_16_BITS_VARIANT
 #if  (PWM_EMIOS_16_BITS_VARIANT == STD_ON)

    /* 16bit EMIOS */


      Calc_rounding = (uint32)((uint32)Period * (uint32)Duty);
      if((Calc_rounding & (uint32)0x40000000) == (uint32)0x40000000)
      {
       dutycycle = (Pwm_PeriodType)((uint32)(Calc_rounding>>(Pwm_PeriodType)15)+(Pwm_PeriodType)1);
      }
      else
      {
       dutycycle = (Pwm_PeriodType)((uint32)Calc_rounding>>(Pwm_PeriodType)15);
      }


 #else

    /* 24bit EMIOS */

    VAR(uint8, AUTOMATIC)   period_high;
    VAR(uint16, AUTOMATIC)  period_low;

    period_high = (uint8)(Period >> 16); /* get the 8bit  MS byte of 24-bit value
                                             stored on uint32 */
    period_low  = (uint16)Period;        /* get the 16bit LS word of 24-bit value
                                             stored on uint32 */


    dutycycle = (uint32)((uint32)((uint32)period_high * (uint32)Duty) << 1) +
                (uint32)((uint32)((uint32)period_low  * (uint32)Duty) >> 15);

 #endif

#else

 #error "Unknown EMIOS type, PWM_EMIOS_16_BITS_VARIANT is undefined";

#endif

    return dutycycle;

}




/**
@brief   Function to get the period of PWM channel
@details This function returns the channel period depending on the selected
         counter bus - BusA / Bus Diverse
@param[in] mIdx - eMIOS module index
@param[in] chIdx - the index of unified channel
@param[in] Bus - the bus selected by this unified channel
@return Pwm_PeriodType - the period of the selected counter bus
        - uint16 - 16bit EMIOS return value
        - uint32 - 24bit EMIOS return value
*/

STATIC FUNC (Pwm_PeriodType, PWM_CODE) EMIOS_PWM_LLD_GetCounterBusPeriod
                                       (
                                           VAR(Pwm_ChannelType, AUTOMATIC) mIdx,
                                           VAR(Pwm_ChannelType, AUTOMATIC) chIdx,
                                           VAR(Pwm_EmiosCtrlParamType, AUTOMATIC) Bus,
                                           VAR(uint32, AUTOMATIC)ChannelAddr,
                                           VAR(uint32, AUTOMATIC) ModuleAddr
                                       )
{

    VAR(Pwm_PeriodType,  AUTOMATIC)  Period = (Pwm_PeriodType)0;


    if (PWM_BUS_DIVERSE == Bus) {

        if (EMIOS_0_CH_7 >= chIdx) { /* bus B */

            if
            (
/** @file eMIOS_Pwm_LLD.c
            @note Violates MISRA 2004 Advisory Rule  11.1 : See @ref eMIOS_Pwm_LLD_C_REF_7
            */
            /*lint -save -e923 */
            CCR_MODE_MCB_INT_CLOCK == (REG_READ32(EMIOS_CCR(mIdx, EMIOS_0_CH_0)) & CCR_MODE_MASK)
            /*lint -restore  */
            ) {
/** @file eMIOS_Pwm_LLD.c
                @note Violates MISRA 2004 Advisory Rule  10.1, 11.1 : See @ref eMIOS_Pwm_LLD_C_REF_2,
                eMIOS_Pwm_LLD_C_REF_7
                */
                /*lint -save -e960, -e923 */
                /* bus B source : MCB reference - period in A register */
                Period = (Pwm_PeriodType) REG_READ32(EMIOS_CADR(mIdx, EMIOS_0_CH_0));
                /*lint -restore */
            } else {
       /** @file eMIOS_Pwm_LLD.c
                @note Violates MISRA 2004 Advisory Rule  10.1, 11.1 : See @ref eMIOS_Pwm_LLD_C_REF_2,
                eMIOS_Pwm_LLD_C_REF_7
                */
                /*lint -save -e960, -e923 */
                /* bus B source : OPWFMB reference - period in B register */
                Period = (Pwm_PeriodType) REG_READ32(EMIOS_CBDR(mIdx, EMIOS_0_CH_0));
                /*lint -restore */
            }
        } else if (EMIOS_0_CH_15 >= chIdx) { /* Bus C */

            if
            (
    /** @file eMIOS_Pwm_LLD.c
            @note Violates MISRA 2004 Advisory Rule 11.1 : See @ref eMIOS_Pwm_LLD_C_REF_7
            */
            /*lint -save -e923 */
            CCR_MODE_MCB_INT_CLOCK == (REG_READ32(EMIOS_CCR(mIdx, EMIOS_0_CH_8)) & CCR_MODE_MASK)
            /*lint -restore  */
            )  {
       /** @file eMIOS_Pwm_LLD.c
                @note Violates MISRA 2004 Advisory Rule 10.1, 11.1 : See @ref eMIOS_Pwm_LLD_C_REF_2,
                eMIOS_Pwm_LLD_C_REF_7
                */
                /*lint -save -e960, -e923 */
                /* bus C source : MCB reference - period in A register */
                Period = (Pwm_PeriodType) REG_READ32(EMIOS_CADR(mIdx, EMIOS_0_CH_8));
                /*lint -restore */
            } else {
    /** @file eMIOS_Pwm_LLD.c
                @note Violates MISRA 2004 Advisory Rule 10.1, 11.1 : See @ref eMIOS_Pwm_LLD_C_REF_2,
                eMIOS_Pwm_LLD_C_REF_7
                */
                /*lint -save -e960, -e923 */
                /* bus C source : OPWFMB reference - period in B register */
                Period = (Pwm_PeriodType) REG_READ32(EMIOS_CBDR(mIdx, EMIOS_0_CH_8));
                /*lint -restore */
            }

        } else if (EMIOS_0_CH_23 >= chIdx) { /* bus D */

            if
            (
    /** @file eMIOS_Pwm_LLD.c
            @note Violates MISRA 2004 Advisory Rule 11.1 : See @ref eMIOS_Pwm_LLD_C_REF_7
            */
            /*lint -save -e923 */
            CCR_MODE_MCB_INT_CLOCK == (REG_READ32(EMIOS_CCR(mIdx, EMIOS_0_CH_16))&CCR_MODE_MASK)
            /*lint -restore  */
            ) {
    /** @file eMIOS_Pwm_LLD.c
                @note Violates MISRA 2004 Advisory Rule 10.1, 11.1 : See @ref eMIOS_Pwm_LLD_C_REF_2,
                eMIOS_Pwm_LLD_C_REF_7
                */
                /*lint -save -e960, -e923 */
                /* bus D source : MCB reference - period in A register */
                Period = (Pwm_PeriodType) REG_READ32(EMIOS_CADR(mIdx, EMIOS_0_CH_16));
                /*lint -restore */
            } else {
    /** @file eMIOS_Pwm_LLD.c
                @note Violates MISRA 2004 Advisory Rule 10.1, 11.1 : See @ref eMIOS_Pwm_LLD_C_REF_2,
                eMIOS_Pwm_LLD_C_REF_7
                */
                /*lint -save -e960, -e923 */
                /* bus D source : OPWFMB reference - period in B register */
                Period = (Pwm_PeriodType) REG_READ32(EMIOS_CBDR(mIdx, EMIOS_0_CH_16));
                /*lint -restore */
            }

        }
#if (PWM_EMIOS_HW_CHANNELS > PWM_EMIOS_CH_24)
        else
        { /* Bus E remaining */
            if
            (
    /** @file eMIOS_Pwm_LLD.c
            @note Violates MISRA 2004 Advisory Rule 11.1 : See @ref eMIOS_Pwm_LLD_C_REF_7
            */
            /*lint -save -e923 */
            CCR_MODE_MCB_INT_CLOCK == (REG_READ32(EMIOS_CCR(mIdx, EMIOS_0_CH_24))&CCR_MODE_MASK)
            /*lint -restore  */
            )  {
    /** @file eMIOS_Pwm_LLD.c
            @note Violates MISRA 2004 Advisory Rule 10.1, 11.1 : See @ref eMIOS_Pwm_LLD_C_REF_2,
            eMIOS_Pwm_LLD_C_REF_7
            */
            /*lint -save -e960, -e923 */
            /* bus E source : MCB reference - period in A register */
            Period = (Pwm_PeriodType) REG_READ32(EMIOS_CADR(mIdx, EMIOS_0_CH_24));
            /*lint -restore */
            } else {
    /** @file eMIOS_Pwm_LLD.c
                @note Violates MISRA 2004 Advisory Rule 10.1, 11.1 : See @ref eMIOS_Pwm_LLD_C_REF_2,
                eMIOS_Pwm_LLD_C_REF_7
                */
                /*lint -save -e960, -e923 */
                /* bus E source : OPWFMB reference - period in B register */
                Period = (Pwm_PeriodType) REG_READ32(EMIOS_CBDR(mIdx, EMIOS_0_CH_24));
                /*lint -restore */
            }
        }
#else
    else
        {
        /*Empty else to fix misra*/
        }
#endif
    } else {  /* bus A remaining */

        if
        (
    /** @file eMIOS_Pwm_LLD.c
        @note Violates MISRA 2004 Advisory Rule 11.1 : See @ref eMIOS_Pwm_LLD_C_REF_7
        */
        /*lint -save -e923 */
        CCR_MODE_MCB_INT_CLOCK == (REG_READ32(EMIOS_CCR(mIdx, EMIOS_0_CH_23))&CCR_MODE_MASK)
        /*lint -restore  */
        ) {
    /** @file eMIOS_Pwm_LLD.c
            @note Violates MISRA 2004 Advisory Rule 10.1, 11.1 : See @ref eMIOS_Pwm_LLD_C_REF_2,
            eMIOS_Pwm_LLD_C_REF_7
            */
            /*lint -save -e960, -e923 */
            /* bus A source : MCB reference - period in A register */
            Period = (Pwm_PeriodType) REG_READ32(EMIOS_CADR(mIdx, EMIOS_0_CH_23));
            /*lint -restore */
        } else {
    /** @file eMIOS_Pwm_LLD.c
            @note Violates MISRA 2004 Advisory Rule 10.1, 11.1 : See @ref eMIOS_Pwm_LLD_C_REF_2,
            eMIOS_Pwm_LLD_C_REF_7
            */
            /*lint -save -e960, -e923 */
            /* bus A source : OPWFMB reference - period in B register */
            Period = (Pwm_PeriodType) REG_READ32(EMIOS_CBDR(mIdx, EMIOS_0_CH_23));
            /*lint -restore */
        }
    }

    return Period;
}

/*===============================================================================================
                                       GLOBAL FUNCTIONS
===============================================================================================*/
#define PWM_START_SEC_CODE
/*lint -save -e961 -e537 -e451 */
/** @file eMIOS_Pwm_LLD.c
    @note Violates MISRA 2004 Advisory Rule 19.1, 19.15 : See @ref eMIOS_Pwm_LLD_C_REF_1,
    eMIOS_Pwm_LLD_C_REF_8 */
#include "MemMap.h"
/*lint -restore */

/**
@brief   Service for initializing the hardware timer module (low level)
@details This function initializes all the configured hardware channels as per the
         configured mode
         - puts the channel in GPIO mode
         - disables the interrupt corresponding to Emios channel
         - ulear pending interrupt flag for the channel
         - enables/disables the Freeze Mode
         - clears the (pending) interrupt flag corresponding to Emios channel
         - get the Period that the current UC is using and also calculates the dutycycle
         - update registers A and B with the dutycycle and period value for the configured mode
         - force a match on B register for OPWFMB mode
         - force a match on A register for OPWMB and OPWMT modes
         - write trigger delay to alternate A register for OPWMT mode and offset to A register
           for OPWMB and OPWMT modes
         - FLAG assigned to DMA request and FLAG event is enabled for OPWMT mode
         - FLAG event is disabled for OPWMB and OPWFMB modes
         - sets the prescaler value
         - enable prescaler which will start the internal counter, for Counter Bus


@param[in] ConfigPtr - pointer to PWM top configuration structure

@remarks Covers   PWM009, PWM018, PWM020, PWM052, PWM062, PWM080


@remarks Implements   DPWM03005
*/

FUNC (void, PWM_CODE) EMIOS_Pwm_LLD_Init
                      (
                          P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr
                      )
{
    /* Pwm channel generic parameters from config structure */
    P2CONST(Pwm_ChannelConfigType, AUTOMATIC, PWM_APPL_CONST) PwmChannel = NULL_PTR;
    /* Pwm channel Emios specific parameters from config structure */
    P2CONST(Pwm_EMIOS_ChannelConfigType, AUTOMATIC, PWM_APPL_CONST) PwmEmiosSpecificParam= NULL_PTR;

    VAR(Pwm_EmiosCtrlParamType, AUTOMATIC) ctrlRegVal;

    VAR(Pwm_PeriodType, AUTOMATIC)  Period;

    VAR(uint16, AUTOMATIC)  DutyCycle;
    VAR(Pwm_PeriodType, AUTOMATIC)  tempDuty;
    VAR(uint32, AUTOMATIC)  tempDuty32;

    VAR(Pwm_ChannelType, AUTOMATIC) hw_ch; /* hw channel */

    VAR(Pwm_ChannelType, AUTOMATIC) ch = (Pwm_ChannelType )0; /* logical channel */

    VAR(Pwm_ChannelType, AUTOMATIC) mIdx;   /* assigned eMIOS HW module  index */
    VAR(Pwm_ChannelType, AUTOMATIC) chIdx;  /* assigned eMIOS HW channel index */

    VAR(uint32, AUTOMATIC) ModuleAddr;
    VAR(uint32, AUTOMATIC) ChannelAddr;


    /* copy the top level configuration pointer to EMIOS implementation */
    Pwm_EMIOS_Cfg = ConfigPtr;

#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
    for (ch=0U; ch < (Pwm_ChannelType)PWM_EMIOS_HW_CHANNELS; ch++)
    {
        /* invalidate the reverse hardware channel 2 logical channel map */
        Pwm_EMIOS_LLD_RevHardwareTable[ ch ] = (Pwm_ChannelType)0xFFU;
        /* notifications disabled */
        Pwm_EMIOS_LLD_Notifications[ ch ] = 0xFFU;
    }
#endif

    for (ch=0U; ch < Pwm_EMIOS_Cfg->ChannelCount; ch++)  {
        /* only handle EMIOS channels */
        /** @file eMIOS_Pwm_LLD.c
    @note Violates MISRA 2004 Advisory Rule 17.4: See @ref eMIOS_Pwm_LLD_C_REF_11 */



        if (PWM_EMIOS_CHANNEL == Pwm_EMIOS_Cfg->ChannelsPtr[ch].IpType)
        {
          /* extract from conf structure the generic channel information */
           PwmChannel = &Pwm_EMIOS_Cfg->ChannelsPtr[ch];

          /* extract from conf structure the EMIOS specific channel information */
           PwmEmiosSpecificParam =  &PwmChannel->SpecificCfg.EmiosCfg;

           ModuleAddr = PwmEmiosSpecificParam->Pwm_Emios_ModuleAddr;
           ChannelAddr = PwmEmiosSpecificParam->Pwm_Emios_ChannelAddr;


            hw_ch = PwmEmiosSpecificParam->Pwm_HwChannelID;

            mIdx  = (uint8)(hw_ch >> EMIOS_MOD_SHIFT);
            chIdx = (uint8)(hw_ch &  EMIOS_CH_MASK);


#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
            /* add hw2logical translation  */
            Pwm_EMIOS_LLD_RevHardwareTable[ hw_ch ] = ch;
#endif

            /* save current channel control register config value in local variable */
            ctrlRegVal = PwmEmiosSpecificParam->Pwm_ParamValue;

            /* only write UCDIS register if it's available */
#ifdef EMIOS_UCDIS
            /* enable unified channel to make registers writable */
            /**
            @note Violates MISRA 2004 Advisory Rule 11.1 : See @ref eMIOS_Pwm_LLD_C_REF_7
            */
            /*lint -save -e923 */
            REG_BIT_CLEAR32( (ModuleAddr+EMIOS_UCDIS_OFFSET), (uint32)((uint32)1<<(chIdx)) );
#endif

            /* set the freeze bit to the configured value */
            REG_RMW32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_FREN_MASK, CCR_FREN_MASK & ctrlRegVal );

            /* before entering GPIO mode set the EDPOL bit to the configured IDLE value */
            if (PWM_HIGH == PwmChannel->Pwm_IdleState)  {
                REG_BIT_SET32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_EDPOL_MASK );
            }
            else {
                REG_BIT_CLEAR32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_EDPOL_MASK );
            }

            /* enter GPIO output mode */
            REG_RMW32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_MODE_MASK, CCR_MODE_GPO );

            /* disable channel interrupts */

            REG_BIT_CLEAR32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_FEN_MASK ); /* disable interrupt */

            /* Clear pending interrupt flag for the channel */
            REG_WRITE32( ChannelAddr + EMIOS_CSR_OFFSET, CSR_FLAG_BIT );
            /*lint -restore */

            /* get the Period that the current UC is using */
            if (PWM_BUS_INTERNAL_COUNTER == ((uint32)ctrlRegVal & PWM_BUS_MASK))
            {
                /* internal counter - period from configuration */
                /* increment with 1 as counter always starts at 1 */
                Period = PwmChannel->Pwm_DefaultPeriodValue;

                /* disable prescaler - this will stop the internal counter */
                /* enable unified channel to make registers writable */
    /** @file eMIOS_Pwm_LLD.c
                @note Violates MISRA 2004 Advisory Rule 11.1 : See @ref eMIOS_Pwm_LLD_C_REF_7
                */
                /*lint -save -e923 */
                REG_BIT_CLEAR32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_UCPREN_MASK );

                REG_WRITE32( ChannelAddr + EMIOS_CCNTR_OFFSET, 1); /* set internal counter to 1 */

                /* select internal counter bus */
                REG_BIT_SET32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_BSL_MASK );
                /*lint -restore */
            }
            else { /* Bus A or Bus Diverse */

                Period = EMIOS_PWM_LLD_GetCounterBusPeriod
                         (
                             mIdx,
                             chIdx,
                             ctrlRegVal & CCR_BSL_MASK,
                             ChannelAddr,
                             ModuleAddr
                         );

#if (PWM_DEV_ERROR_DETECT == STD_ON)

                /*
                 * if the configured channel Offset is >= than the associated MCB
                 * channel period then raise PWM_E_OPWMB_CHANNEL_OFFSET_VALUE  error.
                 */
                if (PwmEmiosSpecificParam->Pwm_Offset >= Period)
                {
                    Det_ReportError
                    (
                        (uint16) PWM_MODULE_ID,
                        (uint8) 0,
                        (uint8) PWM_INIT_ID,
                        (uint8) PWM_E_OPWMB_CHANNEL_OFFSET_VALUE
                    );
        /** @file eMIOS_Pwm_LLD.c
                    @note Violates MISRA 2004 Advisory Rule 14.6 :
                          See @ref eMIOS_Pwm_LLD_C_REF_5
                    @note we need to exit the FOR loop in each case a
                          DET Error is detected
                    */
                    /*lint -save -e960 */
                    /* exit for loop and Pwm_Init function -
                       we can't continue further */
                    break;
                    /*lint -restore */
                }
#endif

            }


            /* save channel period value for later use */
            Pwm_EMIOS_LLD_Period[ hw_ch ] = Period;
#ifdef PWM_FEATURE_OPWMT
    #if (PWM_FEATURE_OPWMT == STD_ON)
            Pwm_PeriodInit[hw_ch] = Period;
        Pwm_Current_TriggerDelay[hw_ch] = (uint16)(PwmEmiosSpecificParam->Pwm_TriggerDelay);
    #endif
#endif
            /* get the dutycycle */
            DutyCycle = PwmChannel->Pwm_DefaultDutyCycleValue;

            tempDuty = EMIOS_PWM_LLD_ComputeDutycycle(Period, DutyCycle);

            if (((uint16)0x0000 == DutyCycle) || (0x0U == tempDuty))
            {

#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
                Pwm_EMIOS_LLD_DutyState[ hw_ch ] = 0U; /* no transitions in the signal */
#endif

                if (CCR_MODE_OPWFMB_FLAG_B == (ctrlRegVal & CCR_MODE_MASK)) {
                    /* OPWFMB */
        /** @file eMIOS_Pwm_LLD.c
                    @note Violates MISRA 2004 Advisory Rule 10.1 :
                          See @ref eMIOS_Pwm_LLD_C_REF_3
                    */
                    /*lint -save -e960 */
                    EMIOS_LLD_UpdateChannel_AB
                    (
                        mIdx,
                        chIdx,
                        (uint32)0U,
                        (uint32)Period,
                        ChannelAddr,
                        ModuleAddr
                    );
                    /*lint -restore  */
                } else

#ifdef PWM_FEATURE_OPWMT
    #if (PWM_FEATURE_OPWMT == STD_ON)
                if (CCR_MODE_OPWMB_FLAG_B == (ctrlRegVal & CCR_MODE_MASK))
    #endif
#endif

                {
                    /* OPWMB */
                    /**
                    @note Violates MISRA 2004 Advisory Rule 10.1 :
                          See @ref eMIOS_Pwm_LLD_C_REF_3
                    */
                    /*lint -save -e960 */
                    EMIOS_LLD_UpdateChannel_AB
                    (
                        mIdx,
                        chIdx,
                        (uint32)0U,
                        (uint32)0U,
                        ChannelAddr,
                        ModuleAddr
                    );
                    /*lint -restore  */
                }

#ifdef PWM_FEATURE_OPWMT
    #if (PWM_FEATURE_OPWMT == STD_ON)
                else {
                    /* OPWMT */
        /** @file eMIOS_Pwm_LLD.c
                    @note Violates MISRA 2004 Advisory Rule 10.1 :
                          See @ref eMIOS_Pwm_LLD_C_REF_3
                    */
                    /*lint -save -e960 */
                    EMIOS_LLD_UpdateChannel_AB
                    (
                        mIdx,
                        chIdx,
                        (uint32)1U,
                        (uint32)1U,
                        ChannelAddr,
                        ModuleAddr
                    );
                    /*lint -restore  */
                }
    #endif
#endif

           }

            else if (PWM_DUTY_CYCLE_100 == DutyCycle)
            {

#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
                /* no transitions in the signal */
                Pwm_EMIOS_LLD_DutyState[ hw_ch ] = 0U;
#endif

                if (CCR_MODE_OPWFMB_FLAG_B == (ctrlRegVal & CCR_MODE_MASK)) {
                    /* OPWFMB */
        /** @file eMIOS_Pwm_LLD.c
                    @note Violates MISRA 2004 Advisory Rule 10.1 :
                          See @ref eMIOS_Pwm_LLD_C_REF_3
                    */
                    /*lint -save -e960 */
                    EMIOS_LLD_UpdateChannel_AB
                    (
                        mIdx,
                        chIdx,
                        (uint32)Period,
                        (uint32)Period,
                        ChannelAddr,
                        ModuleAddr
                    );
                    /*lint -restore  */
                } else

#ifdef PWM_FEATURE_OPWMT
    #if (PWM_FEATURE_OPWMT == STD_ON)
                if (CCR_MODE_OPWMB_FLAG_B == (ctrlRegVal & CCR_MODE_MASK))
    #endif
#endif

                {
                    /* OPWMB */
       /** @file eMIOS_Pwm_LLD.c
                    @note Violates MISRA 2004 Advisory Rule 10.1 :
                          See @ref eMIOS_Pwm_LLD_C_REF_3
                    */
                    /*lint -save -e960 */
                    EMIOS_LLD_UpdateChannel_AB
                    (
                        mIdx,
                        chIdx,
                        (uint32)0U,
                        (uint32)Period,
                        ChannelAddr,
                        ModuleAddr
                    );
                    /*lint -restore  */
                }


#ifdef PWM_FEATURE_OPWMT
    #if (PWM_FEATURE_OPWMT == STD_ON)
                else {
                    /* OPWMT */
    /** @file eMIOS_Pwm_LLD.c
                    @note Violates MISRA 2004 Advisory Rule 10.1 :
                          See @ref eMIOS_Pwm_LLD_C_REF_3
                    */
                    /*lint -save -e960 */
                    EMIOS_LLD_UpdateChannel_AB
                    (
                        mIdx,
                        chIdx,
                        (uint32)1U,
                        (uint32)(Period+(uint32)1U),
                        ChannelAddr,
                        ModuleAddr
                    );
                    /*lint -restore  */
                }
    #endif
#endif

            } else
            {
                /* != (0%, 100%) */

#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
                /*  transitions available in the signal */
                Pwm_EMIOS_LLD_DutyState[ hw_ch ] = 1U;
#endif

                if
                (
                    CCR_MODE_OPWFMB_FLAG_B == (ctrlRegVal & CCR_MODE_MASK)
                ) { /* OPWFMB */

    /** @file eMIOS_Pwm_LLD.c
                    @note Violates MISRA 2004 Advisory Rule 10.1 :
                          See @ref eMIOS_Pwm_LLD_C_REF_3
                    */
                    /*lint -save -e960 */
                    EMIOS_LLD_UpdateChannel_AB
                    (
                        mIdx,
                        chIdx,
                        (uint32)tempDuty,
                        (uint32)Period,
                        ChannelAddr,
                        ModuleAddr
                    );
                    /*lint -restore  */

                } else

#ifdef PWM_FEATURE_OPWMT
    #if (PWM_FEATURE_OPWMT == STD_ON)

                if ((ctrlRegVal & CCR_MODE_MASK) == CCR_MODE_OPWMB_FLAG_B)

    #endif
#endif

                { /* OPWMB */

                    tempDuty32 = (uint32)tempDuty + PwmEmiosSpecificParam->Pwm_Offset;

#if (PWM_DEV_ERROR_DETECT == STD_ON)

                    /* check that the configured channel Offset parameter
                     * combined with the Dutycycle will not program event B
                     * in time after the period
                     * - leading to unexpected behavior -
                     * signal will take the value of EDPOL (=signal polarity)
                     * This can happen only if Pwm_Offset != 0 because
                     * the Dutycycle formula limits event B
                     * to [0, Period];
                     * In this case (Pwm_Offset != 0) 100% dutycycle is
                     * impossible to reach
                     */
                    if (tempDuty32 >= Period)
                    {
                        Det_ReportError
                        (
                            (uint16) PWM_MODULE_ID,
                            (uint8)0,
                            (uint8)PWM_INIT_ID,
                            (uint8)PWM_E_OPWMB_CHANNEL_OFFSET_DUTYCYCLE_RANGE
                        );
        /** @file eMIOS_Pwm_LLD.c
                        @note Violates MISRA 2004 Advisory Rule 14.6:
                              See @ref eMIOS_Pwm_LLD_C_REF_5
                        @note we need to exit the FOR loop in
                              each case a DET Error is detected
                        */
                        /*lint -save -e960 */
                        break; /* exit for loop and Pwm_Init function
                                  - we can't continue further */
                        /*lint -restore */
                    }
                    else
#endif

                    {
        /** @file eMIOS_Pwm_LLD.c
                        @note Violates MISRA 2004 Advisory Rule 10.1 :
                              See @ref eMIOS_Pwm_LLD_C_REF_3
                        */
                        /*lint -save -e960 */
                        EMIOS_LLD_UpdateChannel_AB
                        (
                            mIdx,
                            chIdx,
                            (uint32)(PwmEmiosSpecificParam->Pwm_Offset + (uint32)1U),
                            (uint32)tempDuty32,
                            ChannelAddr,
                            ModuleAddr
                        );
                        /*lint -restore  */
                    }

                }

#ifdef PWM_FEATURE_OPWMT
    #if (PWM_FEATURE_OPWMT == STD_ON)

                else {  /* OPWMT */


        #if (PWM_CHANGE_REGISTER_A_SWITCH == STD_ON)
                    {
                        /* register A is updated on dutycycle change */
                        VAR(uint16, AUTOMATIC)  tempRegB;

                        /* Calculate the B-register value */
                        if (0 != PwmEmiosSpecificParam->Pwm_Offset)
                        {
                            tempRegB = (
                                           Period
                                           -
                                           PwmEmiosSpecificParam->Pwm_Offset
                                       ) + 1U;
                        }
                        else
                        {
                            tempRegB = (uint16)1U;
                        }

                        /* Calculate the A-register value */
                        if (tempRegB > tempDuty)
                        {
                            tempDuty = tempRegB - tempDuty;
                        }
                        else
                        {
                            tempDuty = (Period - tempDuty) + (tempRegB - 1);
                        }

        /** @file eMIOS_Pwm_LLD.c
                        @note Violates MISRA 2004 Advisory Rule 10.1 :
                              See @ref eMIOS_Pwm_LLD_C_REF_3
                        */
                        /*lint -save -e960 */
                        EMIOS_LLD_UpdateChannel_AB
                        (
                            mIdx,
                            chIdx,
                            (uint32)tempDuty,
                            (uint32)tempRegB,
                            ChannelAddr,
                            ModuleAddr
                        );
                        /*lint -restore  */
                    }
        #else
                    /* register B is updated on dutycycle change */
                    tempDuty32 = (
                                     (uint32)tempDuty
                                     +
                                     PwmEmiosSpecificParam->Pwm_Offset
                                 ) % Period ;

                    /* if (tempDuty + Pwm_Offset == Period) then tempDuty32
                     * will be 0 if the reference channel is MCB/OPWFMB
                     * then we have [ 0x1, Period ] if we program regB
                     * with 0 a compare event will never be generated
                     * in this case we program the Period value instead
                     * and accept an error equal with 1 tick.
                     */
                    if ( 0x0U == tempDuty32 )  {
                        tempDuty32 = Period;
                    }

        /** @file eMIOS_Pwm_LLD.c
                    @note Violates MISRA 2004 Advisory Rule 10.1 :
                          See @ref eMIOS_Pwm_LLD_C_REF_3
                    */
                    /*lint -save -e960 */
                    EMIOS_LLD_UpdateChannel_AB
                    (
                        mIdx,
                        chIdx,
                        (uint32)(PwmEmiosSpecificParam->Pwm_Offset + (uint32)1U),
                        (uint32)tempDuty32,
                        ChannelAddr,
                        ModuleAddr
                    );
                    /*lint -restore  */

        #endif

                }

    #endif
#endif

            }

#ifdef PWM_FEATURE_OPWMT
    #if (PWM_FEATURE_OPWMT == STD_ON)
           /*
            * set the trigger offset for the OPWMT channel
            */
            if (CCR_MODE_OPWMT != (ctrlRegVal & CCR_MODE_MASK))
            {
    #endif
#endif

                /* OPWFMB, OPWMB */
                /* FLAG assigned to interrupt request  */
                /* enable unified channel to make registers writable */
    /** @file eMIOS_Pwm_LLD.c
                @note Violates MISRA 2004 Advisory Rule 11.1 : See @ref eMIOS_Pwm_LLD_C_REF_7
                */
                /*lint -save -e923 */
                REG_BIT_CLEAR32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_DMA_MASK );
                /* disable interrupt */
                REG_BIT_CLEAR32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_FEN_MASK );
                /*lint -restore  */

#ifdef PWM_FEATURE_OPWMT
    #if (PWM_FEATURE_OPWMT == STD_ON)

            } else {

                /* OPWMT */
    /** @file eMIOS_Pwm_LLD.c
                @note Violates MISRA 2004 Advisory Rule 10.3, 11.1 :
                      See @ref eMIOS_Pwm_LLD_C_REF_6, eMIOS_Pwm_LLD_C_REF_7
                */
                /*lint -save -e960, -e923 */
                REG_WRITE32
                (
                    ChannelAddr + EMIOS_ALTA_OFFSET,
                    (uint32)(PwmEmiosSpecificParam->Pwm_TriggerDelay + (uint32)1U)
                );
                /*lint -restore  */
                /* FLAG assigned to DMA request */
    /** @file eMIOS_Pwm_LLD.c
                @note Violates MISRA 2004 Advisory Rule 11.1 : See @ref eMIOS_Pwm_LLD_C_REF_7
                */
                /*lint -save -e923 */
                REG_BIT_SET32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_DMA_MASK );
                /* FLAG event enabled  */
                REG_BIT_SET32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_FEN_MASK );
                /*lint -restore  */
            }
    #endif
#endif

    /** @file eMIOS_Pwm_LLD.c
            @note Violates MISRA 2004 Advisory Rule 11.1 : See @ref eMIOS_Pwm_LLD_C_REF_7
            */
            /*lint -save -e923 */
            /* select the counter bus: internal / busA / bus diverse */
            REG_RMW32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_BSL_MASK, ctrlRegVal & CCR_BSL_MASK );

            /* set EDPOL */
            if (CCR_MODE_OPWFMB_FLAG_B == (ctrlRegVal & CCR_MODE_MASK)) {
                /* OPWFMB */
                if (PWM_HIGH == PwmChannel->Pwm_Polarity) {
                    REG_BIT_CLEAR32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_EDPOL_MASK );
                } else {
                    REG_BIT_SET32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_EDPOL_MASK );
                }
            } else {
                /* OPWMB */
                if (PWM_HIGH == PwmChannel->Pwm_Polarity) {
                    REG_BIT_SET32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_EDPOL_MASK );
                } else {
                    REG_BIT_CLEAR32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_EDPOL_MASK );
                }
            }

            /* set mode */
            REG_RMW32
            (
                ChannelAddr + EMIOS_CCR_OFFSET,
                CCR_MODE_MASK,
                ctrlRegVal & CCR_MODE_MASK
            );

            /* force match on the first edge - this also sets the signal level */
            if (CCR_MODE_OPWFMB_FLAG_B == ((uint32)ctrlRegVal & CCR_MODE_MASK)) {

                /* OPWFMB */
                REG_BIT_SET32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_FORCMB_MASK ); /* force match B */
            } else {

                /* OPWMB / OPWMT */
                /* do not force event A for OPWMB/OPWMT and 0% duty */
                if (((uint16)0x0000 != DutyCycle) && (0x0U != tempDuty)) {
                    /* force match A */
                    REG_BIT_SET32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_FORCMA_MASK );
                } else {
                    /* force match B */
                    REG_BIT_SET32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_FORCMB_MASK );
                }
            }

            if (PWM_BUS_INTERNAL_COUNTER == ((uint32)ctrlRegVal & PWM_BUS_MASK)) {
                /* set the prescaler divide value */
                REG_RMW32(ChannelAddr + EMIOS_CCR_OFFSET, CCR_UCPRE_MASK,ctrlRegVal&CCR_UCPRE_MASK);
                /* enable prescaler - this will start the internal counter */
                REG_BIT_SET32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_UCPREN_MASK );
            }
            /*lint -restore  */


        } /* end if EMIOS channel */

    } /* end for */

}



/**
@brief   This function deinitializes all eMIOS channels assigned to PWM
@details This function
         - sets the channel output to the configured Idle state
         - Reset Timer control register, Internal Counter, A, B registers
         - clears the (pending) interrupt flag corresponding to Emios channel

@remarks Covers PWM011, PWM012, PWM062

@remarks Implements DPWM03001
*/
#if (PWM_DE_INIT_API == STD_ON)
FUNC (void, PWM_CODE) EMIOS_Pwm_LLD_DeInit(void)
{

    VAR(Pwm_ChannelType, AUTOMATIC) ch = (Pwm_ChannelType ) 0;

    /* Pwm channel generic parameters from config structure */
    P2CONST(Pwm_ChannelConfigType, AUTOMATIC, PWM_APPL_CONST) PwmChannel = NULL_PTR;
    /* Pwm channel Emios specific parameters from config structure */
    P2CONST(Pwm_EMIOS_ChannelConfigType, AUTOMATIC, PWM_APPL_CONST) PwmEmiosSpecificParam= NULL_PTR;

    VAR(Pwm_ChannelType, AUTOMATIC) hw_ch; /* hw channel */

    VAR(Pwm_ChannelType, AUTOMATIC) mIdx;   /*  assigned eMIOS HW module  index */
    VAR(Pwm_ChannelType, AUTOMATIC) chIdx;  /*  assigned eMIOS HW channel index */

    VAR(uint32, AUTOMATIC) ModuleAddr;
    VAR(uint32, AUTOMATIC) ChannelAddr;



    for (ch = 0U; ch < Pwm_EMIOS_Cfg->ChannelCount; ch++)
    {
   /* only handle EMIOS channels */
    /** @file eMIOS_Pwm_LLD.c
         @note Violates MISRA 2004 Advisory Rule 17.4: See @ref eMIOS_Pwm_LLD_C_REF_11 */
   if (PWM_EMIOS_CHANNEL == Pwm_EMIOS_Cfg->ChannelsPtr[ch].IpType)
        {
            /* extract from conf structure the generic        channel information */
            PwmChannel = &Pwm_EMIOS_Cfg->ChannelsPtr[ch];

            /* extract from conf structure the EMIOS specific channel information */
            PwmEmiosSpecificParam =  &PwmChannel->SpecificCfg.EmiosCfg;

            ModuleAddr = PwmEmiosSpecificParam->Pwm_Emios_ModuleAddr;
            ChannelAddr = PwmEmiosSpecificParam->Pwm_Emios_ChannelAddr;

            /* store the associated hw channel ID */
            hw_ch = PwmEmiosSpecificParam->Pwm_HwChannelID;


            mIdx  = (uint8)(hw_ch >> EMIOS_MOD_SHIFT);
            chIdx = (uint8)(hw_ch &  EMIOS_CH_MASK);


            /* set the channel output to the configured Idle state */
    /** @file eMIOS_Pwm_LLD.c
            @note Violates MISRA 2004 Advisory Rule 11.1 : See @ref eMIOS_Pwm_LLD_C_REF_7
            */
            /*lint -save -e923 */
            if (PWM_HIGH == PwmChannel->Pwm_IdleState) {
                REG_BIT_SET32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_EDPOL_MASK );
            }
            else {
                REG_BIT_CLEAR32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_EDPOL_MASK );
            }

            /* enter GPIO ouput mode - this will set the ouput pin to the EDPOL value */
            REG_RMW32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_MODE_MASK, CCR_MODE_GPO );

            /* Reset Timer control register - except mode and edpol to keep channel
                                              in output idle mode */
            /* Internal Counter is also cleared when entering GPIO Mode */
            REG_BIT_CLEAR32( ChannelAddr + EMIOS_CCR_OFFSET, (~(CCR_EDPOL_MASK | CCR_MODE_MASK)) );



            REG_BIT_CLEAR32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_FEN_MASK ); /* disable interrupt */
            /*lint -restore  */

            REG_WRITE32( ChannelAddr + EMIOS_CCR_OFFSET, CSR_FLAG_BIT ); /* clear interrupt flag */

            /* reset A,B regs 0 */
            REG_WRITE32( ChannelAddr + EMIOS_CCR_OFFSET , 0U ); /* write A register */
            REG_WRITE32( ChannelAddr + EMIOS_CCR_OFFSET , 0U ); /* write B register */

            /* only write UCDIS register if it's available */
    #ifdef EMIOS_UCDIS
            /* disable unified channel */
            REG_BIT_SET32( (ModuleAddr+EMIOS_UCDIS_OFFSET), (uint32)((uint32)1<<(chIdx)) );
    #endif

            /* reset stored period value */
            Pwm_EMIOS_LLD_Period[ hw_ch ]=0U;

    #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
            /* invalidate the reverse hardware channel 2 logical channel map */
            Pwm_EMIOS_LLD_RevHardwareTable[ hw_ch ] = (Pwm_ChannelType)0xFFU;
            /* notifications disabled */
            Pwm_EMIOS_LLD_Notifications[ hw_ch ] = 0xFFU;
    #endif

        } /* end if emios channel */

    } /* end for */

    /* invalidate EMIOS LLD top level private config pointer */
    Pwm_EMIOS_Cfg = NULL_PTR;

}
#endif


/**
@brief   This function sets the dutycycle for the specified eMIOS channel
@details This function:
         - disable the interrupt and clear the interrupt flag
         - sets the A register with value 0 for OPWFMB mode for 0% dutycycle
         - sets the A and B registers with value 0 for OPWMB mode for 0% dutycycle
         - sets the A and B registers with value 1 for OPWMT mode for 0% dutycycle
         - sets the A register with value period for OPWFMB mode for 100% dutycycle
         - sets the A register with 0 and B register with period for OPWMB mode for
           100% dutycycle
         - sets the A register with 1 and B register with period+1 for OPWMT mode for
           100% dutycycle
         - for dutycycle not equal to 0% and 100%, FLAG event is enabled
         - sets the A register with value dutycycle for OPWFMB mode
         - sets the A register with value offset+1 and B register with dutycycle+offset
           for OPWMB mode
         - sets the A register with value offset+1 and B register with
           (dutycycle + offset) % period for OPWMT mode

@param[in]     LogicalChannelNumber - pwm channel id
@param[in]     DutyCycle     - pwm dutycycle value 0x0000 for 0% ... 0x8000 for 100%
@param[in]     useSection    - critical section for logical channel
@note      EMIOS_Pwm_LLD_SetDutyCycle is used by EMIOS_Pwm_LLD_SetCounterBus
           it is enabled when at least one of the APIs is enabled

@remarks Covers PWM013, PWM014, PWM016, PWM024, PWM058, PWM059, PWM062, PWM082, PWM086

@remarks Implements DPWM03006
*/
#if ((PWM_SET_DUTY_CYCLE_API == STD_ON) || (PWM_SETCOUNTERBUS_API == STD_ON))
FUNC (void, PWM_CODE) EMIOS_Pwm_LLD_SetDutyCycle
                      (
                          VAR(Pwm_ChannelType, AUTOMATIC) LogicalChannelNumber,
                          VAR(uint16, AUTOMATIC) DutyCycle,
                          VAR(uint8,  AUTOMATIC) useSection
                      )
{

    VAR(Pwm_PeriodType, AUTOMATIC) Period;
    VAR(Pwm_PeriodType, AUTOMATIC) tempDuty;
    VAR(uint32, AUTOMATIC) tempDuty32;

    /* Pwm channel generic parameters from config structure */
    P2CONST(Pwm_ChannelConfigType, AUTOMATIC, PWM_APPL_CONST) PwmChannel = NULL_PTR;
    /* Pwm channel Emios specific parameters from config structure */
    P2CONST(Pwm_EMIOS_ChannelConfigType, AUTOMATIC, PWM_APPL_CONST) PwmEmiosSpecificParam= NULL_PTR;

    VAR(Pwm_EmiosCtrlParamType, AUTOMATIC) ctrlRegVal;

    VAR(Pwm_ChannelType, AUTOMATIC) hw_ch; /* hw channel */

    VAR(Pwm_ChannelType, AUTOMATIC) mIdx;  /*  assigned eMIOS HW module  index */
    VAR(Pwm_ChannelType, AUTOMATIC) chIdx; /*  assigned eMIOS HW channel index */

    VAR(uint32, AUTOMATIC) ModuleAddr;
    VAR(uint32, AUTOMATIC) ChannelAddr;

    VAR(uint16, AUTOMATIC) Offset;
    VAR(uint16, AUTOMATIC) Trigger_Delay;


    if ((uint8)STD_ON == useSection) {
        /* start critical section for logical channel */
        SchM_Enter_Pwm(SCHM_PWM_INSTANCE_0, LogicalChannelNumber);
    }
     /* extract from conf structure the generic        channel information */
        /** @file eMIOS_Pwm_LLD.c
           @note Violates MISRA 2004 Advisory Rule 17.4: See @ref eMIOS_Pwm_LLD_C_REF_11 */
    PwmChannel = &Pwm_EMIOS_Cfg->ChannelsPtr[LogicalChannelNumber];

    /* extract from conf structure the EMIOS specific channel information */
    PwmEmiosSpecificParam =  &PwmChannel->SpecificCfg.EmiosCfg;

    ModuleAddr = PwmEmiosSpecificParam->Pwm_Emios_ModuleAddr;
    ChannelAddr = PwmEmiosSpecificParam->Pwm_Emios_ChannelAddr;


    /* store the associated hw channel ID */
    hw_ch = PwmEmiosSpecificParam->Pwm_HwChannelID;


    mIdx  = (uint8)(hw_ch >> EMIOS_MOD_SHIFT);
    chIdx = (uint8)(hw_ch &  EMIOS_CH_MASK);


    /* save current channel control register config value in local variable */
    ctrlRegVal = PwmEmiosSpecificParam->Pwm_ParamValue;

    /* get period for current channel */
    Period = Pwm_EMIOS_LLD_Period[ hw_ch ];
    #ifdef PWM_FEATURE_OPWMT
        #if (PWM_FEATURE_OPWMT == STD_ON)
            if ((Period != Pwm_PeriodInit[hw_ch])
                && ((PwmEmiosSpecificParam->Pwm_OffsetTriggerDelayAdjust) == (boolean)TRUE))
            {
                /* Adjust the Offset and Trigger Delay if the frequency is modified */
                Offset =
                    (uint16) ((uint16)(PwmEmiosSpecificParam->Pwm_Offset * Period) /
                              Pwm_PeriodInit[hw_ch]);
                Trigger_Delay =
                    (uint16) ((uint16)(Pwm_Current_TriggerDelay[hw_ch] * Period) /
                              (uint16)Pwm_PeriodInit[hw_ch]);
            }
            else
            {
                Offset = PwmEmiosSpecificParam->Pwm_Offset;
                Trigger_Delay =(uint16)(Pwm_Current_TriggerDelay[hw_ch]);
            }
        #endif
    #endif

    tempDuty = EMIOS_PWM_LLD_ComputeDutycycle(Period, DutyCycle);



    if (((uint16)0x0000 == DutyCycle) || (0x0U == tempDuty))
    {

    #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)

        Pwm_EMIOS_LLD_DutyState[ hw_ch ] = 0U; /* no transitions in the signal */

        #ifdef PWM_FEATURE_OPWMT
            #if (PWM_FEATURE_OPWMT == STD_ON)
        if (CCR_MODE_OPWMT != (ctrlRegVal & CCR_MODE_MASK)) {
            #endif
        #endif

            /* at 0% dutycycle no edges are present in the output signal
                thus no notifications */
            REG_BIT_CLEAR32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_FEN_MASK ); /* disable interrupt */
            /* clear interrupt flag */
            REG_WRITE32( ChannelAddr + EMIOS_CSR_OFFSET, CSR_FLAG_BIT );

        #ifdef PWM_FEATURE_OPWMT
            #if (PWM_FEATURE_OPWMT == STD_ON)
        }
            #endif
        #endif

    #endif

        if (CCR_MODE_OPWFMB_FLAG_B == (ctrlRegVal & CCR_MODE_MASK)) {
            /* OPWFMB */
            REG_WRITE32( ChannelAddr + EMIOS_CADR_OFFSET , 0U ); /* write A register */

        } else

    #ifdef PWM_FEATURE_OPWMT
        #if (PWM_FEATURE_OPWMT == STD_ON)
            if (CCR_MODE_OPWMB_FLAG_B == (ctrlRegVal & CCR_MODE_MASK))
        #endif
    #endif

        {
            /* OPWMB */
    /** @file eMIOS_Pwm_LLD.c
            @note Violates MISRA 2004 Advisory Rule 10.1 : See @ref eMIOS_Pwm_LLD_C_REF_3
            */
            /*lint -save -e960 */
            EMIOS_LLD_UpdateChannel_AB(mIdx, chIdx, (uint32)0U, (uint32)0U,ChannelAddr,ModuleAddr);
            /*lint -restore  */
        }

    #ifdef PWM_FEATURE_OPWMT
        #if (PWM_FEATURE_OPWMT == STD_ON)
        else {
            /* OPWMT */
/** @file eMIOS_Pwm_LLD.c
            @note Violates MISRA 2004 Advisory Rule 10.1 :
                  See @ref eMIOS_Pwm_LLD_C_REF_3
            */
            /*lint -save -e960 */
            EMIOS_LLD_UpdateChannel_AB(mIdx, chIdx, (uint32)1U, (uint32)1U,ChannelAddr,ModuleAddr);
            /*lint -restore  */
        }
        #endif
    #endif

    }
    else if (PWM_DUTY_CYCLE_100 == DutyCycle)
    {

    #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)

        Pwm_EMIOS_LLD_DutyState[ hw_ch ] = 0U; /* no transitions in the signal */

        #ifdef PWM_FEATURE_OPWMT
            #if (PWM_FEATURE_OPWMT == STD_ON)
        if (CCR_MODE_OPWMT != (ctrlRegVal & CCR_MODE_MASK)) {
            #endif
        #endif
            /* at 100% dutycycle no edges are present in the output signal
               thus no notifications */
            /* disable interrupt */
            REG_BIT_CLEAR32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_FEN_MASK );
            /* clear interrupt flag */
            REG_WRITE32( ChannelAddr + EMIOS_CSR_OFFSET , CSR_FLAG_BIT );

        #ifdef PWM_FEATURE_OPWMT
            #if (PWM_FEATURE_OPWMT == STD_ON)
        }
            #endif
        #endif

    #endif


        if (CCR_MODE_OPWFMB_FLAG_B == (ctrlRegVal & CCR_MODE_MASK)) {
            /* OPWFMB */
            REG_WRITE32( ChannelAddr + EMIOS_CADR_OFFSET , Period ); /* write A register */
        } else

    #ifdef PWM_FEATURE_OPWMT
        #if (PWM_FEATURE_OPWMT == STD_ON)
        if (CCR_MODE_OPWMB_FLAG_B == (ctrlRegVal & CCR_MODE_MASK))
        #endif
    #endif

        {
            /* OPWMB */
    /** @file eMIOS_Pwm_LLD.c
            @note Violates MISRA 2004 Advisory Rule 10.1 :
                  See @ref eMIOS_Pwm_LLD_C_REF_3
            */
            /*lint -save -e960 */
            EMIOS_LLD_UpdateChannel_AB
            (
                mIdx,
                chIdx,
                (uint32)0U,
                (uint32)Period,
                ChannelAddr,
                ModuleAddr
            );
            /*lint -restore  */
        }

    #ifdef PWM_FEATURE_OPWMT
        #if (PWM_FEATURE_OPWMT == STD_ON)
        else {
            /* OPWMT */
    /** @file eMIOS_Pwm_LLD.c
            @note Violates MISRA 2004 Advisory Rule 10.1 :
                  See @ref eMIOS_Pwm_LLD_C_REF_3
            */
            /*lint -save -e960 */
            EMIOS_LLD_UpdateChannel_AB
            (
                mIdx,
                chIdx,
                (uint32)1U,
                (uint32)(Period+(uint32)1U),
                ChannelAddr,
                ModuleAddr
            );
            /*lint -restore  */
        }
        #endif
    #endif

    } else
    {
        /* != (0%, 100%) */

    #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
        /*  transitions available in the signal */
        Pwm_EMIOS_LLD_DutyState[ hw_ch ] = 1U;

        #ifdef PWM_FEATURE_OPWMT
            #if (PWM_FEATURE_OPWMT == STD_ON)
        if (CCR_MODE_OPWMT != (ctrlRegVal & CCR_MODE_MASK)) {
            #endif
        #endif

            /* if notifications are enabled and the dutycycle in
             * the next period is != 0%,100% (we have edges)
             * thus enable notifications - this is for the case when
             * we are coming from duty 0%,100% where
             * the notifications are disabled because we have no edges there
             */
            if (0xFFU != Pwm_EMIOS_LLD_Notifications[ hw_ch ]) {
                /* FLAG event enabled */
                REG_BIT_SET32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_FEN_MASK );
            }

        #ifdef PWM_FEATURE_OPWMT
            #if (PWM_FEATURE_OPWMT == STD_ON)
        }
            #endif
        #endif

    #endif

        if (CCR_MODE_OPWFMB_FLAG_B == (ctrlRegVal & CCR_MODE_MASK)) { /* OPWFMB */
            /* write A register */
            REG_WRITE32( ChannelAddr + EMIOS_CADR_OFFSET , (tempDuty) );
        } else

    #ifdef PWM_FEATURE_OPWMT
        #if (PWM_FEATURE_OPWMT == STD_ON)
        if (CCR_MODE_OPWMB_FLAG_B == (ctrlRegVal & CCR_MODE_MASK))
        #endif
    #endif

        { /* OPWMB */

            tempDuty32 = (uint32)tempDuty + PwmEmiosSpecificParam->Pwm_Offset;

    #if (PWM_DEV_ERROR_DETECT == STD_ON)

            /* check that the configured channel Offset parameter combined
             * with the Dutycycle will not program event B in time after
             * the period - leading to unexpected behavior -
             * signal will take the value of EDPOL ( = signal polarity )
             * This can happen only if Pwm_Offset != 0 because
             * the Dutycycle formula limits event B
             * to [0, Period];
             * In this case (Pwm_Offset != 0) 100% dutycycle is impossible
             * to reach
             */
            if (tempDuty32 >= Period) {

                Det_ReportError
                (
                    (uint16) PWM_MODULE_ID,
                    (uint8)0,
                    (uint8)PWM_SETDUTYCYCLE_ID,
                    (uint8)PWM_E_OPWMB_CHANNEL_OFFSET_DUTYCYCLE_RANGE
                );

                /*
                 * force event B equal with Period
                 */
    /** @file eMIOS_Pwm_LLD.c
                @note Violates MISRA 2004 Advisory Rule 10.1 :
                      See @ref eMIOS_Pwm_LLD_C_REF_3
                */
                /*lint -save -e960 */
                EMIOS_LLD_UpdateChannel_AB
                (
                    mIdx,
                    chIdx,
                    (uint32)(PwmEmiosSpecificParam->Pwm_Offset + (uint32)1U),
                    (uint32)Period,
                    ChannelAddr,
                    ModuleAddr
                );
                /*lint -restore  */

            }
            else
    #endif
            {
    /** @file eMIOS_Pwm_LLD.c
                @note Violates MISRA 2004 Advisory Rule 10.1 :
                      See @ref eMIOS_Pwm_LLD_C_REF_3
                */
                /*lint -save -e960 */
                EMIOS_LLD_UpdateChannel_AB
                (
                    mIdx,
                    chIdx,
                    (uint32)(PwmEmiosSpecificParam->Pwm_Offset + (uint32)1U),
                    (uint32)tempDuty32,
                    ChannelAddr,
                    ModuleAddr
                );
                /*lint -restore  */
            }
        }

    #ifdef PWM_FEATURE_OPWMT
        #if (PWM_FEATURE_OPWMT == STD_ON)
        else {  /* OPWMT */
            #if (PWM_CHANGE_REGISTER_A_SWITCH == STD_ON)
            {
                /* register A is updated on dutycycle change */
                VAR(uint16, AUTOMATIC)  tempRegB;

                /* Calculate the B-register value */
                if (0 != PwmEmiosSpecificParam->Pwm_Offset)
                {
                    tempRegB = (
                                    Period
                                    -
                                    PwmEmiosSpecificParam->Pwm_Offset
                               ) + 1U;
                }
                else
                {
                    tempRegB = (uint16)1U;
                }

                /* Calculate the A-register value */
                if (tempRegB > tempDuty)
                {
                    tempDuty = tempRegB - tempDuty;
                }
                else
                {
                    tempDuty = (Period - tempDuty) + (tempRegB - 1);
                }

    /** @file eMIOS_Pwm_LLD.c
                @note Violates MISRA 2004 Advisory Rule 10.1 :
                      See @ref eMIOS_Pwm_LLD_C_REF_3
                */
                /*lint -save -e960 */
                EMIOS_LLD_UpdateChannel_AB
                (
                    mIdx,
                    chIdx,
                    (uint32)tempDuty,
                    (uint32)tempRegB,
                    ChannelAddr,
                    ModuleAddr
                );
                /*lint -restore  */
            }
            #else
            /* register B is updated on dutycycle change */
            tempDuty32 = (
                             (uint32) tempDuty
                             +
                             PwmEmiosSpecificParam->Pwm_Offset
                         ) % Period ;

            /* if (tempDuty + Pwm_Offset == Period) then
             * tempDuty32 will be 0
             * if the reference channel is MCB/OPWFMB then
             * we have [ 0x1, Period ]
             * if we program regB with 0 a compare event will
             * never be generated
             * in this case we program the Period value instead
             * and accept an error equal with 1 tick.
             */
            if ( 0x0U == tempDuty32 ) {

                tempDuty32 = Period;
            }

    /** @file eMIOS_Pwm_LLD.c
            @note Violates MISRA 2004 Advisory Rule 10.1 :
                  See @ref eMIOS_Pwm_LLD_C_REF_3
            */
            /*lint -save -e960 */
            EMIOS_LLD_UpdateChannel_AB
            (
                mIdx,
                chIdx,
                (uint32)(PwmEmiosSpecificParam->Pwm_Offset + (uint32)1U),
                (uint32)tempDuty32,
                ChannelAddr,
                ModuleAddr
            );
            /*lint -restore  */
            #endif

        }
        #endif
    #endif
    }


    /*
     * this part is needed only if Pwm_SetOutputToIdle is available
     */
    #if (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON)
    /* check if the channel had been put to idle state - restart the channel */

    if (CCR_MODE_GPO == (REG_READ32(ChannelAddr + EMIOS_CCR_OFFSET) & CCR_MODE_MASK)) {

        /* set EDPOL */
        if (CCR_MODE_OPWFMB_FLAG_B == (ctrlRegVal & CCR_MODE_MASK)) {
            /* set internal counter value to 1 -
               internal counter only used in OPWFMB mode for now */
            REG_WRITE32( ChannelAddr + EMIOS_CCNTR_OFFSET , 1);

            /* OPWFMB */
            if (PWM_HIGH == PwmChannel->Pwm_Polarity) {
                REG_BIT_CLEAR32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_EDPOL_MASK );
            } else {
                REG_BIT_SET32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_EDPOL_MASK );
            }
        } else {
            /* OPWMB */
            if (PWM_HIGH == PwmChannel->Pwm_Polarity) {
                REG_BIT_SET32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_EDPOL_MASK );
            } else {
                REG_BIT_CLEAR32(ChannelAddr + EMIOS_CCR_OFFSET, CCR_EDPOL_MASK );
            }
        }


        #ifdef PWM_FEATURE_OPWMT
            #if (PWM_FEATURE_OPWMT == STD_ON)
        /* in OPWMT there is no edge selection for trigger */
        if (CCR_MODE_OPWMT != (ctrlRegVal & CCR_MODE_MASK)) {
            #endif
        #endif

        #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
            {
                VAR(Pwm_EdgeNotificationType, AUTOMATIC) Notification =
                (Pwm_EdgeNotificationType)Pwm_EMIOS_LLD_Notifications[ hw_ch ];

                if ( 0xFFU != (uint8)Notification ) { /* if notifications enabled */

                    /* set notification edge in ctrlRegVal */

                    if (PWM_BOTH_EDGES == Notification) {
                        /* notification on both edges */
        /** @file eMIOS_Pwm_LLD.c
                        @note Violates MISRA 2004 Advisory Rule 11.4:See @ref eMIOS_Pwm_LLD_C_REF_10
                        */
                        /*lint -save -e929 */
                        REG_BIT_SET32( &ctrlRegVal, CCR_MODE_EDGE_SELECT_MASK );
                        /*lint -restore  */
                    }
                    else {
                        /* notification on period event */
        /** @file eMIOS_Pwm_LLD.c
                        @note Violates MISRA 2004 Advisory Rule 11.4:See @ref eMIOS_Pwm_LLD_C_REF_10
                        */
                        /*lint -save -e929 */
                        REG_BIT_CLEAR32( &ctrlRegVal, CCR_MODE_EDGE_SELECT_MASK );
                        /*lint -restore  */
                    }

                }
            }
        #endif

        #ifdef PWM_FEATURE_OPWMT
            #if (PWM_FEATURE_OPWMT == STD_ON)
        }
            #endif
        #endif

        /* set mode */
        REG_RMW32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_MODE_MASK, ctrlRegVal & CCR_MODE_MASK );

        /* force match on the first edge - this also sets the signal level */
        if (CCR_MODE_OPWFMB_FLAG_B == (ctrlRegVal & CCR_MODE_MASK)) {
            REG_BIT_SET32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_FORCMB_MASK ); /* force match B */
        } else {
            REG_BIT_SET32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_FORCMA_MASK ); /* force match A */
        }
    }
    #endif

    if ((uint8)STD_ON == useSection) {
        /* exit critical section for logical channel */
        SchM_Exit_Pwm(SCHM_PWM_INSTANCE_0, LogicalChannelNumber);
    }
}
#endif


/**
@brief   This function sets the period and the dutycycle for the specified eMIOS channel
@details This function is applicable for mode OPWFMB
         - disable the interrupt and clear the interrupt flag
         - sets the A register with value 0 and B register with period for 0% dutycycle
         - sets the A and B registers with value period for 100% dutycycle
         - for dutycycle not equal to 0% and 100% set the A register with value dutycycle
           and B register with value period

@param[in]     LogicalChannelNumber - pwm channel id
@param[in]     Period        - pwm signal period value
@param[in]     DutyCycle     - pwm dutycycle value 0x0000 for 0% ... 0x8000 for 100%

@remarks Covers PWM083, PWM062, PWM059, PWM086, PWM024, PWM076

@remarks Implements DPWM03008
*/
#if (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)
FUNC (void, PWM_CODE) EMIOS_Pwm_LLD_SetPeriodAndDuty
                      (
                          VAR(Pwm_ChannelType, AUTOMATIC) LogicalChannelNumber,
                          VAR(Pwm_PeriodType,  AUTOMATIC) Period,
                          VAR(uint16,          AUTOMATIC) DutyCycle
                      )
{

    /* Pwm channel generic parameters from config structure */
    P2CONST(Pwm_ChannelConfigType, AUTOMATIC, PWM_APPL_CONST) PwmChannel = NULL_PTR;
    /* Pwm channel Emios specific parameters from config structure */
    P2CONST(Pwm_EMIOS_ChannelConfigType, AUTOMATIC, PWM_APPL_CONST) PwmEmiosSpecificParam= NULL_PTR;

    VAR(Pwm_EmiosCtrlParamType, AUTOMATIC) ctrlRegVal;

    VAR(Pwm_PeriodType, AUTOMATIC) tempDuty;

    VAR(Pwm_ChannelType, AUTOMATIC) hw_ch; /* hw channel */

    VAR(Pwm_ChannelType, AUTOMATIC) mIdx;   /*  assigned eMIOS HW module  index */
    VAR(Pwm_ChannelType, AUTOMATIC) chIdx;  /*  assigned eMIOS HW channel index */
    VAR(uint32, AUTOMATIC) ModuleAddr;
    VAR(uint32, AUTOMATIC) ChannelAddr;

    VAR(uint16, AUTOMATIC) Offset;
    VAR(uint16, AUTOMATIC) Trigger_Delay;
        /* start critical section for logical channel */
    SchM_Enter_Pwm(SCHM_PWM_INSTANCE_0, LogicalChannelNumber);
    /* extract from conf structure the generic        channel information */
    /** @file eMIOS_Pwm_LLD.c
           @note Violates MISRA 2004 Advisory Rule 17.4: See @ref eMIOS_Pwm_LLD_C_REF_11 */
    PwmChannel = &Pwm_EMIOS_Cfg->ChannelsPtr[LogicalChannelNumber];

    /* extract from conf structure the EMIOS specific channel information */
    PwmEmiosSpecificParam = &PwmChannel->SpecificCfg.EmiosCfg;

    ModuleAddr = PwmEmiosSpecificParam->Pwm_Emios_ModuleAddr;
    ChannelAddr = PwmEmiosSpecificParam->Pwm_Emios_ChannelAddr;



    /* store the associated hw channel ID */
    hw_ch = PwmEmiosSpecificParam->Pwm_HwChannelID;


    mIdx  = (uint8)( hw_ch >> EMIOS_MOD_SHIFT);
    chIdx = (uint8)( hw_ch &  EMIOS_CH_MASK);


    /* save current channel control register config value in local variable */
    ctrlRegVal = PwmEmiosSpecificParam->Pwm_ParamValue;

    /* only makes sense for OPWFMB as OPWMB/OPWMT channels get their period
       from the selected UC */
    if (CCR_MODE_OPWFMB_FLAG_B == (ctrlRegVal & CCR_MODE_MASK))
    {
        /* save new period value */
        Pwm_EMIOS_LLD_Period[ hw_ch ] = Period;
    #ifdef PWM_FEATURE_OPWMT
        #if (PWM_FEATURE_OPWMT == STD_ON)
            if ((Period != Pwm_PeriodInit[hw_ch])
                && ((PwmEmiosSpecificParam->Pwm_OffsetTriggerDelayAdjust) == (boolean)TRUE))
            {
                /* Adjust the Offset and Trigger Delay if the frequency is modified */
                Offset =
                    (uint16) ((PwmEmiosSpecificParam->Pwm_Offset * Period) /
                              Pwm_PeriodInit[hw_ch]);
                Trigger_Delay =
                    (uint16) ((uint16)(Pwm_Current_TriggerDelay[hw_ch] * Period) /
                              (uint16)Pwm_PeriodInit[hw_ch]);
            }
            else
            {
                Offset = PwmEmiosSpecificParam->Pwm_Offset;
                Trigger_Delay = (uint16)Pwm_Current_TriggerDelay[hw_ch];
            }
        #endif
    #endif

        tempDuty = EMIOS_PWM_LLD_ComputeDutycycle(Period, DutyCycle);

        /* Duty Cycle and Period update */
        if (((uint16)0x0000 == DutyCycle) || (0x0U == tempDuty))
        {

            #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)

                Pwm_EMIOS_LLD_DutyState[ hw_ch ] = 0U; /* no transitions in the signal */

                /* at 0% dutycycle no edges are present in
                   the output signal thus no notifications */
                /* disable interrupt */
                REG_BIT_CLEAR32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_FEN_MASK );
                /* clear interrupt flag */
                REG_WRITE32( ChannelAddr + EMIOS_CSR_OFFSET, CSR_FLAG_BIT );

            #endif

            /* 0%, RegA = 0 */
    /** @file eMIOS_Pwm_LLD.c
            @note Violates MISRA 2004 Advisory Rule 10.1 : See @ref eMIOS_Pwm_LLD_C_REF_3
            */
            /*lint -save -e960 */
            EMIOS_LLD_UpdateChannel_AB
            (
                mIdx,
                chIdx,
                (uint32)0U,
                (uint32)Period,
                ChannelAddr,
                ModuleAddr
            );
            /*lint -restore  */
        }
        else if (PWM_DUTY_CYCLE_100 == DutyCycle)
        {
            #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
            /* no transitions in the signal */
            Pwm_EMIOS_LLD_DutyState[ hw_ch ] = 0U;

            /* at 100% dutycycle no edges are present in
               the output signal thus no notifications */
            /* disable interrupt */
            REG_BIT_CLEAR32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_FEN_MASK );
            /* clear interrupt flag */
            REG_WRITE32( ChannelAddr + EMIOS_CSR_OFFSET, CSR_FLAG_BIT );

            #endif

            /* 100%, A = B */
            /**
            @note Violates MISRA 2004 Advisory Rule 10.1 : See @ref eMIOS_Pwm_LLD_C_REF_3
            */
            /*lint -save -e960 */
            EMIOS_LLD_UpdateChannel_AB
            (
                mIdx,
                chIdx,
                (uint32)Period,
                (uint32)Period,
                ChannelAddr,
                ModuleAddr
            );
            /*lint -restore  */
        }
        else
        {   /* != 0%, 100% */

            #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
            /*  transitions available in the signal */
            Pwm_EMIOS_LLD_DutyState[ hw_ch ] = 1U;

            /* if notifications are enabled and the dutycycle
             * in the next period is != 0%,100% (we have edges)
             * thus enable notifications - this is for the case
             * when we are coming from duty 0%,100% where
             * the notifications are disabled because we have no edges there
             */
            if (Pwm_EMIOS_LLD_Notifications[ hw_ch ] != 0xFFU) {
            /* FLAG event enabled */
                REG_BIT_SET32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_FEN_MASK );
            }

            #endif

    /** @file eMIOS_Pwm_LLD.c
            @note Violates MISRA 2004 Advisory Rule 10.1 :
                  See @ref eMIOS_Pwm_LLD_C_REF_3
            */
            /*lint -save -e960 */
            EMIOS_LLD_UpdateChannel_AB
            (
                mIdx,
                chIdx,
                (uint32)tempDuty,
                (uint32)Period,
                ChannelAddr,
                ModuleAddr
            );
            /*lint -restore  */
        }

        /*
         * this part is needed only if Pwm_SetOutputToIdle is available
         */
        #if (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON)

        /* check if the channel had been put to idle state - restart the channel */

        if (CCR_MODE_GPO == (REG_READ32(ChannelAddr + EMIOS_CCR_OFFSET) & CCR_MODE_MASK)) {

            /* set internal counter value to 1 - internal counter only used in
            * OPWFMB mode for now
            * we need to set it to 1 in order to avoid the case when
            * the channel is started with
            * register value B less than the counter value -
            * in this case will have to wait until
            * the counter reaches 0xFFFF
            */
            REG_WRITE32( EMIOS_CCNTR(mIdx, chIdx), 1); /* set internal counter to 1 */


            /* set EDPOL */
            if (PWM_HIGH == PwmChannel->Pwm_Polarity) {
                REG_BIT_CLEAR32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_EDPOL_MASK );
            } else {
                REG_BIT_SET32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_EDPOL_MASK );
            }


            #ifdef PWM_FEATURE_OPWMT
                #if (PWM_FEATURE_OPWMT == STD_ON)
                    /* in OPWMT there is no edge selection for trigger */
            if (CCR_MODE_OPWMT != (ctrlRegVal & CCR_MODE_MASK)) {
                #endif
            #endif

            #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
                {
                    VAR(Pwm_EdgeNotificationType, AUTOMATIC) Notification =
                    (Pwm_EdgeNotificationType)Pwm_EMIOS_LLD_Notifications[ hw_ch ];

                    if ( 0xFFU != (uint8)Notification ) { /* if notifications enabled */

                        /* set notification edge in ctrlRegVal */

                        if (PWM_BOTH_EDGES == Notification) {
                        /* notification on both edges */
        /** @file eMIOS_Pwm_LLD.c
                            @note Violates MISRA 2004 Advisory Rule 11.4 :
                                  See @ref eMIOS_Pwm_LLD_C_REF_10
                            */
                            /*lint -save -e929 */
                            REG_BIT_SET32( &ctrlRegVal, CCR_MODE_EDGE_SELECT_MASK );
                            /*lint -restore  */
                        }
                        else {
                            /* notification on both edges */
                            /* notification on period event */
                            /* notification on both edges */
        /** @file eMIOS_Pwm_LLD.c
                            @note Violates MISRA 2004 Advisory Rule 11.4 :
                                  See @ref eMIOS_Pwm_LLD_C_REF_10
                            */
                            /*lint -save -e929 */
                            REG_BIT_CLEAR32( &ctrlRegVal, CCR_MODE_EDGE_SELECT_MASK );
                            /*lint -restore  */
                        }
                    }
                }
            #endif

            #ifdef PWM_FEATURE_OPWMT
                #if (PWM_FEATURE_OPWMT == STD_ON)
            }
                #endif
            #endif

            /* set mode */
            REG_RMW32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_MODE_MASK, ctrlRegVal&CCR_MODE_MASK );

            /* force match on the first edge - this also sets the signal level */
            REG_BIT_SET32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_FORCMB_MASK ); /* force match B */

        }
        #endif

    }

    /* exit critical section for logical channel */
    SchM_Exit_Pwm(SCHM_PWM_INSTANCE_0, LogicalChannelNumber);

}
#endif


/**
@brief   This function sets the generated eMIOS channel to the idle value configured
@details This function
         - puts the channel in High or Low state by writing to the Control Register
           based on the configured Idle state
         - puts the Emios channel into GPIO mode

@param[in]     LogicalChannelNumber - pwm channel id

@remarks Covers PWM084, PWM062, PWM021

@remarks Implements DPWM03007
*/
#if (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON)
FUNC (void, PWM_CODE) EMIOS_Pwm_LLD_SetOutputToIdle
                      (
                          VAR(Pwm_ChannelType, AUTOMATIC) LogicalChannelNumber
                      )
{

    /* Pwm channel generic parameters from config structure */
    P2CONST(Pwm_ChannelConfigType, AUTOMATIC, PWM_APPL_CONST) PwmChannel = NULL_PTR;
    /* Pwm channel Emios specific parameters from config structure */
    P2CONST(Pwm_EMIOS_ChannelConfigType, AUTOMATIC, PWM_APPL_CONST) PwmEmiosSpecificParam= NULL_PTR;

    VAR(Pwm_ChannelType, AUTOMATIC) hw_ch; /* hw channel */

    VAR(Pwm_ChannelType, AUTOMATIC) mIdx;   /*  assigned eMIOS HW module  index */
    VAR(Pwm_ChannelType, AUTOMATIC) chIdx;  /*  assigned eMIOS HW channel index */
    VAR(uint32, AUTOMATIC) ModuleAddr;
    VAR(uint32, AUTOMATIC) ChannelAddr;

    /* start critical section for logical channel */
    SchM_Enter_Pwm(SCHM_PWM_INSTANCE_0, LogicalChannelNumber);

    /* extract from conf structure the generic        channel information */
    /** @file eMIOS_Pwm_LLD.c
           @note Violates MISRA 2004 Advisory Rule 17.4: See @ref eMIOS_Pwm_LLD_C_REF_11 */
    PwmChannel = &Pwm_EMIOS_Cfg->ChannelsPtr[ LogicalChannelNumber ];

    /* extract from conf structure the EMIOS specific channel information */
    PwmEmiosSpecificParam =  &PwmChannel->SpecificCfg.EmiosCfg;

    ModuleAddr = PwmEmiosSpecificParam->Pwm_Emios_ModuleAddr;
    ChannelAddr = PwmEmiosSpecificParam->Pwm_Emios_ChannelAddr;


    /* store the associated hw channel ID */
    hw_ch = PwmEmiosSpecificParam->Pwm_HwChannelID;


    mIdx  = (uint8)(hw_ch >> EMIOS_MOD_SHIFT);
    chIdx = (uint8)(hw_ch &  EMIOS_CH_MASK);

    /* Put the channel in Idle state */
    if ( PWM_HIGH == PwmChannel->Pwm_IdleState ) {
        REG_BIT_SET32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_EDPOL_MASK );
    }
    else {
        REG_BIT_CLEAR32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_EDPOL_MASK );
    }


    REG_RMW32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_MODE_MASK, CCR_MODE_GPO );

    /* exit critical section for logical channel */
    SchM_Exit_Pwm(SCHM_PWM_INSTANCE_0, LogicalChannelNumber);

}
#endif


/**
@brief   This function returns the pwm signal output state
@details This function returns the PWM Channel state as High or Low

@param[in]     LogicalChannelNumber - pwm channel id

@return        Pwm_OutputStateType - pwm signal output logic value
               - PWM_LOW - The output state of PWM channel is low
               - PWM_HIGH - The output state of PWM channel is high

@remarks Covers PWM085, PWM062, PWM022

@remarks Implements DPWM03004
*/
#if (PWM_GET_OUTPUT_STATE_API == STD_ON)
FUNC (Pwm_OutputStateType, PWM_CODE) EMIOS_Pwm_LLD_GetOutputState
                                     (
                                         VAR(Pwm_ChannelType, AUTOMATIC) LogicalChannelNumber
                                     )
{

    /* Pwm channel Emios specific parameters from config structure */
    P2CONST(Pwm_EMIOS_ChannelConfigType, AUTOMATIC, PWM_APPL_CONST) PwmEmiosSpecificParam= NULL_PTR;

    VAR(Pwm_OutputStateType, AUTOMATIC) output_state;

    VAR(Pwm_ChannelType, AUTOMATIC) hw_ch; /* hw channel */

    VAR(Pwm_ChannelType, AUTOMATIC) mIdx;   /*  assigned eMIOS HW module  index */
    VAR(Pwm_ChannelType, AUTOMATIC) chIdx;  /*  assigned eMIOS HW channel index */

    VAR(uint32, AUTOMATIC) ModuleAddr;
    VAR(uint32, AUTOMATIC) ChannelAddr;

    /* start critical section for logical channel */
    SchM_Enter_Pwm(SCHM_PWM_INSTANCE_0, LogicalChannelNumber);

    /* extract from conf structure the EMIOS specific channel information */
        /** @file eMIOS_Pwm_LLD.c
          @note Violates MISRA 2004 Advisory Rule 17.4: See @ref eMIOS_Pwm_LLD_C_REF_11 */
    PwmEmiosSpecificParam=&Pwm_EMIOS_Cfg->ChannelsPtr[LogicalChannelNumber].SpecificCfg.EmiosCfg;
    ModuleAddr = PwmEmiosSpecificParam->Pwm_Emios_ModuleAddr;
    ChannelAddr = PwmEmiosSpecificParam->Pwm_Emios_ChannelAddr;




    /* store the associated hw channel ID */
    hw_ch = PwmEmiosSpecificParam->Pwm_HwChannelID;


    mIdx  = (uint8)(hw_ch >> EMIOS_MOD_SHIFT);
    chIdx = (uint8)(hw_ch &  EMIOS_CH_MASK);


    if (0U != (REG_READ32(ChannelAddr + EMIOS_CSR_OFFSET) & CSR_UCOUT_MASK)) {
        output_state = PWM_HIGH;
    } else {
        output_state = PWM_LOW;
    }

    /* exit critical section for logical channel */
    SchM_Exit_Pwm(SCHM_PWM_INSTANCE_0, LogicalChannelNumber);

    return output_state;

}
#endif


/**
@brief   This function disables the user notifications
@details This function
         - enables the notification
         - sets the Edge select bit in control register if notification is both edges
         - clears the Edge select bit in control register if notification is both edges
         - clears the interrupt flag and enables the FLAG event for OPWMB and OPWFMB modes
         - clear interrupt flag in Status register and clear the DMA bit in
           Control register for OPWMT mode


@param[in]     LogicalChannelNumber - pwm channel id
@param[in]     Notification  - notification type to be enabled

@remarks Covers PWM112, PWM113, PWM064, PWM051, PWM062, PWM024, PWM081

@remarks Implements DPWM03003
*/
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
FUNC (void, PWM_CODE) EMIOS_Pwm_LLD_EnableNotification
                      (
                          VAR(Pwm_ChannelType, AUTOMATIC) LogicalChannelNumber,
                          VAR(Pwm_EdgeNotificationType, AUTOMATIC) Notification
                      )
{

    /* Pwm channel generic parameters from config structure */
    P2CONST(Pwm_ChannelConfigType, AUTOMATIC, PWM_APPL_CONST) PwmChannel = NULL_PTR;
    /* Pwm channel Emios specific parameters from config structure */
    P2CONST(Pwm_EMIOS_ChannelConfigType, AUTOMATIC, PWM_APPL_CONST) PwmEmiosSpecificParam= NULL_PTR;

    VAR(Pwm_EmiosCtrlParamType, AUTOMATIC) ctrlRegVal;

    VAR(Pwm_ChannelType, AUTOMATIC) hw_ch;  /* hw channel */

    VAR(Pwm_ChannelType, AUTOMATIC) mIdx;   /*  assigned eMIOS HW module  index */
    VAR(Pwm_ChannelType, AUTOMATIC) chIdx;  /*  assigned eMIOS HW channel index */

    VAR(uint32, AUTOMATIC) ModuleAddr;
    VAR(uint32, AUTOMATIC) ChannelAddr;

    /* start critical section for logical channel */
    SchM_Enter_Pwm(SCHM_PWM_INSTANCE_0, LogicalChannelNumber);

    /* extract from conf structure the generic        channel information */
    /** @file eMIOS_Pwm_LLD.c
           @note Violates MISRA 2004 Advisory Rule 17.4 : See @ref eMIOS_Pwm_LLD_C_REF_11 */
    PwmChannel = &Pwm_EMIOS_Cfg->ChannelsPtr[ LogicalChannelNumber ];

    /* extract from conf structure the EMIOS specific channel information */
    PwmEmiosSpecificParam =  &PwmChannel->SpecificCfg.EmiosCfg;

    ModuleAddr = PwmEmiosSpecificParam->Pwm_Emios_ModuleAddr;
    ChannelAddr = PwmEmiosSpecificParam->Pwm_Emios_ChannelAddr;

    /* save current channel control register config value in local variable */
    ctrlRegVal = PwmEmiosSpecificParam->Pwm_ParamValue;


    #if (PWM_DEV_ERROR_DETECT == STD_ON)

    /* check for eMIOS triggering limitations */
    /* invalid flag generation modes for OPWFMB  */
    if ((CCR_MODE_OPWFMB_FLAG_B == (ctrlRegVal & CCR_MODE_MASK)) &&
        ((PWM_HIGH == PwmChannel->Pwm_Polarity) && (PWM_FALLING_EDGE == Notification)))
    {
        Det_ReportError
        (
            (uint16) PWM_MODULE_ID,
            (uint8) 0,
            (uint8) PWM_ENABLENOTIFICATION_ID,
            (uint8) PWM_E_PARAM_NOTIFICATION
        );
    /* invalid flag generation modes for OPWFMB  */
    } else if ((CCR_MODE_OPWFMB_FLAG_B == (ctrlRegVal & CCR_MODE_MASK)) &&
        ((PWM_LOW == PwmChannel->Pwm_Polarity) && (PWM_RISING_EDGE == Notification)))
    {
        Det_ReportError
        (
            (uint16) PWM_MODULE_ID,
            (uint8) 0,
            (uint8) PWM_ENABLENOTIFICATION_ID,
            (uint8) PWM_E_PARAM_NOTIFICATION
        );
    /* invalid flag generation modes for OPWMB  */
    } else if ((CCR_MODE_OPWMB_FLAG_B == (ctrlRegVal & CCR_MODE_MASK)) &&
        ((PWM_HIGH == PwmChannel->Pwm_Polarity) && (PWM_RISING_EDGE == Notification)))
    {
        Det_ReportError
        (
            (uint16) PWM_MODULE_ID,
            (uint8) 0,
            (uint8) PWM_ENABLENOTIFICATION_ID,
            (uint8) PWM_E_PARAM_NOTIFICATION
        );
    /* invalid flag generation modes for OPWMB  */
    } else if ((CCR_MODE_OPWMB_FLAG_B == (ctrlRegVal & CCR_MODE_MASK)) &&
        ((PWM_LOW == PwmChannel->Pwm_Polarity) && (PWM_FALLING_EDGE == Notification)))
    {
        Det_ReportError
        (
            (uint16) PWM_MODULE_ID,
            (uint8) 0,
            (uint8) PWM_ENABLENOTIFICATION_ID,
            (uint8) PWM_E_PARAM_NOTIFICATION
        );
    } else {
    #endif

        /* store the associated hw channel ID */
        hw_ch = PwmEmiosSpecificParam->Pwm_HwChannelID;


        mIdx  = (uint8)(hw_ch >> EMIOS_MOD_SHIFT);
        chIdx = (uint8)(hw_ch &  EMIOS_CH_MASK);

        /* note that notifications are enabled for this channel */
        Pwm_EMIOS_LLD_Notifications[ hw_ch ] = (uint8)Notification;

        /* only enable notifications if channel is not in idle state */
        if (CCR_MODE_GPO != (REG_READ32(ChannelAddr + EMIOS_CCR_OFFSET) & CCR_MODE_MASK))
        {

        #ifdef PWM_FEATURE_OPWMT
            #if (PWM_FEATURE_OPWMT == STD_ON)
            /* activation edge not available in OPWMT */
            if (CCR_MODE_OPWMT != (ctrlRegVal & CCR_MODE_MASK)) {
            #endif
        #endif
                /*
                * transitions are present in the signal ( duty != 0%,100% )
                * dutycycle doesn't affect trigger in OPWMT mode
                */
                if (1U == Pwm_EMIOS_LLD_DutyState[ hw_ch ])
                {
                    /* Change activation edge if required */

                    if (PWM_BOTH_EDGES == Notification) {
                        /* notification on both edges */
                        REG_BIT_SET32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_MODE_EDGE_SELECT_MASK );
                    } else {
                        /* notification on period event */
                        REG_BIT_CLEAR32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_MODE_EDGE_SELECT_MASK);
                    }

                    /* clear interrupt flag */
                    REG_WRITE32( ChannelAddr + EMIOS_CSR_OFFSET, CSR_FLAG_BIT );

                    /* FLAG event enabled */
                    REG_BIT_SET32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_FEN_MASK );
                }

        #ifdef PWM_FEATURE_OPWMT
            #if (PWM_FEATURE_OPWMT == STD_ON)

            } else { /* OPWMT */
                REG_WRITE32( ChannelAddr + EMIOS_CSR_OFFSET, CSR_FLAG_BIT ); /* clear interrupt flag */
                /* FLAG assigned to interrupt request */
                REG_BIT_CLEAR32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_DMA_MASK );
            }

            #endif
        #endif

        }

    #if (PWM_DEV_ERROR_DETECT == STD_ON)
    }
    #endif

    /* exit critical section for logical channel */
    SchM_Exit_Pwm(SCHM_PWM_INSTANCE_0, LogicalChannelNumber);

}
#endif


/**
@brief   This function disables the user notifications
@details This function
         - disables the notification
         - disables the FEN bit in Control register for OPWMB and OPWFMB modes
         - clear interrupt flag in Status register and Set the DMA bit in
           Control register for OPWMT mode

@param[in]     LogicalChannelNumber - pwm channel id

@remarks Covers PWM062, PWM023

@remarks Implements DPWM03002
*/
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
FUNC (void, PWM_CODE) EMIOS_Pwm_LLD_DisableNotification
                      (
                          VAR(Pwm_ChannelType, AUTOMATIC) LogicalChannelNumber
                      )
{
    /* Pwm channel generic parameters from config structure */
    P2CONST(Pwm_ChannelConfigType, AUTOMATIC, PWM_APPL_CONST) PwmChannel = NULL_PTR;
    /* Pwm channel Emios specific parameters from config structure */
    P2CONST(Pwm_EMIOS_ChannelConfigType, AUTOMATIC, PWM_APPL_CONST) PwmEmiosSpecificParam= NULL_PTR;

    VAR(Pwm_ChannelType, AUTOMATIC) hw_ch;  /* hw channel */

    VAR(Pwm_ChannelType, AUTOMATIC) mIdx;   /*  assigned eMIOS HW module  index */
    VAR(Pwm_ChannelType, AUTOMATIC) chIdx;  /*  assigned eMIOS HW channel index */

    VAR(uint32, AUTOMATIC) ModuleAddr;
    VAR(uint32, AUTOMATIC) ChannelAddr;

    /* start critical section for logical channel */
    SchM_Enter_Pwm(SCHM_PWM_INSTANCE_0, LogicalChannelNumber);

    /* extract from conf structure the generic        channel information */
     /** @file eMIOS_Pwm_LLD.c
         @note Violates MISRA 2004 Advisory Rule 17.4 : See @ref eMIOS_Pwm_LLD_C_REF_11 */
    PwmChannel = &Pwm_EMIOS_Cfg->ChannelsPtr[ LogicalChannelNumber ];
    /* extract from conf structure the EMIOS specific channel information */
    PwmEmiosSpecificParam = &PwmChannel->SpecificCfg.EmiosCfg;

    ModuleAddr = PwmEmiosSpecificParam->Pwm_Emios_ModuleAddr;
    ChannelAddr = PwmEmiosSpecificParam->Pwm_Emios_ChannelAddr;


    /* store the associated hw channel ID */
    hw_ch = PwmEmiosSpecificParam->Pwm_HwChannelID;


    mIdx  = (uint8)(hw_ch >> EMIOS_MOD_SHIFT);
    chIdx = (uint8)(hw_ch &  EMIOS_CH_MASK);


    #ifdef PWM_FEATURE_OPWMT
        #if (PWM_FEATURE_OPWMT == STD_ON)
            if (CCR_MODE_OPWMT != (PwmEmiosSpecificParam->Pwm_ParamValue & CCR_MODE_MASK)) {
        #endif
    #endif


    REG_BIT_CLEAR32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_FEN_MASK ); /* disable interrupt */
    /* no need to clear the flag as it will be cleared in
     * EnableNotification before interrupts are enabled
     */

    #ifdef PWM_FEATURE_OPWMT
        #if (PWM_FEATURE_OPWMT == STD_ON)
            } else {

                /* OPWMT */
                /* clear interrupt flag */
                REG_WRITE32( ChannelAddr + EMIOS_CSR_OFFSET, CSR_FLAG_BIT );
                /* FLAG event routed to CTU */
                REG_BIT_SET32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_DMA_MASK );
            }
        #endif
    #endif

    Pwm_EMIOS_LLD_Notifications[ hw_ch ] = 0xFFU;  /* notifications disabled */

    /* exit critical section for logical channel */
    SchM_Exit_Pwm(SCHM_PWM_INSTANCE_0, LogicalChannelNumber);

}
#endif


/**
@brief   Implementation specific function to set the frequency of pwm channel
         running on PWM_MODE_OPWMB or PWM_MODE_OPWMT mode
@details This function
         - changes the counter bus from Bus A to Bus Diverse or vice versa
         - Bus selection bits will be configured in Control register
         - update dutycycle to the configured default value

@param[in] LogicalChannelNumber - pwm channel id
@param[in] Bus           - the eMIOS bus to change to

@remarks Covers PWM062, PWM023,PWM_CUSTOM001

@remarks Implements   DPWM03009
*/
#if (PWM_SETCOUNTERBUS_API == STD_ON)
FUNC (void, PWM_CODE) EMIOS_Pwm_LLD_SetCounterBus
                      (
                          VAR(Pwm_ChannelType, AUTOMATIC) LogicalChannelNumber,
                          VAR(uint32, AUTOMATIC)          Bus
                      )
{
    /* Pwm channel generic parameters from config structure */
    P2CONST(Pwm_ChannelConfigType, AUTOMATIC, PWM_APPL_CONST) PwmChannel = NULL_PTR;
    /* Pwm channel Emios specific parameters from config structure */
    P2CONST(Pwm_EMIOS_ChannelConfigType, AUTOMATIC, PWM_APPL_CONST) PwmEmiosSpecificParam= NULL_PTR;

    VAR(Pwm_ChannelType, AUTOMATIC) hw_ch;  /* hw channel */

    VAR(Pwm_ChannelType, AUTOMATIC) mIdx;   /*  assigned eMIOS HW module  index */
    VAR(Pwm_ChannelType, AUTOMATIC) chIdx;  /*  assigned eMIOS HW channel index */

    VAR(uint32, AUTOMATIC) ModuleAddr;
    VAR(uint32, AUTOMATIC) ChannelAddr;

    /* start critical section for logical channel */
    SchM_Enter_Pwm(SCHM_PWM_INSTANCE_0, LogicalChannelNumber);

    /* extract from conf structure the generic channel information */
       /** @file eMIOS_Pwm_LLD.c
          @note Violates MISRA 2004 Advisory Rule 17.4 : See @ref eMIOS_Pwm_LLD_C_REF_11 */
    PwmChannel = &Pwm_EMIOS_Cfg->ChannelsPtr[ LogicalChannelNumber ];
    /* extract from generic conf structure the EMIOS specific channel information */
    PwmEmiosSpecificParam = &PwmChannel->SpecificCfg.EmiosCfg;

    ModuleAddr = PwmEmiosSpecificParam->Pwm_Emios_ModuleAddr;
    ChannelAddr = PwmEmiosSpecificParam->Pwm_Emios_ChannelAddr;

    /* store the associated hw channel ID */
    hw_ch = PwmEmiosSpecificParam->Pwm_HwChannelID;


    mIdx  = (uint8)(hw_ch >> EMIOS_MOD_SHIFT);
    chIdx = (uint8)(hw_ch &  EMIOS_CH_MASK);

    /* update the channel period with the period of the new selected counter bus */
    Pwm_EMIOS_LLD_Period[ hw_ch ] =
                 EMIOS_PWM_LLD_GetCounterBusPeriod(mIdx, chIdx, Bus,ChannelAddr,ModuleAddr);

    /* set the new counter bus */
    if (PWM_BUS_DIVERSE == Bus)
    {
        /* select bus Diverse */
        REG_RMW32(ChannelAddr+EMIOS_CCR_OFFSET, CCR_BSL_MASK, CCR_BSL_BUS_DIVERSE << CCR_BSL_SHIFT);
    }
    else
    {
        REG_BIT_CLEAR32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_BSL_MASK ); /* select bus A */
    }

  /** @file eMIOS_Pwm_LLD.c
    @note Violates MISRA 2004 Advisory Rule 10.1 : See @ref eMIOS_Pwm_LLD_C_REF_3 */
    /* update dutycycle to the configured default value, do not enable the critical section
       as it's already on */
    /*lint -save -e960 */
    EMIOS_Pwm_LLD_SetDutyCycle
    (
        (Pwm_ChannelType)LogicalChannelNumber,
        (uint16)PwmChannel->Pwm_DefaultDutyCycleValue,
        (uint8)STD_OFF
    );
    /*lint -restore  */

    /* exit critical section for logical channel */
    SchM_Exit_Pwm(SCHM_PWM_INSTANCE_0, LogicalChannelNumber);

}
#endif


/**
@brief   Implementation specific function to set the state of the PWM pin as requested
         for the current cycle
@details This function is useful to to set the state of the PWM pin as requested
         for the current cycle and continues
         with normal PWM operation from the next cycle
         - OPWFMB: if the passed state is Active, force a match on B Register otherwise
           force a match on A Register
         - OPWMB or OPWMT: if the passed state is Active, force a match on A Register
           otherwise force a match on B Register
         - the force match is done by setting the FORCMA and FORCMB bits is Control Register

@param[in] LogicalChannelNumber - pwm channel id
@param[in] State           - Active/Inactive state of the channel

@remarks Covers PR-MCAL-3173

@remarks Implements   DPWM03010
*/
#if (PWM_SETCHANNELOUTPUT_API == STD_ON)
FUNC (void, PWM_CODE) EMIOS_Pwm_LLD_SetChannelOutput
                      (
                          VAR(Pwm_ChannelType, AUTOMATIC) LogicalChannelNumber,
                          VAR(Pwm_StateType, AUTOMATIC)          State
                      )
{
    /* Pwm channel generic parameters from config structure */
    P2CONST(Pwm_ChannelConfigType, AUTOMATIC, PWM_APPL_CONST) PwmChannel = NULL_PTR;
    /* Pwm channel Emios specific parameters from config structure */
    P2CONST(Pwm_EMIOS_ChannelConfigType, AUTOMATIC, PWM_APPL_CONST) PwmEmiosSpecificParam= NULL_PTR;

    VAR(Pwm_ChannelType, AUTOMATIC) hw_ch;  /* hw channel */
    VAR(Pwm_EmiosCtrlParamType, AUTOMATIC) ctrlRegVal;
    VAR(Pwm_ChannelType, AUTOMATIC) mIdx;   /* assigned eMIOS HW module  index */
    VAR(Pwm_ChannelType, AUTOMATIC) chIdx;  /* assigned eMIOS HW channel index */

    VAR(uint32, AUTOMATIC) ModuleAddr;
    VAR(uint32, AUTOMATIC) ChannelAddr;

    /* start critical section for logical channel */
    SchM_Enter_Pwm(SCHM_PWM_INSTANCE_0, LogicalChannelNumber);

    /* extract from conf structure the generic channel information */
   /** @file eMIOS_Pwm_LLD.c
         @note Violates MISRA 2004 Advisory Rule 17.4 : See @ref eMIOS_Pwm_LLD_C_REF_11 */
   PwmChannel = &Pwm_EMIOS_Cfg->ChannelsPtr[ LogicalChannelNumber ];
    /* extract from generic conf structure the EMIOS specific channel information */
    PwmEmiosSpecificParam = &PwmChannel->SpecificCfg.EmiosCfg;

    ModuleAddr = PwmEmiosSpecificParam->Pwm_Emios_ModuleAddr;
    ChannelAddr = PwmEmiosSpecificParam->Pwm_Emios_ChannelAddr;




    /* store the associated hw channel ID */
    hw_ch = PwmEmiosSpecificParam->Pwm_HwChannelID;

    /* save current channel control register config value in local variable */
    ctrlRegVal = PwmEmiosSpecificParam->Pwm_ParamValue;

    mIdx  = (uint8)(hw_ch >> EMIOS_MOD_SHIFT);
    chIdx = (uint8)(hw_ch &  EMIOS_CH_MASK);


    if (CCR_MODE_OPWFMB_FLAG_B == ((uint32)ctrlRegVal & CCR_MODE_MASK)) {
        /* OPWFMB */
        if (PWM_ACTIVE == State) {
    /** @file eMIOS_Pwm_LLD.c
            @note Violates MISRA 2004 Advisory Rule 11.1 : See @ref eMIOS_Pwm_LLD_C_REF_7
            */
            /*lint -save -e923 */
            REG_BIT_SET32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_FORCMB_MASK ); /**< force match B */
            /*lint -restore  */
        }
        else {
    /** @file eMIOS_Pwm_LLD.c
            @note Violates MISRA 2004 Advisory Rule 11.1 : See @ref eMIOS_Pwm_LLD_C_REF_7
            */
            /*lint -save -e923 */
            REG_BIT_SET32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_FORCMA_MASK ); /**< force match A */
            /*lint -restore  */
        }
    }
    else {
        /* OPWMB / OPWMT */
        if (PWM_ACTIVE == State) {
    /** @file eMIOS_Pwm_LLD.c
            @note Violates MISRA 2004 Advisory Rule 11.1 : See @ref eMIOS_Pwm_LLD_C_REF_7
            */
            /*lint -save -e923 */
            REG_BIT_SET32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_FORCMA_MASK ); /**< force match A */
            /*lint -restore  */
        }
        else {
    /** @file eMIOS_Pwm_LLD.c
            @note Violates MISRA 2004 Advisory Rule 11.1 : See @ref eMIOS_Pwm_LLD_C_REF_7
            */
            /*lint -save -e923 */
            REG_BIT_SET32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_FORCMB_MASK ); /**< force match B */
            /*lint -restore  */
        }
    }

    /* exit critical section for logical channel */
    SchM_Exit_Pwm(SCHM_PWM_INSTANCE_0, LogicalChannelNumber);

}
#endif


/**
@brief Implementation specific function to set the channel prescaler.
@details This function is useful to set the value of the channel prescaler.
         For this purpose, the following actions are taken for each configured channel
         running on internal counter bus:
         - write 0 at both GPREN bit in EMIOSMCR register and UCPREN bit in EMIOSC[n] register,
           thus disabling prescalers;
         - write the desired value for prescaling rate at UCPRE[0:1] bits in EMIOSC[n] register;
         - enable channel prescaler by writing 1 at UCPREN bit in EMIOSC[n] register;
         - enable global prescaler by writing 1 at GPREN bit in EMIOSMCR register.

@param[in] Prescaler - prescaler type

@remarks Covers PR-MCAL-3199

@remarks Implements   DPWM03011
*/
#if (PWM_DUAL_CLOCK_MODE == STD_ON)
FUNC (void, PWM_CODE) EMIOS_Pwm_LLD_SelectPrescaler
                      (
                          VAR(Pwm_SelectPrescalerType, AUTOMATIC) Prescaler
                      )
{
    /* Pwm channel generic parameters from config structure */
    P2CONST(Pwm_ChannelConfigType, AUTOMATIC, PWM_APPL_CONST) PwmChannel = NULL_PTR;
    /* Pwm channel Emios specific parameters from config structure */
    P2CONST(Pwm_EMIOS_ChannelConfigType, AUTOMATIC, PWM_APPL_CONST) PwmEmiosSpecificParam= NULL_PTR;

    VAR(Pwm_EmiosCtrlParamType, AUTOMATIC) ctrlRegVal;

    VAR(Pwm_ChannelType, AUTOMATIC) hw_ch; /* hw channel */

    VAR(Pwm_ChannelType, AUTOMATIC) ch = (Pwm_ChannelType )0; /* logical channel */

    VAR(Pwm_ChannelType, AUTOMATIC) mIdx;   /* assigned eMIOS HW module  index */
    VAR(Pwm_ChannelType, AUTOMATIC) chIdx;  /* assigned eMIOS HW channel index */

    VAR(uint32, AUTOMATIC) mcrRegVal;

    VAR(uint32, AUTOMATIC) ModuleAddr;
    VAR(uint32, AUTOMATIC) ChannelAddr;

    for (ch=0U; ch < Pwm_EMIOS_Cfg->ChannelCount; ch++)  {
        /* only handle EMIOS channels */
        if (PWM_EMIOS_CHANNEL == Pwm_EMIOS_Cfg->ChannelsPtr[ch].IpType)
        {

            /* extract from conf structure the generic channel information */
            PwmChannel = &Pwm_EMIOS_Cfg->ChannelsPtr[ch];

            /* extract from conf structure the EMIOS specific channel information */
            PwmEmiosSpecificParam =  &PwmChannel->SpecificCfg.EmiosCfg;

            ModuleAddr = PwmEmiosSpecificParam->Pwm_Emios_ModuleAddr;
            ChannelAddr = PwmEmiosSpecificParam->Pwm_Emios_ChannelAddr;

            hw_ch = PwmEmiosSpecificParam->Pwm_HwChannelID;

            mIdx  = (uint8)(hw_ch >> EMIOS_MOD_SHIFT);
            chIdx = (uint8)(hw_ch &  EMIOS_CH_MASK);

            /* save current channel control register config value in local variable */
            ctrlRegVal = PwmEmiosSpecificParam->Pwm_ParamValue;

            if (PWM_BUS_INTERNAL_COUNTER == ((uint32)ctrlRegVal & PWM_BUS_MASK))
            {
                /* only write UCDIS register if it's available */
                #ifdef EMIOS_UCDIS
                    /* enable unified channel to make registers writable */
                    REG_BIT_CLEAR32( (ModuleAddr+EMIOS_UCDIS_OFFSET), (uint32)((uint32)1<<(chIdx)));
                #endif

                mcrRegVal = REG_READ32(ModuleAddr+EMIOS_MCR_OFFSET);

                /* disable global prescaler - this will stop the EMIOS clock */
                REG_BIT_CLEAR32( (ModuleAddr+EMIOS_MCR_OFFSET), MCR_GPREN_MASK );

                /* disable prescaler - this will stop the internal counter */
                REG_BIT_CLEAR32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_UCPREN_MASK );

                REG_WRITE32( ChannelAddr + EMIOS_CCNTR_OFFSET, 1); /* set internal counter to 1 */

                /* select internal counter bus */
                REG_BIT_SET32( ChannelAddr + EMIOS_CCR_OFFSET, CCR_BSL_MASK );

                if (PWM_NORMAL == Prescaler)
                {
                    /* set the prescaler divide value */
                    REG_RMW32
                    (
                        (ChannelAddr + EMIOS_CCR_OFFSET),
                        CCR_UCPRE_MASK,
                        ctrlRegVal & CCR_UCPRE_MASK
                    );
                }
                else if (PWM_ALTERNATE == Prescaler)
                {
                    /* set the alternate prescaler divide value */
                    REG_RMW32
                    (
                        (ChannelAddr + EMIOS_CCR_OFFSET),
                        CCR_UCPRE_MASK,
                        PwmEmiosSpecificParam->Pwm_Prescaler_Alternate & CCR_UCPRE_MASK
                    );
                }
                else
                {
                    /* Do nothing. Empty else added to fix MISRA Violation*/
                }

                /* enable prescaler - this will start the internal counter */
                REG_BIT_SET32( (ChannelAddr + EMIOS_CCR_OFFSET), CCR_UCPREN_MASK );

                if ((mcrRegVal & MCR_GPREN_MASK) == MCR_GPREN_MASK)
                {
                    /* enable global prescaler */
                    REG_BIT_SET32( (ModuleAddr+EMIOS_MCR_OFFSET), MCR_GPREN_MASK );
                }
            }

        } /* end if EMIOS channel */

    } /* end for */

}

#endif

#ifdef PWM_FEATURE_OPWMT
    #if (PWM_FEATURE_OPWMT == STD_ON)
/**
@brief   Implementation specific function to set the trigger delay  for  pwm channel
         running on PWM_MODE_OPWMT mode
         - write trigger delay to alternate A register for OPWMT mode

@param[in] LogicalChannelNumber - pwm channel id
@param[in] TriggerDelay         - triggerdelay

@remarks Covers       PR-MCAL-3234
@remarks Implements   DPWM07050
*/
#if (PWM_SET_TRIGGER_DELAY_API == STD_ON)
FUNC (void, PWM_CODE) EMIOS_Pwm_LLD_SetTriggerDelay
                      (
                          VAR(Pwm_ChannelType, AUTOMATIC) LogicalChannelNumber,
                          VAR(uint16, AUTOMATIC)  TriggerDelay
                      )
{


    /* Pwm channel generic parameters from config structure */
    P2CONST(Pwm_ChannelConfigType, AUTOMATIC, PWM_APPL_CONST) PwmChannel = NULL_PTR;
    /* Pwm channel Emios specific parameters from config structure */
    P2CONST(Pwm_EMIOS_ChannelConfigType, AUTOMATIC, PWM_APPL_CONST) PwmEmiosSpecificParam= NULL_PTR;

    VAR(Pwm_ChannelType, AUTOMATIC) hw_ch; /* hw channel */
    VAR(uint32, AUTOMATIC) ModuleAddr;
    VAR(uint32, AUTOMATIC) ChannelAddr;

      /* extract from conf structure the generic        channel information */
        /** @file eMIOS_Pwm_LLD.c
           @note Violates MISRA 2004 Advisory Rule 17.4: See @ref eMIOS_Pwm_LLD_C_REF_11 */
    PwmChannel = &Pwm_EMIOS_Cfg->ChannelsPtr[LogicalChannelNumber];

    /* extract from conf structure the EMIOS specific channel information */
    PwmEmiosSpecificParam =  &PwmChannel->SpecificCfg.EmiosCfg;

    ModuleAddr = PwmEmiosSpecificParam->Pwm_Emios_ModuleAddr;
    ChannelAddr = PwmEmiosSpecificParam->Pwm_Emios_ChannelAddr;

    /* store the associated hw channel ID */
    hw_ch = PwmEmiosSpecificParam->Pwm_HwChannelID;

        /*Save current Trigger Delay in local variable*/
    Pwm_Current_TriggerDelay[hw_ch] = (uint16)TriggerDelay;
    Pwm_PeriodInit[hw_ch] = Pwm_EMIOS_LLD_Period[ hw_ch ];

   REG_WRITE32(   (ChannelAddr + EMIOS_ALTA_OFFSET),(uint32)( (uint32)TriggerDelay + (uint32) 1) );
}
#endif
#endif
#endif



#define PWM_STOP_SEC_CODE
/*lint -save -e961 -e537 -e451 */
/** @file eMIOS_Pwm_LLD.c
    @note Violates MISRA 2004 Advisory Rule 19.1, 19.15 : See @ref eMIOS_Pwm_LLD_C_REF_1,
    eMIOS_Pwm_LLD_C_REF_8 */
#include "MemMap.h"
/*lint -restore */

#ifdef __cplusplus
}
#endif
