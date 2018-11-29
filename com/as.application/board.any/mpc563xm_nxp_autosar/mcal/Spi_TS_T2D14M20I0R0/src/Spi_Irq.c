/**
    @file    Spi_Irq.c
    @version 2.0.0

    @brief   AUTOSAR Spi - Brief description.
    @details Detailed description.

    Project AUTOSAR 3.0 MCAL
    Patform PA
    Peripheral DSPI
    Dependencies 

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

@section Spi_Irq_c_REF_1
Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before "#include"
AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed
@section Spi_Irq_c_REF_2
Violates MISRA 2004 Rule 19.15, precautions shall be taken in order to prevent the content of a
header file to be included twice. The inclusion of MemMap.h is as per Autosar requirement MEMMAP003.
@section Spi_Irq_c_REF_3
Violates MISRA 2004 Rule 11.3, a cast should not be performed between a pointer type and an
integral type. The cast can not be avoided as it is used to access memory mapped registers.
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
#include "Spi.h"
#include "Spi_LLD.h"
#include "Mcal.h"

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/
#define SPI_AR_MAJOR_VERSION_IRQ        3
#define SPI_AR_MINOR_VERSION_IRQ        0
#define SPI_AR_PATCH_VERSION_IRQ        0
#define SPI_SW_MAJOR_VERSION_IRQ        2
#define SPI_SW_MINOR_VERSION_IRQ        0
#define SPI_SW_PATCH_VERSION_IRQ        0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
#ifdef CHECK_AUTOSAR_VERSION
  #if ((SPI_AR_MAJOR_VERSION_IRQ != SPI_AR_MAJOR_VERSION) || \
       (SPI_AR_MINOR_VERSION_IRQ != SPI_AR_MINOR_VERSION) || \
       (SPI_AR_PATCH_VERSION_IRQ != SPI_AR_PATCH_VERSION))
  #error "AutoSar Version Numbers of Spi_Irq.c and Spi.h are different"
  #endif
#endif

#if ((SPI_SW_MAJOR_VERSION_IRQ != SPI_SW_MAJOR_VERSION) || \
     (SPI_SW_MINOR_VERSION_IRQ != SPI_SW_MINOR_VERSION))
#error "Software Version Numbers of Spi_Irq.c and DSPI_LLD.h are different"
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


/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/
#define SPI_START_SEC_CODE
/**
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_Irq_c_REF_1 & @ref Spi_Irq_c_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/


    /* Interrupt service routines */
#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
#if (DSPI_0_ENABLED == STD_ON)
    ISR(Spi_LLD_IsrRxDma_DSPI_0);
#endif
#endif

#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
#if (DSPI_1_ENABLED == STD_ON)
    ISR(Spi_LLD_IsrRxDma_DSPI_1);
#endif
#endif

#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
#if (DSPI_2_ENABLED == STD_ON)
    ISR(Spi_LLD_IsrRxDma_DSPI_2);
#endif
#endif
#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
#if (DSPI_0_ENABLED == STD_ON)
    ISR(Spi_LLD_IsrEOQ_DSPI_0);
#endif
#endif

#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
#if (DSPI_1_ENABLED == STD_ON)
    ISR(Spi_LLD_IsrEOQ_DSPI_1);
#endif
#endif

#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
#if (DSPI_2_ENABLED == STD_ON)
    ISR(Spi_LLD_IsrEOQ_DSPI_2);
#endif
#endif

