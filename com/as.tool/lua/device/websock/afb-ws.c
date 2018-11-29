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
/* ============================ [ INCLUDES  ] ====================================================== */
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <sys/queue.h>
#include <pthread.h>
#include <unistd.h>
#include "afb-ws.h"
#ifdef __LINUX__
#include <sys/uio.h>
#endif

/* ============================ [ MACROS    ] ====================================================== */
/* ============================ [ TYPES     ] ====================================================== */
/*
 * a common scheme of buffer handling
 */
struct buf
{
	char *buffer;
	size_t size;
};

/*
 * the state
 */
enum state
{
	waiting,
	reading_text,
	reading_binary
};
/*
 * the afb_ws structure
 */
struct afb_ws
{
	int fd;			/* the socket file descriptor */
	enum state state;	/* current state */
	const struct afb_ws_itf *itf; /* the callback interface */
	void *closure;		/* closure when calling the callbacks */
	struct websock *ws;	/* the websock handler */
	struct buf buffer;	/* the last read fragment */
	STAILQ_ENTRY(afb_ws) entry;
};

struct afb_ws_list
{
	pthread_mutex_t q_lock;
	STAILQ_HEAD(,afb_ws) head;
};
/* ============================ [ DECLARES  ] ====================================================== */
/*
 * declaration of the websock interface for aws
 */
static ssize_t aws_writev(struct afb_ws *ws, const struct iovec *iov, int iovcnt);
static ssize_t aws_readv(struct afb_ws *ws, const struct iovec *iov, int iovcnt);
static void aws_on_close(struct afb_ws *ws, uint16_t code, size_t size);
static void aws_on_text(struct afb_ws *ws, int last, size_t size);
static void aws_on_binary(struct afb_ws *ws, int last, size_t size);
static void aws_on_continue(struct afb_ws *ws, int last, size_t size);
static int aws_on_readable(struct afb_ws *ws);
static void aws_on_error(struct afb_ws *ws, uint16_t code, const void *data, size_t size);
static void* daemon_main(void* param);
/* ============================ [ DATAS     ] ====================================================== */
static struct websock_itf aws_itf = {
	.writev = (void*)aws_writev,
	.readv = (void*)aws_readv,

	.on_ping = NULL,
	.on_pong = NULL,
	.on_close = (void*)aws_on_close,
	.on_text = (void*)aws_on_text,
	.on_binary = (void*)aws_on_binary,
	.on_continue = (void*)aws_on_continue,
	.on_extension = NULL,

	.on_error = (void*)aws_on_error
};

static struct afb_ws_list afbwsList = {
	.q_lock=PTHREAD_MUTEX_INITIALIZER,
	.head = STAILQ_HEAD_INITIALIZER(afbwsList.head)
};
static pthread_t daemonThread;
/* ============================ [ LOCALS    ] ====================================================== */
/*
 * callback for writing data
 */
static ssize_t aws_writev(struct afb_ws *ws, const struct iovec *iov, int iovcnt)
{
	ssize_t rc;

	rc = ask_writev(ws->fd, iov, iovcnt);

	return rc;
}

/*
 * callback for reading data
 */
static ssize_t aws_readv(struct afb_ws *ws, const struct iovec *iov, int iovcnt)
{
	ssize_t rc;

	rc = ask_readv(ws->fd, iov, iovcnt);

	return rc;
}

/*
 * Returns the current buffer of 'ws' that is reset.
 */
static inline struct buf aws_pick_buffer(struct afb_ws *ws)
{
	struct buf result = ws->buffer;
	ws->buffer.buffer = NULL;
	ws->buffer.size = 0;
	return result;
}

/*
 * Disconnect the websocket 'ws' and calls on_hangup if
 * 'call_on_hangup' is not null.
 */
static void aws_disconnect(struct afb_ws *ws, int call_on_hangup)
{
	struct websock *wsi = ws->ws;
	if (wsi != NULL) {
		ws->ws = NULL;
		websock_destroy(wsi);
		free(aws_pick_buffer(ws).buffer);
		ws->state = waiting;
		if (call_on_hangup && ws->itf->on_hangup)
			ws->itf->on_hangup(ws->closure);
	}
}


/*
 * callback on incoming data
 */
static int aws_on_readable(struct afb_ws *ws)
{
	int rc;

	assert(ws->ws != NULL);
	rc = websock_dispatch(ws->ws, 0);
	if (rc < 0 )
		afb_ws_hangup(ws);

	return rc;
}

/*
 * Reads from the websocket handled by 'ws' data of length 'size'
 * and append it to the current buffer of 'ws'.
 * Returns 0 in case of error or 1 in case of success.
 */
static int aws_read(struct afb_ws *ws, size_t size)
{
	ssize_t sz;
	char *buffer;

	if (size != 0 || ws->buffer.buffer == NULL) {
		buffer = realloc(ws->buffer.buffer, ws->buffer.size + size + 1);
		if (buffer == NULL)
			return 0;
		ws->buffer.buffer = buffer;
		while (size != 0) {
			sz = websock_read(ws->ws, &buffer[ws->buffer.size], size);
			if (sz < 0) {
					return 0;
			} else {
				ws->buffer.size += (size_t)sz;
				size -= (size_t)sz;
			}
		}
	}
	return 1;
}

/*
 * Callback when 'close' command received from 'ws' with 'code' and 'size'.
 */
static void aws_on_close(struct afb_ws *ws, uint16_t code, size_t size)
{
	struct buf b;

	ws->state = waiting;
	free(aws_pick_buffer(ws).buffer);
	if (ws->itf->on_close == NULL) {
		websock_drop(ws->ws);
		afb_ws_hangup(ws);
	} else if (!aws_read(ws, size))
		ws->itf->on_close(ws->closure, code, NULL, 0);
	else {
		b = aws_pick_buffer(ws);
		ws->itf->on_close(ws->closure, code, b.buffer, b.size);
	}
}

/*
 * Drops any incoming data and send an error of 'code'
 */
static void aws_drop_error(struct afb_ws *ws, uint16_t code)
{
	ws->state = waiting;
	free(aws_pick_buffer(ws).buffer);
	websock_drop(ws->ws);
	websock_error(ws->ws, code, NULL, 0);
}

/*
 * Reads either text or binary data of 'size' from 'ws' eventually 'last'.
 */
static void aws_continue(struct afb_ws *ws, int last, size_t size)
{
	struct buf b;
	int istxt;

	if (!aws_read(ws, size))
		aws_drop_error(ws, WEBSOCKET_CODE_ABNORMAL);
	else if (last) {
		istxt = ws->state == reading_text;
		ws->state = waiting;
		b = aws_pick_buffer(ws);
		b.buffer[b.size] = 0;
		(istxt ? ws->itf->on_text : ws->itf->on_binary)(ws->closure, b.buffer, b.size);
	}
}

/*
 * Callback when 'text' message received from 'ws' with 'size' and possibly 'last'.
 */
static void aws_on_text(struct afb_ws *ws, int last, size_t size)
{
	if (ws->state != waiting)
		aws_drop_error(ws, WEBSOCKET_CODE_PROTOCOL_ERROR);
	else if (ws->itf->on_text == NULL)
		aws_drop_error(ws, WEBSOCKET_CODE_CANT_ACCEPT);
	else {
		ws->state = reading_text;
		aws_continue(ws, last, size);
	}
}

/*
 * Callback when 'binary' message received from 'ws' with 'size' and possibly 'last'.
 */
static void aws_on_binary(struct afb_ws *ws, int last, size_t size)
{
	if (ws->state != waiting)
		aws_drop_error(ws, WEBSOCKET_CODE_PROTOCOL_ERROR);
	else if (ws->itf->on_binary == NULL)
		aws_drop_error(ws, WEBSOCKET_CODE_CANT_ACCEPT);
	else {
		ws->state = reading_binary;
		aws_continue(ws, last, size);
	}
}

/*
 * Callback when 'continue' command received from 'ws' with 'code' and 'size'.
 */
static void aws_on_continue(struct afb_ws *ws, int last, size_t size)
{
	if (ws->state == waiting)
		aws_drop_error(ws, WEBSOCKET_CODE_PROTOCOL_ERROR);
	else
		aws_continue(ws, last, size);
}

/*
 * Callback when 'close' command is sent to 'ws' with 'code' and 'size'.
 */
static void aws_on_error(struct afb_ws *ws, uint16_t code, const void *data, size_t size)
{
	if (ws->itf->on_error != NULL)
		ws->itf->on_error(ws->closure, code, data, size);
	else
		afb_ws_hangup(ws);
}
static void* daemon_main(void* param)
{
	while(!STAILQ_EMPTY(&afbwsList.head))
	{
		struct afb_ws* ws;
		(void)pthread_mutex_lock(&afbwsList.q_lock);
		STAILQ_FOREACH(ws,&afbwsList.head,entry)
		{
			int rc = aws_on_readable(ws);
			if(rc < 0)
			{
				break;/* something wrong, the ws maybe closed */
			}
		}
		(void)pthread_mutex_unlock(&afbwsList.q_lock);
	}

	return 0;
}
/* ============================ [ FUNCTIONS ] ====================================================== */
/*
 * Creates the afb_ws structure for the file descritor
 * 'fd' and the callbacks described by the interface 'itf'
 * and its 'closure'.
 * When the creation is a success, the systemd event loop 'eloop' is
 * used for handling event for 'fd'.
 *
 * Returns the handle for the afb_ws created or NULL on error.
 */
struct afb_ws *afb_ws_create(int fd, const struct afb_ws_itf *itf, void *closure)
{
	struct afb_ws *result;

	assert(fd >= 0);

	/* allocation */
	result = malloc(sizeof * result);
	if (result == NULL)
		goto error;

	/* init */
	result->fd = fd;
	result->state = waiting;
	result->itf = itf;
	result->closure = closure;
	result->buffer.buffer = NULL;
	result->buffer.size = 0;

	/* creates the websocket */
	result->ws = websock_create_v13(&aws_itf, result);
	if (result->ws == NULL)
		goto error2;
	(void)pthread_mutex_lock(&afbwsList.q_lock);
	if(STAILQ_EMPTY(&afbwsList.head))
	{
		pthread_create(&daemonThread,NULL,daemon_main,NULL);
	}

	STAILQ_INSERT_TAIL(&afbwsList.head,result,entry);
	(void)pthread_mutex_unlock(&afbwsList.q_lock);

	return result;

error2:
	free(result);
error:
	return NULL;
}

/*
 * Destroys the websocket 'ws'
 * It first hangup (but without calling on_hangup for safety reasons)
 * if needed.
 */
void afb_ws_destroy(struct afb_ws *ws)
{
	aws_disconnect(ws, 0);
	free(ws);
}

/*
 * Hangup the websocket 'ws'
 */
void afb_ws_hangup(struct afb_ws *ws)
{
	aws_disconnect(ws, 1);
}

/*
 * Is the websocket 'ws' still connected ?
 */
int afb_ws_is_connected(struct afb_ws *ws)
{
	return ws->ws != NULL;
}

/*
 * Sends a 'close' command to the endpoint of 'ws' with the 'code' and the
 * 'reason' (that can be NULL and that else should not be greater than 123
 * characters).
 * Returns 0 on success or -1 in case of error.
 */
int afb_ws_close(struct afb_ws *ws, uint16_t code, const char *reason)
{
	int lock;
	if (ws->ws == NULL) {
		/* disconnected */
		return -1;
	}

	lock = pthread_mutex_trylock(&afbwsList.q_lock);
	STAILQ_REMOVE(&afbwsList.head,ws,afb_ws,entry);
	if(0==lock)
	{
		pthread_mutex_unlock(&afbwsList.q_lock);
	}
	return websock_close(ws->ws, code, reason, reason == NULL ? 0 : strlen(reason));
}

/*
 * Sends a 'close' command to the endpoint of 'ws' with the 'code' and the
 * 'reason' (that can be NULL and that else should not be greater than 123
 * characters).
 * Raise an error after 'close' command is sent.
 * Returns 0 on success or -1 in case of error.
 */
int afb_ws_error(struct afb_ws *ws, uint16_t code, const char *reason)
{
	if (ws->ws == NULL) {
		/* disconnected */
		return -1;
	}
	return websock_error(ws->ws, code, reason, reason == NULL ? 0 : strlen(reason));
}

/*
 * Sends a 'text' of 'length' to the endpoint of 'ws'.
 * Returns 0 on success or -1 in case of error.
 */
int afb_ws_text(struct afb_ws *ws, const char *text, size_t length)
{
	if (ws->ws == NULL) {
		/* disconnected */
		return -1;
	}
	return websock_text(ws->ws, 1, text, length);
}

/*
 * Sends a variable list of texts to the endpoint of 'ws'.
 * Returns 0 on success or -1 in case of error.
 */
int afb_ws_texts(struct afb_ws *ws, ...)
{
	va_list args;
	struct iovec ios[32];
	int count;
	const char *s;

	if (ws->ws == NULL) {
		/* disconnected */
		return -1;
	}

	count = 0;
	va_start(args, ws);
	s = va_arg(args, const char *);
	while (s != NULL) {
		if (count == 32) {
			return -1;
		}
		ios[count].iov_base = (void*)s;
		ios[count].iov_len = strlen(s);
		count++;
		s = va_arg(args, const char *);
	}
	va_end(args);
	return websock_text_v(ws->ws, 1, ios, count);
}

/*
 * Sends a text data described in the 'count' 'iovec' to the endpoint of 'ws'.
 * Returns 0 on success or -1 in case of error.
 */
int afb_ws_text_v(struct afb_ws *ws, const struct iovec *iovec, int count)
{
	if (ws->ws == NULL) {
		/* disconnected */
		return -1;
	}
	return websock_text_v(ws->ws, 1, iovec, count);
}

/*
 * Sends a binary 'data' of 'length' to the endpoint of 'ws'.
 * Returns 0 on success or -1 in case of error.
 */
int afb_ws_binary(struct afb_ws *ws, const void *data, size_t length)
{
	if (ws->ws == NULL) {
		/* disconnected */
		return -1;
	}
	return websock_binary(ws->ws, 1, data, length);
}

/*
 * Sends a binary data described in the 'count' 'iovec' to the endpoint of 'ws'.
 * Returns 0 on success or -1 in case of error.
 */
int afb_ws_binary_v(struct afb_ws *ws, const struct iovec *iovec, int count)
{
	if (ws->ws == NULL) {
		/* disconnected */
		return -1;
	}
	return websock_binary_v(ws->ws, 1, iovec, count);
}

