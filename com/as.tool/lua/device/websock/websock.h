/*
 * Copyright (C) 2016, 2017 "IoT.bzh"
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * This work is a far adaptation of apache-websocket:
 *   origin:  https://github.com/disconnect/apache-websocket
 *   commit:  cfaef071223f11ba016bff7e1e4b7c9e5df45b50
 *   Copyright 2010-2012 self.disconnect (APACHE-2)
 */

/* Parai:
 * copy from https://gerrit.automotivelinux.org/gerrit/p/src/app-framework-binder.git
 * make it both runnable on win or linux
 */

#ifndef _WEBSOCK_H
#define _WEBSOCK_H

#include <stdint.h>

struct iovec;

#define WEBSOCKET_CODE_OK                1000
#define WEBSOCKET_CODE_GOING_AWAY        1001
#define WEBSOCKET_CODE_PROTOCOL_ERROR    1002
#define WEBSOCKET_CODE_CANT_ACCEPT       1003
#define WEBSOCKET_CODE_RESERVED          1004
#define WEBSOCKET_CODE_NOT_SET           1005
#define WEBSOCKET_CODE_ABNORMAL          1006
#define WEBSOCKET_CODE_INVALID_UTF8      1007
#define WEBSOCKET_CODE_POLICY_VIOLATION  1008
#define WEBSOCKET_CODE_MESSAGE_TOO_LARGE 1009
#define WEBSOCKET_CODE_INTERNAL_ERROR    1011

struct websock_itf {
	ssize_t (*writev) (void *, const struct iovec *, int);
	ssize_t (*readv) (void *, const struct iovec *, int);

	void (*on_ping) (void *, size_t size); /* optional, if not NULL, responsible of pong */
	void (*on_pong) (void *, size_t size); /* optional */
	void (*on_close) (void *, uint16_t code, size_t size);
	void (*on_text) (void *, int last, size_t size);
	void (*on_binary) (void *, int last, size_t size);
	void (*on_continue) (void *, int last, size_t size);
	int (*on_extension) (void *, int last, int rsv1, int rsv2, int rsv3, int opcode, size_t size);

	void (*on_error) (void *, uint16_t code, const void *data, size_t size); /* optional */
};

struct websock;

extern int websock_close_empty(struct websock *ws);
extern int websock_close(struct websock *ws, uint16_t code, const void *data, size_t length);
extern int websock_error(struct websock *ws, uint16_t code, const void *data, size_t length);

extern int websock_ping(struct websock *ws, const void *data, size_t length);
extern int websock_pong(struct websock *ws, const void *data, size_t length);
extern int websock_text(struct websock *ws, int last, const void *text, size_t length);
extern int websock_text_v(struct websock *ws, int last, const struct iovec *iovec, int count);
extern int websock_binary(struct websock *ws, int last, const void *data, size_t length);
extern int websock_binary_v(struct websock *ws, int last, const struct iovec *iovec, int count);
extern int websock_continue(struct websock *ws, int last, const void *data, size_t length);
extern int websock_continue_v(struct websock *ws, int last, const struct iovec *iovec, int count);

extern ssize_t websock_read(struct websock *ws, void *buffer, size_t size);
extern int websock_drop(struct websock *ws);

extern int websock_dispatch(struct websock *ws, int loop);

extern struct websock *websock_create_v13(const struct websock_itf *itf, void *closure);
extern void websock_destroy(struct websock *ws);
#endif /* _WEBSOCK_H */
