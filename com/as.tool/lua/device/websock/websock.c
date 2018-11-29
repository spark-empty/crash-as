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

#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#ifdef __WINDOWS__
#include "asocket.h"
#else
#include <sys/uio.h>
#endif

#include "websock.h"


#define BLOCK_DATA_SIZE              4096

#define FRAME_GET_FIN(BYTE)         (((BYTE) >> 7) & 0x01)
#define FRAME_GET_RSV1(BYTE)        (((BYTE) >> 6) & 0x01)
#define FRAME_GET_RSV2(BYTE)        (((BYTE) >> 5) & 0x01)
#define FRAME_GET_RSV3(BYTE)        (((BYTE) >> 4) & 0x01)
#define FRAME_GET_OPCODE(BYTE)      ( (BYTE)       & 0x0F)
#define FRAME_GET_MASK(BYTE)        (((BYTE) >> 7) & 0x01)
#define FRAME_GET_PAYLOAD_LEN(BYTE) ( (BYTE)       & 0x7F)

#define FRAME_SET_FIN(BYTE)         (((BYTE) & 0x01) << 7)
#define FRAME_SET_RSV1(BYTE)        (((BYTE) & 0x01) << 6)
#define FRAME_SET_RSV2(BYTE)        (((BYTE) & 0x01) << 5)
#define FRAME_SET_RSV3(BYTE)        (((BYTE) & 0x01) << 4)
#define FRAME_SET_OPCODE(BYTE)      ((BYTE) & 0x0F)
#define FRAME_SET_MASK(BYTE)        (((BYTE) & 0x01) << 7)
#define FRAME_SET_LENGTH(X64, IDX)  (unsigned char)((sizeof(X64)) <= (IDX) ? 0 : (((X64) >> ((IDX)*8)) & 0xFF))

#define OPCODE_CONTINUATION 0x0
#define OPCODE_TEXT         0x1
#define OPCODE_BINARY       0x2
#define OPCODE_CLOSE        0x8
#define OPCODE_PING         0x9
#define OPCODE_PONG         0xA

#define STATE_INIT    0
#define STATE_START   1
#define STATE_LENGTH  2
#define STATE_DATA    3

struct websock {
	int state;
	uint64_t maxlength;
	int lenhead, szhead;
	uint64_t length;
	uint32_t mask;
	unsigned char header[14];	/* 2 + 8 + 4 */
	const struct websock_itf *itf;
	void *closure;
};

static ssize_t ws_writev(struct websock *ws, const struct iovec *iov, int iovcnt)
{
	return ws->itf->writev(ws->closure, iov, iovcnt);
}

static ssize_t ws_readv(struct websock *ws, const struct iovec *iov, int iovcnt)
{
	return ws->itf->readv(ws->closure, iov, iovcnt);
}

#if 0
static ssize_t ws_write(struct websock *ws, const void *buffer, size_t buffer_size)
{
	struct iovec iov;
	iov.iov_base = (void *)buffer;	/* const cast */
	iov.iov_len = buffer_size;
	return ws_writev(ws, &iov, 1);
}
#endif

static ssize_t ws_read(struct websock *ws, void *buffer, size_t buffer_size)
{
	struct iovec iov;
	iov.iov_base = buffer;
	iov.iov_len = buffer_size;
	return ws_readv(ws, &iov, 1);
}

static int websock_send_internal_v(struct websock *ws, unsigned char first, const struct iovec *iovec, int count)
{
	struct iovec iov[32];
	int i, j;
	size_t pos, size, len;
	ssize_t rc;
	unsigned char header[32];

	/* checks count */
	if (count < 0 || (count + 1) > (int)(sizeof iov / sizeof * iov)) {
		errno = EINVAL;
		return -1;
	}

	/* computes the size */
	size = 0;
	i = 1;
	for (j = 0 ; j < count ; j++) {
		iov[i].iov_base = iovec[j].iov_base;
		len = iovec[j].iov_len;
		if (len != 0) {
			iov[i].iov_len = len;
			size += len;
			i++;
		}
	}

	/* makes the header */
	pos = 0;
	header[pos++] = first;
	size = (uint64_t) size;
	if (size < 126) {
		header[pos++] = FRAME_SET_MASK(0) | FRAME_SET_LENGTH(size, 0);
	} else {
		if (size < 65536) {
			header[pos++] = FRAME_SET_MASK(0) | 126;
		} else {
			header[pos++] = FRAME_SET_MASK(0) | 127;
			header[pos++] = FRAME_SET_LENGTH(size, 7);
			header[pos++] = FRAME_SET_LENGTH(size, 6);
			header[pos++] = FRAME_SET_LENGTH(size, 5);
			header[pos++] = FRAME_SET_LENGTH(size, 4);
			header[pos++] = FRAME_SET_LENGTH(size, 3);
			header[pos++] = FRAME_SET_LENGTH(size, 2);
		}
		header[pos++] = FRAME_SET_LENGTH(size, 1);
		header[pos++] = FRAME_SET_LENGTH(size, 0);
	}

	/* allocates the vec */
	iov[0].iov_base = header;
	iov[0].iov_len = pos;
	rc = ws_writev(ws, iov, i);

	return rc < 0 ? -1 : 0;
}

