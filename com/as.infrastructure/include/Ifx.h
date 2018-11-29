#ifndef COM_AS_INFRASTRUCTURE_INCLUDE_IFX_H_
#define COM_AS_INFRASTRUCTURE_INCLUDE_IFX_H_
/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2016  AS <parai@foxmail.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"

/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */
typedef struct
{
	uint16 Index; /* Data point index */
	uint16 Ratio; /* Data point ratio */
}Ifx_DPResultU16_Type;
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */

/* Interpolation between two given points is calculated as shown below.
 *                          x - x0
 *   y = y0 + (y1 - y0) * -----------
 *                          x1 - x0
 */

/* Ifx_DPSearch_<InTypeMn> routine searches the position of input Xin within the
 * given distribution array X_array, and returns index and ratio necessary for interpolation.
 */
void Ifx_DPSearch_u8  (Ifx_DPResultU16_Type* dpResult,uint8  Xin,uint8  N,const uint8*  X_array);
void Ifx_DPSearch_s8  (Ifx_DPResultU16_Type* dpResult,sint8  Xin,sint8  N,const sint8*  X_array);
void Ifx_DPSearch_u16 (Ifx_DPResultU16_Type* dpResult,uint16 Xin,uint16 N,const uint16* X_array);
void Ifx_DPSearch_s16 (Ifx_DPResultU16_Type* dpResult,sint16 Xin,sint16 N,const sint16* X_array);

/* Based on searched index and ratio information, this routine calculates and returns
 * interpolation for curve.
 */
sint8  Ifx_IpoCur_s8  (const Ifx_DPResultU16_Type* dpResult, const sint8*  Val_array);
sint16 Ifx_IpoCur_s16 (const Ifx_DPResultU16_Type* dpResult, const sint16* Val_array);
uint16 Ifx_IpoCur_u16 (const Ifx_DPResultU16_Type* dpResult, const uint16* Val_array);
uint8  Ifx_IpoCur_u8  (const Ifx_DPResultU16_Type* dpResult, const uint8*  Val_array);

sint8  Ifx_LkUpCur_s8  (const Ifx_DPResultU16_Type* dpResult, const sint8*  Val_array);
sint16 Ifx_LkUpCur_s16 (const Ifx_DPResultU16_Type* dpResult, const sint16* Val_array);
uint16 Ifx_LkUpCur_u16 (const Ifx_DPResultU16_Type* dpResult, const uint16* Val_array);
uint8  Ifx_LkUpCur_u8  (const Ifx_DPResultU16_Type* dpResult, const uint8*  Val_array);

uint8  Ifx_IpoMap_u8  ( const Ifx_DPResultU16_Type* dpResultX,const Ifx_DPResultU16_Type* dpResultY,uint16 num_value,const uint8*  Val_array);
uint16 Ifx_IpoMap_u16 ( const Ifx_DPResultU16_Type* dpResultX,const Ifx_DPResultU16_Type* dpResultY,uint16 num_value,const uint16* Val_array);
sint8  Ifx_IpoMap_s8  ( const Ifx_DPResultU16_Type* dpResultX,const Ifx_DPResultU16_Type* dpResultY,uint16 num_value,const sint8*  Val_array);
sint16 Ifx_IpoMap_s16 ( const Ifx_DPResultU16_Type* dpResultX,const Ifx_DPResultU16_Type* dpResultY,uint16 num_value,const sint16* Val_array);

uint8  Ifx_LkUpMap_u8 (const Ifx_DPResultU16_Type* dpResultX,const Ifx_DPResultU16_Type* dpResultY,uint16 num_value,const uint8*  Val_array);
uint16 Ifx_LkUpMap_u16(const Ifx_DPResultU16_Type* dpResultX,const Ifx_DPResultU16_Type* dpResultY,uint16 num_value,const uint16* Val_array);
sint8  Ifx_LkUpMap_s8 (const Ifx_DPResultU16_Type* dpResultX,const Ifx_DPResultU16_Type* dpResultY,uint16 num_value,const sint8*  Val_array);
sint16 Ifx_LkUpMap_s16(const Ifx_DPResultU16_Type* dpResultX,const Ifx_DPResultU16_Type* dpResultY,uint16 num_value,const sint16* Val_array);

