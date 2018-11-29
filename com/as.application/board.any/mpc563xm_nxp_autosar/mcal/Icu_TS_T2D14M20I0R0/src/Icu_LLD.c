/**
    @file    Icu_LLD.c
    @version 2.0.0

    @brief   AUTOSAR Icu - ICU Driver LLD source file.
    @details ICU driver source file, containing the LLD variables and functions that are used by
             the ICU driver.

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
/*==================================================================================================
==================================================================================================*/

/**
@file    Icu_LLD.c
@remarks Implements DICU07000
*/

/**
@page misra_violations MISRA-C:2004 violations

@section Icu_LLD_c_REF_1
         Violates MISRA-C 2004 Advisory Rule 19.1, only preprocessor statements and comments
         before "#include". This violation  is not  fixed since  the inclusion  of MemMap.h
         is as  per Autosar  requirement MEMMAP003.

@section Icu_LLD_c_REF_2
         Violates  MISRA-C  2004 Advisory  Rule  19.15,  Precautions shall be taken in order to
         prevent the contents of a header file being included twice. This is not a violation since
         all header files are protected against multiple inclusions.

@section Icu_LLD_c_REF_3
         Violates MISRA-C:2004 1.2: No reliance shall be placed on undefined or unspecified
         behavior.Taking address of near auto variable "value" (arg. no. 2)
         This violation  is not  fixed since  the local variable is used to keep the critical
         region as short as possible.

@section Icu_LLD_c_REF_4
         Violates MISRA-C 2004 Advisory Rule 17.4 Array indexing shall be the only allowed form of
         pointer arithmetic.This violation is due to the use of pointer arithematic, to access the
         channel parameters,the indexing of the pointer is taken care and hence the unintended
         memory location will not be accessed.
*/

#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
/**
@file  Icu_LLD.c
@note  Violates  MISRA  2004 Advisory Rule 19.15, Precautions shall be taken in order to prevent
the contents of a header file being included twice -  See @ref Icu_LLD_c_REF_2
*/

/*lint -save -e537*/
#include "Icu.h"
#include "Icu_LLD.h"
#include "eMIOS_Icu_LLD.h"
#include "Siu_Icu_LLD.h"
#include "Reg_Macros.h"
#include "SchM_Icu.h"
#include "Reg_eSys_EMIOS.h"
/*lint -restore*/

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/
/**
@{
@brief   Source file version information
@remarks Covers BSW00374, BSW00379, BSW00318
*/
#define ICU_LLD_VENDOR_ID_C         43

#define ICU_LLD_AR_MAJOR_VERSION_C  3
#define ICU_LLD_AR_MINOR_VERSION_C  0
#define ICU_LLD_AR_PATCH_VERSION_C  0
#define ICU_LLD_SW_MAJOR_VERSION_C  2
#define ICU_LLD_SW_MINOR_VERSION_C  0
#define ICU_LLD_SW_PATCH_VERSION_C  0
/**@}*/

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and ICU header file are of the same vendor */
#if (ICU_LLD_VENDOR_ID_C != ICU_VENDOR_ID)
#error "Icu_LLD.c and Icu.h have different vendor IDs"
#endif

/* Check if source file Icu_LLD.c and Icu.h header file are of the same Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
    #if ((ICU_LLD_AR_MAJOR_VERSION_C != ICU_AR_MAJOR_VERSION) || \
         (ICU_LLD_AR_MINOR_VERSION_C != ICU_AR_MINOR_VERSION) || \
         (ICU_LLD_AR_PATCH_VERSION_C != ICU_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Icu_LLD.c and Icu.h are different"
    #endif
#endif

/* Check if source file Icu_LLD.c and Icu.h header file are of the same Software version */
#if ((ICU_LLD_SW_MAJOR_VERSION_C != ICU_SW_MAJOR_VERSION) || \
     (ICU_LLD_SW_MINOR_VERSION_C != ICU_SW_MINOR_VERSION) || \
     (ICU_LLD_SW_PATCH_VERSION_C != ICU_SW_PATCH_VERSION))
#error "Software Version Numbers of Icu_LLD.c and Icu.h are different"
#endif

#if (ICU_LLD_VENDOR_ID_C != ICU_LLD_VENDOR_ID)
    #error "Icu_LLD.c and Icu_LLD.h have different vendor IDs"
#endif
/* Check if source file and Icu_LLD header file are of the same Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
    #if ((ICU_LLD_AR_MAJOR_VERSION_C != ICU_LLD_AR_MAJOR_VERSION) || \
         (ICU_LLD_AR_MINOR_VERSION_C != ICU_LLD_AR_MINOR_VERSION) || \
         (ICU_LLD_AR_PATCH_VERSION_C != ICU_LLD_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Icu_LLD.c and Icu_LLD.h are different"
    #endif
#endif
/* Check if source file and Icu_LLD header file are of the same Software version */
#if ((ICU_LLD_SW_MAJOR_VERSION_C != ICU_LLD_SW_MAJOR_VERSION) || \
     (ICU_LLD_SW_MINOR_VERSION_C != ICU_LLD_SW_MINOR_VERSION) || \
     (ICU_LLD_SW_PATCH_VERSION_C != ICU_LLD_SW_PATCH_VERSION))
#error "Software Version Numbers of Icu_LLD.c and Icu_LLD.h are different"
#endif


/* Check if Icu_LLD.h and SchM_Icu.h file are of the same Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
    #if ((ICU_LLD_AR_MAJOR_VERSION_C != SCHM_ICU_AR_MAJOR_VERSION) || \
         (ICU_LLD_AR_MINOR_VERSION_C != SCHM_ICU_AR_MINOR_VERSION))
    #error "AutoSar Version Numbers of Icu_LLD.c and SchM_Icu.h are different"
    #endif
#endif


/* Check if Icu_LLD.c and eMIOS_Icu_LLD.h file are of the same Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
    #if ((ICU_LLD_AR_MAJOR_VERSION_C != EMIOS_ICU_LLD_AR_MAJOR_VERSION) || \
         (ICU_LLD_AR_MINOR_VERSION_C != EMIOS_ICU_LLD_AR_MINOR_VERSION) || \
         (ICU_LLD_AR_PATCH_VERSION_C != EMIOS_ICU_LLD_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Icu_LLD.c and eMIOS_Icu_LLD.h are different"
    #endif
#endif
/* Check if source file and eMIOS_Icu_LLD.h file are of the same Software version */
#if ((ICU_LLD_SW_MAJOR_VERSION_C != EMIOS_ICU_LLD_SW_MAJOR_VERSION) || \
     (ICU_LLD_SW_MINOR_VERSION_C != EMIOS_ICU_LLD_SW_MINOR_VERSION) || \
     (ICU_LLD_SW_PATCH_VERSION_C != EMIOS_ICU_LLD_SW_PATCH_VERSION))
#error "Software Version Numbers of Icu_LLD.c and eMIOS_Icu_LLD.h are different"
#endif


/* Check if Icu_LLD.h and SIU_Icu_LLD.h file are of the same Autosar version */
#ifdef CHECK_AUTOSAR_VERSION
    #if ((ICU_LLD_AR_MAJOR_VERSION_C != SIU_ICU_LLD_AR_MAJOR_VERSION) || \
         (ICU_LLD_AR_MINOR_VERSION_C != SIU_ICU_LLD_AR_MINOR_VERSION) || \
         (ICU_LLD_AR_PATCH_VERSION_C != SIU_ICU_LLD_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Icu_LLD.c and SIU_Icu_LLD.h are different"
    #endif
#endif
/* Check if source file and SIU_Icu_LLD.h file are of the same Software version */
#if ((ICU_LLD_SW_MAJOR_VERSION_C != SIU_ICU_LLD_SW_MAJOR_VERSION) || \
     (ICU_LLD_SW_MINOR_VERSION_C != SIU_ICU_LLD_SW_MINOR_VERSION) || \
     (ICU_LLD_SW_PATCH_VERSION_C != SIU_ICU_LLD_SW_PATCH_VERSION))
#error "Software Version Numbers of Icu_LLD.c and SIU_Icu_LLD.h are different"
#endif

/* Check if Icu_LLD.c and Reg_eSys_EMIOS.h file are of the same vendor */
#if (ICU_LLD_VENDOR_ID_C != REG_ESYS_EMIOS_H_VENDOR_ID)
#error "Icu_LLD.c and Reg_eSys_EMIOS.h have different vendor IDs"
#endif

