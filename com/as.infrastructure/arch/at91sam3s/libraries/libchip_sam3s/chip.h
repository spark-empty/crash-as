#ifndef _LIB_SAM3S_
#define _LIB_SAM3S_

/*
 * Peripherals registers definitions
 */
#if defined sam3s4
#elif defined sam3s2
#elif defined sam3s1
#else
    #warning Library does not support the specified chip, specifying sam3s4.
    #define sam3s4
#endif
#include "include/SAM3S.h"


/* Define attribute */
#if defined   ( __CC_ARM   ) /* Keil �Vision 4 */
    #define WEAK __attribute__ ((weak))
#elif defined ( __ICCARM__ ) /* IAR Ewarm 5.41+ */
    #define WEAK __weak
#elif defined (  __GNUC__  ) /* GCC CS3 2009q3-68 */
    #define WEAK __attribute__ ((weak))
#endif

/* Define NO_INIT attribute */
#if defined   ( __CC_ARM   )
    #define NO_INIT
#elif defined ( __ICCARM__ )
    #define NO_INIT __no_init
#elif defined (  __GNUC__  )
    #define NO_INIT
#endif


/*
 * Core
 */

#include "include/exceptions.h"

/*
 * Peripherals
 */
#include "include/acc.h"
#include "include/adc.h"
#include "include/async.h"
#include "include/crccu.h"
#include "include/dacc.h"
#include "include/efc.h"
#include "include/flashd.h"
#include "include/hsmci.h"
#include "include/pio.h"
#include "include/pio_it.h"
#include "include/pio_capture.h"
#include "include/pmc.h"
#include "include/pwmc.h"
#include "include/rtc.h"
#include "include/rtt.h"
#include "include/spi.h"
#include "include/spi_pdc.h"
#include "include/ssc.h"
#include "include/tc.h"
#include "include/twi.h"
#include "include/twid.h"
#include "include/usart.h"
#include "include/led.h"
#include "include/USBD_Config.h"

#include "include/trace.h"
#include "include/wdt.h"

#endif /* _LIB_SAM3S_ */
