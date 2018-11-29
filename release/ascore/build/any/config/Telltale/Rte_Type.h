#ifndef RTE_TYPE_H
#define RTE_TYPE_H

/*********************************************************************************************************************
* Includes
*********************************************************************************************************************/
#include "Std_Types.h"

/*********************************************************************************************************************
* Data Type Definitions
*********************************************************************************************************************/

#define Rte_TypeDef_OnOff_T
typedef uint8 OnOff_T;
#define OnOff_T_LowerLimit ((OnOff_T)0u)
#define OnOff_T_UpperLimit ((OnOff_T)4u)
#define RTE_CONST_OnOff_Off (0u)
#define RTE_CONST_OnOff_On (1u)
#define RTE_CONST_OnOff_1Hz (2u)
#define RTE_CONST_OnOff_2Hz (3u)
#define RTE_CONST_OnOff_3Hz (4u)

#define OnOff_Off ((OnOff_T)0u)
#define OnOff_On ((OnOff_T)1u)
#define OnOff_1Hz ((OnOff_T)2u)
#define OnOff_2Hz ((OnOff_T)3u)
#define OnOff_3Hz ((OnOff_T)4u)


#ifndef RTE_SUPPRESS_UNUSED_DATATYPES

typedef boolean Boolean;

typedef sint16 SInt16;
#define SInt16_LowerLimit ((SInt16)-32768)
#define SInt16_UpperLimit ((SInt16)32767)

typedef sint32 SInt32;
#define SInt32_LowerLimit ((SInt32)-2147483648)
#define SInt32_UpperLimit ((SInt32)2147483647)

typedef sint8 SInt8;
#define SInt8_LowerLimit ((SInt8)-128)
#define SInt8_UpperLimit ((SInt8)127)

typedef uint16 UInt16;
#define UInt16_LowerLimit ((UInt16)0u)
#define UInt16_UpperLimit ((UInt16)65535u)

typedef uint32 UInt32;
#define UInt32_LowerLimit ((UInt32)0u)
#define UInt32_UpperLimit ((UInt32)4294967295u)

typedef uint8 UInt8;
#define UInt8_LowerLimit ((UInt8)0u)
#define UInt8_UpperLimit ((UInt8)255u)

#endif

#endif //RTE_TYPE_H