static int websock_send_internal(struct websock *ws, unsigned char first, const void *buffer, size_t size)
{
	struct iovec iov;

	iov.iov_base = (void *)buffer;
	iov.iov_len = size;
	return websock_send_internal_v(ws, first, &iov, 1);
}

static inline int websock_send_v(struct websock *ws, int last, int rsv1, int rsv2, int rsv3, int opcode, const struct iovec *iovec, int count)
{
	unsigned char first = (unsigned char)(FRAME_SET_FIN(last)
				| FRAME_SET_RSV1(rsv1)
				| FRAME_SET_RSV1(rsv2)
				| FRAME_SET_RSV1(rsv3)
				| FRAME_SET_OPCODE(opcode));
	return websock_send_internal_v(ws, first, iovec, count);
}

static inline int websock_send(struct websock *ws, int last, int rsv1, int rsv2, int rsv3, int opcode, const void *buffer, size_t size)
{
	unsigned char first = (unsigned char)(FRAME_SET_FIN(last)
				| FRAME_SET_RSV1(rsv1)
				| FRAME_SET_RSV1(rsv2)
				| FRAME_SET_RSV1(rsv3)
				| FRAME_SET_OPCODE(opcode));
	return websock_send_internal(ws, first, buffer, size);
}

int websock_close_empty(struct websock *ws)
{
	return websock_close(ws, WEBSOCKET_CODE_NOT_SET, NULL, 0);
}

int websock_close(struct websock *ws, uint16_t code, const void *data, size_t length)
{
	unsigned char buffer[2];
	struct iovec iov[2];

	if (code == WEBSOCKET_CODE_NOT_SET && length == 0)
		return websock_send(ws, 1, 0, 0, 0, OPCODE_CLOSE, NULL, 0);

	/* checks the length */
	if (length > 123) {
		errno = EINVAL;
		return -1;
	}

	/* prepare the buffer */
	buffer[0] = (unsigned char)((code >> 8) & 0xFF);
	buffer[1] = (unsigned char)(code & 0xFF);

	/* Send server-side closing handshake */
	iov[0].iov_base = (void *)buffer;
	iov[0].iov_len = 2;
	iov[1].iov_base = (void *)data;
	iov[1].iov_len = length;
	return websock_send_v(ws, 1, 0, 0, 0, OPCODE_CLOSE, iov, 2);
}

int websock_ping(struct websock *ws, const void *data, size_t length)
{
	/* checks the length */
	if (length > 125) {
		errno = EINVAL;
		return -1;
	}

	return websock_send(ws, 1, 0, 0, 0, OPCODE_PING, data, length);
}

int websock_pong(struct websock *ws, const void *data, size_t length)
{
	/* checks the length */
	if (length > 125) {
		errno = EINVAL;
		return -1;
	}

	return websock_send(ws, 1, 0, 0, 0, OPCODE_PONG, data, length);
}

int websock_text(struct websock *ws, int last, const void *text, size_t length)
{
	return websock_send(ws, last, 0, 0, 0, OPCODE_TEXT, text, length);
}

int websock_text_v(struct websock *ws, int last, const struct iovec *iovec, int count)
{
	return websock_send_v(ws, last, 0, 0, 0, OPCODE_TEXT, iovec, count);
}

int websock_binary(struct websock *ws, int last, const void *data, size_t length)
{
	return websock_send(ws, last, 0, 0, 0, OPCODE_BINARY, data, length);
}

int websock_binary_v(struct websock *ws, int last, const struct iovec *iovec, int count)
{
	return websock_send_v(ws, last, 0, 0, 0, OPCODE_BINARY, iovec, count);
}

int websock_continue(struct websock *ws, int last, const void *data, size_t length)
{
	return websock_send(ws, last, 0, 0, 0, OPCODE_CONTINUATION, data, length);
}

int websock_continue_v(struct websock *ws, int last, const struct iovec *iovec, int count)
{
	return websock_send_v(ws, last, 0, 0, 0, OPCODE_CONTINUATION, iovec, count);
}

int websock_error(struct websock *ws, uint16_t code, const void *data, size_t size)
{
	int rc = websock_close(ws, code, data, size);
	if (ws->itf->on_error != NULL)
		ws->itf->on_error(ws->closure, code, data, size);
	return rc;
}