uint8  Ifx_LkUpBaseMap_u8 (const Ifx_DPResultU16_Type* dpResultX,const Ifx_DPResultU16_Type* dpResultY,uint16 num_value,const uint8*  Val_array);
uint16 Ifx_LkUpBaseMap_u16(const Ifx_DPResultU16_Type* dpResultX,const Ifx_DPResultU16_Type* dpResultY,uint16 num_value,const uint16* Val_array);
sint8  Ifx_LkUpBaseMap_s8 (const Ifx_DPResultU16_Type* dpResultX,const Ifx_DPResultU16_Type* dpResultY,uint16 num_value,const sint8*  Val_array);
sint16 Ifx_LkUpBaseMap_s16(const Ifx_DPResultU16_Type* dpResultX,const Ifx_DPResultU16_Type* dpResultY,uint16 num_value,const sint16* Val_array);

uint8  Ifx_IntIpoCur_u8_u8   ( uint8  Xin, uint8  N, const uint8*  X_array, const uint8*  Val_array);
uint16 Ifx_IntIpoCur_u8_u16  ( uint8  Xin, uint8  N, const uint8*  X_array, const uint16* Val_array);
sint8  Ifx_IntIpoCur_u8_s8   ( uint8  Xin, uint8  N, const uint8*  X_array, const sint8*  Val_array);
sint16 Ifx_IntIpoCur_u8_s16  ( uint8  Xin, uint8  N, const uint8*  X_array, const sint16* Val_array);
uint8  Ifx_IntIpoCur_u16_u8  ( uint16 Xin, uint16 N, const uint16* X_array, const uint8*  Val_array);
uint16 Ifx_IntIpoCur_u16_u16 ( uint16 Xin, uint16 N, const uint16* X_array, const uint16* Val_array);
sint8  Ifx_IntIpoCur_u16_s8  ( uint16 Xin, uint16 N, const uint16* X_array, const sint8*  Val_array);
sint16 Ifx_IntIpoCur_u16_s16 ( uint16 Xin, uint16 N, const uint16* X_array, const sint16* Val_array);
uint8  Ifx_IntIpoCur_s8_u8   ( sint8  Xin, sint8  N, const sint8*  X_array, const uint8*  Val_array);
uint16 Ifx_IntIpoCur_s8_u16  ( sint8  Xin, sint8  N, const sint8*  X_array, const uint16* Val_array);
sint8  Ifx_IntIpoCur_s8_s8   ( sint8  Xin, sint8  N, const sint8*  X_array, const sint8*  Val_array);
sint16 Ifx_IntIpoCur_s8_s16  ( sint8  Xin, sint8  N, const sint8*  X_array, const sint16* Val_array);
uint8  Ifx_IntIpoCur_s16_u8  ( sint16 Xin, sint16 N, const sint16* X_array, const uint8*  Val_array);
uint16 Ifx_IntIpoCur_s16_u16 ( sint16 Xin, sint16 N, const sint16* X_array, const uint16* Val_array);
sint8  Ifx_IntIpoCur_s16_s8  ( sint16 Xin, sint16 N, const sint16* X_array, const sint8*  Val_array);
sint16 Ifx_IntIpoCur_s16_s16 ( sint16 Xin, sint16 N, const sint16* X_array, const sint16* Val_array);

uint8  Ifx_IntLkUpCur_u8_u8   ( uint8  Xin, uint8  N, const uint8*  X_array, const uint8*  Val_array);
uint16 Ifx_IntLkUpCur_u8_u16  ( uint8  Xin, uint8  N, const uint8*  X_array, const uint16* Val_array);
sint8  Ifx_IntLkUpCur_u8_s8   ( uint8  Xin, uint8  N, const uint8*  X_array, const sint8*  Val_array);
sint16 Ifx_IntLkUpCur_u8_s16  ( uint8  Xin, uint8  N, const uint8*  X_array, const sint16* Val_array);
uint8  Ifx_IntLkUpCur_u16_u8  ( uint16 Xin, uint16 N, const uint16* X_array, const uint8*  Val_array);
uint16 Ifx_IntLkUpCur_u16_u16 ( uint16 Xin, uint16 N, const uint16* X_array, const uint16* Val_array);
sint8  Ifx_IntLkUpCur_u16_s8  ( uint16 Xin, uint16 N, const uint16* X_array, const sint8*  Val_array);
sint16 Ifx_IntLkUpCur_u16_s16 ( uint16 Xin, uint16 N, const uint16* X_array, const sint16* Val_array);
uint8  Ifx_IntLkUpCur_s8_u8   ( sint8  Xin, sint8  N, const sint8*  X_array, const uint8*  Val_array);
uint16 Ifx_IntLkUpCur_s8_u16  ( sint8  Xin, sint8  N, const sint8*  X_array, const uint16* Val_array);
sint8  Ifx_IntLkUpCur_s8_s8   ( sint8  Xin, sint8  N, const sint8*  X_array, const sint8*  Val_array);
sint16 Ifx_IntLkUpCur_s8_s16  ( sint8  Xin, sint8  N, const sint8*  X_array, const sint16* Val_array);
uint8  Ifx_IntLkUpCur_s16_u8  ( sint16 Xin, sint16 N, const sint16* X_array, const uint8*  Val_array);
uint16 Ifx_IntLkUpCur_s16_u16 ( sint16 Xin, sint16 N, const sint16* X_array, const uint16* Val_array);
sint8  Ifx_IntLkUpCur_s16_s8  ( sint16 Xin, sint16 N, const sint16* X_array, const sint8*  Val_array);
sint16 Ifx_IntLkUpCur_s16_s16 ( sint16 Xin, sint16 N, const sint16* X_array, const sint16* Val_array);