#ifdef CHECK_AUTOSAR_VERSION
    /* Check if Icu_LLD.c and Reg_eSys_EMIOS.h file are of the same Autosar version */
    #if ((ICU_LLD_AR_MAJOR_VERSION_C != REG_ESYS_EMIOS_H_AR_MAJOR_VERSION) || \
         (ICU_LLD_AR_MINOR_VERSION_C != REG_ESYS_EMIOS_H_AR_MINOR_VERSION) || \
         (ICU_LLD_AR_PATCH_VERSION_C != REG_ESYS_EMIOS_H_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Icu_LLD.c and Reg_eSys_EMIOS.h are different"
    #endif
#endif

/* Check if Icu_LLD.c and Reg_eSys_EMIOS.h file are of the same Software version */
#if ((ICU_LLD_SW_MAJOR_VERSION_C != REG_ESYS_EMIOS_H_SW_MAJOR_VERSION) || \
     (ICU_LLD_SW_MINOR_VERSION_C != REG_ESYS_EMIOS_H_SW_MINOR_VERSION) || \
     (ICU_LLD_SW_PATCH_VERSION_C != REG_ESYS_EMIOS_H_SW_PATCH_VERSION))
#error "Software Version Numbers of Icu_LLD.c and Reg_eSys_EMIOS.h are different"
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
#define ICU_START_SEC_VAR_UNSPECIFIED
/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
       "#include". See @ref Icu_LLD_c_REF_1
@note  Violates  MISRA  2004 Advisory Rule 19.15, Precautions shall be taken in order to prevent
       the contents of a header file being included twice -  See @ref Icu_LLD_c_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

/**
@{
@brief Extern variable declarations
*/
/**
@{
@brief   Stores actual state and configuration of ICU Channels
*/
extern volatile VAR(uint8, ICU_VAR) Icu_ChannelState[ICU_MAX_CHANNEL];


/**
@brief Saves the current Icu mode
*/
extern volatile VAR(Icu_ModeType, ICU_VAR) Icu_Current_Mode;

#if (ICU_TIMESTAMP_API == STD_ON)
/**
@brief Pointer to the buffer-array where the timestamp values shall be placed.
*/
extern P2VAR(Icu_ValueType, ICU_VAR, ICU_APPL_DATA) Icu_Buffer[ICU_MAX_CHANNEL];
/**
@brief Array for saving the size of the external buffer (number of entries)
*/
extern volatile VAR(Icu_ValueType, ICU_VAR) Icu_BufferSize[ICU_MAX_CHANNEL];
/**
@brief Array for saving Notification interval (number of events).
*/
extern volatile VAR(Icu_ValueType, ICU_VAR) Icu_BufferNotify[ICU_MAX_CHANNEL];
/**
@brief Array for saving the number of notify counts
*/
extern volatile VAR(Icu_ValueType, ICU_VAR) Icu_NotifyCount[ICU_MAX_CHANNEL];
/**
@brief Array for saving the time stamp index
*/
extern volatile VAR(Icu_IndexType, ICU_VAR) Icu_BufferIndex[ICU_MAX_CHANNEL];
#endif

#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
/**
@brief Array for saving the pulse width of active time
*/
extern volatile VAR(Icu_ValueType, ICU_VAR) Icu_ActivePulseWidth[ICU_MAX_CHANNEL];
/**
@brief Array for saving the pulse width of active time
*/
volatile VAR(Icu_ValueType, ICU_VAR) Icu_CapturedActivePulseWidth[ICU_MAX_CHANNEL];
/**
@brief Array for saving the period
*/
extern volatile VAR(Icu_ValueType, ICU_VAR) Icu_Period[ICU_MAX_CHANNEL];
/**
@brief Array for saving the timer start value
*/
volatile VAR(Icu_ValueType, ICU_VAR) Icu_Start[ICU_MAX_CHANNEL];
/**
@brief Array for saving the initial counter value
*/
volatile VAR(uint8, ICU_VAR) Icu_Int_Counter[ICU_MAX_CHANNEL];
#endif


#if (ICU_EDGE_COUNT_API == STD_ON)
/**
@brief Array for saving the edge count value
*/
STATIC volatile VAR(Icu_EdgeNumberType, ICU_VAR) Icu_EdgeCount[ICU_MAX_CHANNEL];
#endif


#define ICU_STOP_SEC_VAR_UNSPECIFIED
/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
       "#include". See @ref Icu_LLD_c_REF_1
@note  Violates  MISRA  2004 Advisory Rule 19.15, Precautions shall be taken in order to prevent
       the contents of a header file being included twice -  See @ref Icu_LLD_c_REF_2
*/

/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
#define ICU_START_SEC_CODE
/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
       "#include". See @ref Icu_LLD_c_REF_1
@note  Violates  MISRA  2004 Advisory Rule 19.15, Precautions shall be taken in order to prevent
       the contents of a header file being included twice -  See @ref Icu_LLD_c_REF_2
*/

/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

/*================================================================================================*/
/**
@brief      Icu driver function that gets the bitfield value in channel state.
@details    This function returns the Icu_ChannelState bitfield specified by mask parameter
            in an atomic way.

@param[in]  numChl  - The index of ICU channel for current configuration structure
@param[in]  mask    - bitfield mask

@return     Icu_ChannelStateType - Bitfield specified by mask parameter
*/
/*================================================================================================*/
INLINE STATIC FUNC (Icu_ChannelStateType, ICU_CODE) Icu_LLD_GetBitChState(
                    VAR(Icu_ChannelType, AUTOMATIC) numChl, Icu_ChannelStateType mask)
{
    VAR(Icu_ChannelStateType, AUTOMATIC) value;

    SchM_Enter_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_02);
    {
        value = Icu_ChannelState[numChl] & mask;
    }
    SchM_Exit_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_02);

    return value;
}

/*================================================================================================*/
/**
@brief      Icu driver function that sets the bitfield value in channel state.
@details    This function sets the Icu_ChannelState bitfield specified by mask parameter in an
            atomic way.

@param[in]  numChl  - The index of ICU channel for current configuration structure
@param[in]  mask    - bitfield mask
*/
/*================================================================================================*/
INLINE STATIC FUNC (void, ICU_CODE) Icu_LLD_SetBitChState(VAR(Icu_ChannelType, AUTOMATIC) numChl,
                                                          Icu_ChannelStateType mask)
{
    SchM_Enter_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_03);
    {
        Icu_ChannelState[numChl] |= mask;
    }
    SchM_Exit_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_03);
}

/*================================================================================================*/
/**
@brief      Icu driver function that resets the bitfield value in channel state.
@details    This function clears the Icu_ChannelState bitfield specified by mask parameter in an
            atomic way.

@param[in]  numChl  - The index of ICU channel for current configuration structure
@param[in]  mask    - bitfield mask
*/
/*================================================================================================*/
INLINE STATIC FUNC (void, ICU_CODE) Icu_LLD_ClearBitChState(VAR(Icu_ChannelType, AUTOMATIC) numChl,
                                                            Icu_ChannelStateType mask)
{
    SchM_Enter_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_04);
    {
        Icu_ChannelState[numChl] &= ((Icu_ChannelStateType)(~mask));
    }
    SchM_Exit_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_04);
}

/*================================================================================================*/
/**
@brief      Icu driver function that checks if overflow event occured for given eMIOS channel
@details    This function returns TRUE if on the given channel an overflow event occurred.

@param[in]  numChl  - The index of ICU channel for current configuration structure
@param[in]  flags   - bitfield mask

@return     boolean
             - true -  if an overflow event occurred
             - false - if no overflow event has occurred
*/
/*================================================================================================*/
INLINE STATIC FUNC (boolean, ICU_CODE) Icu_LLD_CheckHwOverflowFlag(
                                                             VAR(Icu_ChannelType, AUTOMATIC) numChl,
                                                             VAR(uint32, AUTOMATIC) flags)
{
    boolean result = (boolean)FALSE;
/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic - See @ref Icu_LLD_c_REF_4
*/
    CONST(Icu_ChannelType, AUTOMATIC) hwChannel = Icu_Cfg_Ptr->Icu_ChannelId[numChl];

    if (hwChannel < ICU_MAX_eMIOS_CHANNELS)
    {
        result = eMIOS_LLD_CheckOverflowFlag(flags);
    }

    return result;
}


/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

/*================================================================================================*/
/**
@brief      Icu driver function that initializes the ICU hardware channel.
@details    This function initializes a hardware ICU channel

@param[in]  tempPtr     - Pointer to configuration structure
@param[in]  numChl      - The index of ICU channel for current configuration structure
@param[in]  msChannel   - This index relates the Icu Channel number with the respective global
                          variable, depending on the measurement mode. Each kind of measurement
                          mode has an array(s) in the ICU driver, this index points to the
                          corresponding variable within the ICU channel.
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_LLD_InitChannel(
                                  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_APPL_CONST) tempPtr,
                                  VAR(Icu_ChannelType, AUTOMATIC) numChl,
                                  CONST(Icu_ChannelType, AUTOMATIC) msChannel)
{
/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 2004 Advisory Rule 17.4: Array indexing shall be the only
allowed form of pointer arithmetic - See @ref Icu_LLD_c_REF_4
*/    
    CONST(Icu_ChannelType, AUTOMATIC) hwChannel = Icu_Cfg_Ptr->Icu_ChannelId[numChl];

    /* The wakeup-capability of a channel shall be disabled
     * This service shall disable all notifications.
     * All ICU channel status shall be set to ICU_IDLE
     */

    /* Clear channel internal state */
    Icu_ChannelState[numChl] =  0x00U;

    /* Store activation edge */
    switch ((tempPtr->Icu_ParamValue & ICU_EDGE_PARAM_MASK) >> ICU_EDGE_PARAM_SHIFT)
    {
        case ICU_RISING_EDGE:
            Icu_LLD_SetBitChState(numChl, ICU_CHANNEL_STATE_RISING);
            break;

        case ICU_FALLING_EDGE:
            Icu_LLD_SetBitChState(numChl, ICU_CHANNEL_STATE_FALLING);
            break;

        default:
            Icu_LLD_SetBitChState(numChl, ICU_CHANNEL_STATE_BOTH_EDGES);
            break;
    }


    /* eMIOS Channel Configuration */
    if (hwChannel < ICU_MAX_eMIOS_CHANNELS)
    {
#if (ICU_EDGE_COUNT_API == STD_ON)
        if (ICU_MODE_EDGE_COUNTER == tempPtr->Icu_Channel_Mode)
        {
            Icu_EdgeCount[msChannel] = (Icu_EdgeNumberType)0U;
        }
/* ICU_EDGE_COUNT_API */    
#endif 
#if (ICU_TIMESTAMP_API == STD_ON)
        if (ICU_MODE_TIMESTAMP == tempPtr->Icu_Channel_Mode)
        {
            Icu_Buffer[msChannel] = NULL_PTR;
        }
/* ICU_TIMESTAMP_API */    
#endif 

        if (ICU_MODE_EDGE_COUNTER == tempPtr->Icu_Channel_Mode)
        {
            eMIOS_LLD_InitChannel(tempPtr->Icu_ParamValue, EMIOS_CHANNEL_MODE_EDGE_COUNTER,
                                  ICU_eMIOS_CHANNEL(hwChannel));
        }
        else if (ICU_MODE_SIGNAL_EDGE_DETECT == tempPtr->Icu_Channel_Mode)
        {
            eMIOS_LLD_InitChannel(tempPtr->Icu_ParamValue, EMIOS_CHANNEL_MODE_EDGE_DETECT,
                                  ICU_eMIOS_CHANNEL(hwChannel));
        }
        else
        {
            eMIOS_LLD_InitChannel(tempPtr->Icu_ParamValue, EMIOS_CHANNEL_MODE_CAPTURE_MODE,
                                  ICU_eMIOS_CHANNEL(hwChannel));
        }
    }
    /* External Interrupt Channel Configuration */
    else
    {
        SIU_LLD_InitChannel(tempPtr->Icu_ParamValue,      
                           (SIU_Icu_IRQ_ChannelType)ICU_IRQ_CHANNEL(hwChannel));
    }

}

/*================================================================================================*/
/**
@brief      Icu driver function that de-initializes the ICU hardware channel.
@details    This function de-initializes the ICU hardware channel.

@param[in]  numChl - The index of ICU channel for current configuration structure
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_LLD_DeInitChannel(VAR(Icu_ChannelType, AUTOMATIC) numChl)
{
/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_LLD_c_REF_4
*/    
    CONST(Icu_ChannelType, AUTOMATIC) hwChannel = Icu_Cfg_Ptr->Icu_ChannelId[numChl];

    /* eMIOS Channel Configuration */
    if (hwChannel < ICU_MAX_eMIOS_CHANNELS)
    {
        VAR(boolean,AUTOMATIC) reg_EMIOSCNT_available = (boolean)FALSE;
        VAR(boolean,AUTOMATIC) reg_EMIOSB_available   = (boolean)FALSE;

/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic. See @ref Icu_LLD_c_REF_4
*/
        if (ICU_MODE_EDGE_COUNTER == Icu_Cfg_Ptr->Icu_ChannelConfigPtr[numChl].Icu_Channel_Mode)
        {
            reg_EMIOSCNT_available = (boolean)TRUE;
        }
/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic - See @ref Icu_LLD_c_REF_4
*/  
        else if (ICU_MODE_SIGNAL_MEASUREMENT == \
                 Icu_Cfg_Ptr->Icu_ChannelConfigPtr[numChl].Icu_Channel_Mode)
        {
            reg_EMIOSB_available = (boolean)TRUE;
        }
        else
        {
                /* does nothing  - structure request by misra*/
        }
        eMIOS_LLD_DeInitChannel(ICU_eMIOS_CHANNEL(hwChannel),
                                reg_EMIOSCNT_available, reg_EMIOSB_available);
    }
    /* External Interrupt Channel Configuration */
    else
    {
        SIU_LLD_DeInitChannel((SIU_Icu_IRQ_ChannelType)ICU_IRQ_CHANNEL(hwChannel));
    }
}

#if (ICU_SET_MODE_API == STD_ON)
/*================================================================================================*/
/**
@brief      Icu driver function that sets the ICU hardware channel into sleep mode.
@details    This function sets the ICU hardware channels (eMIOS, SIU or WKUP) into SLEEP mode

@param[in]  numChl - The index of ICU channel for current configuration structure
@param[in]  active - ICU channel is active during SLEEP mode (wakeup was enabled)
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_LLD_SetSleepMode(VAR(Icu_ChannelType, AUTOMATIC) numChl,
                                           VAR(boolean, AUTOMATIC) active)
{
/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic - See @ref Icu_LLD_c_REF_4
*/      
    CONST(Icu_ChannelType, AUTOMATIC) hwChannel = Icu_Cfg_Ptr->Icu_ChannelId[numChl];

    if (hwChannel < ICU_MAX_eMIOS_CHANNELS)
    {
        eMIOS_LLD_SetSleepMode(ICU_eMIOS_CHANNEL(hwChannel), active);
    }
    else
    {
        SIU_LLD_SetSleepMode((SIU_Icu_IRQ_ChannelType)ICU_IRQ_CHANNEL(hwChannel), active);
    }

}

/*================================================================================================*/
/**
@brief      Icu driver function that sets the ICU hardware channel into NORMAL mode.
@details    This function sets the ICU hardware channels (eMIOS, SIU or WKUP) into NORMAL mode,
            Enables the notification for the channel.

@param[in]  numChl - The index of ICU channel for current configuration structure
@param[in]  active - ICU channel is active during NORMAL mode (notification was enabled)
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_LLD_SetNormalMode(VAR(Icu_ChannelType, AUTOMATIC) numChl,
                                            VAR(boolean, AUTOMATIC) active)
{
/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic - See @ref Icu_LLD_c_REF_4
*/     
    CONST(Icu_ChannelType, AUTOMATIC) hwChannel = Icu_Cfg_Ptr->Icu_ChannelId[numChl];

    if (hwChannel < ICU_MAX_eMIOS_CHANNELS)
    {
        eMIOS_LLD_SetNormalMode(ICU_eMIOS_CHANNEL(hwChannel), active);
    }
    else
    {
        SIU_LLD_SetNormalMode((SIU_Icu_IRQ_ChannelType)ICU_IRQ_CHANNEL(hwChannel), active);
    }
}
/* ICU_SET_MODE_API */
#endif  

#if (ICU_DISABLE_WAKEUP_API == STD_ON)
/*================================================================================================*/
/**
@brief      Icu driver function that disables the wakeup for channel.
@details    This function disables wakeup for ICU hardware channels.
@param[in]  numChl - The index of ICU channel for current configuration structure
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_LLD_DisableWakeup(VAR(Icu_ChannelType, AUTOMATIC) numChl)
{
    Icu_LLD_ClearBitChState(numChl, ICU_CHANNEL_STATE_WKUP);
}
/* ICU_DISABLE_WAKEUP_API */
#endif  

#if (ICU_ENABLE_WAKEUP_API == STD_ON)
/*================================================================================================*/
/**
@brief      Icu driver function that enables the wakeup for channel.
@details    This function enables wakeup for ICU hardware channels.

@param[in]  numChl - The index of ICU channel for current configuration structure
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_LLD_EnableWakeup(VAR(Icu_ChannelType, AUTOMATIC) numChl)
{
    Icu_LLD_SetBitChState(numChl, ICU_CHANNEL_STATE_WKUP);
}
/* ICU_ENABLE_WAKEUP_API */
#endif  

/*================================================================================================*/
/**
@brief      Icu driver function that sets activation conditiond for channel with requested
            activation type.
@details    This function sets the requested Activation for the channels (eMIOS, SIU or WKUP)

@param[in]  numChl     - The index of ICU channel for current configuration structure
@param[in]  Activation - the type of activation for the ICU channel.
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_LLD_SetActivationCondition(VAR(Icu_ChannelType, AUTOMATIC) numChl,
                                                     VAR(Icu_ActivationType, AUTOMATIC) Activation)
{
/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic - See @ref Icu_LLD_c_REF_4
*/     
    CONST(Icu_ChannelType, AUTOMATIC) hwChannel = Icu_Cfg_Ptr->Icu_ChannelId[numChl];

    /* Clear IDLE status */
    Icu_LLD_ClearBitChState(numChl, ICU_CHANNEL_STATE_IDLE);

    /* Clear activation bitfield */
    Icu_LLD_ClearBitChState(numChl, ICU_CHANNEL_STATE_BOTH_EDGES);

    switch (Activation)
    {
        case ICU_RISING_EDGE:
            Icu_LLD_SetBitChState(numChl, ICU_CHANNEL_STATE_RISING);
            break;

        case ICU_FALLING_EDGE:
            Icu_LLD_SetBitChState(numChl, ICU_CHANNEL_STATE_FALLING);
            break;

        default:
            Icu_LLD_SetBitChState(numChl, ICU_CHANNEL_STATE_BOTH_EDGES);
            break;
    }

    /* eMIOS Channel Configuration */
    if (hwChannel < ICU_MAX_eMIOS_CHANNELS)
    {
        eMIOS_LLD_SetActivationCondition(ICU_eMIOS_CHANNEL(hwChannel),
                                         (eMIOS_ActivationType)Activation);
    }
    /* External Interrupt Channel Configuration */
    else
    {
        SIU_LLD_SetActivationCondition((SIU_Icu_IRQ_ChannelType)ICU_IRQ_CHANNEL(hwChannel), 
                                        (SIU_ActivationType)Activation);
    }
}

/*================================================================================================*/
/**
@brief      Icu driver function that disables the notification for channel.
@details    This function disables notification for an ICU Hardware Channel.
            For disabling notification, for some ICU channels, the interrupt
            for the channel must be also disabled

@param[in]  numChl - The index of ICU channel for current configuration structure
@param[in]  DisableInterrupt - true if the interrupt must be also disabled
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_LLD_DisableNotification(VAR(Icu_ChannelType, AUTOMATIC) numChl,
                                                  VAR(boolean, AUTOMATIC) DisableInterrupt)
{
     
    Icu_LLD_ClearBitChState(numChl, ICU_CHANNEL_STATE_NOTIFICATION);

    if (DisableInterrupt)
    {
/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic - See @ref Icu_LLD_c_REF_4
*/    
        CONST(Icu_ChannelType, AUTOMATIC) hwChannel = Icu_Cfg_Ptr->Icu_ChannelId[numChl];

        if (hwChannel < ICU_MAX_eMIOS_CHANNELS)
        {
            eMIOS_LLD_DisableNotification(ICU_eMIOS_CHANNEL(hwChannel));
        }
        else
        {
            SIU_LLD_DisableNotification((SIU_Icu_IRQ_ChannelType)ICU_IRQ_CHANNEL(hwChannel));
        }
    }
}

/*================================================================================================*/
/**
@brief      Icu driver function that enables the notification for channel.
@details    This function enables notification for an ICU Hardware Channel.
            For enabling notifications for some ICU channels, the interrupt
            for the channel must be also re-enabled

@param[in]  numChl - The index of ICU channel for current configuration structure
@param[in]  EnableInterrupt - true if interrupt of the channel must be also enabled
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_LLD_EnableNotification(VAR(Icu_ChannelType, AUTOMATIC) numChl,
                                                 VAR(boolean, AUTOMATIC) EnableInterrupt)
{     
    Icu_LLD_SetBitChState(numChl, ICU_CHANNEL_STATE_NOTIFICATION);

    if (EnableInterrupt)
    {
/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic - See @ref Icu_LLD_c_REF_4
*/    
        CONST(Icu_ChannelType, AUTOMATIC) hwChannel = Icu_Cfg_Ptr->Icu_ChannelId[numChl];

        if (hwChannel < ICU_MAX_eMIOS_CHANNELS)
        {
            eMIOS_LLD_EnableNotification(ICU_eMIOS_CHANNEL(hwChannel));
        }
        else
        {
            SIU_LLD_EnableNotification((SIU_Icu_IRQ_ChannelType)ICU_IRQ_CHANNEL(hwChannel));
        }
    }
}

#if (ICU_GET_INPUT_STATE_API == STD_ON)
/*================================================================================================*/
/**
@brief      Icu driver function that gets the input state of ICU hardware channel.
@details    This function gets the state of ICU channel (eMIOS, SIU or WKUP)

@param[in]  numChl - The index of ICU channel for current configuration structure

@return     Icu_InputStateType
             - ICU_ACTIVE - An activation edge has been detected
             - ICU_IDLE - No activation edge has been detected.
*/
/*================================================================================================*/
FUNC (Icu_InputStateType, ICU_CODE) Icu_LLD_GetInputState(VAR(Icu_ChannelType, AUTOMATIC) numChl)
{
    VAR(Icu_InputStateType, AUTOMATIC) tempReturn = ICU_IDLE;
/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic - See @ref Icu_LLD_c_REF_4
*/     
    CONST(Icu_ChannelType, AUTOMATIC) hwChannel = Icu_Cfg_Ptr->Icu_ChannelId[numChl];

        /* If active edge detected already and status updated in ISR, this first condition MAY
           result true */
        if (ICU_CHANNEL_STATE_IDLE == Icu_LLD_GetBitChState(numChl, ICU_CHANNEL_STATE_IDLE))
        {
            tempReturn = ICU_ACTIVE;

            /* Clear IDLE status */
            Icu_LLD_ClearBitChState(numChl, ICU_CHANNEL_STATE_IDLE);
        }
        else if (hwChannel < ICU_MAX_eMIOS_CHANNELS)
        {
            if (eMIOS_LLD_GetInputState(ICU_eMIOS_CHANNEL(hwChannel)))
            {
                tempReturn = ICU_ACTIVE;
            }
        }
        else
        {
            if (SIU_LLD_GetInputState((SIU_Icu_IRQ_ChannelType)ICU_IRQ_CHANNEL(hwChannel)))
            {
                tempReturn = ICU_ACTIVE;
            }
        }

    return (tempReturn);
}
/* ICU_GET_INPUT_STATE_API */
#endif  

#if (ICU_TIMESTAMP_API == STD_ON)
/*================================================================================================*/
/**
@brief      Icu driver function that starts the time stamp of ICU hardware channel.
@details    This function starts the time stamp measurement of ICU channel.

@param[in]  numChl - The index of ICU channel for current configuration structure
@param[in]  msChannel - The index of Logical ICU channel
@param[in]  BufferPtr - Pointer to the buffer
@param[in]  BufferSize - Size of buffer
@param[in]  NotifyInterval - Notification interval time
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_LLD_StartTimestamp(VAR(Icu_ChannelType, AUTOMATIC) numChl,
                                           CONST(Icu_ChannelType, AUTOMATIC) msChannel,
                                           P2VAR(Icu_ValueType, AUTOMATIC, ICU_APPL_DATA) BufferPtr,
                                           VAR(uint16, AUTOMATIC) BufferSize,
                                           VAR(uint16, AUTOMATIC) NotifyInterval)
{
/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic - See @ref Icu_LLD_c_REF_4
*/     
    CONST(Icu_ChannelType, AUTOMATIC) hwChannel = Icu_Cfg_Ptr->Icu_ChannelId[numChl];

    /* Time stamp is running */
    Icu_LLD_SetBitChState(numChl, ICU_CHANNEL_STATE_RUNNING);

    SchM_Enter_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_05);
    {
        Icu_Buffer[msChannel]       = BufferPtr;
        Icu_BufferSize[msChannel]   = BufferSize;
        Icu_BufferNotify[msChannel] = NotifyInterval;
        Icu_NotifyCount[msChannel]  = 0U;
        Icu_BufferIndex[msChannel]  = 0U;
    }
    SchM_Exit_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_05);

    eMIOS_LLD_StartTimestamp(ICU_eMIOS_CHANNEL(hwChannel));
}
/* ICU_TIMESTAMP_API */
#endif  

#if (ICU_TIMESTAMP_API == STD_ON)
/*================================================================================================*/
/**
@brief      Icu driver function that stops the time stamp of ICU hardware channel.
@details    This function stops the time stamp measurement of ICU channel.

@param[in]  numChl - The index of ICU channel for current configuration structure
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_LLD_StopTimestamp(VAR(Icu_ChannelType, AUTOMATIC) numChl)
{
/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic - See @ref Icu_LLD_c_REF_4
*/     
    CONST(Icu_ChannelType, AUTOMATIC) hwChannel = Icu_Cfg_Ptr->Icu_ChannelId[numChl];

    /* Stop time stamp channel */
    Icu_LLD_ClearBitChState(numChl, ICU_CHANNEL_STATE_RUNNING);

    eMIOS_LLD_StopTimestamp(ICU_eMIOS_CHANNEL(hwChannel));
}
/* ICU_TIMESTAMP_API */
#endif  

#if (ICU_TIMESTAMP_API == STD_ON)
/*================================================================================================*/
/**
@brief      Icu driver function that gets the time stamp index of ICU logical channel.
@details    This function gets the time stamp measurement index of ICU logical channel.
            If Buffer pointer of channel is NULL_PTR then it returns value as 0 else
            it returns the value of time stamp index.

@param[in]  msChannel - The index of ICU channel for current configuration structure

@return     Icu_IndexType - Timestamp index
*/
/*================================================================================================*/
FUNC (Icu_IndexType, ICU_CODE) Icu_LLD_GetTimestampIndex(
                                                        CONST(Icu_ChannelType, AUTOMATIC) msChannel)
{
    VAR(Icu_IndexType, AUTOMATIC) tempIndex = 0U;

    /* The service shall return "0" in case the service is called before
     * Icu_StartTimestamp (no buffer is defined in this case).
     */
    SchM_Enter_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_06);
    {
        if (NULL_PTR == Icu_Buffer[msChannel])
        {
            tempIndex = 0U;
        }
        else
        {
            /* return timestamp index */
            tempIndex = Icu_BufferIndex[msChannel];
        }
    }
    SchM_Exit_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_06);

    return (tempIndex);
}
/* ICU_TIMESTAMP_API */
#endif  

#if ((ICU_EDGE_COUNT_API == STD_ON) || (ICU_TIMESTAMP_API == STD_ON))
/*================================================================================================*/
/**
@brief      Icu driver function that gets the status of ICU hardware channel.
@details    This function returns TRUE if channel is running else returns FALSE.

@param[in]  numChl - The index of ICU channel for current configuration structure

@return     boolean
             - true - if the given channel is running
             - false - if the channel is in idle state
*/
/*================================================================================================*/
FUNC (boolean, ICU_CODE) Icu_LLD_Channel_Get_Status(VAR(Icu_ChannelType, AUTOMATIC) numChl)
{
    return (boolean)((ICU_CHANNEL_STATE_RUNNING ==  \
        Icu_LLD_GetBitChState(numChl, ICU_CHANNEL_STATE_RUNNING)) ? TRUE : FALSE);
}
/* ((ICU_EDGE_COUNT_API == STD_ON) || (ICU_TIMESTAMP_API == STD_ON)) */
#endif 

#if (ICU_EDGE_COUNT_API == STD_ON)
/*================================================================================================*/
/**
@brief      Icu driver function that resets the edge counter measurement of ICU channel.
@details    This function:
             - Clears the overflow flag
             - Resets the edge counter measurement of ICU hardware channel

@param[in]  numChl - The index of ICU channel for current configuration structure
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_LLD_ResetEdgeCount(VAR(Icu_ChannelType, AUTOMATIC) numChl)
{
/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic - See @ref Icu_LLD_c_REF_4
*/     
    CONST(Icu_ChannelType, AUTOMATIC) hwChannel = Icu_Cfg_Ptr->Icu_ChannelId[numChl];
/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic - See @ref Icu_LLD_c_REF_4
*/     
    CONST(Icu_ChannelType, AUTOMATIC) msChannel = Icu_Cfg_Ptr->Icu_ChannelIndex[numChl];

    /* Clear overflow flag */
    Icu_LLD_ClearBitChState(numChl, ICU_CHANNEL_STATE_OVERFLOW);

    SchM_Enter_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_07);
    {
        /* Sync. variable with internal hardware eMIOS module counter */
        Icu_EdgeCount[msChannel] = (Icu_EdgeNumberType)EMIOS_INIT_CCNTR;
    }
    SchM_Exit_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_07);

    eMIOS_LLD_ResetEdgeCount(ICU_eMIOS_CHANNEL(hwChannel));
}
/* ICU_EDGE_COUNT_API */
#endif  

#if (ICU_EDGE_COUNT_API == STD_ON)
/*================================================================================================*/
/**
@brief      Icu driver function that enables the edge counter measurement of ICU channel.
@details    This function enables the edge counter measurement of ICU hardware channel

@param[in]  numChl - The index of ICU channel for current configuration structure
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_LLD_EnableEdgeCount(VAR(Icu_ChannelType, AUTOMATIC) numChl)
{
/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic - See @ref Icu_LLD_c_REF_4
*/     
    CONST(Icu_ChannelType, AUTOMATIC) hwChannel = Icu_Cfg_Ptr->Icu_ChannelId[numChl];
/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic - See @ref Icu_LLD_c_REF_4
*/     
    CONST(Icu_ChannelType, AUTOMATIC) msChannel = Icu_Cfg_Ptr->Icu_ChannelIndex[numChl];

    /* Edge counting enabled */
    Icu_LLD_SetBitChState(numChl, ICU_CHANNEL_STATE_RUNNING);

    eMIOS_LLD_EnableEdgeCount(ICU_eMIOS_CHANNEL(hwChannel),(uint32)Icu_EdgeCount[msChannel]);
}
/* ICU_EDGE_COUNT_API */
#endif  

#if (ICU_EDGE_COUNT_API == STD_ON)
/*================================================================================================*/
/**
@brief      Icu driver function that disables the edge counter measurement of ICU channel.
@details    This function disables the edge counter measurement of ICU hardware channel

@param[in]  numChl - The index of ICU channel for current configuration structure
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_LLD_DisableEdgeCount(VAR(Icu_ChannelType, AUTOMATIC) numChl)
{
/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic - See @ref Icu_LLD_c_REF_4
*/     
    CONST(Icu_ChannelType, AUTOMATIC) hwChannel = Icu_Cfg_Ptr->Icu_ChannelId[numChl];
/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic - See @ref Icu_LLD_c_REF_4
*/     
    CONST(Icu_ChannelType, AUTOMATIC) msChannel = Icu_Cfg_Ptr->Icu_ChannelIndex[numChl];
    VAR(uint32, AUTOMATIC) value = 0U;

/**
@note  Violates MISRA 2004 Advisory Rule 1.2, No reliance shall be placed on undefined or
       unspecified behavior See @ref Icu_LLD_c_REF_3 */
/*lint -save -e934*/
    eMIOS_LLD_DisableEdgeCount(ICU_eMIOS_CHANNEL(hwChannel), &value);
/*lint -restore*/

    SchM_Enter_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_08);
    {
        Icu_EdgeCount[msChannel] = (Icu_EdgeNumberType)value;
    }
    SchM_Exit_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_08);

    /* Edge counting stopped */
    Icu_LLD_ClearBitChState(numChl, ICU_CHANNEL_STATE_RUNNING);
}
/* ICU_EDGE_COUNT_API */
#endif  

#if (ICU_EDGE_COUNT_API == STD_ON)
/*================================================================================================*/
/**
@brief      Icu driver function thatgets edge counter measurement of ICU channel.
@details    his function returns counter value (the number of counter edges) of ICU channel

@param[in]  numChl - The index of ICU channel for current configuration structure

@return     Icu_EdgeNumberType - Counted edges number
*/
/*================================================================================================*/
FUNC (Icu_EdgeNumberType, ICU_CODE) Icu_LLD_GetEdgeNumbers(VAR(Icu_ChannelType, AUTOMATIC) numChl)
{
/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic - See @ref Icu_LLD_c_REF_4
*/     
    CONST(Icu_ChannelType, AUTOMATIC) hwChannel = Icu_Cfg_Ptr->Icu_ChannelId[numChl];
/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic - See @ref Icu_LLD_c_REF_4
*/     
    CONST(Icu_ChannelType, AUTOMATIC) msChannel = Icu_Cfg_Ptr->Icu_ChannelIndex[numChl];
    VAR(Icu_EdgeNumberType, AUTOMATIC) tempEdge = 0U;

    /* If MCB is activated, read must come from the counter register otherwise it must come from
       sync. variable */
    if (Icu_LLD_Channel_Get_Status(numChl))
    {
        tempEdge = (Icu_EdgeNumberType)eMIOS_LLD_GetEdgeNumbers(hwChannel);
    }
    else
    {
        SchM_Enter_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_09);
        {
            tempEdge = (Icu_EdgeNumberType)Icu_EdgeCount[msChannel];
        }
        SchM_Exit_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_09);
    }

    return (tempEdge);
}
/* ICU_EDGE_COUNT_API */
#endif  

#if ((ICU_EDGE_COUNT_API == STD_ON) || (ICU_TIMESTAMP_API == STD_ON) || \
     (ICU_GET_TIME_ELAPSED_API == STD_ON) || (ICU_GET_DUTY_CYCLE_VALUES_API == STD_ON) )
/*================================================================================================*/
/**
@brief      Icu driver function that checks overflow flag status of ICU channel
@details    This function returns the overflow status for the given channel and
            resets the channel status flag

@param[in]  numChl - The index of ICU channel for current configuration structure

@return     boolean
             - true - if an overflow event occurred for the given channel
             - false - if no overflow event occurred for the given channel
*/
/*================================================================================================*/
FUNC (boolean, ICU_CODE) Icu_LLD_Get_Overflow(VAR(Icu_ChannelType, AUTOMATIC) numChl)
{
    VAR(boolean, AUTOMATIC) result;
    result = (boolean)(  \
             (Icu_LLD_GetBitChState(numChl, ICU_CHANNEL_STATE_OVERFLOW) != 0U) ? TRUE : FALSE);

    if (result)
    {
        /* Reset overflow status flag of the logic channel */
        Icu_LLD_ClearBitChState(numChl, ICU_CHANNEL_STATE_OVERFLOW);
    }

    return result;
}
/* ((ICU_EDGE_COUNT_API == STD_ON) || (ICU_TIMESTAMP_API == STD_ON) || \
     (ICU_GET_TIME_ELAPSED_API == STD_ON) || (ICU_GET_DUTY_CYCLE_VALUES_API == STD_ON) ) */
#endif 

#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
/*================================================================================================*/
/**
@brief      Icu driver function that starts the signal measurement of ICU channel.
@details    This function:
            - Configures the Activation type depends on tempProperty value
            - starts the signal measurement of ICU channel.


@param[in]  tempPtr - Buffer pointer
@param[in]  hwChannel - ICU hardware channel number
@param[in]  tempProperty - Time measurement type (HIGH or LOW)
@param[in]  msChannel - The index of ICU logical channel
@param[in]  numChl - The index of ICU channel for current configuration structure
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_LLD_StartSignalMeasurement(
                                  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_APPL_CONST) tempPtr,
                                  CONST(Icu_ChannelType, AUTOMATIC) hwChannel,
                                  VAR(Icu_ParamType, AUTOMATIC) tempProperty,
                                  CONST(Icu_ChannelType, AUTOMATIC) msChannel,
                                  VAR(Icu_ChannelType, AUTOMATIC) numChl)
{
    eMIOS_ActivationType activation = EMIOS_RISING_EDGE;
    eMIOS_OperationMode  opmode = (eMIOS_OperationMode)((tempPtr->Icu_ParamValue &  \
                            ICU_EMIOS_UC_MODE_PARAM_MASK) >> ICU_EMIOS_UC_MODE_PARAM_SHIFT);

    /* Signal measurement is running */
    Icu_LLD_SetBitChState(numChl, ICU_CHANNEL_STATE_RUNNING);

    /* Clear the previous overflow status flag (if was the case) */
    Icu_LLD_ClearBitChState(numChl, ICU_CHANNEL_STATE_OVERFLOW);

    SchM_Enter_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_10);
    {
#if ((ICU_GET_TIME_ELAPSED_API == STD_ON) || (ICU_GET_DUTY_CYCLE_VALUES_API == STD_ON))
        Icu_ActivePulseWidth[msChannel] = 0U;
        Icu_Period[msChannel] = 0U;
/* ICU_GET_TIME_ELAPSED_API || ICU_GET_DUTY_CYCLE_VALUES_API */
#endif  

        /* Clear the counter for signal measurement */
        Icu_Int_Counter[msChannel] = 0U;
    }
    SchM_Exit_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_10);

#if (ICU_GET_TIME_ELAPSED_API == STD_ON)
    /* Configure channels to measure high and low time */
    if ((uint32)ICU_HIGH_TIME == tempProperty)
    {
        activation = EMIOS_RISING_EDGE;
    }
    else if ((uint32)ICU_LOW_TIME == tempProperty)
    {
        activation = EMIOS_FALLING_EDGE;
    }
    else
/* ICU_GET_TIME_ELAPSED_API== STD_ON */    
#endif 
    {
        /* Set Default Start Edge, signal can be start measured either by falling
           edge or rising edge */
        if ((Icu_ParamType)((Icu_ParamType)ICU_FALLING_EDGE << ICU_EDGE_PARAM_SHIFT) == \
            (Icu_ParamType)(tempPtr->Icu_ParamValue & ICU_EDGE_PARAM_MASK))
        {
            activation = EMIOS_FALLING_EDGE;
        }
        else
        {
            activation = EMIOS_RISING_EDGE;
        }
    }

    /* Start Signal Measurement */
    eMIOS_LLD_StartSignalMeasurement(hwChannel, activation, opmode);

    /* This service shall reset the state for the given channel to ICU_IDLE. */
    Icu_LLD_ClearBitChState(numChl, ICU_CHANNEL_STATE_IDLE);
}
/* ICU_SIGNAL_MEASUREMENT_API */
#endif  

#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
/*================================================================================================*/
/**
@brief      Icu driver function that stops the signal measurement of ICU channel.
@details    This function stops the signal measurement of ICU channel.

@param[in]  numChl - The index of ICU channel for current configuration structure
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_LLD_StopSignalMeasurement(VAR(Icu_ChannelType, AUTOMATIC) numChl)
{
/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic - See @ref Icu_LLD_c_REF_4
*/     
    CONST(Icu_ChannelType, AUTOMATIC) hwChannel = Icu_Cfg_Ptr->Icu_ChannelId[numChl];

    /* Signal Measurement stopped  */
    Icu_LLD_ClearBitChState(numChl, ICU_CHANNEL_STATE_RUNNING);

    eMIOS_LLD_StopSignalMeasurement(ICU_eMIOS_CHANNEL(hwChannel));
}
/* ICU_SIGNAL_MEASUREMENT_API */
#endif  

