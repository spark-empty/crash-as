/**
    @file    FMPLL_Mcu_LLD.c
    @version 2.0.0

@brief   AUTOSAR Mcu - Brief description.
@details Detailed description.

Project AUTOSAR 3.0 MCAL
Patform PA
Peripheral FMPLL
Dependencies none

ARVersion 3.0.0
ARRevision ASR_REL_3_0_REV_0003
ARConfVariant
SWVersion 2.0.0
BuildVersion XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223

(c) Copyright 2006-2011 Freescale Semiconductor Inc. & PITicroelectronics
All Rights Reserved.
*/
/*==================================================================================================
==================================================================================================*/
/**
@page misra_violations MISRA-C:2004 violations

@section FMPLL_Mcu_LLD_C_REF_1
Violates  MISRA  2004 Advisory  Rule  19.1,  only preprocessor statements and comments before
'#include'
This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003

@section FMPLL_Mcu_LLD_C_REF_2
MISRA-C:2004  19.15 Precautions shall be taken in order to prevent the contents of a
header file being included twice.
This is not a violation since all header files are protected against multiple inclusions.

@section FMPLL_Mcu_LLD_C_REF_3
MISRA-C 2004  11.1 VIOLATION, Conversions shall not be performed between a pointer to a
function and any type other than an integral type.This violation is due to cast from unsigned long to 
pointer.The cast can not be avoided as it is used to access memory mapped registers.
*/
#ifdef __cplusplus
extern "C"
{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
2) needed interfaces from external units
3) internal and external interfaces from this unit
==================================================================================================*/
#include "Mcu_LLD.h"
#include "SchM_Mcu.h"

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/
/** @remarks Covers BSW00374, BSW00318 */
#define FMPLL_MCU_LLD_VENDOR_ID_C         43
#define FMPLL_MCU_LLD_AR_MAJOR_VERSION_C  3
#define FMPLL_MCU_LLD_AR_MINOR_VERSION_C  0
#define FMPLL_MCU_LLD_AR_PATCH_VERSION_C  0
#define FMPLL_MCU_LLD_SW_MAJOR_VERSION_C  2
#define FMPLL_MCU_LLD_SW_MINOR_VERSION_C  0
#define FMPLL_MCU_LLD_SW_PATCH_VERSION_C  0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and MCU_LLD header file are of the same vendor */
#if (FMPLL_MCU_LLD_VENDOR_ID_C != MCU_LLD_VENDOR_ID)
#error "FMPLL_MCU_LLD.c and Mcu_LLD.h have different vendor ids"
#endif

#ifdef CHECK_AUTOSAR_VERSION
/* Check if source file and MCU_LLD header file are of the same Autosar version */
#if ((FMPLL_MCU_LLD_AR_MAJOR_VERSION_C != MCU_LLD_AR_MAJOR_VERSION) || \
(FMPLL_MCU_LLD_AR_MINOR_VERSION_C != MCU_LLD_AR_MINOR_VERSION) || \
(FMPLL_MCU_LLD_AR_PATCH_VERSION_C != MCU_LLD_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of FMPLL_MCU_LLD.c and Mcu_LLD.h are different"
#endif
#endif
/* Check if source file and MCU_LLD header file are of the same Software version */
#if ((FMPLL_MCU_LLD_SW_MAJOR_VERSION_C != MCU_LLD_SW_MAJOR_VERSION) || \
(FMPLL_MCU_LLD_SW_MINOR_VERSION_C != MCU_LLD_SW_MINOR_VERSION) || \
(FMPLL_MCU_LLD_SW_PATCH_VERSION_C != MCU_LLD_SW_PATCH_VERSION))
#error "Software Version Numbers of FMPLL_MCU_LLD.c and Mcu_LLD.h are different"
#endif

#ifdef CHECK_AUTOSAR_VERSION
/* Check if source file and SCHM_MCU_LLD header file are of the same Software version */
#if ((FMPLL_MCU_LLD_SW_MAJOR_VERSION_C != SCHM_MCU_AR_MAJOR_VERSION) || \
(FMPLL_MCU_LLD_SW_MINOR_VERSION_C != SCHM_MCU_AR_MINOR_VERSION))
#error "Software Version Numbers of FMPLL_MCU_LLD.c and SchM_Mcu.h are different"
#endif
#endif

/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/
#define MCU_START_SEC_VAR_UNSPECIFIED
/** @note Violates MISRA 2004  19.1, 19.15 : 
See @ref FMPLL_Mcu_LLD_C_REF_1, FMPLL_Mcu_LLD_C_REF_2 above*/
/*lint -save -e961 -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/

/* PLL Initialization Wait State */
    STATIC VAR(uint32, MCU_VAR) Mcu_PllWaitState = MCU_PLL_WAIT_FINISHED;

