/* -------------------------------- Arctic Core ------------------------------
 * Arctic Core - the open source AUTOSAR platform http://arccore.com
 *
 * Copyright (C) 2009  ArcCore AB <contact@arccore.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * -------------------------------- Arctic Core ------------------------------*/








#ifndef MEMIF_TYPES_H_
#define MEMIF_TYPES_H_

typedef enum {

	//	The underlying abstraction module or device driver has
	//	not been initialized (yet).
	MEMIF_UNINIT,
	// The underlying abstraction module or device driver is
	// currently idle.
	MEMIF_IDLE,
	
	// The underlying abstraction module or device driver is
	// currently busy.
	MEMIF_BUSY,
	
	//	The underlying abstraction module is busy with internal
	// management operations. The underlying device driver
	// can be busy or idle.
	MEMIF_BUSY_INTERNAL              
} MemIf_StatusType;

typedef enum {
	//The job has been finished successfully.
	MEMIF_JOB_OK,
	// The job has not been finished successfully.
	MEMIF_JOB_FAILED,
	//	The job has not yet been finished.
	MEMIF_JOB_PENDING,
	//	The job has been canceled.
	MEMIF_JOB_CANCELLED,
	//	The requested block is inconsistent, it may contain
	//	corrupted data.	       
	MEMIF_BLOCK_INCONSISTENT,
	// The requested block has been marked as invalid,
	// the requested operation can not be performed.
	MEMIF_BLOCK_INVALID
	
} MemIf_JobResultType; 


typedef enum {
	//    The underlying memory abstraction modules and
	//    drivers are working in slow mode.
	MEMIF_MODE_SLOW,
	// The underlying memory abstraction modules and
	// drivers are working in fast mode.
    MEMIF_MODE_FAST
} MemIf_ModeType;

// Definition of broadcast device ID
#define MEMIF_BROADCAST_ID	0xff

#endif /*MEMIF_TYPES_H_*/