uint8  Ifx_IntIpoFixCur_u8_u8   ( uint8  Xin, uint8  N, const uint8*  Val_array, uint8  Offset, uint8  Shift);
uint16 Ifx_IntIpoFixCur_u16_u16 ( uint16 Xin, uint16 N, const uint16* Val_array, uint16 Offset, uint16 Shift);
sint8  Ifx_IntIpoFixCur_s8_s8   ( sint8  Xin, sint8  N, const sint8*  Val_array, sint8  Offset, sint8  Shift);
sint16 Ifx_IntIpoFixCur_s16_s16 ( sint16 Xin, sint16 N, const sint16* Val_array, sint16 Offset, sint16 Shift);

uint8  Ifx_IntLkUpFixCur_u8_u8   (uint8  Xin, uint8  N, const uint8*  Val_array, uint8  Offset, uint8  Shift);
uint16 Ifx_IntLkUpFixCur_u16_u16 (uint16 Xin, uint16 N, const uint16* Val_array, uint16 Offset, uint16 Shift);
sint8  Ifx_IntLkUpFixCur_s8_s8   (sint8  Xin, sint8  N, const sint8*  Val_array, sint8  Offset, sint8  Shift);
sint16 Ifx_IntLkUpFixCur_s16_s16 (sint16 Xin, sint16 N, const sint16* Val_array, sint16 Offset, sint16 Shift);


uint8  Ifx_IntIpoFixICur_u8_u8   (uint8  Xin, uint8  N, const uint8*  Val_array, uint8  Offset, uint8  Interval);
uint16 Ifx_IntIpoFixICur_u16_u16 (uint16 Xin, uint16 N, const uint16* Val_array, uint16 Offset, uint16 Interval);
sint8  Ifx_IntIpoFixICur_s8_s8   (sint8  Xin, sint8  N, const sint8*  Val_array, sint8  Offset, sint8  Interval);
sint16 Ifx_IntIpoFixICur_s16_s16 (sint16 Xin, sint16 N, const sint16* Val_array, sint16 Offset, sint16 Interval);


uint8  Ifx_IntLkUpFixICur_u8_u8   (uint8  Xin, uint8  N, const uint8*  Val_array, uint8  Offset, uint8  Interval);
uint16 Ifx_IntLkUpFixICur_u16_u16 (uint16 Xin, uint16 N, const uint16* Val_array, uint16 Offset, uint16 Interval);
sint8  Ifx_IntLkUpFixICur_s8_s8   (sint8  Xin, sint8  N, const sint8*  Val_array, sint8  Offset, sint8  Interval);
sint16 Ifx_IntLkUpFixICur_s16_s16 (sint16 Xin, sint16 N, const sint16* Val_array, sint16 Offset, sint16 Interval);


uint8  Ifx_IntIpoMap_u16u8_u8   (uint16 Xin, uint8  Yin, uint16 Nx, uint16 Ny, const uint16* X_array, const uint8*  Y_array, const uint8*  Val_array);
uint16 Ifx_IntIpoMap_u16u8_u16  (uint16 Xin, uint8  Yin, uint16 Nx, uint16 Ny, const uint16* X_array, const uint8*  Y_array, const uint16* Val_array);
sint8  Ifx_IntIpoMap_u16u8_s8   (uint16 Xin, uint8  Yin, uint16 Nx, uint16 Ny, const uint16* X_array, const uint8*  Y_array, const sint8*  Val_array);
sint16 Ifx_IntIpoMap_u16u8_s16  (uint16 Xin, uint8  Yin, uint16 Nx, uint16 Ny, const uint16* X_array, const uint8*  Y_array, const sint16* Val_array);
uint8  Ifx_IntIpoMap_u16u16_u8  (uint16 Xin, uint16 Yin, uint16 Nx, uint16 Ny, const uint16* X_array, const uint16* Y_array, const uint8*  Val_array);
uint16 Ifx_IntIpoMap_u16u16_u16 (uint16 Xin, uint16 Yin, uint16 Nx, uint16 Ny, const uint16* X_array, const uint16* Y_array, const uint16* Val_array);
sint8  Ifx_IntIpoMap_u16u16_s8  (uint16 Xin, uint16 Yin, uint16 Nx, uint16 Ny, const uint16* X_array, const uint16* Y_array, const sint8*  Val_array);
sint16 Ifx_IntIpoMap_u16u16_s16 (uint16 Xin, uint16 Yin, uint16 Nx, uint16 Ny, const uint16* X_array, const uint16* Y_array, const sint16* Val_array);
uint8  Ifx_IntIpoMap_u16s8_u8   (uint16 Xin, sint8  Yin, uint16 Nx, uint16 Ny, const uint16* X_array, const sint8*  Y_array, const uint8*  Val_array);
uint16 Ifx_IntIpoMap_u16s8_u16  (uint16 Xin, sint8  Yin, uint16 Nx, uint16 Ny, const uint16* X_array, const sint8*  Y_array, const uint16* Val_array);
sint8  Ifx_IntIpoMap_u16s8_s8   (uint16 Xin, sint8  Yin, uint16 Nx, uint16 Ny, const uint16* X_array, const sint8*  Y_array, const sint8*  Val_array);
sint16 Ifx_IntIpoMap_u16s8_s16  (uint16 Xin, sint8  Yin, uint16 Nx, uint16 Ny, const uint16* X_array, const sint8*  Y_array, const sint16* Val_array);
uint8  Ifx_IntIpoMap_u16s16_u8  (uint16 Xin, sint16 Yin, uint16 Nx, uint16 Ny, const uint16* X_array, const sint16* Y_array, const uint8*  Val_array);
uint16 Ifx_IntIpoMap_u16s16_u16 (uint16 Xin, sint16 Yin, uint16 Nx, uint16 Ny, const uint16* X_array, const sint16* Y_array, const uint16* Val_array);
sint8  Ifx_IntIpoMap_u16s16_s8  (uint16 Xin, sint16 Yin, uint16 Nx, uint16 Ny, const uint16* X_array, const sint16* Y_array, const sint8*  Val_array);
sint16 Ifx_IntIpoMap_u16s16_s16 (uint16 Xin, sint16 Yin, uint16 Nx, uint16 Ny, const uint16* X_array, const sint16* Y_array, const sint16* Val_array);
uint8  Ifx_IntIpoMap_s16u8_u8   (sint16 Xin, uint8  Yin, sint16 Nx, sint16 Ny, const sint16* X_array, const uint8*  Y_array, const uint8*  Val_array);
uint16 Ifx_IntIpoMap_s16u8_u16  (sint16 Xin, uint8  Yin, sint16 Nx, sint16 Ny, const sint16* X_array, const uint8*  Y_array, const uint16* Val_array);
sint8  Ifx_IntIpoMap_s16u8_s8   (sint16 Xin, uint8  Yin, sint16 Nx, sint16 Ny, const sint16* X_array, const uint8*  Y_array, const sint8*  Val_array);
sint16 Ifx_IntIpoMap_s16u8_s16  (sint16 Xin, uint8  Yin, sint16 Nx, sint16 Ny, const sint16* X_array, const uint8*  Y_array, const sint16* Val_array);
uint8  Ifx_IntIpoMap_s16s8_u8   (sint16 Xin, sint8  Yin, sint16 Nx, sint16 Ny, const sint16* X_array, const sint8*  Y_array, const uint8*  Val_array);
uint16 Ifx_IntIpoMap_s16s8_u16  (sint16 Xin, sint8  Yin, sint16 Nx, sint16 Ny, const sint16* X_array, const sint8*  Y_array, const uint16* Val_array);
sint8  Ifx_IntIpoMap_s16s8_s8   (sint16 Xin, sint8  Yin, sint16 Nx, sint16 Ny, const sint16* X_array, const sint8*  Y_array, const sint8*  Val_array);
sint16 Ifx_IntIpoMap_s16s8_s16  (sint16 Xin, sint8  Yin, sint16 Nx, sint16 Ny, const sint16* X_array, const sint8*  Y_array, const sint16* Val_array);
uint8  Ifx_IntIpoMap_s16s16_u8  (sint16 Xin, sint16 Yin, sint16 Nx, sint16 Ny, const sint16* X_array, const sint16* Y_array, const uint8*  Val_array);
uint16 Ifx_IntIpoMap_s16s16_u16 (sint16 Xin, sint16 Yin, sint16 Nx, sint16 Ny, const sint16* X_array, const sint16* Y_array, const uint16* Val_array);
sint8  Ifx_IntIpoMap_s16s16_s8  (sint16 Xin, sint16 Yin, sint16 Nx, sint16 Ny, const sint16* X_array, const sint16* Y_array, const sint8*  Val_array);
sint16 Ifx_IntIpoMap_s16s16_s16 (sint16 Xin, sint16 Yin, sint16 Nx, sint16 Ny, const sint16* X_array, const sint16* Y_array, const sint16* Val_array);
uint8  Ifx_IntIpoMap_u8u8_u8    (uint8  Xin, uint8  Yin, uint8  Nx, uint8  Ny, const uint8*  X_array, const uint8*  Y_array, const uint8*  Val_array);
uint16 Ifx_IntIpoMap_u8u8_u16   (uint8  Xin, uint8  Yin, uint8  Nx, uint8  Ny, const uint8*  X_array, const uint8*  Y_array, const uint16* Val_array);
sint8  Ifx_IntIpoMap_u8u8_s8    (uint8  Xin, uint8  Yin, uint8  Nx, uint8  Ny, const uint8*  X_array, const uint8*  Y_array, const sint8*  Val_array);
sint16 Ifx_IntIpoMap_u8u8_s16   (uint8  Xin, uint8  Yin, uint8  Nx, uint8  Ny, const uint8*  X_array, const uint8*  Y_array, const sint16* Val_array);
uint8  Ifx_IntIpoMap_u8s8_u8    (uint8  Xin, sint8  Yin, uint8  Nx, uint8  Ny, const uint8*  X_array, const sint8*  Y_array, const uint8*  Val_array);
uint16 Ifx_IntIpoMap_u8s8_u16   (uint8  Xin, sint8  Yin, uint8  Nx, uint8  Ny, const uint8*  X_array, const sint8*  Y_array, const uint16* Val_array);
sint8  Ifx_IntIpoMap_u8s8_s8    (uint8  Xin, sint8  Yin, uint8  Nx, uint8  Ny, const uint8*  X_array, const sint8*  Y_array, const sint8*  Val_array);
sint16 Ifx_IntIpoMap_u8s8_s16   (uint8  Xin, sint8  Yin, uint8  Nx, uint8  Ny, const uint8*  X_array, const sint8*  Y_array, const sint16* Val_array);
uint8  Ifx_IntIpoMap_s8s8_u8    (sint8  Xin, sint8  Yin, sint8  Nx, sint8  Ny, const sint8*  X_array, const sint8*  Y_array, const uint8*  Val_array);
uint16 Ifx_IntIpoMap_s8s8_u16   (sint8  Xin, sint8  Yin, sint8  Nx, sint8  Ny, const sint8*  X_array, const sint8*  Y_array, const uint16* Val_array);
sint8  Ifx_IntIpoMap_s8s8_s8    (sint8  Xin, sint8  Yin, sint8  Nx, sint8  Ny, const sint8*  X_array, const sint8*  Y_array, const sint8*  Val_array);
sint16 Ifx_IntIpoMap_s8s8_s16   (sint8  Xin, sint8  Yin, sint8  Nx, sint8  Ny, const sint8*  X_array, const sint8*  Y_array, const sint16* Val_array);


uint8  Ifx_IntLkUpMap_u8u8_u8    (uint8  Xin, uint8  Yin, uint8  Nx, uint8  Ny, const uint8*  X_array, const uint8*  Y_array, const uint8*  Val_array);
sint8  Ifx_IntLkUpMap_s8s8_s8    (sint8  Xin, sint8  Yin, sint8  Nx, sint8  Ny, const sint8*  X_array, const sint8*  Y_array, const sint8*  Val_array);
uint16 Ifx_IntLkUpMap_u16u16_u16 (uint16 Xin, uint16 Yin, uint16 Nx, uint16 Ny, const uint16* X_array, const uint16* Y_array, const uint16* Val_array);
sint16 Ifx_IntLkUpMap_s16s16_s16 (sint16 Xin, sint16 Yin, sint16 Nx, sint16 Ny, const sint16* X_array, const sint16* Y_array, const sint16* Val_array);
#endif /* COM_AS_INFRASTRUCTURE_INCLUDE_IFX_H_ */