static int read_header(struct websock *ws)
{
	if (ws->lenhead < ws->szhead) {
		ssize_t rbc =
		    ws_read(ws, &ws->header[ws->lenhead], (size_t)(ws->szhead - ws->lenhead));
		if (rbc < 0)
			return -1;
		ws->lenhead += (int)rbc;
	}
	return 0;
}

static int check_control_header(struct websock *ws)
{
	/* sanity checks */
	if (FRAME_GET_RSV1(ws->header[0]) != 0)
		return 0;
	if (FRAME_GET_RSV2(ws->header[0]) != 0)
		return 0;
	if (FRAME_GET_RSV3(ws->header[0]) != 0)
		return 0;
	if (FRAME_GET_PAYLOAD_LEN(ws->header[1]) > 125)
		return 0;
	if (FRAME_GET_OPCODE(ws->header[0]) == OPCODE_CLOSE)
		return FRAME_GET_PAYLOAD_LEN(ws->header[1]) != 1;
	return 1;
}

int websock_dispatch(struct websock *ws, int loop)
{
	uint16_t code;
loop:
	switch (ws->state) {
	case STATE_INIT:
		ws->lenhead = 0;
		ws->szhead = 2;
		ws->state = STATE_START;

	case STATE_START:
		/* read the header */
		if (read_header(ws))
			return -1;
		else if (ws->lenhead < ws->szhead)
			return 0;
		/* fast track */
		switch (FRAME_GET_OPCODE(ws->header[0])) {
		case OPCODE_CONTINUATION:
		case OPCODE_TEXT:
		case OPCODE_BINARY:
			break;
		case OPCODE_CLOSE:
			if (!check_control_header(ws))
				goto protocol_error;
			if (FRAME_GET_PAYLOAD_LEN(ws->header[1]))
				ws->szhead += 2;
			break;
		case OPCODE_PING:
		case OPCODE_PONG:
			if (!check_control_header(ws))
				goto protocol_error;
		default:
			break;
		}
		/* update heading size */
		switch (FRAME_GET_PAYLOAD_LEN(ws->header[1])) {
		case 127:
			ws->szhead += 6;
		case 126:
			ws->szhead += 2;
		default:
			ws->szhead += 4 * FRAME_GET_MASK(ws->header[1]);
		}
		ws->state = STATE_LENGTH;

	case STATE_LENGTH:
		/* continue to read the header */
		if (read_header(ws))
			return -1;
		else if (ws->lenhead < ws->szhead)
			return 0;

		/* compute length */
		switch (FRAME_GET_PAYLOAD_LEN(ws->header[1])) {
		case 127:
			ws->length = (((uint64_t) ws->header[2]) << 56)
			    | (((uint64_t) ws->header[3]) << 48)
			    | (((uint64_t) ws->header[4]) << 40)
			    | (((uint64_t) ws->header[5]) << 32)
			    | (((uint64_t) ws->header[6]) << 24)
			    | (((uint64_t) ws->header[7]) << 16)
			    | (((uint64_t) ws->header[8]) << 8)
			    | (uint64_t) ws->header[9];
			break;
		case 126:
			ws->length = (((uint64_t) ws->header[2]) << 8)
			    | (uint64_t) ws->header[3];
			break;
		default:
			ws->length = FRAME_GET_PAYLOAD_LEN(ws->header[1]);
			break;
		}
		if (FRAME_GET_OPCODE(ws->header[0]) == OPCODE_CLOSE && ws->length != 0)
			ws->length -= 2;
		if (ws->length > ws->maxlength)
			goto too_long_error;

		/* compute mask */
		if (FRAME_GET_MASK(ws->header[1])) {
			((unsigned char *)&ws->mask)[0] = ws->header[ws->szhead - 4];
			((unsigned char *)&ws->mask)[1] = ws->header[ws->szhead - 3];
			((unsigned char *)&ws->mask)[2] = ws->header[ws->szhead - 2];
			((unsigned char *)&ws->mask)[3] = ws->header[ws->szhead - 1];
		} else
			ws->mask = 0;

		/* all heading fields are known, process */
		ws->state = STATE_DATA;
		if (ws->itf->on_extension != NULL) {
			if (ws->itf->on_extension(ws->closure,
					FRAME_GET_FIN(ws->header[0]),
					FRAME_GET_RSV1(ws->header[0]),
					FRAME_GET_RSV2(ws->header[0]),
					FRAME_GET_RSV3(ws->header[0]),
					FRAME_GET_OPCODE(ws->header[0]),
					(size_t) ws->length)) {
				return 0;
			}
		}

		/* not an extension case */
		if (FRAME_GET_RSV1(ws->header[0]) != 0)
			goto protocol_error;
		if (FRAME_GET_RSV2(ws->header[0]) != 0)
			goto protocol_error;
		if (FRAME_GET_RSV3(ws->header[0]) != 0)
			goto protocol_error;

		/* handle */
		switch (FRAME_GET_OPCODE(ws->header[0])) {
		case OPCODE_CONTINUATION:
			ws->itf->on_continue(ws->closure,
					     FRAME_GET_FIN(ws->header[0]),
					     (size_t) ws->length);
			if (!loop)
				return 0;
			break;
		case OPCODE_TEXT:
			ws->itf->on_text(ws->closure,
					 FRAME_GET_FIN(ws->header[0]),
					 (size_t) ws->length);
			if (!loop)
				return 0;
			break;
		case OPCODE_BINARY:
			ws->itf->on_binary(ws->closure,
					   FRAME_GET_FIN(ws->header[0]),
					   (size_t) ws->length);
			if (!loop)
				return 0;
			break;
		case OPCODE_CLOSE:
			if (ws->length == 0)
				code = WEBSOCKET_CODE_NOT_SET;
			else {
				code = (uint16_t)(ws->header[ws->szhead - 2] & 0xff);
				code = (uint16_t)(code << 8);
				code = (uint16_t)(code | (uint16_t)(ws->header[ws->szhead - 1] & 0xff));
			}
			ws->itf->on_close(ws->closure, code, (size_t) ws->length);
			return 0;
		case OPCODE_PING:
			if (ws->itf->on_ping)
				ws->itf->on_ping(ws->closure, ws->length);
			else {
				websock_drop(ws);
				websock_pong(ws, NULL, 0);
			}
			ws->state = STATE_INIT;
			if (!loop)
				return 0;
			break;
		case OPCODE_PONG:
			if (ws->itf->on_pong)
				ws->itf->on_pong(ws->closure, ws->length);
			else
				websock_drop(ws);
			ws->state = STATE_INIT;
			if (!loop)
				return 0;
			break;
		default:
			goto protocol_error;
		}
		break;

	case STATE_DATA:
		if (ws->length)
			return 0;
		ws->state = STATE_INIT;
		break;
	}
	goto loop;

 too_long_error:
	websock_error(ws, WEBSOCKET_CODE_MESSAGE_TOO_LARGE, NULL, 0);
	return 0;

 protocol_error:
	websock_error(ws, WEBSOCKET_CODE_PROTOCOL_ERROR, NULL, 0);
	return 0;
}

static void unmask(struct websock * ws, void *buffer, size_t size)
{
	uint32_t mask, *b32;
	uint8_t m, *b8;

	mask = ws->mask;
	b8 = buffer;
	while (size && ((sizeof(uint32_t) - 1) & (uintptr_t) b8)) {
		m = ((uint8_t *) & mask)[0];
		((uint8_t *) & mask)[0] = ((uint8_t *) & mask)[1];
		((uint8_t *) & mask)[1] = ((uint8_t *) & mask)[2];
		((uint8_t *) & mask)[2] = ((uint8_t *) & mask)[3];
		((uint8_t *) & mask)[3] = m;
		*b8++ ^= m;
		size--;
	}
	b32 = (uint32_t *) b8;
	while (size >= sizeof(uint32_t)) {
		*b32++ ^= mask;
		size -= sizeof(uint32_t);
	}
	b8 = (uint8_t *) b32;
	while (size) {
		m = ((uint8_t *) & mask)[0];
		((uint8_t *) & mask)[0] = ((uint8_t *) & mask)[1];
		((uint8_t *) & mask)[1] = ((uint8_t *) & mask)[2];
		((uint8_t *) & mask)[2] = ((uint8_t *) & mask)[3];
		((uint8_t *) & mask)[3] = m;
		*b8++ ^= m;
		size--;
	}
	ws->mask = mask;
}

ssize_t websock_read(struct websock * ws, void *buffer, size_t size)
{
	ssize_t rc;

	if (ws->state != STATE_DATA)
		return 0;

	if (size > ws->length)
		size = (size_t) ws->length;

	rc = ws_read(ws, buffer, size);
	if (rc > 0) {
		size = (size_t) rc;
		ws->length -= size;

		if (ws->mask != 0)
			unmask(ws, buffer, size);
	}
	return rc;
}

int websock_drop(struct websock *ws)
{
	char buffer[8000];

	while (ws->length)
		if (websock_read(ws, buffer, sizeof buffer) < 0)
			return -1;
	return 0;
}

struct websock *websock_create_v13(const struct websock_itf *itf, void *closure)
{
	struct websock *result = calloc(1, sizeof *result);
	if (result) {
		result->itf = itf;
		result->closure = closure;
		result->maxlength = 65000;
	}
	return result;
}

void websock_destroy(struct websock *ws)
{
	free(ws);
}
