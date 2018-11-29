/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2018  AS <parai@foxmail.com>
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

#ifndef _RINGBUFFER_H_
#define _RINGBUFFER_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include <stdint.h>
/* ============================ [ MACROS    ] ====================================================== */
#ifndef RB_SIZE_TYPE
#define RB_SIZE_TYPE uint32_t
#endif
#define RB_DECLARE(name, type, size)					\
	static type rbBuf_##name[size];						\
	static const RingBufferConstType rbC_##name = {		\
			(char*)rbBuf_##name,						\
			sizeof(rbBuf_##name),						\
			sizeof(type)								\
	};													\
	static RingBufferVariantType rbV_##name = {	\
			sizeof(rbBuf_##name)-1,						\
			sizeof(rbBuf_##name)-1						\
	};													\
	const RingBufferType rb_##name = {					\
		&rbC_##name,									\
		&rbV_##name										\
	}

#define RB_EXTERN(name) extern RingBufferType rb_##name;

#define RB_PUSH(name, data, sz) RB_Push(&rb_##name, data, sz)
#define RB_POLL(name, data, sz) RB_Poll(&rb_##name, data, sz)
#define RB_POP(name, data, sz)  RB_Pop(&rb_##name, data, sz)
#define RB_LEFT(name)           RB_Left(&rb_##name)
#define RB_SIZE(name)           RB_Size(&rb_##name)
/* ============================ [ TYPES     ] ====================================================== */
typedef RB_SIZE_TYPE rb_size_t;

typedef struct
{
	char*     buffer;
	rb_size_t max;
	uint8_t   min;
} RingBufferConstType;

typedef struct
{
	rb_size_t in;
	rb_size_t out;
} RingBufferVariantType;

typedef struct
{
	const RingBufferConstType*   C;
	RingBufferVariantType* V;
} RingBufferType;
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
void      RB_Init(const RingBufferType* rb);
rb_size_t RB_Push(const RingBufferType* rb, void* data, rb_size_t len);
rb_size_t RB_Pop (const RingBufferType* rb, void* data, rb_size_t len);
rb_size_t RB_Poll (const RingBufferType* rb, void* data, rb_size_t len);
rb_size_t RB_Left(const RingBufferType* rb);
rb_size_t RB_Size(const RingBufferType* rb);
#endif /* _RINGBUFFER_H_ */