#define MCU_STOP_SEC_VAR_UNSPECIFIED
/** @note Violates MISRA 2004  19.1, 19.15 : 
See @ref FMPLL_Mcu_LLD_C_REF_1, FMPLL_Mcu_LLD_C_REF_2 above*/
/*lint -save -e961 -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/
/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/

#define MCU_START_SEC_CODE
/** @note Violates MISRA 2004  19.1, 19.15 : 
See @ref FMPLL_Mcu_LLD_C_REF_1, FMPLL_Mcu_LLD_C_REF_2 above*/
/*lint -save -e961 -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/
/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

/**
@brief   This function initializes the pll.
@details The pll is started  by configuring its parameters.

@param[in]     ClockPtr      Pointer to clock configuration structure

@return void

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers MCU138
@remarks Implements DMCU09000
*/
    FUNC(void, MCU_CODE) Mcu_FMPLL_Init(P2CONST(Mcu_ClockConfigType, AUTOMATIC, MCU_APPL_DATA) \
        ClockPtr)
    {
        VAR(uint32, AUTOMATIC) ERFD_value;

#ifdef IPV_FMPLL
    /* if Andorra or Monaco*/
    #if ((IPV_FMPLL == IPV_FMPLL_01_01_07_00) || (IPV_FMPLL == IPV_FMPLL_01_01_02_00))

        ERFD_value = 3UL;
    #elif (IPV_FMPLL == IPV_FMPLL_00_00_01_02)  /*If FADO*/
/*Get the configured ERFD value from the configuration */
        ERFD_value = (uint32)((uint32)(ClockPtr->Pll_ESYNCR2) & FMPLL_ESYNCR2_ERFD);
        if (0UL == ERFD_value)
        {
/* increase ERFD value to ERFD + 3 to ensure clock frequency doesn't go beyond valid range */
            ERFD_value = ERFD_value + 3UL;
        }
    #endif
#else
/*Get the configured ERFD value from the configuration */
        ERFD_value = (uint32)((uint32)(ClockPtr->Pll_ESYNCR2) & FMPLL_ESYNCR2_ERFD);
        if (0UL == ERFD_value)
        {
/* increase ERFD value to ERFD + 3 to ensure clock frequency doesn't go beyond valid range */
            ERFD_value = ERFD_value + 3UL;
        }
#endif
/** @remarks Covers MCU138 */
/*Write a value of ERFD = ERFD + 3 to the ERFD field of the  FMPLL_ESYNCR2  */
#ifdef IPV_FMPLL
    /* if FADO / Andorra / Monaco */
    #if ((IPV_FMPLL == IPV_FMPLL_00_00_01_02) || (IPV_FMPLL == IPV_FMPLL_01_01_07_00) \
        || (IPV_FMPLL == IPV_FMPLL_01_01_02_00)) 
        /** @note Violates MISRA 2004 11.1: 
See @ref FMPLL_Mcu_LLD_C_REF_3 above*/
        REG_WRITE32(FMPLL_ESYNCR2, (uint32)(ERFD_value));
    #else
        REG_WRITE32(FMPLL_ESYNCR2, ((uint32)ClockPtr->Pll_ESYNCR2
                                   & (FMPLL_ESYNCR2_CLKCFG_DIS)) | (uint32)(ERFD_value));
    #endif
#else
        REG_WRITE32(FMPLL_ESYNCR2, ((uint32)ClockPtr->Pll_ESYNCR2
                                   & (FMPLL_ESYNCR2_CLKCFG_DIS)) | (uint32)(ERFD_value));
#endif
/*Write configured values of CLKCFG, EPREDIV,EMFD to  FMPLL_ESYNCR1 Register    */
        /** @note Violates MISRA-C:2004 11.1: See @ref FMPLL_Mcu_LLD_C_REF_3 above*/
        REG_WRITE32(FMPLL_ESYNCR1, (uint32)(ClockPtr->Pll_ESYNCR1));
        Mcu_PllWaitState = MCU_Pll_WAIT_NONFMLOCK;/* FM Programming */
    }

