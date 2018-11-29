/*
* Configuration of module: Ea
*
* Created by:   parai
* Copyright:    (C)parai@foxmail.com  
*
* Configured for (MCU):    posix
*
* Module vendor:           ArcCore
* Generator version:       01.00
*
* Generated by easySAR Studio (https://github.com/parai/as)
*/
#ifndef EA_CFG_H_
#define EA_CFG_H_

#include "MemIf_Types.h"
#ifdef USE_NVM
#include "NvM.h"
#endif

#define EA_DEV_ERROR_DETECT            STD_ON
#define EA_VERSION_INFO_API            STD_OFF
#define EA_SET_MODE_SUPPORTED          STD_ON

#define EA_INDEX                        (0xEA)
#define EA_VIRTUAL_PAGE_SIZE            8

#define EA_BLOCK_NUM_EaTest1                          1
#define EA_BLOCK_NUM_EaTest2                          2

#define EA_NUMBER_OF_BLOCKS 2

#ifdef USE_NVM
  #define EA_MAX_BLOCK_SIZE NVM_EA_MAX_BLOCK_LENGTH
#else
  #define EA_MAX_BLOCK_SIZE 32
#endif


/*
    ITEM NAME:        <Ea_BlockConfigType>
    SCOPE:            <Ea Module>
    DESCRIPTION:
        Configuration of block specific parameters for the EEPROM abstraction module.
*/
/*@req EA040
*/

typedef struct {
    /*@req EA116
    */
    /*Block identifier (handle). 0x0000 and 0xFFFF shall not be used for block numbers (see EA006).
    Range:    min = 2^NVM_DATA_SELECTION_BITS
            max = 0xFFFF -2^NVM_DATA_SELECTION_BITS
    Note:     Depending on the number of bits set aside for dataset selection several other block numbers shall
            also be left out to ease implementation.
    NVM_DATA_SELECTION_BITS = 4        So range: 0x10 ~ 0xFFEF*/
    uint16    EaBlockNumber;

    /*Size of a logical block in bytes.*/
    /*@req EA117
    */
    uint16    EaBlockSize;

    /*Marker for high priority data.
    true: Block contains immediate data.
    false: Block does not contain immediate data.*/
    /*@req EA118
    */
    boolean    EaImmediateData;

    /*Device index (handle). Range: 0 .. 254 (0xFF reserved for broadcast call to GetStatus function).
    Type:    Reference to EepGeneral item 'EepDriverIndex'
    dependency: This information is needed by the NVRAM manager respectively the Memory Abstraction
    Interface to address a certain logical block. It is listed in this specification to give a complete overview
    over all block related configuration parameters.*/
    /*@req EA115
    */
    uint8    EaDeviceIndex;

    /*indicates the end of the Ea Block List*/
    boolean EaBlockEOL;
}Ea_BlockConfigType;

/*
    ITEM NAME:        <Ea_GeneralType>
    SCOPE:            <Ea Module>
    DESCRIPTION:
        General configuration of the EEPROM abstraction module. This container lists block independent
        configuration parameters.
*/
typedef struct {
    /*Specifies the InstanceId of this module instance. If only one instance is present it shall have the Id 0.*/
    uint8    EaIndex;

    /*Mapped to the job end notification routine provided by the upper layer module (NvM_JobEndNotification).*/
    void (*EaNvmJobEndNotification)(void);

    /*Mapped to the job error notification routine provided by the upper layer module (NvM_JobErrorNotification). */
    void (*EaNvmJobErrorNotification)(void);
}Ea_GeneralType;

extern const Ea_GeneralType Ea_GeneralData;
extern const Ea_BlockConfigType Ea_BlockConfigData[];

#endif /*EA_CFG_H_*/
