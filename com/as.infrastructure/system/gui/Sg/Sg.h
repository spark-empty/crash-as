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
#ifndef COM_CLANG_INCLUDE_SG_H_
#define COM_CLANG_INCLUDE_SG_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"

/* ============================ [ MACROS    ] ====================================================== */
/* declaration of the LCD size */
#define SG_LCD_WIGTH 	__SG_WIDTH__
#define SG_LCD_HEIGHT   __SG_HEIGHT__

enum
{
	SGT_DMP,
	SGT_BMP,
	SGT_TXT,
	SGT_INVALID = 0xFF
};
enum
{	/* layer */
	SGL_0,
	SGL_1,
	SGL_2,
	SGL_3,
	SGL_4,
	SGL_5,
	SGL_6,
	SGL_7,
	SGL_8,
	SGL_9,
	SGL_10,
	SGL_11,
	SGL_12,
	SGL_13,
	SGL_14,
	SGL_15,
	SGL_INVALID = 0xFF
};
/* ============================ [ TYPES     ] ====================================================== */
typedef struct	/* base resource object */
{
	uint32  x;
	uint32  y;
	uint32  w;
	uint32  h;
	union{
		uint8*   pu8;
		uint32*  pu32;
		void* (*f)(void*);
	}u;
}SgRes;

typedef struct	/* public:SgRes*/
{
	uint32  x;
	uint32  y;
	uint32  w;
	uint32  h;
	const uint8*  p;	/* without information of color, for fonts */
}SgDMP;	/* dotmap */

typedef struct	/* public:SgRes*/
{
	/* (x,y) record the related center point of this BMP resource */
	uint32  x;
	uint32  y;
	uint32  w;
	uint32  h;
	const uint32* p;	/* with information of color, for pictures */
}SgBMP;	/* bitmap */

typedef struct	/* public:SgRes */
{
	uint32  x;
	uint32  y;
	uint32  w;
	uint32  h;
	void* (*f)(void*);
}SgSDD;	/*Sg Special Dynamic Draw */

typedef struct	/* public:SgRes */
{
	const uint16* l;	/* look up table          */
	const uint8** p;	/* resource pointer table */
	uint32  w;
	uint32  h;
	uint16  s;
}SgTXT;

typedef struct
{
	uint8           t;
	uint16  		rs;	/* resource size */
	const SgRes **  r;	/* resource */
	void*         (*rf)(void*);	/* refresh resource according to the cache */
	void          (*cf)(void*);	/* cache current status/data of the widget */
	uint16          weight;     /* weight of this widget */
	char*           name;
}SgSRC;	/* static resource configuration */
/*		  	  Width (w)
 * 		  + ---------- x
 *  H     |
 *  e     |
 *  i     |
 *  g (h) |
 *  h     |
 *  t     |
 *        y
 */
typedef struct
{
	uint32 x;
	uint32 y;
	uint32 w;
	uint32 h;
	uint32 c;	/* color 		 */
	uint16 d;	/* rotate degree:unit in 1 */
	uint8  l;	/* layer number of the widget */
	uint8  ri;  /* resource index */
	const SgSRC const* src;
}SgWidget;
#include "SgRes.h"
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
void Sg_Init(void);
void Sg_ManagerTask(void);
boolean Sg_IsDataReady ( void );
#endif /* COM_CLANG_INCLUDE_SG_H_ */