/**
@brief   This function returns the status of the pll.
@details This reads the pll status and returns if the pll locked or not.

@param[in]     ClockPtr      Pointer to clock configuration structure

@return Status
@retval MCU_PLL_LOCKED
@retval MCU_PLL_UNLOCKED

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers MCU008
@remarks Implements DMCU09000
*/
    FUNC(Mcu_PllStatusType, MCU_CODE) Mcu_FMPLL_GetPllStatus(\
        P2CONST(Mcu_ClockConfigType, AUTOMATIC, MCU_APPL_DATA) ClockPtr,\
        VAR(uint32, MCU_VAR) Mcu_TimeOut)
    {
        VAR(Mcu_PllStatusType, AUTOMATIC) status = MCU_PLL_UNLOCKED;
#ifdef IPV_FMPLL
    /* if Andorra or Monaco*/
    #if ((IPV_FMPLL == IPV_FMPLL_01_01_07_00) || (IPV_FMPLL == IPV_FMPLL_01_01_02_00))
       VAR(uint32, AUTOMATIC) timeout = 0UL;
    #endif
#endif

/* Read the LOCK bit of the FMPLL_SYNSR */
        /** @note Violates MISRA-C:2004 11.1: See @ref FMPLL_Mcu_LLD_C_REF_3 above*/
        status = (Mcu_PllStatusType)(((REG_READ32(FMPLL_SYNSR) & FMPLL_SYNSR_LOCK) == \
        FMPLL_SYNSR_LOCK) ? MCU_PLL_LOCKED : MCU_PLL_UNLOCKED);

        if ((MCU_PLL_LOCKED == status) && (Mcu_PllWaitState != MCU_PLL_WAIT_FINISHED))
        {
/* Continue PLL Setup according to eSys FMPLL specification */
            if (MCU_Pll_WAIT_NONFMLOCK == Mcu_PllWaitState)
            {
#ifdef IPV_FMPLL
    /* if Andorra or Monaco*/
    #if ((IPV_FMPLL == IPV_FMPLL_01_01_07_00) || (IPV_FMPLL == IPV_FMPLL_01_01_02_00))

                /* clear MODEN into FMPLL_SYNFMMR register - Frequency Modulation Disabled */
                REG_BIT_CLEAR32(FMPLL_SYNFMMR, FMPLL_SYNFMMR_MODEN_EN); 

                /* wait for SYNFMMR BSY bit */
                while( (REG_READ32(FMPLL_SYNFMMR) & FMPLL_SYNFMMR_BSY) == FMPLL_SYNFMMR_BSY ) 
                {
                    if( timeout > Mcu_TimeOut){
                        break;
                    }
                    timeout++;
                 }

                /* check for MODEN configuration */
                if(ClockPtr->Pll_SYNFMMR & FMPLL_SYNFMMR_MODEN_EN)
                { 
                    /* The configuration would like hte Modulation Frequency Enabled */
                    /* control BSY bit before accessing to register */
                    /* modulation rate must be programmed first of modulation depth */
                    REG_WRITE32(FMPLL_SYNFMMR, ((ClockPtr->Pll_SYNFMMR)& \
                               (FMPLL_SYNFMMR_MODPERIOD_MASK|FMPLL_SYNFMMR_INCSTEP_MASK|\
                                FMPLL_SYNFMMR_MODSEL_MASK)));
                    /* wait for SYNFMMR BSY bit */
                    while( (REG_READ32(FMPLL_SYNFMMR) & FMPLL_SYNFMMR_BSY) == FMPLL_SYNFMMR_BSY ) {
                        if( timeout >Mcu_TimeOut){
                            break;
                        }
                        timeout++;
                    }
                    REG_BIT_SET32(FMPLL_SYNFMMR, FMPLL_SYNFMMR_MODEN_EN);
                    Mcu_PllWaitState = MCU_Pll_WAIT_FMLOCK;
                }
                else
                {
                    REG_WRITE32(FMPLL_ESYNCR2, (uint32)(ClockPtr->Pll_ESYNCR2));
                    Mcu_PllWaitState = MCU_PLL_WAIT_FINISHED;
                }
    #elif (IPV_FMPLL == IPV_FMPLL_00_00_01_02)  /*If FADO*/
/* Check the EDEPTH bit of FMPLL_ESYNCR2 register to check FM is enabled or not */
                if (((ClockPtr->Pll_ESYNCR2) & FMPLL_ESYNCR2_EDEPTH) == 0UL)
                {
/* No Modulation */
/*When the PLL achieves lock, write the ERFD value desired & enable clock notification bits */
                    /** @note Violates MISRA-C:2004 11.1: See @ref FMPLL_Mcu_LLD_C_REF_3 above*/
                    REG_WRITE32(FMPLL_ESYNCR2, (uint32)(ClockPtr->Pll_ESYNCR2));
                    Mcu_PllWaitState = MCU_PLL_WAIT_FINISHED;
                }
                else
                {
/*FM Enabled, Write the desired modulation rate and depth to the ERATE and EDEPTH fields in the
  ESYNCR2 : step 3 */
                    REG_WRITE32(FMPLL_ESYNCR2, (((ClockPtr->Pll_ESYNCR2)) & \
                               (FMPLL_ESYNCR2_EDEPTH | FMPLL_ESYNCR2_ERATE | (~FMPLL_ESYNCR2_ERFD)))
/* ERFD is left unchanged */
                    /** @note Violates MISRA-C:2004 11.1: See @ref FMPLL_Mcu_LLD_C_REF_3 above*/
                        | ((uint32) REG_READ32(FMPLL_ESYNCR2) & FMPLL_ESYNCR2_ERFD));
/* finished step 3 from programming system clock frequency With frequency modulation
 *  step 4 will be completed on the next call to this function
 */
                    Mcu_PllWaitState = MCU_Pll_WAIT_FMLOCK;
                }
    #endif
#else

/* Check the EDEPTH bit of FMPLL_ESYNCR2 register to check FM is enabled or not */
                if (((ClockPtr->Pll_ESYNCR2) & FMPLL_ESYNCR2_EDEPTH) == 0UL)
                {
/* No Modulation */
/*When the PLL achieves lock, write the ERFD value desired & enable clock notification bits */
                    REG_WRITE32(FMPLL_ESYNCR2, (uint32)(ClockPtr->Pll_ESYNCR2));
                    Mcu_PllWaitState = MCU_PLL_WAIT_FINISHED;
                }
                else
                {
/* this write actually targets register SYNFMCR (FMDAC_CTL bitfield) */
                    REG_WRITE32(FMPLL_SYNFMCR, (((uint32)(ClockPtr->Pll_ESYNCR2) & \
                                FMPLL_ESYNCR2_EDEPTH) << MCU_SHIFT_TEN) | FMPLL_SYNFMCR_FMDACEN);
/*FM Enabled, Write the desired modulation rate and depth to the ERATE and EDEPTH fields in the
  ESYNCR2 : step 3 */
                    REG_WRITE32(FMPLL_ESYNCR2, (((ClockPtr->Pll_ESYNCR2)) & \
                              (FMPLL_ESYNCR2_EDEPTH | FMPLL_ESYNCR2_ERATE | (~FMPLL_ESYNCR2_ERFD)))
/* ERFD is left unchanged */
                        | ((uint32) REG_READ32(FMPLL_ESYNCR2) & FMPLL_ESYNCR2_ERFD));
/* finished step 3 from programming system clock frequency With frequency modulation
 *  step 4 will be completed on the next call to this function
 */
                    Mcu_PllWaitState = MCU_Pll_WAIT_FMLOCK;
                }
#endif
            }
            else
            {
                /** @note Violates MISRA-C:2004 11.1: See @ref FMPLL_Mcu_LLD_C_REF_3 above*/
                REG_WRITE32(FMPLL_ESYNCR2, (uint32)(ClockPtr->Pll_ESYNCR2));
/* complete step 4 from programming system clock frequency with frequency modulation or step 5 from
   programming system clock frequency*/
                Mcu_PllWaitState = MCU_PLL_WAIT_FINISHED;
            }
        }
        if (Mcu_PllWaitState != MCU_PLL_WAIT_FINISHED)
        {
            status = MCU_PLL_UNLOCKED;
        }
/* Return the PLL status*/
        return status;
    }

/**
@brief   This function disables the PLL.
@details The pll is disabled for going to sleep mode.

@return void

@pre Preconditions of this function
@post Postconditions of this function

@remarks Covers MCU138
@remarks Implements DMCU09000
*/
#ifdef IPV_FMPLL
    #if (IPV_FMPLL == IPV_FMPLL_00_00_01_02) /*FADO*/

    FUNC(void, MCU_CODE) Mcu_FMPLL_Sleep(void)
    {
        /* Set system clock to 16MHz IRC clock */
        /** @note Violates MISRA-C:2004 11.1: See @ref FMPLL_Mcu_LLD_C_REF_3 above*/
        REG_BIT_CLEAR32(FMPLL_ESYNCR1, (uint32) SIU_SYSCLK_SYSCLKSEL);
    }

    #endif
#endif
#define MCU_STOP_SEC_CODE
/** @note Violates MISRA 2004  19.1, 19.15 : 
See @ref FMPLL_Mcu_LLD_C_REF_1, FMPLL_Mcu_LLD_C_REF_2 above*/
/*lint -save -e961 -e537 -e451*/
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif
