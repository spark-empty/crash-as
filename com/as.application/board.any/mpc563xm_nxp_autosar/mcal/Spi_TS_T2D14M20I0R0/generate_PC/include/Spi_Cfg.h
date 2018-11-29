[!CODE!][!//
/**
    @file    Spi_Cfg.h
    @version 2.0.0

    @brief   AUTOSAR Spi - Spi configuration header file.
    @details This file is the header containing all the necessary information for SPI
             module configuration(s).

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

@section Spi_Cfg_h_REF_1
Violates MISRA 2004 Advisory Rule Rule 19.1, only preprocessor statements
and comments before '#include'. AUTOSAR imposes the specification of the
sections in which certain parts of the driver must be placed.
@section Spi_Cfg_h_REF_2
Violates MISRA 2004 Rule 19.15, precautions shall be taken in order to prevent the content of a
header file to be included twice. The inclusion of MemMap.h is as per Autosar requirement MEMMAP003.
*/

#ifndef SPI_CFG_H
#define SPI_CFG_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
@brief Parameters that shall be published within the configuration header file and also in the
       module's description file
@remarks Covers BSW00374, BSW00379, BSW00318
@{
*/
#define SPI_MODULE_ID_CFG           83
#define SPI_VENDOR_ID_CFG           43
#define SPI_AR_MAJOR_VERSION_CFG    3
#define SPI_AR_MINOR_VERSION_CFG    0
#define SPI_AR_PATCH_VERSION_CFG    0
#define SPI_SW_MAJOR_VERSION_CFG    2
#define SPI_SW_MINOR_VERSION_CFG    0
#define SPI_SW_PATCH_VERSION_CFG    0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

[!NOCODE!][!//
[!VAR "OuterLoopCounter" = "0"!][!//
[!VAR "InnerLoopCounter" = "0"!][!//
[!LOOP "SpiDriver/*/SpiJob/*"!][!//
[!VAR "OuterLoopCounter" = "$OuterLoopCounter + 1"!]
    [!VAR "InnerLoopCounter" = "0"!]
    [!VAR "Matchcounter" = "0"!]
    [!VAR "Name" = "node:name(.)"!]
    [!LOOP "../../../*/SpiJob/*"!]
    [!VAR "InnerLoopCounter" = "$InnerLoopCounter + 1"!]
    [!IF "$OuterLoopCounter >= $InnerLoopCounter"!]
      [!IF "($Name = node:name(.))"!]
          [!VAR "Matchcounter" = "$Matchcounter + 1"!]
       [!ENDIF!][!//
    [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!IF "$Matchcounter = 1"!]
    [!ELSE!][!//
        [!ERROR!]SpiJob Symbolic name "[!"@name"!]" for the two or more SpiJobs is repeated.[!ENDERROR!]
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!VAR "OuterLoopCounter" = "0"!][!//
[!VAR "InnerLoopCounter" = "0"!][!//
[!LOOP "SpiDriver/*/SpiSequence/*"!][!//
[!VAR "OuterLoopCounter" = "$OuterLoopCounter + 1"!]
    [!VAR "InnerLoopCounter" = "0"!]
    [!VAR "Matchcounter" = "0"!]
    [!VAR "Name" = "node:name(.)"!]
    [!LOOP "../../../*/SpiSequence/*"!]
    [!VAR "InnerLoopCounter" = "$InnerLoopCounter + 1"!]
    [!IF "$OuterLoopCounter >= $InnerLoopCounter"!]
      [!IF "($Name = node:name(.))"!]
          [!VAR "Matchcounter" = "$Matchcounter + 1"!]
       [!ENDIF!][!//
    [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!IF "$Matchcounter = 1"!]
    [!ELSE!][!//
        [!ERROR!]SpiSequences Symbolic name "[!"@name"!]" for the two or more SpiSequences is repeated.[!ENDERROR!]
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!VAR "OuterLoopCounter" = "0"!][!//
[!VAR "InnerLoopCounter" = "0"!][!//
[!LOOP "SpiDriver/*/SpiExternalDevice/*"!][!//
[!VAR "OuterLoopCounter" = "$OuterLoopCounter + 1"!]
    [!VAR "InnerLoopCounter" = "0"!]
    [!VAR "Matchcounter" = "0"!]
    [!VAR "Name" = "node:name(.)"!]
    [!LOOP "../../../*/SpiExternalDevice/*"!]
    [!VAR "InnerLoopCounter" = "$InnerLoopCounter + 1"!]
    [!IF "$OuterLoopCounter >= $InnerLoopCounter"!]
      [!IF "($Name = node:name(.))"!]
          [!VAR "Matchcounter" = "$Matchcounter + 1"!]
       [!ENDIF!][!//
    [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!IF "$Matchcounter = 1"!]
    [!ELSE!][!//
        [!ERROR!]SpiExternalDevice Symbolic name "[!"@name"!]" for the two or more SpiExternalDevices is repeated.[!ENDERROR!]
    [!ENDIF!][!//
[!ENDLOOP!][!//

[!IF "ecu:get('SpiDMAPresent') = 'TRUE'"!]
    [!LOOP "SpiGeneral/SpiPhyUnit/*"!][!//
        [!VAR "Unit_Name"="@name"!]
        [!IF "node:exists(SpiPhyUnitAsyncMethod) and (SpiPhyUnitAsyncMethod = 'DMA')"!]
            [!VAR "Spi_PhyTxDmaChannel1"="SpiPhyTxDmaChannel"!]
            [!VAR "Spi_PhyTxDmaChannel2"="SpiPhyTxDmaChannelAux"!]
            [!VAR "Spi_PhyRxDmaChannel"="SpiPhyRxDmaChannel"!]

            [!IF "($Spi_PhyTxDmaChannel1 = $Spi_PhyTxDmaChannel2)"!]
                [!ERROR!]
                        SpiPhyTxDmaChannel ([!"$Spi_PhyTxDmaChannel1"!]) and SpiPhyTxDmaChannelAux ([!"$Spi_PhyTxDmaChannel2"!]) values in [!"@name"!] are repeated. Please select different values for SpiPhyTxDmaChannel and SpiPhyTxDmaChannelAux.
                [!ENDERROR!]
            [!ENDIF!]
            [!IF "($Spi_PhyTxDmaChannel1 = $Spi_PhyRxDmaChannel)"!]
                [!ERROR!]
                        SpiPhyTxDmaChannel ([!"$Spi_PhyTxDmaChannel1"!]) and SpiPhyRxDmaChannel ([!"$Spi_PhyRxDmaChannel"!]) values in [!"@name"!] are repeated. Please select different values for SpiPhyTxDmaChannel and SpiPhyRxDmaChannel.
                [!ENDERROR!]
            [!ENDIF!]
            [!IF "($Spi_PhyTxDmaChannel2 = $Spi_PhyRxDmaChannel)"!]
                [!ERROR!]
                        SpiPhyTxDmaChannelAux ([!"$Spi_PhyTxDmaChannel2"!]) and SpiPhyRxDmaChannel ([!"$Spi_PhyRxDmaChannel"!]) values in [!"@name"!] are repeated. Please select different values for SpiPhyTxDmaChannelAux and SpiPhyRxDmaChannel.
                [!ENDERROR!]
            [!ENDIF!]

            [!LOOP "../../SpiPhyUnit/*"!]
                [!IF "(node:exists(SpiPhyUnitAsyncMethod) and (SpiPhyUnitAsyncMethod = 'DMA'))"!]
                    [!IF "($Spi_PhyTxDmaChannel1 = SpiPhyTxDmaChannelAux)"!]
                        [!ERROR!]
                            SpiPhyTxDmaChannel ([!"$Spi_PhyTxDmaChannel1"!]) in [!"$Unit_Name"!] container and SpiPhyTxDmaChannelAux ([!"SpiPhyTxDmaChannelAux"!]) in [!"@name"!] are repeated. Please select different values for SpiPhyTxDmaChannel and SpiPhyTxDmaChannelAux.
                        [!ENDERROR!]
                    [!ENDIF!]
                    [!IF "($Spi_PhyTxDmaChannel1 = SpiPhyRxDmaChannel)"!]
                        [!ERROR!]
                            SpiPhyTxDmaChannel ([!"$Spi_PhyTxDmaChannel1"!]) in [!"$Unit_Name"!] container and SpiPhyRxDmaChannel ([!"SpiPhyRxDmaChannel"!]) in [!"@name"!] are repeated. Please select different values for SpiPhyTxDmaChannel and SpiPhyRxDmaChannel.
                        [!ENDERROR!]
                    [!ENDIF!]
                    [!IF "($Spi_PhyTxDmaChannel2 = SpiPhyRxDmaChannel)"!]
                        [!ERROR!]
                            SpiPhyTxDmaChannelAux ([!"$Spi_PhyTxDmaChannel2"!]) in [!"$Unit_Name"!] container and SpiPhyRxDmaChannel ([!"SpiPhyRxDmaChannel"!]) in [!"@name"!] are repeated. Please select different values for SpiPhyTxDmaChannelAux and SpiPhyRxDmaChannel.
                        [!ENDERROR!]
                    [!ENDIF!]
                [!ENDIF!]
            [!ENDLOOP!][!//
        [!ENDIF!]
    [!ENDLOOP!][!//
[!ENDIF!][!//

[!ENDNOCODE!]

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

[!NOCODE!]
[!// Calculate the maximum number of elements (sequences, jobs, channels) in configuration.
[!VAR "SpiMaxSequencesCount" = "0"!][!//
[!VAR "SpiMaxJobsCount" = "0"!][!//
[!VAR "SpiMaxChannelsCount" = "0"!][!//
[!VAR "SpiMaxOneJobSequences" = "0"!][!//
[!VAR "SpiMaxOneJobSeqChannels" = "0"!][!//
[!LOOP "SpiDriver/*"!][!//
    [!VAR "TmpCounter" = "num:i(count(./SpiSequence/*))"!]
    [!IF "$SpiMaxSequencesCount < $TmpCounter"!]
        [!VAR "SpiMaxSequencesCount" = "$TmpCounter"!]
    [!ENDIF!]
    [!VAR "TmpCounter" = "num:i(count(SpiJob/*))"!]
    [!IF "$SpiMaxJobsCount < $TmpCounter"!]
        [!VAR "SpiMaxJobsCount" = "$TmpCounter"!]
    [!ENDIF!]
    [!VAR "TmpCounter" = "num:i(count(SpiChannel/*))"!]
    [!IF "$SpiMaxChannelsCount < $TmpCounter"!]
        [!VAR "SpiMaxChannelsCount" = "$TmpCounter"!]
    [!ENDIF!]
    [!VAR "TmpCounter" = "num:i(count(SpiSequence/*[count(JobAssignment/*) = 1]))"!]
    [!IF "$SpiMaxOneJobSequences < $TmpCounter"!]
        [!VAR "SpiMaxOneJobSequences" = "$TmpCounter"!]
    [!ENDIF!]
    [!VAR "TmpCounter" = "num:i(count(node:refs(SpiSequence/*[count(JobAssignment/*) = 1]/JobAssignment/*)/ChannelAssignment/*))"!]
    [!IF "$SpiMaxOneJobSeqChannels < $TmpCounter"!]
        [!VAR "SpiMaxOneJobSeqChannels" = "$TmpCounter"!]
    [!ENDIF!]
[!ENDLOOP!][!//
[!ENDNOCODE!]

/**
@brief Switches the Development Error functionality STD_ON or STD_OFF.
@remarks Implements DSPI01431, DSPI01430
*/
#define SPI_DEV_ERROR_DETECT           ([!IF "SpiGeneral/SpiDevErrorDetect"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

/**
@brief Switches the Version Information API functionality STD_ON or STD_OFF.
@remarks Implements DSPI01413
*/
#define SPI_VERSION_INFO_API           ([!IF "SpiGeneral/SpiVersionInfoApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

/**
@brief Switches the Interruptible Sequences handling functionality STD_ON or
   STD_OFF. (see chapter 7.2.4) - Note: This parameter depends on
   SPI_LEVEL_DELIVERED value. It is only used for SPI_LEVEL_DELIVERED
   configured to 1 or 2.

@remarks Implements DSPI01421
*/
#define SPI_INTERRUPTIBLE_SEQ_ALLOWED  ([!IF "SpiGeneral/SpiInterruptibleSeqAllowed"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

/**
@brief Switches the Spi_GetHWUnitStatus function STD_ON or STD_OFF.
   (see chapters 8.2.10 and 8.3.12).
@remarks Implements DSPI01412
*/
#define SPI_HW_STATUS_API          ([!IF "SpiGeneral/SpiHwStatusApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

/**
@brief Switches the Spi_Cancel function STD_ON or STD_OFF. (see chapter 8.3.13)

@remarks Implements DSPI01420
*/
#define SPI_CANCEL_API             ([!IF "SpiGeneral/SpiCancelApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

/**
@brief Only Internal Buffers are allowed in Handler/Driver.
*/
#define USAGE0                          0x00u

/**
@brief Only External Buffers are allowed in Handler/Driver.
*/
#define USAGE1                          0x01u

/**
@brief Both Buffer types are allowd in Handler/Driver.
*/
#define USAGE2                          0x02u
/* Derive the CTAR used */
#define SPI_CTAR_USED                   [!"ecu:get('SpiCTARUsed')"!]u

/**
@brief Selects the SPI Handler/Driver Channel Buffers usage allowed and
   delivered. (see chapter 7.2.1)

@remarks Implements DSPI01411
*/
#define SPI_CHANNEL_BUFFERS_ALLOWED    (USAGE[!"SpiGeneral/SpiChannelBuffersAllowed"!])

/**
@brief The LEVEL 0 Simple Synchronous SPI Handler/Driver functionalities are selected.
*/
#define LEVEL0                          0x00u

/**
@brief The LEVEL 1 Basic Asynchronous SPI Handler/Driver functionalities are selected.
*/
#define LEVEL1                          0x01u

/**
@brief  The LEVEL 2 Enhanced SPI Handler/Driver functionalities are selected.
*/
#define LEVEL2                          0x02u

/**
@brief Selects the SPI Handler/Driver level of scalable functionality that is
   available and delivered. (see chapter 7.1)

@remarks Implements DSPI01410
*/
#define SPI_LEVEL_DELIVERED            (LEVEL[!"SpiGeneral/SpiLevelDelivered"!])

/**
@brief Defines the maximum number of supported channels for all the driver configurations

@remarks Implements DSPI01910
*/
[!NOCODE!][!//
[!VAR "OuterLoopCounter" = "0"!][!//
[!VAR "InnerLoopCounter" = "0"!][!//
[!ENDNOCODE!][!//
[!LOOP "SpiDriver/*/SpiChannel/*"!][!//
[!NOCODE!][!//
[!VAR "OuterLoopCounter" = "$OuterLoopCounter + 1"!][!//
    [!VAR "InnerLoopCounter" = "0"!][!//
    [!VAR "Matchcounter" = "0"!][!//
    [!VAR "TempChannel_FirstSpiChannelId" = "0"!][!//
    [!VAR "TempChannel_FirstSpiChannelType" = "SpiChannelType"!][!//
    [!VAR "TempChannel_FirstSpiDataWidth" = "SpiDataWidth"!][!//
    [!VAR "TempChannel_FirstSpiDefaultData" = "SpiDefaultData"!][!//
    [!VAR "TempChannel_FirstSpiEbMaxLength" = "SpiEbMaxLength"!][!//
    [!VAR "TempChannel_FirstSpiIbNBuffers" = "SpiChannelType"!][!//
    [!VAR "TempChannel_FirstSpiTransferStart" = "SpiTransferStart"!][!//
    [!VAR "Name" = "node:name(.)"!][!//
    [!LOOP "../../../*/SpiChannel/*"!][!//
    [!VAR "InnerLoopCounter" = "$InnerLoopCounter + 1"!][!//
    [!IF "$OuterLoopCounter >= $InnerLoopCounter"!][!//
      [!IF "($Name = node:name(.))"!][!//
         [!VAR "Matchcounter" = "$Matchcounter + 1"!][!//
         [!IF "$Matchcounter = 1"!][!//
         [!VAR "TempChannel_FirstSpiChannelId" = "SpiChannelId"!][!//
         [!VAR "TempChannel_FirstSpiChannelType" = "SpiChannelType"!][!//
         [!VAR "TempChannel_FirstSpiDataWidth" = "SpiDataWidth"!][!//
         [!VAR "TempChannel_FirstSpiDefaultData" = "SpiDefaultData"!][!//
         [!VAR "TempChannel_FirstSpiEbMaxLength" = "SpiEbMaxLength"!][!//
         [!VAR "TempChannel_FirstSpiIbNBuffers" = "SpiIbNBuffers"!][!//
         [!VAR "TempChannel_FirstSpiTransferStart" = "SpiTransferStart"!][!//
         [!ENDIF!][!//
         [!IF "($Matchcounter > 1) and (SpiChannelType = 'IB')"!][!//
         [!IF "($TempChannel_FirstSpiChannelId != SpiChannelId) or ($TempChannel_FirstSpiChannelType != SpiChannelType) or
         ($TempChannel_FirstSpiDataWidth != SpiDataWidth) or ($TempChannel_FirstSpiDefaultData != SpiDefaultData) or
         ($TempChannel_FirstSpiIbNBuffers != SpiIbNBuffers) or($TempChannel_FirstSpiTransferStart != SpiTransferStart) "!][!//
         [!ERROR!]If the same symbolic channel name [!"node:name(.)"!] is used for more than one channel, all channel attributes shall be identical.[!ENDERROR!]
         [!ENDIF!][!//
         [!ENDIF!][!//
         [!IF "($Matchcounter > 1) and (SpiChannelType = 'EB')"!][!//
         [!IF "($TempChannel_FirstSpiChannelId != SpiChannelId) or ($TempChannel_FirstSpiChannelType != SpiChannelType) or
         ($TempChannel_FirstSpiDataWidth != SpiDataWidth) or ($TempChannel_FirstSpiDefaultData != SpiDefaultData) or
         ($TempChannel_FirstSpiEbMaxLength != SpiEbMaxLength) or ($TempChannel_FirstSpiTransferStart != SpiTransferStart) "!][!//
         [!ERROR!]If the same symbolic channel name [!"node:name(.)"!] is used for more than one channel, all channel attributes shall be identical.[!ENDERROR!]
         [!ENDIF!][!//
         [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDNOCODE!][!//
[!IF "$Matchcounter = 1"!][!//
#define [!"name(.)"!]    ((Spi_ChannelType)[!"SpiChannelId"!])
[!ENDIF!][!//
[!ENDLOOP!][!//
#define SPI_MAX_CHANNEL  ((Spi_ChannelType)[!"num:i($SpiMaxChannelsCount)"!])

/**
@brief Defines the maximum number of supported jobs for all the driver configurations

@remarks Implements DSPI01920
*/
[!LOOP "SpiDriver/*/SpiJob/*"!][!//
#define [!"name(.)"!]   ((Spi_JobType)[!"SpiJobId"!])
[!ENDLOOP!][!//
#define SPI_MAX_JOB     ((Spi_JobType)[!"num:i($SpiMaxJobsCount)"!])

/**
@brief Defines the maximum number of supported sequences for all the driver configurations

@remarks Implements DSPI01930
*/
[!LOOP "SpiDriver/*/SpiSequence/*"!][!//
#define [!"name(.)"!]   ((Spi_SequenceType)[!"SpiSequenceId"!])
[!ENDLOOP!][!//
#define SPI_MAX_SEQUENCE  ((Spi_SequenceType)[!"num:i($SpiMaxSequencesCount)"!])

[!IF "node:exists(SpiGeneral/SpiOptimizeOneJobSequences)"!][!//
[!IF "SpiGeneral/SpiOptimizeOneJobSequences"!][!//
[!//
[!IF "node:exists(SpiGeneral/SpiOptimizedSeqNumber)"!][!//
/**
@brief Define the size of sequence cached data buffer for sequences having only one job.
*/
#define SPI_OPTIMIZED_SEQ_BUFFER_SIZE ((Spi_SequenceType)[!//
[!IF "SpiGeneral/SpiOptimizedSeqNumber > 0"!][!//
[!"SpiGeneral/SpiOptimizedSeqNumber"!][!//
[!ELSE!][!//
[!"num:i($SpiMaxOneJobSequences)"!][!//
[!ENDIF!][!//
)
[!ELSE!][!//
    [!ERROR!]Node '/SpiGeneral/SpiOptimizedSeqNumber' does not exists.[!ENDERROR!][!//
[!ENDIF!][!// "node:exists(SpiGeneral/SpiOptimizedSeqNumber)"
[!IF "node:exists(SpiGeneral/SpiOptimizedChannelsNumber)"!][!//
/**
@brief Define the size of channel cached data buffer for sequences having only one job.
*/
#define SPI_OPTIMIZED_CHANNEL_BUFFER_SIZE ((Spi_ChannelType)[!//
[!IF "SpiGeneral/SpiOptimizedChannelsNumber > 0"!][!//
[!"SpiGeneral/SpiOptimizedChannelsNumber"!][!//
[!ELSE!][!//
[!"num:i($SpiMaxOneJobSeqChannels)"!][!//
[!ENDIF!][!//
)
[!ELSE!][!//
    [!ERROR!]Node '/SpiGeneral/SpiOptimizedChannelsNumber' does not exists.[!ENDERROR!][!//
[!ENDIF!][!//
[!//
[!ENDIF!][!//
[!ENDIF!][!//

/**
@brief Defines the peripherals used throughout the configuration(s)
@remarks Implements DSPI01480, DSPI01100
*/
[!LOOP "SpiGeneral/SpiPhyUnit/*"!][!//
#define CSIB[!"@index"!]  (uint8)[!"@index"!]u
[!ENDLOOP!][!//
#define SPI_MAX_HWUNIT   [!"num:i(count(SpiGeneral/SpiPhyUnit/*))"!]u

/**
@brief Physical HWUnits definition - as from resource manager
*/
[!VAR "DSPI_0_Counter" = "0"!][!//
[!VAR "DSPI_1_Counter" = "0"!][!//
[!VAR "DSPI_2_Counter" = "0"!][!//
[!LOOP "SpiGeneral/SpiPhyUnit/*"!][!//
[!IF "SpiPhyUnitMapping = 'DSPI_0'"!][!//
[!VAR "DSPI_0_Counter" = "$DSPI_0_Counter + 1"!][!//
#define DSPI_0_HWUNIT   CSIB[!"@index"!]
[!ENDIF!][!//
[!IF "SpiPhyUnitMapping = 'DSPI_1'"!][!//
[!VAR "DSPI_1_Counter" = "$DSPI_1_Counter + 1"!][!//
#define DSPI_1_HWUNIT   CSIB[!"@index"!]
[!ENDIF!][!//
[!IF "SpiPhyUnitMapping = 'DSPI_2'"!][!//
[!VAR "DSPI_2_Counter" = "$DSPI_2_Counter + 1"!][!//
#define DSPI_2_HWUNIT   CSIB[!"@index"!]
[!ENDIF!][!//
[!ENDLOOP!][!//

/**
@brief Physical HWUnits enabled/disabled
*/
#define DSPI_0_ENABLED  ([!IF "$DSPI_0_Counter = 1"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
#define DSPI_1_ENABLED  ([!IF "$DSPI_1_Counter = 1"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
#define DSPI_2_ENABLED  ([!IF "$DSPI_2_Counter = 1"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
/**
@brief DSPI offset
*/

[!IF "$DSPI_0_Counter = 1"!][!//
#define DSPI_0_OFFSET  0u
[!ENDIF!][!//
[!IF "$DSPI_1_Counter = 1"!][!//
#define DSPI_1_OFFSET  1u
[!ENDIF!][!//
[!IF "$DSPI_2_Counter = 1"!][!//
#define DSPI_2_OFFSET  2u
[!ENDIF!][!//

/**
@brief SPI FIFO size
*/
#define SPI_FIFO_SIZE   (uint8)[!"ecu:get('SpiFifoSize')"!]u

/**
@brief Defines the external devices the driver will use

@remarks Implements DSPI01760
*/
[!LOOP "SpiDriver/*/SpiExternalDevice/*"!][!//
#define [!"name(.)"!]  (Spi_ExternalDeviceType)[!"@index"!]u
[!ENDLOOP!][!//

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
/**
@brief Define values for Autosar configuration variants
*/
#define SPI_VARIANT_PRECOMPILE  (0)
#define SPI_VARIANT_POSTBUILD   (1)
#define SPI_VARIANT_LINKTIME    (2)


[!IF "IMPLEMENTATION_CONFIG_VARIANT='VariantPreCompile'"!][!//
/**
@brief Defines the use of Pre-Compile(PC) support
@remarks Implements DSPI01000, DSPI01200
*/
#define SPI_CONFIG_VARIANT      SPI_VARIANT_PRECOMPILE
#define SPI_CFG_EXTERN_DECLARATIONS  \
extern CONST(Spi_ConfigType, SPI_CONST) SpiDriverConfig_PC;
[!ENDIF!][!//

[!IF "IMPLEMENTATION_CONFIG_VARIANT='VariantPostBuild'"!]
/**
@brief Defines the use of Post-Build(PB) support
@remarks Implements DSPI01000, DSPI01200
*/
#define SPI_CONFIG_VARIANT      SPI_VARIANT_POSTBUILD
#define SPI_CFG_EXTERN_DECLARATIONS \[!NOCODE!]
[!VAR "var_count1"="num:i(count(SpiDriver/*))"!][!VAR "w"="0"!]
[!LOOP "SpiDriver/*"!][!VAR "w"="$w + 1"!][!//
[!CODE!]
extern CONST(Spi_ConfigType, SPI_CONST) [!"@name"!];[!IF "$w < $var_count1"!] \[!ENDIF!][!ENDCODE!]
[!ENDLOOP!][!//
[!ENDNOCODE!][!//
[!ENDIF!]

[!IF "IMPLEMENTATION_CONFIG_VARIANT='VariantLinkTime'"!][!//
/**
@brief Defines the use of Link-Time(L) support
@remarks Implements DSPI01000, DSPI01200
*/
/* Link Time Support. */
#define SPI_CONFIG_VARIANT      SPI_VARIANT_LINKTIME
#define SPI_CFG_EXTERN_DECLARATIONS  \
extern CONST(Spi_ConfigType, SPI_CONST) [!"node:name(SpiDriver/*[1])"!];
[!ENDIF!][!//

/**
@brief Defines if transfers are made using DMA or FIFO.
*/
[!IF "ecu:get('SpiDMAPresent') = 'TRUE' and node:exists(SpiGeneral/SpiGlobalDmaEnable) and SpiGeneral/SpiGlobalDmaEnable = 'true'"!][!//
#define SPI_DMA_USED    (STD_ON)
[!ELSE!][!//
#define SPI_DMA_USED    (STD_OFF)
[!ENDIF!][!//

/**
@brief Defines if Spi driver optimization for sequences having only one job is activated or not.
@remarks If activated, additional RAM memory is required for internal data caching.
*/
[!IF "node:exists(SpiGeneral/SpiOptimizeOneJobSequences)"!][!//
#define SPI_OPTIMIZE_ONE_JOB_SEQUENCES ([!IF "SpiGeneral/SpiOptimizeOneJobSequences"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
[!ELSE!][!//
#define SPI_OPTIMIZE_ONE_JOB_SEQUENCES (STD_OFF)
[!ENDIF!][!//

/**
@brief Number of CPU clock cycles consumed by Spi_SyncTransmit() during the wait on TX/RX transmission
@remarks This value is set to the minimum measure retrieved for GHS, DIAB and CW compilers,
         with all optimizations activated
*/
#define SPI_WAIT_LOOP_TICKS       23u

/**
@brief Defines the "Number of Loops" timeout used by Spi_SyncTransmit function during the wait on TX/RX transmission
*/
[!NOCODE!][!//
    [!SELECT "node:ref(SpiGeneral/SpiClockRef)"!]
    [!VAR "CoreFrequency" = "McuClockReferencePointFrequency"!]
    [!ENDSELECT!]
[!ENDNOCODE!][!//
#define SPI_TIMEOUT_COUNTER       (uint32)(([!"num:i(SpiGeneral/SpiSyncTransmitTimeout * $CoreFrequency div 1000000)"!]u) / SPI_WAIT_LOOP_TICKS)



/*==================================================================================================
                                             Non AUTOSAR DEFINES
==================================================================================================*/
/**
@brief Allow simultaneous calls to Spi_SyncTransmit() for different threads.
       Two concurrent calls to Spi_SyncTransmit() will be allowed only if the related sequences
       do not share HW units.
*/
#define SPI_ENABLE_MULTI_SYNC_TRANSMIT             ([!IF "SpiNonAUTOSAR/SpiEnableMultiSyncTransmit"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

/**
@brief If enabled, allows to configure more than 256 sequences, jobs and channels.
*/
[!IF " node:exists(SpiNonAUTOSAR/SpiAllowBigSizeCollections) and (node:value(SpiNonAUTOSAR/SpiAllowBigSizeCollections) = 'true')"!][!//
#define SPI_ALLOW_BIGSIZE_COLLECTIONS (STD_ON)
[!ELSE!][!//
#define SPI_ALLOW_BIGSIZE_COLLECTIONS (STD_OFF)
[!ENDIF!][!//
/**
@brief If enabled, the asyncronous operation mode (POLLING or INTERRUPT) can
       be defined independently for each HWUnit using Spi_SetHWUnitAsyncMode().
*/
[!IF "(SpiGeneral/SpiLevelDelivered = 2) and node:exists(SpiNonAUTOSAR/SpiEnableHWUnitAsyncMode)"!][!//
#define SPI_HWUNIT_ASYNC_MODE ([!IF "SpiNonAUTOSAR/SpiEnableHWUnitAsyncMode"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
[!ELSE!][!//
#define SPI_HWUNIT_ASYNC_MODE (STD_OFF)
[!ENDIF!][!//

/**
@brief If enabled, allows dual MCU clock configuration settings.
*/
[!IF " node:exists(SpiNonAUTOSAR/SpiEnableDualClockMode) and (node:value(SpiNonAUTOSAR/SpiEnableDualClockMode) = 'true')"!][!//
#define SPI_DUAL_CLOCK_MODE (STD_ON)
[!ELSE!][!//
#define SPI_DUAL_CLOCK_MODE (STD_OFF)
[!ENDIF!][!//

/**
@brief   Specifies if TSB implementation is supported
*/
[!IF "ecu:get('SpiTSBSupport') = 'TRUE'"!][!//
#define TSB_MODE_SUPPORTED
[!ELSE!][!//
[!ENDIF!][!//

/**
@brief   Specifies if TSB feature/mode is available
*/
[!IF "node:exists(SpiNonAUTOSAR/SpiTSBModeSupport) and (node:value(SpiNonAUTOSAR/SpiTSBModeSupport) = 'true')"!][!//
#define SPI_TSB_MODE  (STD_ON)
[!ELSE!][!//
#define SPI_TSB_MODE (STD_OFF)
[!ENDIF!][!//

[!IF "node:exists(SpiNonAUTOSAR/SpiTSBModeSupport) and (node:value(SpiNonAUTOSAR/SpiTSBModeSupport) = 'true')"!][!//
[!LOOP "SpiDriver/*"!][!//
[!VAR "TSBJobCount"="0"!][!//
[!LOOP "SpiJob/*"!][!//
[!IF "node:exists(TSBModeEnable) and TSBModeEnable = 'true'"!][!//
   [!VAR "TSBJobCount" = "$TSBJobCount +1"!] [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDLOOP!][!//
#define SPI_MAX_TSBJOBS (Spi_JobType)([!"num:i($TSBJobCount)"!])
[!ENDIF!][!//
/**
@brief If enabled, SpiDataType is declared as uint8 instead of uint16.
@remarks Implements DSPI05210
*/
#define SPI_DATA_WIDTH_8  0u
#define SPI_DATA_WIDTH_16 1u
[!IF " node:exists(SpiNonAUTOSAR/SpiForceDataType) and (node:value(SpiNonAUTOSAR/SpiForceDataType) = 'true')"!][!//
#define SPI_FORCE_DATA_TYPE (STD_ON)
[!ELSE!][!//
#define SPI_FORCE_DATA_TYPE (STD_OFF)
[!ENDIF!][!//

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

#if (SPI_CONFIG_VARIANT != SPI_VARIANT_PRECOMPILE)
#define SPI_START_CONFIG_DATA_UNSPECIFIED
/**
@file Spi_Cfg.h
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_Cfg_h_REF_1 & @ref Spi_Cfg_h_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/


#define SPI_STOP_CONFIG_DATA_UNSPECIFIED
/**
@file Spi_Cfg.h
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_Cfg_h_REF_1 & @ref Spi_Cfg_h_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/
#endif /* (SPI_CONFIG_VARIANT != SPI_VARIANT_PRECOMPILE) */

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#define SPI_START_SEC_CODE
/**
@file Spi_Cfg.h
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_Cfg_h_REF_1 & @ref Spi_Cfg_h_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/


#define SPI_STOP_SEC_CODE
/**
@file Spi_Cfg.h
@note Violates MISRA 2004 Advisory Rules 19.1 & Rule 19.15
      - See @ref Spi_Cfg_h_REF_1 & @ref Spi_Cfg_h_REF_2
*/
/*lint -save -e537 -e451 -e961*/
#include "MemMap.h"
/*lint -restore*/

#ifdef __cplusplus
}
#endif

#endif /*SPI_CFG_H*/

[!ENDCODE!][!//