#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
/*================================================================================================*/
/**
@brief      Icu driver function that handles the signal measurement type interrupt.
@details    This service is  called when an  interrupt is recognized  as a Signal  Measurement type.
            There are two branch depending on  the sub-function selected: Duty Cycle or  OTHER. Duty
            Cycle requires  an extra  variable, because  three values  are required:  two flanks for
            active signal time and another flank for the end of the pulse. For calculating high, low
            and period is enough with the HW registers.

@param[in]  numChl - The index of ICU channel for current configuration structure
*/
/*================================================================================================*/
INLINE STATIC FUNC (void, ICU_CODE) Icu_LLD_SignalMeasurement(
                                                             VAR(Icu_ChannelType, AUTOMATIC) numChl)
{
/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic - See @ref Icu_LLD_c_REF_4
*/     
    CONST(Icu_ChannelType, AUTOMATIC) msChannel = Icu_Cfg_Ptr->Icu_ChannelIndex[numChl];
/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic - See @ref Icu_LLD_c_REF_4
*/     
    CONST(Icu_ChannelType, AUTOMATIC) hwChannel = Icu_Cfg_Ptr->Icu_ChannelId[numChl];
    VAR(Icu_MeasurementSubModeType, AUTOMATIC) measurement_property;
    VAR(uint32, ICU_VAR) tempA, tempB;
#ifdef SIGNAL_MEASUREMENT_USES_SAIC_MODE
    VAR(uint32, AUTOMATIC) previous_value;
    VAR(uint32, AUTOMATIC) pulse_width;
/* SIGNAL_MEASUREMENT_USES_SAIC_MODE */    
#endif   

    /* Read captured values */
    tempA = eMIOS_LLD_GetCaptureRegA(hwChannel);
    tempB = eMIOS_LLD_GetCaptureRegB(hwChannel);
/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic - See @ref Icu_LLD_c_REF_4
*/ 
    measurement_property = Icu_Cfg_Ptr->Icu_ChannelConfigPtr[numChl].Icu_Channel_Property;

    if ((Icu_Cfg_Ptr->Icu_ChannelConfigPtr[numChl].Icu_ParamValue & \
         ICU_EMIOS_UC_MODE_PARAM_MASK) ==  \
         ((Icu_ParamType)EMIOS_UC_IPWM_MODE << ICU_EMIOS_UC_MODE_PARAM_SHIFT))
       {
           if (((uint32)ICU_HIGH_TIME == measurement_property) || \
                ((uint32)ICU_LOW_TIME == measurement_property))
            {
             if (tempA > tempB)
                {
                 Icu_ActivePulseWidth[msChannel] = (Icu_ValueType)(tempA - tempB);
                }
             else     /*Counter overflow Case*/
                {            
                 Icu_ActivePulseWidth[msChannel] = \
                 (Icu_ValueType)(tempA + ((uint32)EMIOS_INTERNAL_COUNTER_MAX_COUNT - tempB));
                }     
            }

           else
            {

               /* Check if a complete signal was acquired */
               if (0U == Icu_Int_Counter[msChannel])
                {
                /* Mark that the complete signal was acquired */
                Icu_Int_Counter[msChannel] = 1U;
                }
               else
                {
                  /* Compute Period of the signal */
                  if (tempB > Icu_Start[msChannel])
                   {
                    Icu_Period[msChannel] = (Icu_ValueType)tempB - Icu_Start[msChannel];
                   }
                   else     /*Counter overflow Case */
                   {                
                    Icu_Period[msChannel] = (Icu_ValueType)(tempB + \
                    ((uint32)EMIOS_INTERNAL_COUNTER_MAX_COUNT - Icu_Start[msChannel]));
                   }                    
                   Icu_ActivePulseWidth[msChannel] = Icu_CapturedActivePulseWidth[msChannel];
                   Icu_LLD_SetBitChState(numChl, ICU_CHANNEL_STATE_IDLE);
                 }
           
                if (tempA > tempB)
                {
                 Icu_CapturedActivePulseWidth[msChannel] = (Icu_ValueType)(tempA - tempB);
                 }
                else     /*Counter overflow Case */
                {            
                 Icu_CapturedActivePulseWidth[msChannel] = (Icu_ValueType)(tempA + \
                 ((uint32)EMIOS_INTERNAL_COUNTER_MAX_COUNT - tempB));
                }            
                Icu_Start[msChannel]  = (Icu_ValueType)tempB;                
             }
         }

    else
#ifdef SIGNAL_MEASUREMENT_USES_SAIC_MODE
        if ((Icu_Cfg_Ptr->Icu_ChannelConfigPtr[numChl].Icu_ParamValue & \
             ICU_EMIOS_UC_MODE_PARAM_MASK) == (Icu_ParamType)((Icu_ParamType)EMIOS_UC_IPM_MODE << \
             ICU_EMIOS_UC_MODE_PARAM_SHIFT))
/* SIGNAL_MEASUREMENT_USES_SAIC_MODE */        
#endif   
    {
            Icu_Period[msChannel] = (Icu_ValueType)(tempA - tempB);
            Icu_LLD_SetBitChState(numChl, ICU_CHANNEL_STATE_IDLE);
    }
#ifdef SIGNAL_MEASUREMENT_USES_SAIC_MODE
    else
    {
        SchM_Enter_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_11);
        {

            eMIOS_LLD_SetActivationCondition(hwChannel, EMIOS_OPPOSITE_EDGES);

            if (Icu_Int_Counter[msChannel] == 0U)   /* store the first value */
            {
                Icu_Start[msChannel] = (Icu_ValueType)tempA;
                Icu_Int_Counter[msChannel]++;
            }
            else
            {
                previous_value = Icu_Start[msChannel];
                /* if first value is greater than the second value */
                if (tempA < previous_value)
                {
                    pulse_width = ((Icu_ValueType)EMIOS_COUNTER_MASK - previous_value) + tempA;
                }
                else
                {
                    pulse_width = tempA - previous_value;
                }

                /* HIGH TIME or LOW TIME measurement */
                if (((uint32)ICU_HIGH_TIME == measurement_property) || \
                     ((uint32)ICU_LOW_TIME == measurement_property))
                {
                    Icu_ActivePulseWidth[msChannel] = (Icu_ValueType)pulse_width;
                    /* clear to measure next LOW/HIGH pulse */
                    Icu_Int_Counter[msChannel] = 0U;
                    Icu_LLD_SetBitChState(numChl, ICU_CHANNEL_STATE_IDLE);
                }
                else
                {
                    /* DUTYCYCLE or PERIOD measurement */
                    if (Icu_Int_Counter[msChannel] == 1U)
                    {
                        /*capture active pulse width*/
                        Icu_CapturedActivePulseWidth[msChannel] = (Icu_ValueType)pulse_width;
                        Icu_Int_Counter[msChannel] = 2U;
                    }
                    else
                    {
                        /* counter = 2 */
                        Icu_Period[msChannel] = Icu_CapturedActivePulseWidth[msChannel] + \
                                                (Icu_ValueType)pulse_width;

                        /*active pulse width which is captured during previous interrupt*/
                        Icu_ActivePulseWidth[msChannel] = Icu_CapturedActivePulseWidth[msChannel];

                        /* set to 1 to find active pulse width next time */
                        Icu_Int_Counter[msChannel] = 1U;

                        Icu_LLD_SetBitChState(numChl, ICU_CHANNEL_STATE_IDLE);
                    }

                    /* store for next time */
                    Icu_Start[msChannel] = (Icu_ValueType)tempA;
                }
            }
        }
        SchM_Exit_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_11);
    }
/* SIGNAL_MEASUREMENT_USES_SAIC_MODE */    
#endif 
}
/* ICU_SIGNAL_MEASUREMENT_API */
#endif  

#if (ICU_TIMESTAMP_API == STD_ON)
/*================================================================================================*/
/**
@brief      Icu driver function that handles the timestamp measurement type interrupt.
@details    This service is  called when an  interrupt is recognized  as a Timestamp
Measurement type.

@param[in]  numChl - The index of ICU channel for current configuration structure

@remarks    Covers ICU216
@remarks    Implements DICU07000
*/
/*================================================================================================*/
INLINE STATIC FUNC (void, ICU_CODE) Icu_LLD_Timestamp(VAR(Icu_ChannelType, AUTOMATIC) numChl)
{
/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic - See @ref Icu_LLD_c_REF_4
*/     
    P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_APPL_CONST)  \
                                               tempPtr = &Icu_Cfg_Ptr->Icu_ChannelConfigPtr[numChl];
/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic - See @ref Icu_LLD_c_REF_4
*/     
    CONST(Icu_ChannelType, AUTOMATIC) hwChannel  = Icu_Cfg_Ptr->Icu_ChannelId[numChl];
