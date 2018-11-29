/*!
 * @file    Dio_LLD.h
 *
 * @version 2.0.0
 * @brief   AUTOSAR Dio - DIO driver low level driver interface.
 * @details Interface between the high level driver (Autosar dependent) and the low level driver(platform dependent).
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
 *************************************************************************/

/*==================================================================================================
==================================================================================================*/
#ifndef DIO_LLD_H
#define DIO_LLD_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "Siu_LLD.h"

/******************************************************************
| defines and macros (scope: module-local)
|-----------------------------------------------------------------*/
/*
 * @brief   defines for versions checks of the header file
 * @remarks Covers DIO106
*/
#define DIO_VENDOR_ID_LLD            43
#define DIO_AR_MAJOR_VERSION_LLD     3
#define DIO_AR_MINOR_VERSION_LLD     0
#define DIO_AR_PATCH_VERSION_LLD     0
#define DIO_SW_MAJOR_VERSION_LLD     2
#define DIO_SW_MINOR_VERSION_LLD     0
#define DIO_SW_PATCH_VERSION_LLD     0


/******************************************************************
| File Version Checks
|-----------------------------------------------------------------*/
/*
 * @page    misra_violations MISRA-C:2004 violations
 * @section DIO_LLD_REF_1
 *          Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
 *          Middle layer between AUTOSAR and hardware needs a way to map HLD
 *          functions to LLD functions
 */

#ifdef CHECK_AUTOSAR_VERSION
    /* Siu_LLD.h version check start */
    #if ((DIO_AR_MAJOR_VERSION_LLD != SIU_AR_MAJOR_VERSION_LLD_H ) ||\
         (DIO_AR_MINOR_VERSION_LLD != SIU_AR_MINOR_VERSION_LLD_H ) ||\
         (DIO_AR_PATCH_VERSION_LLD != SIU_AR_PATCH_VERSION_LLD_H ))
        #error "AUTOSAR Version Numbers of Dio_LLD.h and Siu_LLD.h are different"
    #endif
#endif
#if ((DIO_SW_MAJOR_VERSION_LLD != SIU_SW_MAJOR_VERSION_LLD_H ) ||\
     (DIO_SW_MINOR_VERSION_LLD != SIU_SW_MINOR_VERSION_LLD_H ) ||\
     (DIO_SW_PATCH_VERSION_LLD != SIU_SW_PATCH_VERSION_LLD_H ))
    #error "Software Version Numbers of Dio_LLD.h and Siu_LLD.h are different"
#endif
#if ((DIO_VENDOR_ID_LLD != SIU_VENDOR_ID_LLD_H))
    #error "VENDOR ID for Dio_LLD.h and Siu_LLD.h is different"
#endif
/* Siu_LLD.h version check end */

/*
 * @brief   Mapping between low level layer and high level layer for
 *          DioLLD_ReadChannel function.
 * @note    Violates MISRA 2004 Advisory Rule 19.7, Function-like macro
 *          defined - See @ref DIO_LLD_REF_1
 */
#define DioLLD_ReadChannel(ChannelId) DIO_SIU_ReadChannel(ChannelId)
/*
 * @brief   Mapping between low level layer and high level layer for
 *          DioLLD_WriteChannel function.
 * @note    Violates MISRA 2004 Advisory Rule 19.7, Function-like macro
 *          defined - See @ref DIO_LLD_REF_1
 */
#define DioLLD_WriteChannel(ChannelId,ChannelLevel) DIO_SIU_WriteChannel(ChannelId, ChannelLevel)
/*
 * @brief   Mapping between low level layer and high level layer for
 *          DioLLD_ReadPort function.
 * @note    Violates MISRA 2004 Advisory Rule 19.7, Function-like macro
 *          defined - See @ref DIO_LLD_REF_1
 *
 */
#define DioLLD_ReadPort(PortId) DIO_SIU_ReadPort(PortId)
/*
 * @brief   Mapping between low level layer and high level layer for
 *          DioLLD_WritePort function.
 * @note    Violates MISRA 2004 Advisory Rule 19.7, Function-like macro
 *          defined - See @ref DIO_LLD_REF_1
 */
#define DioLLD_WritePort(PortId,PortLevel) DIO_SIU_WritePort(PortId, PortLevel)
/*
 * @brief   Mapping between low level layer and high level layer for
 *          DioLLD_ReadChannelGroup function.
 * @note    Violates MISRA 2004 Advisory Rule 19.7, Function-like macro
 *          defined -  See @ref DIO_LLD_REF_1
 */
#define DioLLD_ReadChannelGroup(ChannelGroupIdPtr) DIO_SIU_ReadChannelGroup(ChannelGroupIdPtr)
/*
 * @brief   Mapping between low level layer and high level layer for
 *          DioLLD_WriteChannelGroup function.
 * @note    Violates MISRA 2004 Advisory Rule 19.7, Function-like macro
 *          defined - See @ref DIO_LLD_REF_1
 */
#define DioLLD_WriteChannelGroup(ChannelGroupIdPtr,Level) DIO_SIU_WriteChannelGroup(ChannelGroupIdPtr, Level)
#if (DIO_MASKEDWRITEPORT_API == STD_ON)
/*
 * @brief   Mapping between low level layer and high level layer for
 *          DioLLD_MaskedWritePort function.
 * @note    Violates MISRA 2004 Advisory Rule 19.7, Function-like macro
 *          defined - See @ref DIO_LLD_REF_1
 */
#define DioLLD_MaskedWritePort(PortId,PortLevel,Mask) DIO_SIU_MaskedWritePort(PortId, PortLevel, Mask)
#endif /* DIO_MASKEDWRITEPORT_API */

#ifdef __cplusplus
}
#endif

#endif  /* DIO_LLD_H */

/** @} */

/* End of File */
