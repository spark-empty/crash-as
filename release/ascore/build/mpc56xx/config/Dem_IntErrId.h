/*
* Configuration of module: Dem
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
#ifndef DEM_INTERRID_H
#define DEM_INTERRID_H
/* ============================ [ INCLUDES  ] ====================================================== */
/* ============================ [ MACROS    ] ====================================================== */
/*
 * Definition of event IDs used by BSW
 * NB! Must be unique for each event!
 */

enum {
    // Event IDs from DEM module
    DEM_EVENT_ID_NULL = 0,            // Do not change this entry!!!
	EEP_E_WRITE_FAILED,
	EEP_E_READ_FAILED,
	FLS_E_ERASE_FAILED,
	FLS_E_WRITE_FAILED,
	FLS_E_READ_FAILED,
	CANNM_E_NETWORK_TIMEOUT,
	PDUR_E_PDU_INSTANCE_LOST,
	NVM_E_INTEGRITY_FAILED,
	NVM_E_REQ_FAILED,
	ECUM_E_ALL_RUN_REQUESTS_KILLED,
	ECUM_E_RAM_CHECK_FAILED,
    // DEM last event id for BSW
    DEM_EVENT_ID_LAST_FOR_BSW
};
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
#endif