/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic - See @ref Icu_LLD_c_REF_4
*/     
    CONST(Icu_ChannelType, AUTOMATIC) msChannel  = Icu_Cfg_Ptr->Icu_ChannelIndex[numChl];
    VAR(boolean, AUTOMATIC) stopChannel          = (boolean)FALSE;
    VAR(boolean, AUTOMATIC) callNotification     = (boolean)FALSE;

    SchM_Enter_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_12);
    {
        CONST(Icu_ValueType, AUTOMATIC) chBufferSize   = Icu_BufferSize[msChannel] ;
        CONST(Icu_ValueType, AUTOMATIC) chBufferNotify = Icu_BufferNotify[msChannel] ;
/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic - See @ref Icu_LLD_c_REF_4
*/ 
        /* Store timestamp */
        Icu_Buffer[msChannel][Icu_BufferIndex[msChannel]] = \
        (Icu_ValueType)eMIOS_GetTimeStamp(ICU_eMIOS_CHANNEL(hwChannel));

        Icu_BufferIndex[msChannel]++;
        if (Icu_BufferIndex[msChannel] >= chBufferSize)
        {
            /* If circular buffer, loop; if linear buffer, terminate. */
            if ((uint8)ICU_CIRCULAR_BUFFER == tempPtr->Icu_Channel_Property)
            {
                Icu_BufferIndex[msChannel] = 0U;
            }
            else
            {
                /* Linear buffer is full, stop the channel */
                stopChannel = (boolean)TRUE;
            }
        }

        /*
         *  [ICU134]: The Icu module shall only call a notification function if the following facts
                      are given:
         *      - A notification function is configured
         *      - The notification has been enabled by the call of Icu_EnableNotification()
         *      - NotifyInterval > 0
         *      - The number of events specified by NotifyInterval has been captured
         */
        if (chBufferNotify != 0U)
        {
            Icu_NotifyCount[msChannel]++;
            if (Icu_NotifyCount[msChannel] >= chBufferNotify)
            {
                Icu_NotifyCount[msChannel] = 0U;

                if ((0U != Icu_LLD_GetBitChState(numChl, ICU_CHANNEL_STATE_NOTIFICATION)) &&
                    (NULL_PTR != tempPtr->Icu_Channel_Notification))
                {
                    callNotification = (boolean)TRUE;
                }
            }
        }
    }
    SchM_Exit_Icu(SCHM_ICU_INSTANCE_0, ICU_EXCLUSIVE_AREA_12);


    /* Stop channel */
    if (stopChannel)
    {
        Icu_LLD_StopTimestamp(numChl);
    }

    /* Call User Notification Function and/or Wakeup Function */
    if (callNotification)
    {
        tempPtr->Icu_Channel_Notification();
    }
}
/* ICU_TIMESTAMP_API */
#endif  

/*================================================================================================*/
/**
@brief      Icu driver function that handles the interrupt of ICU channel.
@details    Interrupt function  that may  jump to  the WakeUp  function (Depending  on the  selected
            configuration)  and branches  to the  proper actions  depending the  mode in  which the
            channel is operating.

@param[in]  numChl - ICU logical channel
@param[in]  flags  - Interrupts Status Flags

@remarks    Covers ICU020, ICU021, ICU055, ICU056, ICU057
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_ProcessCommonInterrupt(VAR(Icu_ChannelType, AUTOMATIC) numChl,
                                                 VAR(uint32, AUTOMATIC) flags)
{
/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic - See @ref Icu_LLD_c_REF_4
*/     
    P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_APPL_CONST) tempPtr = \
                                                         &Icu_Cfg_Ptr->Icu_ChannelConfigPtr[numChl];

#if (ICU_ENABLE_WAKEUP_API == STD_ON)
    VAR(boolean, AUTOMATIC) chWakeupCapable;
    VAR(boolean, AUTOMATIC) crtModeSleep;

    chWakeupCapable = (ICU_CHANNEL_STATE_WKUP == Icu_LLD_GetBitChState(numChl, \
                       ICU_CHANNEL_STATE_WKUP))? (boolean)TRUE : (boolean)FALSE ;
    crtModeSleep    = (ICU_MODE_SLEEP == Icu_Current_Mode)? (boolean)TRUE : (boolean)FALSE ;
/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic - See @ref Icu_LLD_c_REF_4
*/     
    if ((chWakeupCapable==(boolean)TRUE) && (crtModeSleep==(boolean)TRUE))
    {
#if (ICU_REPORT_WAKEUP_SOURCE == STD_ON)
/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 17.4: Array indexing shall be the only allowed form of
pointer arithmetic - See @ref Icu_LLD_c_REF_4
*/ 
        EcuM_CheckWakeup(Icu_Cfg_Ptr->Icu_ChannelConfigPtr[numChl].Icu_Channel_WakeupValue);
/* ICU_REPORT_WAKEUP_SOURCE */    
#endif  
    }
/* ICU_ENABLE_WAKEUP_API */    
#endif  

    /* Verify configuration of channel and make the right processing */
    if (ICU_MODE_SIGNAL_EDGE_DETECT == tempPtr->Icu_Channel_Mode)
    {
        Icu_LLD_SetBitChState(numChl, ICU_CHANNEL_STATE_IDLE);

        if ((0U != Icu_LLD_GetBitChState(numChl, ICU_CHANNEL_STATE_NOTIFICATION)) &&
            (NULL_PTR != tempPtr->Icu_Channel_Notification))
        {
            tempPtr->Icu_Channel_Notification();
        }
    }
   
    else if ((Icu_LLD_CheckHwOverflowFlag(numChl, flags)==(boolean)TRUE) || 
             (ICU_MODE_EDGE_COUNTER == (tempPtr->Icu_Channel_Mode)))
    {
        Icu_LLD_SetBitChState(numChl, ICU_CHANNEL_STATE_OVERFLOW);

#if defined(ICU_OVERFLOW_NOTIFICATION_API) && (ICU_OVERFLOW_NOTIFICATION_API == STD_ON)
        if (NULL_PTR != tempPtr->Icu_Channel_OverFlowNotification)
        {
            tempPtr->Icu_Channel_OverFlowNotification();
        }
/* ICU_OVERFLOW_NOTIFICATION_API */    
#endif  
    }
    else
    {
        /* does nothing  - structure request by misra*/
    }

#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)
    if (ICU_MODE_SIGNAL_MEASUREMENT == tempPtr->Icu_Channel_Mode)
    {
        Icu_LLD_SignalMeasurement(numChl);
    }
/* ICU_SIGNAL_MEASUREMENT_API */    
#endif  

#if (ICU_TIMESTAMP_API == STD_ON)
    if (ICU_MODE_TIMESTAMP == tempPtr->Icu_Channel_Mode)
    {
        Icu_LLD_Timestamp(numChl);
    }
/* ICU_TIMESTAMP_API */    
#endif  
}


#if (ICU_DUAL_CLOCK_MODE == STD_ON)
/*================================================================================================*/
/**
@brief      This function changes the channel prescaler.
@details    This function sets all channels prescalers based on the input mode.

@param[in]  tempPtr   - Pointer to configuration structure
@param[in]  numChl    - The index of ICU channel for current configuration structure
@param[in]  Prescaler - Prescaler type ( Normal or Alternate )
@remarks    Covers PR-MCAL-3195
*/
/*================================================================================================*/
FUNC (void, ICU_CODE) Icu_LLD_SelectPrescaler(
                                  P2CONST(Icu_ChannelConfigType, AUTOMATIC, ICU_APPL_CONST) tempPtr,
                                  VAR(Icu_ChannelType, AUTOMATIC) numChl,
                                  VAR(Icu_SelectPrescalerType, AUTOMATIC) Prescaler)
{
    VAR(uint32, AUTOMATIC) ParamValue = 0x00000000U;
    CONST(Icu_ChannelType, AUTOMATIC) hwChannel = Icu_Cfg_Ptr->Icu_ChannelId[numChl];

    /* eMIOS Channel Configuration */
    if (hwChannel < ICU_MAX_eMIOS_CHANNELS)
    {
        if (ICU_NORMAL == Prescaler)
        {
            ParamValue = ((tempPtr->Icu_ParamValue & ICU_EMIOS_PRESCALER_PARAM_MASK) >> \
                                     ICU_EMIOS_PRESCALER_PARAM_SHIFT) << CCR_UCPRE_SHIFT;
        }
        else
        {
            ParamValue = ((tempPtr->Icu_ParamValue & ICU_EMIOS_PRESC_ALT_PARAM_MASK) >> \
                                     ICU_EMIOS_PRESC_ALT_PARAM_SHIFT) << CCR_UCPRE_SHIFT;
        }

        eMIOS_Icu_LLD_SelectPrescaler(ParamValue, ICU_eMIOS_CHANNEL(hwChannel));
    }
}
/* ICU_DUAL_CLOCK_MODE == STD_ON */
#endif 


#define ICU_STOP_SEC_CODE
/**
@file  Icu_LLD.c
@note  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
       "#include". See @ref Icu_LLD_c_REF_1
@note  Violates  MISRA  2004 Advisory Rule 19.15, Precautions shall be taken in order to prevent
       the contents of a header file being included twice -  See @ref Icu_LLD_c_REF_2
*/

/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif


