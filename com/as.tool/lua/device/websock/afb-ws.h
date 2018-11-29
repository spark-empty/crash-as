/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2017 AS <parai@foxmail.com>
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
#ifndef _AWS_WS_H_
#define _AWS_WS_H_

/* ============================ [ INCLUDES  ] ====================================================== */
#include "asocket.h"
#include "websock.h"
/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
struct afb_ws;
struct sd_event;
struct iovec;

struct afb_ws_itf
{
	void (*on_close) (void *, uint16_t code, char *, size_t size); /* optional, if not set hangup is called */
	void (*on_text) (void *, char *, size_t size);
	void (*on_binary) (void *, char *, size_t size);
	void (*on_error) (void *, uint16_t code, const void *, size_t size); /* optional, if not set hangup is called */
	void (*on_hangup) (void *); /* optional, it is safe too call afb_ws_destroy within the callback */
};

/* ============================ [ DECLARES  ] ====================================================== */

/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
extern struct afb_ws *afb_ws_create(int fd, const struct afb_ws_itf *itf, void *closure);
extern void afb_ws_destroy(struct afb_ws *ws);
extern void afb_ws_hangup(struct afb_ws *ws);
extern int afb_ws_is_connected(struct afb_ws *ws);
extern int afb_ws_close(struct afb_ws *ws, uint16_t code, const char *reason);
extern int afb_ws_error(struct afb_ws *ws, uint16_t code, const char *reason);
extern int afb_ws_text(struct afb_ws *ws, const char *text, size_t length);
extern int afb_ws_texts(struct afb_ws *ws, ...);
extern int afb_ws_binary(struct afb_ws *ws, const void *data, size_t length);
extern int afb_ws_text_v(struct afb_ws *ws, const struct iovec *iovec, int count);
extern int afb_ws_binary_v(struct afb_ws *ws, const struct iovec *iovec, int count);
#endif /* _AWS_WS_H_ */
