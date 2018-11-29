/**
    @file    Mcu_PBcfg.c
    @version 2.0.0

    @brief   AUTOSAR Mcu - Mcu postbuild configuration parameters.
    @details This file contains the mcu postbuild configuration parameters.
    
    Project AUTOSAR 3.0 MCAL
    Platform PA
    Peripheral FMPLL
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
@page misra_violations MISRA-C:2004 violations

@section Mcu_PBcfg_c_REF_1
Violates MISRA 2004 Advisory Rule 19.15, : Repeated include file MemMap.h, Precautions shall be
taken in order to prevent the contents of a header file being included twice This is not a violation
since all header files are protected against multiple inclusions

@section Mcu_PBcfg_c_REF_2
Violates  MISRA  2004 Advisory  Rule  19.1,  only preprocessor statements and comments before
'#include'
This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003
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
#include "Mcu_LLD.h"
/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/** @remarks Covers BSW00374, BSW00318 */
#define MCU_VENDOR_ID_PBCFG_C         43
#define MCU_AR_MAJOR_VERSION_PBCFG_C  3
#define MCU_AR_MINOR_VERSION_PBCFG_C  0
#define MCU_AR_PATCH_VERSION_PBCFG_C  0
#define MCU_SW_MAJOR_VERSION_PBCFG_C  2
#define MCU_SW_MINOR_VERSION_PBCFG_C  0
#define MCU_SW_PATCH_VERSION_PBCFG_C  0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and MCU lld header file are of the same vendor */
#if (MCU_VENDOR_ID_PBCFG_C != MCU_LLD_VENDOR_ID)
    #error "Mcu_Cfg.c and Mcu_LLD.h have different vendor ids"
#endif
#ifdef CHECK_AUTOSAR_VERSION
    /* Check if source file and Mcu_LLD header file are of the same Autosar version */
    #if ((MCU_AR_MAJOR_VERSION_PBCFG_C != MCU_LLD_AR_MAJOR_VERSION) || \
         (MCU_AR_MINOR_VERSION_PBCFG_C != MCU_LLD_AR_MINOR_VERSION) || \
         (MCU_AR_PATCH_VERSION_PBCFG_C != MCU_LLD_AR_PATCH_VERSION))
        #error "AutoSar Version Numbers of Mcu_PBcfg.c and Mcu_LLD.h are different"
    #endif
#endif
/* Check if source file and Mcu_LLD header file are of the same Software version */
#if ((MCU_SW_MAJOR_VERSION_PBCFG_C != MCU_LLD_SW_MAJOR_VERSION) || \
     (MCU_SW_MINOR_VERSION_PBCFG_C != MCU_LLD_SW_MINOR_VERSION) || \
     (MCU_SW_PATCH_VERSION_PBCFG_C != MCU_LLD_SW_PATCH_VERSION))
    #error "Software Version Numbers of Mcu_PBcfg.c and Mcu_LLD.h are different"
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
#define MCU_START_CONFIG_DATA_UNSPECIFIED
/** @note  Violates MISRA 2004 Advisory Rule 19.15, Repeated include file, See @ref Mcu_PBcfg_c_REF_1*/
#include "MemMap.h"

[!INCLUDE "Mcu_RegOperations.m"!][!//

[!LOOP "McuModuleConfiguration/*"!][!//

[!NOCODE!][!//
[!INCLUDE "Mcu_checkvalues.m"!][!//

[!VAR "EOLN"!][!// Auxiliary variable for EOF line constant
[!ENDVAR!][!//
[!VAR "Externs" = "''"!][!//
[!LOOP "McuRamSectorSettingConf/*"!][!//
[!// Get Externs
[!IF "McuRamSectionBaseAddrLinkerSym != ''"!][!//
      [!VAR "Externs" = "concat($Externs,'extern  uint32 ',McuRamSectionBaseAddrLinkerSym,'[];',$EOLN)"!]
   [!ENDIF!]
    [!IF "McuRamSectionSizeLinkerSym != ''"!][!//
      [!VAR "Externs" = "concat($Externs,'extern  uint32 ',McuRamSectionSizeLinkerSym,'[];',$EOLN)"!]
   [!ENDIF!]
[!ENDLOOP!]
/* extern definition of linker symbols used in Mcu_RamConfig */
[!ENDNOCODE!][!//
[!"$Externs"!][!//

[!IF "num:i(count(McuRamSectorSettingConf/*))>0"!][!//
[!VAR "var"= "1"!][!VAR "RamSector"= "num:i(count(McuRamSectorSettingConf/*))-1"!]
STATIC CONST(Mcu_RamConfigType, MCU_CONST) Mcu_RamConfigPB_[!"num:i(@index+1)"!][[!"num:i(count(McuRamSectorSettingConf/*))"!]]  = {
[!LOOP "McuRamSectorSettingConf/*"!][!//
/* MISRA-C:2004 19.1 VIOLATION: Refer to REF 1 above*/
[!VAR "PBindex" = "@index"!][!//
[!NOCODE!][!//
[!CALL "MCheckRamSection"!][!//
[!ENDNOCODE!][!//
  [!IF "$RamSector>=$var"!]
    {/* start of Mcu_RamConfig[[!"@index"!]] */
[!IF "McuRamSectionBaseAddrLinkerSym = ''"!][!//
    (uint32 *)[!"num:inttohex(McuRamSectionBaseAddress,8)"!]UL[!//
[!ELSE!][!//
    (uint32)[!"McuRamSectionBaseAddrLinkerSym"!][!//
[!ENDIF!][!//
,/*section base address (must be aligned to 4 bytes) */
[!IF "McuRamSectionSizeLinkerSym = ''"!][!//
    (uint32)[!"num:inttohex(McuRamSectionSize,8)"!]UL[!//
[!ELSE!][!//
    (uint32)[!"McuRamSectionSizeLinkerSym"!][!//
[!ENDIF!][!//
,/* section size in bytes (must be multiple of 4) */
    (uint32)[!"num:inttohex(McuRamDefaultValue,8)"!]ul /* value to be filled with */
    },[!ELSE!]
    {/* start of Mcu_RamConfig[[!"@index"!]] */
[!IF "McuRamSectionBaseAddrLinkerSym = ''"!][!//
    (uint32 *)[!"num:inttohex(McuRamSectionBaseAddress,8)"!]UL[!//
[!ELSE!][!//
    (uint32)[!"McuRamSectionBaseAddrLinkerSym"!][!//
[!ENDIF!][!//
,             /* section base address (must be aligned to 4 bytes) */
[!IF "McuRamSectionSizeLinkerSym = ''"!][!//
    (uint32)[!"num:inttohex(McuRamSectionSize,8)"!]UL[!//
[!ELSE!][!//
    (uint32) [!"McuRamSectionSizeLinkerSym"!][!//
[!ENDIF!][!//
,        /* section size in bytes (must be multiple of 4) */
    (uint32)[!"num:inttohex(McuRamDefaultValue,8)"!]ul /* value to be filled with */
    }[!ENDIF!][!VAR "var"= "$var+1"!]
 /* end of Mcu_RamConfig[[!"@index"!]] */
[!ENDLOOP!]
};[!// End of McuRamSectorSettingConf
[!ENDIF!][!//
[!//

[!VAR "Mode"= "num:i(count(McuModeSettingConf/*))-1"!]
[!IF "num:i(count(McuModeSettingConf/*))>0"!][!//
STATIC CONST(Mcu_ModeConfigType, MCU_CONST) Mcu_ModeConfigPB_[!"num:i(@index+1)"!][[!"num:i(count(McuModeSettingConf/*))"!]] ={
[!LOOP "McuModeSettingConf/*"!][!VAR "PBindex" = "@index"!][!//
 /* start of Mcu_ModeConfig[[!"@index"!]] */
  {
    [!"HaltRegister/SIU_HLTACKTimeOut"!]UL,
    ([!IF "HaltRegister/HaltCPU"!]MCU_HALT_CPU_AND_PLATFORM_CLOCK|[!ELSE!]MCU_KEEP_CPU_AND_PLATFORM_CLOCK|[!ENDIF!]
    [!IF "HaltRegister/HaltNDEDI"!]MCU_HALT_NDEDI_CLOCK|[!ELSE!]MCU_KEEP_NDEDI_CLOCK|[!ENDIF!]
    [!IF "HaltRegister/HalteTPU"!]MCU_HALT_ETPU_CLOCK|[!ELSE!]MCU_KEEP_ETPU_CLOCK|[!ENDIF!]
    [!IF "HaltRegister/HaltNPC"!]MCU_HALT_NPC_CLOCK|[!ELSE!]MCU_KEEP_NPC_CLOCK|[!ENDIF!]
    [!IF "HaltRegister/HaltEBI"!]MCU_HALT_EBI_CLOCK|[!ELSE!]MCU_KEEP_EBI_CLOCK|[!ENDIF!]
    [!IF "HaltRegister/HaltADC"!]MCU_HALT_ADC_CLOCK|[!ELSE!]MCU_KEEP_ADC_CLOCK|[!ENDIF!]
    [!IF "HaltRegister/HalteMIOS"!]MCU_HALT_EMIOS_CLOCK|[!ELSE!]MCU_KEEP_EMIOS_CLOCK|[!ENDIF!]
    [!IF "HaltRegister/HaltDFILT"!]MCU_HALT_DFILT_CLOCK|[!ELSE!]MCU_KEEP_DFILT_CLOCK|[!ENDIF!]
    [!IF "HaltRegister/HaltPIT"!]MCU_HALT_PIT_CLOCK|[!ELSE!]MCU_KEEP_PIT_CLOCK|[!ENDIF!]
    [!IF "HaltRegister/HaltFlexCAN_C"!]MCU_HALT_FLEXCAN_C_CLOCK|[!ELSE!]MCU_KEEP_FLEXCAN_C_CLOCK|[!ENDIF!]
    [!IF "HaltRegister/HaltFlexCAN_A"!]MCU_HALT_FLEXCAN_A_CLOCK|[!ELSE!]MCU_KEEP_FLEXCAN_A_CLOCK|[!ENDIF!]
    [!IF "HaltRegister/HaltDSPI_C"!]MCU_HALT_DSPI_C_CLOCK|[!ELSE!]MCU_KEEP_DSPI_C_CLOCK|[!ENDIF!]
    [!IF "HaltRegister/HaltDSPI_B"!]MCU_HALT_DSPI_B_CLOCK|[!ELSE!]MCU_KEEP_DSPI_B_CLOCK|[!ENDIF!]
    [!IF "HaltRegister/HalteSCI_B"!]MCU_HALT_ESCI_B_CLOCK|[!ELSE!]MCU_KEEP_ESCI_B_CLOCK|[!ENDIF!]
    [!IF "HaltRegister/HalteSCI_A"!]MCU_HALT_ESCI_A_CLOCK[!ELSE!]MCU_KEEP_ESCI_A_CLOCK[!ENDIF!])
  }[!IF "$PBindex<$Mode"!],[!ENDIF!]
/* end of Mcu_ModeConfig[[!"@index"!]] */
[!ENDLOOP!]
};[!//
[!ENDIF!][!//
[!//

[!VAR "Mode"= "num:i(count(McuClockSettingConfig/McuClockReferencePoint/*))-1"!]
[!IF "num:i(count(McuClockSettingConfig/McuClockReferencePoint/*))>0"!][!//
STATIC CONST(Mcu_ClockConfigType, MCU_CONST) Mcu_ClockConfigPB_[!"num:i(@index+1)"!][[!"num:i(count(McuClockSettingConfig/McuClockReferencePoint/*))"!]] = {[!//
[!LOOP "McuClockSettingConfig/McuClockReferencePoint/*"!][!//
/* start of Mcu_ClockConfig[[!"@index"!]] */
    {
[!NOCODE!][!//
[!VAR "PBindex" = "@index"!][!//

    [!VAR "RegValue"="0"!][!//
        [!CALL "Enum2RegValue", "RegValue" = "$RegValue", "ItemName" = "McuEMIOSSettings/MdisBit", "Descriptor" ="'1,1,32##false:0;true:1;:0'"!][!//
        [!CALL "Enum2RegValue", "RegValue" = "$RegValue", "ItemName" = "McuEMIOSSettings/GlobalTimeBaseEnable", "Descriptor" ="'3,3,32##false:0;true:1;:0'"!][!//
        [!CALL "Enum2RegValue", "RegValue" = "$RegValue", "ItemName" = "McuEMIOSSettings/ExternalTimeBase", "Descriptor" ="'4,4,32##false:0;true:1;:0'"!][!//
        [!CALL "Enum2RegValue", "RegValue" = "$RegValue", "ItemName" = "McuEMIOSSettings/FreezeBit", "Descriptor" ="'2,2,32##false:0;true:1;:0'"!][!//
        [!CALL "Enum2RegValue", "RegValue" = "$RegValue", "ItemName" = "McuEMIOSSettings/GlobalPrescalerEnable", "Descriptor" ="'5,5,32##false:0;true:1;:0'"!][!//
        [!CALL "BitGroup2RegValue", "RegValue" = "$RegValue", "Value"= "McuEMIOSSettings/GlobalPrescaler", "StartBit" = "23", "BitWidth" = "8", "RegWidth"="32"!][!//
        [!CALL "BitGroup2RegValue", "RegValue" = "$RegValue", "Value"= "McuEMIOSSettings/ServerTimeSlot", "StartBit" = "15", "BitWidth" = "4", "RegWidth"="32"!][!//
    [!VAR "EMIOS_MCR"="$RegValue"!][!//

    [!VAR "MCUFlashBIUCR0clkdep"!]
        [!CALL "MCUFlashclkdep0" , "F"="McuClockReferencePointFrequency", "APC" = "McuFlashBIUCR0/AddressPipeliningControl", "WWSC" = "McuFlashBIUCR0/WriteWaitStateControl", "RWSC" = "McuFlashBIUCR0/ReadWaitStateControl"!]
    [!ENDVAR!]

 [!ENDNOCODE!]
 
/*[!"GeneralClockSettings/McuOperatingMode "!]*/
  ([!IF "GeneralClockSettings/McuOperatingMode = 'Enhanced'"!]MCU_ENHANCED_MODE|[!ELSE!]MCU_LEGACY_MODE|[!ENDIF!]
   [!IF "GeneralClockSettings/McuBypassDivider"!]MCU_BYPASS_SYSTEM_DIVIDER[!IF "node:exists(GeneralClockSettings/McuSystemClockDivider)"!]|[!ENDIF!][!ELSE!]MCU_NO_BYPASS_SYSTEM_DIVIDER[!IF "node:exists(GeneralClockSettings/McuSystemClockDivider)"!]|[!ENDIF!][!ENDIF!]
   [!IF "node:exists(GeneralClockSettings/McuSystemClockDivider)"!][!IF "GeneralClockSettings/McuSystemClockDivider = 2"!]MCU_DIVIDE_SYSTEM_CLOCK_BY_2[!ELSEIF "GeneralClockSettings/McuSystemClockDivider = 4"!]MCU_DIVIDE_SYSTEM_CLOCK_BY_4[!ELSEIF "GeneralClockSettings/McuSystemClockDivider = 8"!]MCU_DIVIDE_SYSTEM_CLOCK_BY_8[!ELSE!]MCU_DIVIDE_SYSTEM_CLOCK_BY_16[!ENDIF!][!ENDIF!]),
  (
   [!IF "McuExternalClock/McuExternalBusTapSelect"!]MCU_EXT_BUS_TAP_SELECTED|[!ELSE!]MCU_EXT_BUS_TAP_NOT_SELECTED|[!ENDIF!]
   MCU_EXT_BUS_DIV([!"McuExternalClock/McuExternalBusDivisonFactor"!])),
   (MCU_EIGHT_VALUE << MCU_SHIFT_TWENTY_EIGHT) |
   [!IF "node:exists(McuPll/McuPllMode)"!][!IF "McuPll/McuPllMode = 'PLLOffMode'"!](MCU_ONE_VALUE << MCU_SHIFT_TWENTY_EIGHT[!ELSE!](MCU_PLL_NORMAL_MODE[!ENDIF!][!ELSE!](MCU_PLL_NORMAL_MODE[!ENDIF!][!IF "node:exists(McuPll/McuPllParameter/McuInputDivideRatio)"!]|[!ELSE!]),[!ENDIF!][!//
   [!IF "node:exists(McuPll/McuPllParameter/McuInputDivideRatio)"!]MCU_PLL_INPUT_DIVIDE_RATIO([!"num:i(num:i(McuPll/McuPllParameter/McuInputDivideRatio) - num:i(1))"!])|[!ENDIF!]
   [!IF "node:exists(McuPll/McuPllParameter/McuFeedbackDivideRatio)"!]MCU_PLL_FEEDBACK_DIVIDE_RATIO([!"num:i(num:i(McuPll/McuPllParameter/McuFeedbackDivideRatio))"!])),[!ENDIF!][!//
  ([!IF "node:exists(McuPll/McuPllParameter/McuLossOfClockEnable)"!][!IF "McuPll/McuPllParameter/McuLossOfClockEnable"!]MCU_PLL_LOSS_OF_CLOCK_ENABLE|[!ELSE!]MCU_PLL_LOSS_OF_CLOCK_DISABLE|[!ENDIF!][!ENDIF!][!//
   [!IF "node:exists(McuPll/McuPllParameter/McuLossOfLockResetEnable)"!][!IF "McuPll/McuPllParameter/McuLossOfLockResetEnable"!]MCU_PLL_LOSS_OF_LOCK_RESET_ENABLE|[!ELSE!]MCU_PLL_LOSS_OF_LOCK_RESET_DISABLE|[!ENDIF!][!ELSE!]MCU_PLL_LOSS_OF_LOCK_RESET_DISABLE|[!ENDIF!][!//
   [!IF "node:exists(McuPll/McuPllParameter/McuLossOfClockResetEnable)"!][!IF "McuPll/McuPllParameter/McuLossOfClockResetEnable"!]MCU_PLL_LOSS_OF_CLOCK_RESET_ENABLE|[!ELSE!]MCU_PLL_LOSS_OF_CLOCK_RESET_DISABLE|[!ENDIF!][!ELSE!]MCU_PLL_LOSS_OF_CLOCK_RESET_DISABLE|[!ENDIF!][!//
   [!IF "node:exists(McuPll/McuPllParameter/McuLossOfLockInterruptRequest)"!][!IF "McuPll/McuPllParameter/McuLossOfLockInterruptRequest"!]MCU_PLL_LOSS_OF_LOCK_INTR_ENABLE|[!ELSE!]MCU_PLL_LOSS_OF_LOCK_INTR_DISABLE|[!ENDIF!][!ELSE!]MCU_PLL_LOSS_OF_LOCK_INTR_DISABLE|[!ENDIF!]
   [!IF "node:exists(McuPll/McuPllParameter/McuLossOfClockInterruptRequest)"!][!IF "McuPll/McuPllParameter/McuLossOfClockInterruptRequest"!]MCU_PLL_LOSS_OF_CLOCK_INTR_ENABLE|[!ELSE!]MCU_PLL_LOSS_OF_CLOCK_INTR_DISABLE|[!ENDIF!][!ELSE!]MCU_PLL_LOSS_OF_CLOCK_INTR_DISABLE|[!ENDIF!][!// 
   [!IF "node:exists(McuPll/McuPllParameter/McuOutputDivideRatio)"!]MCU_PLL_OUTPUT_DIVIDE_RATIO([!"num:i(num:i(McuPll/McuPllParameter/McuOutputDivideRatio))"!])),[!ENDIF!]
   [!IF "McuPll/McuPllParameter/MODEN"!]([!IF "McuPll/McuPllParameter/MODEN"!]FMPLL_SYNFMMR_MODEN_EN[!ELSE!]FMPLL_SYNFMMR_MODEN_DIS[!ENDIF!]|
   [!IF "McuPll/McuPllParameter/MODSEL"!]FMPLL_SYNFMMR_MODSEL_BELOW[!ELSE!]FMPLL_SYNFMMR_MODSEL_CENTERED[!ENDIF!]|
   [!IF "node:exists(McuPll/McuPllParameter/McuModulationRate)"!]FMPLL_SYNFMMR_MODPERIOD([!"num:i((number(../../CrystalFrequencyHz) div (4*(McuPll/McuPllParameter/McuInputDivideRatio)*(McuPll/McuPllParameter/McuModulationRate)))+0.5)"!])|[!ENDIF!][!//
   [!IF "McuPll/McuPllParameter/MODSEL"!]FMPLL_SYNFMMR_INCSTEP([!" num:i(((32767*McuPll/McuPllParameter/McuPeaktoPeakModulationDepth*McuPll/McuPllParameter/McuFeedbackDivideRatio) div (500*(num:i((number(../../CrystalFrequencyHz)div(McuPll/McuPllParameter/McuInputDivideRatio*4*McuPll/McuPllParameter/McuModulationRate))+0.5))))+0.5)"!])),  /* Below */ [!ELSE!]FMPLL_SYNFMMR_INCSTEP([!"num:i(((32767*McuPll/McuPllParameter/McuPeaktoPeakModulationDepth*McuPll/McuPllParameter/McuFeedbackDivideRatio) div (1000*(num:i((number(../../CrystalFrequencyHz)div(McuPll/McuPllParameter/McuInputDivideRatio*4*McuPll/McuPllParameter/McuModulationRate))+0.5))))+0.5)"!])), /* Centered */ [!ENDIF!][!//
   [!ELSE!]FMPLL_SYNFMMR_RESET_VALUE,[!ENDIF!][!//  

   [!"num:inttohex($EMIOS_MCR,8)"!]UL,   /*  eMIOS */
   [!"num:inttohex($MCUFlashBIUCR0clkdep,8)"!]UL    /* BIUCR0 system clock dependent values*/
    }[!IF "$PBindex<$Mode"!],[!ENDIF!]
/* end of Mcu_ClockConfig[[!"@index"!]] */
[!ENDLOOP!][!//
};[!//
[!ENDIF!][!//
[!//

STATIC CONST(McuLLD_ConfigType, MCU_CONST) McuLLD_ConfigPB_[!"num:i(@index+1)"!] =
    {
[!NOCODE!][!//
    [!VAR "CPR_A0"="num:hextoint('0x00010203')"!]
    [!VAR "CPR_A4"="num:hextoint('0x04050607')"!]
    [!VAR "CPR_A8"="num:hextoint('0x08090A0B')"!]
    [!VAR "CPR_A12"="num:hextoint('0x0C0D0E0F')"!]
    [!VAR "CPR_A16"="num:hextoint('0x00010203')"!]
    [!VAR "CPR_A20"="num:hextoint('0x04050607')"!]
    [!VAR "CPR_A24"="num:hextoint('0x08090A0B')"!]
    [!VAR "CPR_A28"="num:hextoint('0x0C0D0E0F')"!]
    
    [!VAR "CPR_B0"="num:hextoint('0x00010203')"!]
    [!VAR "CPR_B4"="num:hextoint('0x04050607')"!]
    [!VAR "CPR_B8"="num:hextoint('0x08090A0B')"!]
    [!VAR "CPR_B12"="num:hextoint('0x0C0D0E0F')"!]
    [!VAR "CPR_B16"="num:hextoint('0x00010203')"!]
    [!VAR "CPR_B20"="num:hextoint('0x04050607')"!]
    [!VAR "CPR_B24"="num:hextoint('0x08090A0B')"!]
    [!VAR "CPR_B28"="num:hextoint('0x0C0D0E0F')"!]
    
    [!VAR "EDMA_A_CR"="0"!]
    [!VAR "EDMA_A_count"="num:i(count(McuEDMA_A_Config/*))"!]

    [!VAR "BIUCR0"!]
        [!CALL "MCUFlashBIUCR0", "GCE" = "McuFlashBIUCR/GlobalConfigurationEnable", "M3PFE" = "McuFlashBIUCR/Master3PrefetchEnable", "M2PFE" = "McuFlashBIUCR/Master2PrefetchEnable", "M1PFE" = "McuFlashBIUCR/Master1PrefetchEnable", "M0PFE" = "McuFlashBIUCR/Master0PrefetchEnable", "IPFEN" = "McuFlashBIUCR/McuInstructionPrefetchEnable", "DPFEN" = "McuFlashBIUCR/McuDataPrefetchEnable", "PFLIM" = "McuFlashBIUCR/McuPFLASHPrefetchLimit", "BFEN" = "McuFlashBIUCR/McuPFLASHLineReadBuffersEnable"!]
    [!ENDVAR!]

    [!VAR "BIUAPR"!]
        [!CALL "MCUFlashBIUAPR", "M3AP" = "McuFlashBIUAPR/Master3AccessProtection", "M2AP" = "McuFlashBIUAPR/Master2AccessProtection", "M1AP" = "McuFlashBIUAPR/Master1AccessProtection", "M0AP" = "McuFlashBIUAPR/Master0AccessProtection"!]
    [!ENDVAR!]

    [!VAR "BIUCR1"!]
        [!CALL "MCUFlashBIUCR1", "LBCFG" = "McuFlashBIUCR2/McuLineBufferConfiguration"!]
    [!ENDVAR!]

  [!IF "$EDMA_A_count!=0"!][!// only if McuEDMA_A_Config exists
    [!VAR "RegValue"!]
    [!CALL "EDMACR","ERGA" = "McuEDMA_A_Config/ERGA", "ERCA" = "McuEDMA_A_Config/ERCA","EDBG" = "McuEDMA_A_Config/EDBG", "EBW" = "McuEDMA_A_Config/EBW", "GRP0PRI" = "McuEDMA_A_Config/GRP0PRI", "GRP1PRI" = "McuEDMA_A_Config/GRP1PRI", "GRP2PRI" = "McuEDMA_A_Config/GRP2PRI", "GRP3PRI" = "McuEDMA_A_Config/GRP3PRI"!]
    [!ENDVAR!]
    [!VAR "EDMA_A_CR"="$RegValue"!]
    [!VAR "CPR_A0"="McuEDMA_A_Config/eDMAChannelPriority0"!]
    [!VAR "CPR_A4"="McuEDMA_A_Config/eDMAChannelPriority4"!]
    [!VAR "CPR_A8"="McuEDMA_A_Config/eDMAChannelPriority8"!]
    [!VAR "CPR_A12"="McuEDMA_A_Config/eDMAChannelPriority12"!]
    [!VAR "CPR_A16"="McuEDMA_A_Config/eDMAChannelPriority16"!]
    [!VAR "CPR_A20"="McuEDMA_A_Config/eDMAChannelPriority20"!]
    [!VAR "CPR_A24"="McuEDMA_A_Config/eDMAChannelPriority24"!]
    [!VAR "CPR_A28"="McuEDMA_A_Config/eDMAChannelPriority28"!]
  [!ENDIF!]
  

[!ENDNOCODE!][!//
    [!CODE!]    [!IF "McuResetSource/McuResetType = 'SoftwareSystemReset'"!]MCU_SW_SYS_RESET[!ELSEIF "McuResetSource/McuResetType = 'CheckstopReset'"!]MCU_CHKSTOP_RESET[!ELSE!]MCU_SW_EXT_RESET[!ENDIF!],[!ENDCODE!]
    [!CODE!]    {{(uint32)[!"num:inttohex($EDMA_A_CR,8)"!]UL },      /* EDMA_A.CR */[!ENDCODE!]
    [!CODE!]    {(uint8)[!"num:inttohex(bit:and(bit:shr($CPR_A0,24),255),2)"!]U, /* EDMA_A.CPR_A[0] */(uint8)[!"num:inttohex(bit:and(bit:shr($CPR_A0,16),255),2)"!]U, /* EDMA_A.CPR_A[1] */(uint8)[!"num:inttohex(bit:and(bit:shr($CPR_A0,8),255),2)"!]U, /* EDMA_A.CPR_A[2] */(uint8)[!"num:inttohex(bit:and($CPR_A0,255),2)"!]U, /* EDMA_A.CPR_A[3] */[!ENDCODE!]
[!FOR "x" = "0" TO "3"!]    [!CODE!]    (uint8) [!"num:inttohex(bit:and(bit:shr($CPR_A4,(24 - $x*8)),255),2)"!]U, /* EDMA_A.CPR_A[!"num:i($x+4)"!] */[!ENDCODE!][!ENDFOR!]
[!FOR "x" = "0" TO "3"!]    [!CODE!]    (uint8) [!"num:inttohex(bit:and(bit:shr($CPR_A8,(24 - $x*8)),255),2)"!]U, /* EDMA_A.CPR_A[!"num:i($x+8)"!] */[!ENDCODE!][!ENDFOR!]
[!FOR "x" = "0" TO "3"!]    [!CODE!]    (uint8) [!"num:inttohex(bit:and(bit:shr($CPR_A12,(24 - $x*8)),255),2)"!]U, /* EDMA_A.CPR_A[!"num:i($x+12)"!] */[!ENDCODE!][!ENDFOR!]
[!FOR "x" = "0" TO "3"!]    [!CODE!]    (uint8) [!"num:inttohex(bit:and(bit:shr($CPR_A16,(24 - $x*8)),255),2)"!]U, /* EDMA_A.CPR_A[!"num:i($x+16)"!] */[!ENDCODE!][!ENDFOR!]
[!FOR "x" = "0" TO "3"!]    [!CODE!]    (uint8) [!"num:inttohex(bit:and(bit:shr($CPR_A20,(24 - $x*8)),255),2)"!]U, /* EDMA_A.CPR_A[!"num:i($x+20)"!] */[!ENDCODE!][!ENDFOR!]
[!FOR "x" = "0" TO "3"!]    [!CODE!]    (uint8) [!"num:inttohex(bit:and(bit:shr($CPR_A24,(24 - $x*8)),255),2)"!]U, /* EDMA_A.CPR_A[!"num:i($x+24)"!] */[!ENDCODE!][!ENDFOR!]
[!FOR "x" = "0" TO "3"!]    [!CODE!]    (uint8) [!"num:inttohex(bit:and(bit:shr($CPR_A28,(24 - $x*8)),255),2)"!]U, /* EDMA_A.CPR_A[!"num:i($x+28)"!] */[!ENDCODE!][!ENDFOR!]
         },
    0UL},
    [!CODE!]    (uint32)[!"num:inttohex($BIUCR0,8)"!]UL,        /* BIUCR0 */[!ENDCODE!]
    [!CODE!]    (uint32)[!"num:inttohex($BIUCR1,8)"!]UL,        /* BIUCR1 */[!ENDCODE!]
    [!CODE!]    (uint32)[!"num:inttohex($BIUAPR,8)"!]UL         /* BIUAPR */[!ENDCODE!]       
    };
    
[!//

CONST(Mcu_ConfigType, MCU_CONST) [!"@name"!] =
    {
        [!IF "McuClockSrcFailureNotification = 'ENABLED'"!]MCU_CLOCKNOTIFICATION_ENABLE[!ELSE!]MCU_CLOCKNOTIFICATION_DISABLE[!ENDIF!],    /* globally enable/disable SCM, loss of clock and loss of lock notification */
        [!"num:i(count(McuRamSectorSettingConf/*))"!]UL,                       /* number of ram sections */
        [!"num:i(count(McuModeSettingConf/*))"!]UL,                       /* number of low power modes */
        [!"num:i(count(McuClockSettingConfig/McuClockReferencePoint/*))"!]UL,                       /* number of clock settings */
        [!"num:inttohex(McuClockSettingConfig/McuTimeout,8)"!]UL,                                   /* McuTimeout */
        [!IF "num:i(count(McuRamSectorSettingConf/*))>0"!]Mcu_RamConfigPB_[!"num:i(@index+1)"!],[!ELSE!]NULL_PTR,[!ENDIF!]             /* pointer to ram section configurations */
        [!IF "num:i(count(McuModeSettingConf/*))>0"!]Mcu_ModeConfigPB_[!"num:i(@index+1)"!],[!ELSE!]NULL_PTR,[!ENDIF!]            /* pointer to low power mode configurations */
        Mcu_ClockConfigPB_[!"num:i(@index+1)"!],           /* pointer to clock settings configurations */
        &McuLLD_ConfigPB_[!"num:i(@index+1)"!]             /*  pointer to low level*/
    };
/* put [!"node:name(.)"!] structure into specified section */
[!ENDLOOP!][!//
#define MCU_STOP_CONFIG_DATA_UNSPECIFIED
/** @note Violates MISRA 2004 Advisory Rules 19.1 and 19.15, Repeated include file,
    See @ref Mcu_PBcfg_c_REF_1 and @ref Mcu_PBcfg_c_REF_2*/
#include "MemMap.h"

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/


#ifdef __cplusplus
}
#endif