/*================================================================================================*/
/**
@brief   This function is the DMA Rx ISR for the DSPI 0.
@details Non-AutoSar support function used by interrupt service
         routine of the DMA Rx for DSPI 0

@pre Pre-compile parameter SPI_LEVEL_DELIVERED shall be LEVEL1 or LEVEL2.
@pre Pre-compile parameter DSPI_0_ENABLED shall be STD_ON.

@remarks Implements DSPI03509
*/
/*================================================================================================*/
#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
#if (DSPI_0_ENABLED == STD_ON)
ISR(Spi_LLD_IsrRxDma_DSPI_0)
{
#if (SPI_DMA_USED == STD_ON)
    Spi_LLD_IsrDmaRx(DSPI_HWUNIT2DSPI(DSPI_0_HWUNIT));
#endif
    /**
    @note Violates MISRA 2004 Advisory Rules 11.3 - See @ref Spi_Irq_c_REF_3
    */
    /*lint -save -e923*/
    EXIT_INTERRUPT();
    /*lint -restore*/
}
#endif
#endif
/*================================================================================================*/
/**
@brief   This function is the DMA Rx ISR for the DSPI 1.
@details Non-AutoSar support function used by interrupt service
         routine of the DMA Rx for DSPI 1

@pre Pre-compile parameter SPI_LEVEL_DELIVERED shall be LEVEL1 or LEVEL2.
@pre Pre-compile parameter DSPI_1_ENABLED shall be STD_ON.

@remarks Implements DSPI03509
*/
/*================================================================================================*/
#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
#if (DSPI_1_ENABLED == STD_ON)
ISR(Spi_LLD_IsrRxDma_DSPI_1)
{
#if (SPI_DMA_USED == STD_ON)
    Spi_LLD_IsrDmaRx(DSPI_HWUNIT2DSPI(DSPI_1_HWUNIT));
#endif
    /**
    @note Violates MISRA 2004 Advisory Rules 11.3 - See @ref Spi_Irq_c_REF_3
    */
    /*lint -save -e923*/
    EXIT_INTERRUPT();
    /*lint -restore*/
}
#endif
#endif
/*================================================================================================*/
/**
@brief   This function is the DMA Rx ISR for the DSPI 2.
@details Non-AutoSar support function used by interrupt service
         routine of the DMA Rx for DSPI 2

@pre Pre-compile parameter SPI_LEVEL_DELIVERED shall be LEVEL1 or LEVEL2.
@pre Pre-compile parameter DSPI_2_ENABLED shall be STD_ON.

@remarks Implements DSPI03509
*/
/*================================================================================================*/
#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
#if (DSPI_2_ENABLED == STD_ON)
ISR(Spi_LLD_IsrRxDma_DSPI_2)
{
#if (SPI_DMA_USED == STD_ON)
    Spi_LLD_IsrDmaRx(DSPI_HWUNIT2DSPI(DSPI_2_HWUNIT));
#endif
    /**
    @note Violates MISRA 2004 Advisory Rules 11.3 - See @ref Spi_Irq_c_REF_3
    */
    /*lint -save -e923*/
    EXIT_INTERRUPT();
    /*lint -restore*/
}
#endif
#endif
/*================================================================================================*/
/**
@brief   This function is the end-of-queue Rx ISR for the DSPI 0.
@details Non-AutoSar support function used by interrupt service
         routine of the end-of-queue Rx for DSPI 0

@pre Pre-compile parameter SPI_LEVEL_DELIVERED shall be LEVEL1 or LEVEL2.
@pre Pre-compile parameter DSPI_0_ENABLED shall be STD_ON.

@remarks Implements DSPI03512
*/
/*================================================================================================*/
#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
#if (DSPI_0_ENABLED == STD_ON)
ISR(Spi_LLD_IsrEOQ_DSPI_0)
{
    Spi_LLD_IsrFifoRx(DSPI_HWUNIT2DSPI(DSPI_0_HWUNIT));
    /**
    @note Violates MISRA 2004 Advisory Rules 11.3 - See @ref Spi_Irq_c_REF_3
    */
    /*lint -save -e923*/
    EXIT_INTERRUPT();
    /*lint -restore*/
}
#endif
#endif
/*================================================================================================*/
/**
@brief   This function is the end-of-queue Rx ISR for the DSPI 1.
@details Non-AutoSar support function used by interrupt service
         routine of the end-of-queue Rx for DSPI 1

@pre Pre-compile parameter SPI_LEVEL_DELIVERED shall be LEVEL1 or LEVEL2.
@pre Pre-compile parameter DSPI_1_ENABLED shall be STD_ON.

@remarks Implements DSPI03512
*/
/*================================================================================================*/
#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
#if (DSPI_1_ENABLED == STD_ON)
ISR(Spi_LLD_IsrEOQ_DSPI_1)
{
    Spi_LLD_IsrFifoRx(DSPI_HWUNIT2DSPI(DSPI_1_HWUNIT));
    /**
    @note Violates MISRA 2004 Advisory Rules 11.3 - See @ref Spi_Irq_c_REF_3
    */
    /*lint -save -e923*/
    EXIT_INTERRUPT();
    /*lint -restore*/
}
#endif
#endif
/*================================================================================================*/
/**
@brief   This function is the end-of-queue Rx ISR for the DSPI 2.
@details Non-AutoSar support function used by interrupt service
         routine of the end-of-queue Rx for DSPI 2

@pre Pre-compile parameter SPI_LEVEL_DELIVERED shall be LEVEL1 or LEVEL2.
@pre Pre-compile parameter DSPI_2_ENABLED shall be STD_ON.

@remarks Implements DSPI03512
*/
/*================================================================================================*/
#if ((SPI_LEVEL_DELIVERED == LEVEL1) || (SPI_LEVEL_DELIVERED == LEVEL2))
#if (DSPI_2_ENABLED == STD_ON)
ISR(Spi_LLD_IsrEOQ_DSPI_2)
{
    Spi_LLD_IsrFifoRx(DSPI_HWUNIT2DSPI(DSPI_2_HWUNIT));
    /**
    @note Violates MISRA 2004 Advisory Rules 11.3 - See @ref Spi_Irq_c_REF_3
    */
    /*lint -save -e923*/
    EXIT_INTERRUPT();
    /*lint -restore*/
}
#endif
#endif
/*================================================================================================*/
#define SPI_STOP_SEC_CODE
/**
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_Irq_c_REF_1 & @ref Spi_Irq_c_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif




