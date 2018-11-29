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
#include "Ifx.h"
#include "asdebug.h"
/* ============================ [ MACROS    ] ====================================================== */

/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */

void Ifx_DPSearch_u16 (Ifx_DPResultU16_Type* dpResult,uint16 Xin,uint16 N,const uint16* X_array)
{
	uint16 index = 0;
	uint16 ratio = 0;
	asAssert(dpResult != NULL);
	asAssert(X_array != NULL);
	asAssert(N > 1);

	if( Xin < X_array[0] )
	{
		index = 0;
		ratio = 0;
	}
	else if (Xin > X_array[N-1])
	{
		index = N-1;
		ratio = 0;
	}
	else
	{
		for(index=0;index < N;index++)
		{
			if(Xin == X_array[index])
			{
				ratio = 0;
				break;
			}
			else if((Xin < X_array[index + 1]) && ((index + 1) < N) )
			{
				ratio = (Xin - X_array[index]) / (X_array [index+1] - X_array [index]);
			}
			else
			{
				asAssert(0);
			}
		}
	}

	dpResult->Index = index;
	dpResult->Ratio = ratio;
}

uint16 Ifx_IpoCur_u16 (const Ifx_DPResultU16_Type* dpResult, const uint16* Val_array)
{
	uint16 Result = 0;
	uint16 index = dpResult->Index;

	if( 0 == dpResult->Ratio)
	{
		Result = Val_array[index];
	}
	else
	{
		Result = Val_array[index] + (Val_array[index+1] - Val_array[index]) * dpResult->Ratio;
	}
	return Result;
}
