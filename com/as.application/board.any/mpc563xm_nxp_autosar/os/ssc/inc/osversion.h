#ifndef OSVERSION_H 
#define OSVERSION_H

/******************************************************************************
*
*   Freescale(TM) and the Freescale logo are trademarks of Freescale Semiconductor, Inc. 
*   All other product or service names are the property of their respective owners. 
*   (C) Freescale Semiconductor, Inc. 2006-2010
*
*   THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
*   BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
*   Freescale Semiconductor, Inc.
*
* Filename:     $Source: /u/OSEK/src/autosar/src/osmpc56xxAMv3/ssc/inc/osversion.h,v $
* Author:       $Author: b00355 $
* Revision:     $Revision: 1.6 $
*
* History:      Use the CVS command rlog to display revision history
*               information.
*
* Description:  OS version info
*
******************************************************************************/

#define OS_VENDOR_ID        43u     /* Freescale AUTOSAR Vendor ID  */ 
#define OS_MODULE_ID        0x01    /* Module ID of the OS  */
#define OS_AR_MAJOR_VERSION 3       /* Major version number of AUTOSAR specification    */
#define OS_AR_MINOR_VERSION 0       /* Minor version number of AUTOSAR specification    */
#define OS_AR_PATCH_VERSION 3       /* Patch level version number of AUTOSAR specification  */
#define OS_SW_MAJOR_VERSION 30      /* Major version number of the implementation   */
#define OS_SW_MINOR_VERSION 35      /* Minor version number of the implementation   */
#define OS_SW_PATCH_VERSION 0       /* Patch level version number of the implementation */

#define OSBUILDNUMBER   "OS/MPC56xxAM v3.0 build 3.0.35"

#endif  /* OSVERSION_H */
