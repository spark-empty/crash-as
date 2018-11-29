/*!
 * @file    Dio_Cfg.c
 *
 * @version 2.0.0
 * @brief   AUTOSAR Dio - DIO driver config.
 * @details This file contains the precompile configuration for the DIO driver.
 *
 * @addtogroup  Dio
 * @{
 */

/***********************************************************************
 * PROJECT              AUTOSAR 3.0 MCAL
 * PLATFORM             PA
 * PERIPHERAL           SIU
 * DEPENDENCIES         none
 *
 * AUTOSAR VERSION      3.0.0
 * AUTOSAR REVISION     ASR_REL_3_0_REV_0003
 * AUTOSAR CONF.VARIANT
 * SW VERSION           2.0.0
 * BUILDVERSION         XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223
 *
 * COPYRIGHT : (c)      2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
 *                      ALL RIGHTS RESERVED
 ***********************************************************************/

/*==================================================================================================
==================================================================================================*/
/*
 * @page misra_violations MISRA-C:2004 violations
 *
 * @section Dio_CFG_C_REF_1
 *          Violates MISRA 2004 Required Rules 19.1, #include preceded by non
 *          preproc directives. This violation is not fixed since the inclusion
 *          of MemMap.h is as per Autosar requirement MEMMAP003.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "Dio.h"


#ifdef DIO_PRECOMPILE_SUPPORT

/*
 * @brief defines for versions checks of the header file
 * @remarks Covers DIO106
 */
#define DIO_VENDOR_ID_CFG_C         43
#define DIO_AR_MAJOR_VERSION_CFG_C  3
#define DIO_AR_MINOR_VERSION_CFG_C  0
#define DIO_AR_PATCH_VERSION_CFG_C  0
#define DIO_SW_MAJOR_VERSION_CFG_C  2
#define DIO_SW_MINOR_VERSION_CFG_C  0
#define DIO_SW_PATCH_VERSION_CFG_C  0


#ifdef CHECK_AUTOSAR_VERSION
    #if (((DIO_AR_MAJOR_VERSION_CFG_C != DIO_AR_MAJOR_VERSION) || \
          (DIO_AR_MINOR_VERSION_CFG_C != DIO_AR_MINOR_VERSION)) || \
          (DIO_AR_PATCH_VERSION_CFG_C != DIO_AR_PATCH_VERSION))
      #error "AutoSar Version Numbers of Dio_Cfg.c and Dio.h are different"
    #endif
#endif
#if  ((DIO_SW_MAJOR_VERSION_CFG_C != DIO_SW_MAJOR_VERSION) || \
      (DIO_SW_MINOR_VERSION_CFG_C != DIO_SW_MINOR_VERSION) || \
      (DIO_SW_PATCH_VERSION_CFG_C != DIO_SW_PATCH_VERSION))
  #error "Software Version Numbers of Dio_Cfg.c and Dio.h are different"
#endif
#if ((DIO_VENDOR_ID_CFG_C != DIO_VENDOR_ID))
    #error "VENDOR ID for Dio_Cfg.h and Dio.h is different"
#endif

#define DIO_START_SEC_CONST_UNSPECIFIED
/*
 * @note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements
 *       and comments before '#include' - See @ref Dio_CFG_C_REF_1
 */
#include "MemMap.h"

/*
 * @brief valid_pin_ranges is an array containing valid pin intervals, intervals are closed
 */
CONST(Dio_ChannelType, DIO_CONST)valid_pin_ranges[DIO_PIN_INTERVALS]={(Dio_ChannelType)83,(Dio_ChannelType)84,(Dio_ChannelType)87,(Dio_ChannelType)92,(Dio_ChannelType)98,(Dio_ChannelType)99,(Dio_ChannelType)102,(Dio_ChannelType)110,(Dio_ChannelType)114,(Dio_ChannelType)145,(Dio_ChannelType)179,(Dio_ChannelType)179,(Dio_ChannelType)181,(Dio_ChannelType)181,(Dio_ChannelType)183,(Dio_ChannelType)183,(Dio_ChannelType)187,(Dio_ChannelType)194,(Dio_ChannelType)202,(Dio_ChannelType)202,(Dio_ChannelType)208,(Dio_ChannelType)208,(Dio_ChannelType)212,(Dio_ChannelType)213,(Dio_ChannelType)215,(Dio_ChannelType)225,(Dio_ChannelType)227,(Dio_ChannelType)228,(Dio_ChannelType)231,(Dio_ChannelType)232};

/*
 * @brief valid_port_ranges is an array containing valid port intervals, intervals are closed
 */
CONST(Dio_PortType, DIO_CONST)valid_port_ranges[DIO_PORT_INTERVALS]={(Dio_PortType)0,(Dio_PortType)14};
#define DIO_STOP_SEC_CONST_UNSPECIFIED
/* @note Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements
 *       and comments before '#include' - See @ref Dio_CFG_C_REF_1
 */
#include "MemMap.h"

#endif /*DIO_PRECOMPILE_SUPPORT*/

#ifdef __cplusplus
}
#endif
/** @} */
/* End of File */

