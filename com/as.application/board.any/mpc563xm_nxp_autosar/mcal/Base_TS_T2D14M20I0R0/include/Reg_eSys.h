/**
    @file        Reg_eSys.h
    @version     2.0.0

    @brief       AUTOSAR Base - IP Memory and DMA mapping.
    @details     Memory mapping of the IP modules and DMA channels present on the XPC563XM
                 hardware platform.

    Project      : AUTOSAR 3.0 MCAL
    Platform     : PA
    Peripheral   : XPC563XM
    Dependencies : none

    Autosar Version       : 3.0.0
    Autosar Revision      : ASR_REL_3_0_REV_0003
    Autosar Conf. Variant :
    Software Version      : 2.0.0
    Build Version         : XPC563xM_MCAL_2_0_0_RTM_ASR_REL_3_0_REV_0003_20111223

    (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
    All Rights Reserved.
*/
/*==================================================================================================
==================================================================================================*/

/**
@file        Reg_eSys.h
@remarks Implements DBASE07000
*/

/**
@page misra_violations MISRA-C:2004 violations

@section Reg_eSys_h_REF_1
Violates MISRA 2004 Required Rule 19.15, Repeated include file
This comes from the order of includes in the .c file and from include dependencies. As a safe
approach, any file must include all its dependencies. Header files are already protected against
double inclusions.
*/

#ifndef REG_ESYS_H
#define REG_ESYS_H

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
@file        Reg_eSys.h
@brief Include platform types
@note Violates MISRA 2004 Required Rule 19.15, Repeated include file - See @ref Reg_eSys_h_REF_1
*/
#include "Platform_Types.h"
/**
@file        Reg_eSys.h
@brief Include IP module versions
@note Violates MISRA 2004 Required Rule 19.15, Repeated include file - See @ref Reg_eSys_h_REF_1
*/
#include "Soc_Ips.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

/**
@brief Internal Flash
@details XPC563XM System Memory Map
@remarks Implements DBASE07001
*/
#define INTERNAL_FLASH_BASEADDR             ((uint32)0x00000000UL)
/**
@brief Calibration Memory
@details XPC563XM System Memory Map
@remarks Implements DBASE07001
*/
#define CALIBRATION_MEM_BASEADDR           ((uint32)0x30000000UL)
/**
@brief Internal RAM
@details XPC563XM System Memory Map
@remarks Implements DBASE07001
*/
#define INTERNAL_RAM_BASEADDR               ((uint32)0x40000000UL)
/**
@brief FMPLL
@details XPC563XM System Memory Map
@remarks Implements DBASE07001
*/
#define FMPLL_BASEADDR                      ((uint32)0xC3F80000UL)
/**
@brief EBI
@details XPC563XM System Memory Map
@remarks Implements DBASE07001
*/
#define EBI_BASEADDR                        ((uint32)0xC3F84000UL)
/**
@brief Platform FLASH Controller
@details XPC563XM System Memory Map
@remarks Implements DBASE07001
*/
#define FLASHMEM0_PFC0_BASEADDR             ((uint32)0xC3F88000UL)
/**
@brief FLS_ARRAY_0_A
@details XPC563XM System Memory Map
@remarks Implements DBASE07001
*/
#define FLASHMEM0_ARRAY_0_A_BASEADDR        ((uint32)0xC3F88000UL)
/**
@brief FLS_ARRAY_1_B
@details XPC563XM System Memory Map
@remarks Implements DBASE07001
*/
#define FLASHMEM0_ARRAY_1_B_BASEADDR        ((uint32)0xC3FB0000UL)
/**
@brief FLS_ARRAY_1_C
@details XPC563XM System Memory Map
@remarks Implements DBASE07001
*/
#define FLASHMEM0_ARRAY_1_C_BASEADDR        ((uint32)0xC3FB4000UL)
/**
@brief System Integration Unit (SIU)
@details XPC563XM System Memory Map
@remarks Implements DBASE07001
*/
#define SIU_BASEADDR                        ((uint32)0xC3F90000UL)
/**
@brief eMIOS
@details XPC563XM System Memory Map
@remarks Implements DBASE07001
*/
#define EMIOS_BASEADDR                      ((uint32)0xC3FA0000UL)
/**
@brief PMC
@details XPC563XM System Memory Map
@remarks Implements DBASE07001
*/
#define PMC_BASEADDR                        ((uint32)0xC3FBC000UL)
/**
@brief eTPU Registers
@details XPC563XM System Memory Map
@remarks Implements DBASE07001
*/
#define ETPU_REG_BASEADDR                   ((uint32)0xC3FC0000UL)
/**
@brief eTPU Parameter RAM
@details XPC563XM System Memory Map
@remarks Implements DBASE07001
*/
#define ETPU_PARAM_RAM_BASEADDR             ((uint32)0xC3FC8000UL)
/**
@brief eTPU Parameter RAM Mirror
@details XPC563XM System Memory Map
@remarks Implements DBASE07001
*/
#define ETPU_PARAM_RAM_MIRROR_BASEADDR      ((uint32)0xC3FCC000UL)
/**
@brief eTPU Code RAM
@details XPC563XM System Memory Map
@remarks Implements DBASE07001
*/
#define ETPU_CODE_RAM_BASEADDR              ((uint32)0xC3FD0000UL)
/**
@brief Periodic Interrupt Timer (PIT)/RTI
@details XPC563XM System Memory Map
@remarks Implements DBASE07001
*/
#define PITRTI_BASEADDR                     ((uint32)0xC3FF0000UL)
/**
@brief XBAR (AXBS)
@details XPC563XM System Memory Map
@remarks Implements DBASE07001
*/
#define XBAR_BASEADDR                       ((uint32)0xFFF04000UL)
/**
@brief SWT
@details XPC563XM System Memory Map
@remarks Implements DBASE07001
*/
#define SWT_BASEADDR                        ((uint32)0xFFF38000UL)
/**
@brief STM
@details XPC563XM System Memory Map
@remarks Implements DBASE07001
*/
#define STM_BASEADDR                        ((uint32)0xFFF3C000UL)
/**
@brief ECSM
@details XPC563XM System Memory Map
@remarks Implements DBASE07001
*/
#define ECSM_BASEADDR                       ((uint32)0xFFF40000UL)
/**
@brief eDMA_A
@details XPC563XM System Memory Map
@remarks Implements DBASE07001
*/
#define DMA_BASEADDR                       ((uint32)0xFFF44000UL)
/**
@brief INTC
@details XPC563XM System Memory Map
@remarks Implements DBASE07001
*/
#define INTC_BASEADDR                       ((uint32)0xFFF48000UL)
/**
@brief eQADC_A
@details XPC563XM System Memory Map
@remarks Implements DBASE07001
*/
#define EQADCA_BASEADDR                     ((uint32)0xFFF80000UL)
/**
@brief Decimation filter A
@details XPC563XM System Memory Map
@remarks Implements DBASE07001
*/
#define DEC_FILTERA_BASEADDR                ((uint32)0xFFF88000UL)
/**
@brief DSPI 0
@details XPC563XM System Memory Map
@remarks Not implemented on Monaco, but needed by SPI driver
*/
#define DSPI0_BASEADDR                      ((uint32)0xFFF90000UL)
/**
@brief DSPI 1
@details XPC563XM System Memory Map
@remarks Implements DBASE07001

*/
#define DSPI1_BASEADDR                      ((uint32)0xFFF94000UL)
/**
@brief DSPI 2
@details XPC563XM System Memory Map
@remarks Implements DBASE07001
*/
#define DSPI2_BASEADDR                      ((uint32)0xFFF98000UL)
/**
@brief eSCI_A
@details XPC563XM System Memory Map
@remarks Implements DBASE07001
*/
#define ESCIA_BASEADDR                      ((uint32)0xFFFB0000UL)
/**
@brief eSCI_B
@details XPC563XM System Memory Map
@remarks Implements DBASE07001
*/
#define ESCIB_BASEADDR                      ((uint32)0xFFFB4000UL)
/**
@brief FlexCan 0 (CAN0)
@details XPC563XM System Memory Map
@remarks Implements DBASE07001
*/
#define FLEXCAN0_BASEADDR                   ((uint32)0xFFFC0000UL)
/**
@brief FlexCan 1 (CAN1)
@details XPC563XM System Memory Map - FlexCAN_B base address (dummy - FlexCAN_B Not available on HardWare)
@remarks Implements DBASE07001
*/
#define FLEXCAN1_BASEADDR                   ((uint32)0xFFFC4000UL)
/**
@brief FlexCan 2 (CAN2)
@details XPC563XM System Memory Map
@remarks Implements DBASE07001
*/
#define FLEXCAN2_BASEADDR                   ((uint32)0xFFFC8000UL)
/**
@brief Temp Sensor
@details XPC563XM System Memory Map
@remarks Implements DBASE07001
*/
#define TEMP_SENSOR_BASEADDR                ((uint32)0xFFFEC000UL)
/**
@brief BAM
@details XPC563XM System Memory Map
@remarks Implements DBASE07001
*/
#define BAM_BASEADDR                        ((uint32)0xFFFFC000UL)

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* #ifndef REG_ESYS_H*/







