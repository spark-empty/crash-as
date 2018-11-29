/*
 *  TOPPERS ATK2
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 *      Automotive Kernel Version 2
 *
 *  Copyright (C) 2011-2015 by Center for Embedded Computing Systems
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2011-2015 by FUJI SOFT INCORPORATED, JAPAN
 *  Copyright (C) 2011-2013 by Spansion LLC, USA
 *  Copyright (C) 2011-2015 by NEC Communication Systems, Ltd., JAPAN
 *  Copyright (C) 2011-2015 by Panasonic Advanced Technology Development Co., Ltd., JAPAN
 *  Copyright (C) 2011-2014 by Renesas Electronics Corporation, JAPAN
 *  Copyright (C) 2011-2015 by Sunny Giken Inc., JAPAN
 *  Copyright (C) 2011-2015 by TOSHIBA CORPORATION, JAPAN
 *  Copyright (C) 2011-2015 by Witz Corporation
 *  Copyright (C) 2014-2015 by AISIN COMCRUISE Co., Ltd., JAPAN
 *  Copyright (C) 2014-2015 by eSOL Co.,Ltd., JAPAN
 *  Copyright (C) 2014-2015 by SCSK Corporation, JAPAN
 *  Copyright (C) 2015 by SUZUKI MOTOR CORPORATION
 *  Copyright (C) 2016 by Fan Wang(parai@foxmail.com), China
 * 
 * The above copyright holders grant permission gratis to use,
 * duplicate, modify, or redistribute (hereafter called use) this
 * software (including the one made by modifying this software),
 * provided that the following four conditions (1) through (4) are
 * satisfied.
 * 
 * (1) When this software is used in the form of source code, the above
 *    copyright notice, this use conditions, and the disclaimer shown
 *    below must be retained in the source code without modification.
 *
 * (2) When this software is redistributed in the forms usable for the
 *    development of other software, such as in library form, the above
 *    copyright notice, this use conditions, and the disclaimer shown
 *    below must be shown without modification in the document provided
 *    with the redistributed software, such as the user manual.
 *
 * (3) When this software is redistributed in the forms unusable for the
 *    development of other software, such as the case when the software
 *    is embedded in a piece of equipment, either of the following two
 *    conditions must be satisfied:
 *
 *  (a) The above copyright notice, this use conditions, and the
 *      disclaimer shown below must be shown without modification in
 *      the document provided with the redistributed software, such as
 *      the user manual.
 *
 *  (b) How the software is to be redistributed must be reported to the
 *      TOPPERS Project according to the procedure described
 *      separately.
 *
 * (4) The above copyright holders and the TOPPERS Project are exempt
 *    from responsibility for any type of damage directly or indirectly
 *    caused from the use of this software and are indemnified by any
 *    users or end users of this software from any and all causes of
 *    action whatsoever.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS." THE ABOVE COPYRIGHT HOLDERS AND
 * THE TOPPERS PROJECT DISCLAIM ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, ITS APPLICABILITY TO A PARTICULAR
 * PURPOSE. IN NO EVENT SHALL THE ABOVE COPYRIGHT HOLDERS AND THE
 * TOPPERS PROJECT BE LIABLE FOR ANY TYPE OF DAMAGE DIRECTLY OR
 * INDIRECTLY CAUSED FROM THE USE OF THIS SOFTWARE.
 *
 *  $Id: check.h 504 2015-12-24 01:22:56Z witz-itoyo $
 */

/*
 *		Error checking for macro
 */

#ifndef TOPPERS_CHECK_H
#define TOPPERS_CHECK_H

#include "Os_Cfg.h"
#include "memory.h"

/*
 * General-purpose check macro
 */
#define CHECK_ERROR_ERCD(exp, error) \
	do {							 \
		if (!(exp)) {				 \
			ercd = (error);			 \
			goto error_exit;		 \
		}							 \
	} while (0)

#define CHECK_ERROR_NO_ERCD(exp) \
	do {						 \
		if (!(exp)) {			 \
			goto error_exit;	 \
		}						 \
	} while (0)

#define D_CHECK_ERROR_ERCD(exp, error) \
	do {							   \
		if (!(exp)) {				   \
			ercd = (error);			   \
			goto d_error_exit;		   \
		}							   \
	} while (0)

#define D_CHECK_ERROR_NO_ERCD(exp) \
	do {						   \
		if (!(exp)) {			   \
			goto d_error_exit;	   \
		}						   \
	} while (0)

/*
 *  Of standard error checking macro
 */
#define S_CHECK_ERROR(exp, error)		CHECK_ERROR_ERCD(exp, error)


#ifdef CFG_USE_ERRORHOOK
/*
 *  Re-definition of the label by the error hook use the presence or absence
 */
#define error_exit		exit_errorhook
#define d_error_exit	d_exit_errorhook

/*
 *  When using error hook substitutes the error code
 */
#define S_N_CHECK_ERROR(exp, error)		CHECK_ERROR_ERCD(exp, error)

#else /* CFG_USE_ERRORHOOK */
/*
 *  Re-definition of the label by the error hook use the presence or absence
 */
#define error_exit		exit_no_errorhook
#define d_error_exit	d_exit_no_errorhook

/*
 *  Do not assign the error code when you do not want to use the error hook
 */
#define S_N_CHECK_ERROR(exp, error)		CHECK_ERROR_NO_ERCD(exp)

#endif /* CFG_USE_ERRORHOOK */


/* We use the following check macro inside the OS */

/*
 *  Macro corresponding to the error code
 *   Standard error
 */
#ifdef OMIT_STANDARD_DISALLINT

#define S_CHECK_DISALLINT()
#define S_N_CHECK_DISALLINT()

#else /* OMIT_STANDARD_DISALLINT */

#define S_CHECK_DISALLINT()								 \
	S_CHECK_ERROR(										 \
		((callevel_stat & TSYS_DISALLINT) == TSYS_NULL), \
		E_OS_DISABLEDINT								 \
		)
#define S_N_CHECK_DISALLINT()							 \
	S_N_CHECK_ERROR(									 \
		((callevel_stat & TSYS_DISALLINT) == TSYS_NULL), \
		E_OS_DISABLEDINT								 \
		)

#endif /* OMIT_STANDARD_DISALLINT */

#define S_CHECK_STATE(exp)				S_CHECK_ERROR(exp, E_OS_STATE)
#define S_N_CHECK_STATE(exp)			S_N_CHECK_ERROR(exp, E_OS_STATE)
#define S_CHECK_LIMIT(exp)				S_CHECK_ERROR(exp, E_OS_LIMIT)
#define S_N_CHECK_LIMIT(exp)			S_N_CHECK_ERROR(exp, E_OS_LIMIT)
#define S_D_CHECK_NOFUNC(exp)			D_CHECK_ERROR_ERCD(exp, E_OS_NOFUNC)
#define S_D_CHECK_STATE(exp)			D_CHECK_ERROR_ERCD(exp, E_OS_STATE)
#define S_D_CHECK_LIMIT(exp)			D_CHECK_ERROR_ERCD(exp, E_OS_LIMIT)

#define S_D_CHECK_PROTECTION_ARRIVAL_TASK(exp)			D_CHECK_ERROR_ERCD(exp, E_OS_PROTECTION_ARRIVAL_TASK)

#define S_D_CHECK_IOC_LIMIT(exp) do { \
		if (!(exp)) {				  \
			ercd = IOC_E_LIMIT;		  \
			p_ioccb->lostflg = TRUE;  \
			goto d_error_exit;		  \
		}							  \
} while (0)

#define S_D_CHECK_IOC_LOST(exp) do {  \
		if (!(exp)) {				  \
			ercd = IOC_E_LOST_DATA;	  \
			p_ioccb->lostflg = FALSE; \
			goto d_error_exit;		  \
		}							  \
} while (0)

#define S_D_CHECK_IOC_NO_DATA(exp)		D_CHECK_ERROR_ERCD(exp, IOC_E_NO_DATA)


/*
 *  Macro corresponding to the error code
 *   Extended Error
 */
#define CHECK_ACCESS(exp)				CHECK_ERROR_ERCD(exp, E_OS_ACCESS)
#define D_CHECK_ACCESS(exp)				D_CHECK_ERROR_ERCD(exp, E_OS_ACCESS)
#define CHECK_CALLEVEL(clmask)					  \
	CHECK_ERROR_ERCD(							  \
		((callevel_stat | (clmask)) == (clmask)), \
		E_OS_CALLEVEL							  \
		)
#define CHECK_NOFUNC(exp)				CHECK_ERROR_ERCD(exp, E_OS_NOFUNC)
#define CHECK_RESOURCE(exp)				CHECK_ERROR_ERCD(exp, E_OS_RESOURCE)
#define CHECK_STATE(exp)				CHECK_ERROR_ERCD(exp, E_OS_STATE)
#define D_CHECK_STATE(exp)				D_CHECK_ERROR_ERCD(exp, E_OS_STATE)
#define CHECK_VALUE(exp)				CHECK_ERROR_ERCD(exp, E_OS_VALUE)
#define CHECK_DISABLEDINT()										\
	CHECK_ERROR_ERCD(											\
		((callevel_stat &										\
		  (TSYS_DISALLINT | TSYS_SUSALLINT | TSYS_SUSOSINT)) ==	\
		 TSYS_NULL												\
		),														\
		E_OS_DISABLEDINT										\
		)
#define CHECK_PARAM_POINTER(p_exp)		CHECK_ERROR_ERCD(((p_exp) != NULL), OS_E_PARAM_POINTER)
#define CHECK_ID(exp)					CHECK_ERROR_ERCD(exp, E_OS_ID)
#define D_CHECK_ID(exp)					D_CHECK_ERROR_ERCD(exp, E_OS_ID)
#define CHECK_IOC_ACCESS(exp)			CHECK_ERROR_ERCD(exp, IOC_E_NOK)
#define CHECK_IOC_CALLEVEL_DISABLEDINT(clmask)	  \
	CHECK_ERROR_ERCD(							  \
		((callevel_stat | (clmask)) == (clmask)), \
		IOC_E_NOK								  \
		)
#define CHECK_SERVICEID(exp)			CHECK_ERROR_ERCD(exp, E_OS_SERVICEID)
#define CHECK_RIGHT(btmp)														   \
	CHECK_ERROR_ERCD(															   \
		(run_trusted != FALSE) || ((p_runosap->p_osapinib->btptn & (btmp)) != 0U), \
		E_OS_ACCESS																   \
		)
#define CHECK_ILLEGAL_ADDRESS(exp)		CHECK_ERROR_ERCD(exp, E_OS_ILLEGAL_ADDRESS)
#define CHECK_MEM_WRITE(p_var, type)	CHECK_ERROR_ERCD((PROBE_MEM_WRITE(p_var, type) != FALSE), E_OS_ILLEGAL_ADDRESS)
#define CHECK_MEM_RW(p_var, type)		CHECK_ERROR_ERCD((PROBE_MEM_RW(p_var, type) != FALSE), E_OS_ILLEGAL_ADDRESS)
#define CHECK_NO_ERCD(exp)				CHECK_ERROR_NO_ERCD(exp)
#define CHECK_IOC_MEM_READ(p_var, size, alignsz) {			\
		if ((probe_memory_read(p_var, size) == FALSE) ||	\
			(((uintptr) (p_var) & (alignsz - 1U)) != 0U)) {	\
			ercd = E_OS_SYS_ASSERT_FATAL;					\
			goto exit_no_errorhook;							\
		}													\
}
#define CHECK_IOC_MEM_WRITE(p_var, size, alignsz) {			\
		if ((probe_memory_write(p_var, size) == FALSE) ||	\
			(((uintptr) (p_var) & (alignsz - 1U)) != 0U)) {	\
			ercd = E_OS_SYS_ASSERT_FATAL;					\
			goto exit_no_errorhook;							\
		}													\
}

#endif /* TOPPERS_CHECK_H */
