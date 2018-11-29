/*==================================================================================================
Revision History:
                             Modification     Tracking
Author (core ID)              Date D/M/Y       Number     Description of Changes
---------------------------   ----------    ------------  ------------------------------------------
Jaromir Jasik (R60817)        16/09/2009    ENGR00114912  [Fls]: CodeBase Updates
Jaromir Jasik (R60817)        22/09/2009    ENGR00116576  [Fls]: Updates for MPC5604B, MPC5607B platforms
Jaromir Jasik (R60817)        26/01/2010    ENGR00120421  [FLS] Updates for Beta 2.9.2
Cosimo Stornaiuolo            01/02/2011    ENGR00138719  [FLS]: Updates for XPC563M
---------------------------   ----------    ------------  ------------------------------------------
==================================================================================================*/

#include "Fls_sectors_unlock.h"
#include "Platform_Types.h"

void Fls_SectorsUnlock(void)
{
    /* FLASHMEM0_CF0_A unprotect/unlock */
    *((volatile uint32*)(0xC3F88004)) = 0xA1A11111; /* FLASHMEM_LML */
    *((volatile uint32*)(0xC3F88004)) = 0x00000000; /* FLASHMEM_LML */
    *((volatile uint32*)(0xC3F8800C)) = 0xC3C33333; /* FLASHMEM_SLL */
    *((volatile uint32*)(0xC3F8800C)) = 0x00000000; /* FLASHMEM_SLL */

    /* FLASHMEM0_CF0_A unprotect/unlock */
    *((volatile uint32*)(0xC3FB0008)) = 0xB2B22222; /* FLASHMEM_HBL */
    *((volatile uint32*)(0xC3FB0008)) = 0x00000000; /* FLASHMEM_HBL */

        /* FLASHMEM0_CF0_A unprotect/unlock */
    *((volatile uint32*)(0xC3FB4008)) = 0xB2B22222; /* FLASHMEM_HBL */
    *((volatile uint32*)(0xC3FB4008)) = 0x00000000; /* FLASHMEM_HBL */

}
