/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2015  AS <parai@foxmail.com>
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
#ifndef STMO_H_
#define STMO_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"
#include "Stmo_Cfg.h"
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
extern void Stmo_Init(const Stmo_ConfigType *Config);
extern Std_ReturnType Stmo_SetPosDegree(Stmo_IdType Id,Stmo_DegreeType Degree);
extern Std_ReturnType Stmo_GetPosDegree(Stmo_IdType Id,Stmo_DegreeType* Degree);
extern void Stmo_MainFunction(void);

#endif /* STMO_H_ */
