/**
    @file     Lin_Cfg.c
    @version  2.0.0
    
    @brief    Lin Channel Configuration for pre-compile support
    @details  Lin Channel Configuration for pre-compile support
    
    Project        AUTOSAR 3.0 MCAL
    Platform       PA
    Peripheral     ESCI
    Dependencies   
    
    ARVersion      3.0.0
    ARRevision     ASR_REL_3_0_REV_0003
    ARConfVariant  
    SWVersion      2.0.0
    BuildVersion   XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223
    
    (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
    All Rights Reserved.
*/
/*==================================================================================================
==================================================================================================*/

/**
 * @page misra_violations MISRA-C:2004 violations
 * 
 * @section LIN_CFG_C_REF_1
 * Violates MISRA 2004 Required Rule 19.15, Precautions shall be taken in order to prevent the 
 * contents of a header file being included twice. This is not a violation since all header 
 * files are protected against multiple inclusions.
 */

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
**                            Include Files                                 **
*****************************************************************************/
#include "Std_Types.h"
#include "Lin.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**@remarks Covers LIN062 */
#define LIN_AR_MAJOR_VERSION_CFG_C  1
#define LIN_AR_MINOR_VERSION_CFG_C  2
#define LIN_AR_PATCH_VERSION_CFG_C  1
#define LIN_SW_MAJOR_VERSION_CFG_C  2
#define LIN_SW_MINOR_VERSION_CFG_C  0
#define LIN_SW_PATCH_VERSION_CFG_C  0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/**@remarks Covers LIN062 */
#ifdef CHECK_AUTOSAR_VERSION
  #if ((LIN_AR_MAJOR_VERSION_CFG_C != LIN_AR_MAJOR_VERSION) || \
       (LIN_AR_MINOR_VERSION_CFG_C != LIN_AR_MINOR_VERSION) || \
       (LIN_AR_PATCH_VERSION_CFG_C != LIN_AR_PATCH_VERSION))
    #error "AutoSar Version Numbers of Lin_Cfg.c and Lin.h are different"
  #endif
#endif

#if ((LIN_SW_MAJOR_VERSION_CFG_C != LIN_SW_MAJOR_VERSION) || \
     (LIN_SW_MINOR_VERSION_CFG_C != LIN_SW_MINOR_VERSION))
    #error "Software Version Numbers of Lin_Cfg.c and Lin.h are different"
#endif

#ifdef CHECK_AUTOSAR_VERSION
  #if ((LIN_AR_MAJOR_VERSION_CFG_C != STD_TYPES_AR_MAJOR_VERSION) || \
       (LIN_AR_MINOR_VERSION_CFG_C != STD_TYPES_AR_MINOR_VERSION) || \
       (LIN_AR_PATCH_VERSION_CFG_C != STD_TYPES_AR_PATCH_VERSION))
      #error "AutoSar Version Numbers of Lin_Cfg.c and Std_Types.h are different"
  #endif
#endif

#ifdef CHECK_AUTOSAR_VERSION
  #if ((LIN_AR_MAJOR_VERSION_CFG_C != ECUM_CFG_AR_MAJOR_VERSION) || \
       (LIN_AR_MINOR_VERSION_CFG_C != ECUM_CFG_AR_MINOR_VERSION) || \
       (LIN_AR_PATCH_VERSION_CFG_C != ECUM_CFG_AR_PATCH_VERSION))
      #error "AutoSar Version Numbers of Lin_Cfg.c and EcuM_Cfg.h are different"
  #endif
#endif


/*****************************************************************************
**                               Global Variable                            **
*****************************************************************************/


#define LIN_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"


#ifdef LIN_PRECOMPILE_SUPPORT



/**
 * @brief Configuration for Lin Channel 0 - Configuration: LinGlobalConfig_0
 * @remarks Covers LIN064
 * 
 * @api
 */
CONST(Lin_ChannelConfigType,LIN_APPL_CONST) Lin_LinChannel_1_C0=
    {
#ifdef LIN_USE_MSC
      (uint8)STD_OFF, /* MSC support disabled */
      MSC_EVEN,        /* MSC Parity */
      MSC_NORMAL,     /* MSC polarity */
      MSC_16_BITS,    /* MSC frame format */
      STD_OFF,        /* MSC polling mode */
      0x0000U,         /* Default MSC upstream channel baudrate value as MSC support is disabled for this channel */
#endif
    (uint8)STD_OFF,    /* Receiver Full Interrupt Enable */
    LinHWCh_1,     /* Lin Hardware channel*/
    0x0186U,               /* Baudrate 9600 ; Baudrate difference = 0.959375 */
    (uint16)STD_OFF,    /* Wakeup support disabled */

    0x00U,                /* Default Wakeup Source as the Wakeup Support is disabled for this channel */
#ifdef LIN_USE_DMA
  (uint8)STD_OFF,   /* No DMA support for eSCI_B */
  0U,               /* No DMA channel assigned */
  0U,               /* No DMA channel assigned */
  0U,
  0U,
  0U,
  0U,
  0U
#endif
    };




/**
 * @brief  Lin Configuration data for LinGlobalConfig_0
 * @remarks Covers LIN031
 *
 * @api
 */
CONST(Lin_ConfigType,LIN_APPL_CONST)LinGlobalConfig_0 =
    {
/** @brief Configuration for Lin Channel 0 --------- */
    &Lin_LinChannel_1_C0 

    };

#endif /* #ifdef LIN_PRECOMPILE_SUPPORT */

#define LIN_STOP_SEC_CONST_UNSPECIFIED
/**
 * @file Lin_Cfg.c
 * @note Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h: 
 *       See @ref LIN_CFG_C_REF_1
 */
#include "MemMap.h"

#ifdef __cplusplus
extern "C" }
#endif

