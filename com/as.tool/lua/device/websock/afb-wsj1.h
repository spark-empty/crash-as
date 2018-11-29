/*
 * Copyright (C) 2016, 2017 "IoT.bzh"
 * Author: José Bollo <jose.bollo@iot.bzh>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _AFB_WSJ1_H
#define _AFB_WSJ1_H

struct afb_wsj1;
struct afb_wsj1_msg;

struct json_object;
struct sd_event;

/*
 * Interface for callback functions.
 * The received closure is the closure passed when creating the afb_wsj1
 * socket using afb_wsj1_create.
 */
struct afb_wsj1_itf {
	/*
	 *  This function is called on hangup.
	 *  Receives the 'closure' and the handle 'wsj1'
	 */
	void (*on_hangup)(void *closure, struct afb_wsj1 *wsj1);

	/*
	 * This function is called on incoming call.
	 * Receives the 'closure'
	 */
	void (*on_call)(void *closure, const char *api, const char *verb, struct afb_wsj1_msg *msg);

	/*
	 * This function is called on incoming event
	 */
	void (*on_event)(void *closure, const char *event, struct afb_wsj1_msg *msg);
};

/*
 * Creates the afb_wsj1 socket connected to the file descriptor 'fd'
 * and having the callback interface defined by 'itf' for the 'closure'.
 * When the creation is a success, the systemd event loop 'eloop' is
 * used for handling event for 'fd'.
 * Returns the created wsj1 websocket or NULL in case of error.
 */
extern struct afb_wsj1 *afb_wsj1_create(int fd, struct afb_wsj1_itf *itf, void *closure);

/*
 * Increases by one the count of reference to 'wsj1'
 */
extern void afb_wsj1_addref(struct afb_wsj1 *wsj1);

/*
 * Decreases by one the count of reference to 'wsj1'
 * and if it falls to zero releases the used resources
 * and free the memory
 */
extern void afb_wsj1_unref(struct afb_wsj1 *wsj1);

/*
 * Sends a close message to the websocket of 'wsj1'.
 * The close message is sent with the 'code' and 'text'.
 * 'text' can be NULL.
 * Return 0 in case of success. Otherwise, returns -1 and set errno.
 */
extern int afb_wsj1_close(struct afb_wsj1 *wsj1, uint16_t code, const char *text);

/*
 * Sends on 'wsj1' the event of name 'event' with the
 * data 'object'. If not NULL, 'object' should be a valid
 * JSON string.
 * Return 0 in case of success. Otherwise, returns -1 and set errno.
 */
extern int afb_wsj1_send_event_s(struct afb_wsj1 *wsj1, const char *event, const char *object);

/*
 * Sends on 'wsj1' the event of name 'event' with the
 * data 'object'. 'object' can be NULL.
 * 'object' is dereferenced using 'json_object_put'. Use 'json_object_get' to keep it.
 * Return 0 in case of success. Otherwise, returns -1 and set errno.
 */
extern int afb_wsj1_send_event_j(struct afb_wsj1 *wsj1, const char *event, struct json_object *object);

/*
 * Sends on 'wsj1' a call to the method of 'api'/'verb' with arguments
 * given by 'object'. If not NULL, 'object' should be a valid JSON string.
 * On receiving the reply, the function 'on_reply' is called with 'closure'
 * as its first argument and the message of the reply.
 * Return 0 in case of success. Otherwise, returns -1 and set errno.
 */
extern int afb_wsj1_call_s(struct afb_wsj1 *wsj1, const char *api, const char *verb, const char *object, void (*on_reply)(void *closure, struct afb_wsj1_msg *msg), void *closure);

/*
 * Sends on 'wsj1' a call to the method of 'api'/'verb' with arguments
 * given by 'object'. 'object' can be NULL.
 * 'object' is dereferenced using 'json_object_put'. Use 'json_object_get' to keep it.
 * On receiving the reply, the function 'on_reply' is called with 'closure'
 * as its first argument and the message of the reply.
 * Return 0 in case of success. Otherwise, returns -1 and set errno.
 */
extern int afb_wsj1_call_j(struct afb_wsj1 *wsj1, const char *api, const char *verb, struct json_object *object, void (*on_reply)(void *closure, struct afb_wsj1_msg *msg), void *closure);

/*
 * Sends for message 'msg' the reply with the 'object' and, if not NULL, the token.
 * When 'iserror' is zero a OK reply is send, otherwise an ERROR reply is sent.
 * If not NULL, 'object' should be a valid JSON string.
 * Return 0 in case of success. Otherwise, returns -1 and set errno.
 */
extern int afb_wsj1_reply_s(struct afb_wsj1_msg *msg, const char *object, const char *token, int iserror);

/*
 * Sends for message 'msg' the reply with the 'object' and, if not NULL, the token.
 * When 'iserror' is zero a OK reply is send, otherwise an ERROR reply is sent.
 * 'object' can be NULL.
 * 'object' is dereferenced using 'json_object_put'. Use 'json_object_get' to keep it.
 * Return 0 in case of success. Otherwise, returns -1 and set errno.
 */
extern int afb_wsj1_reply_j(struct afb_wsj1_msg *msg, struct json_object *object, const char *token, int iserror);

/*
 * Sends for message 'msg' the OK reply with the 'object' and, if not NULL, the token.
 * If not NULL, 'object' should be a valid JSON string.
 * Return 0 in case of success. Otherwise, returns -1 and set errno.
 */
static inline int afb_wsj1_reply_ok_s(struct afb_wsj1_msg *msg, const char *object, const char *token)
{
	return afb_wsj1_reply_s(msg, object, token, 0);
}

/*
 * Sends for message 'msg' the OK reply with the 'object' and, if not NULL, the token.
 * 'object' can be NULL.
 * 'object' is dereferenced using 'json_object_put'. Use 'json_object_get' to keep it.
 * Return 0 in case of success. Otherwise, returns -1 and set errno.
 */
static inline int afb_wsj1_reply_ok_j(struct afb_wsj1_msg *msg, struct json_object *object, const char *token)
{
	return afb_wsj1_reply_j(msg, object, token, 0);
}

/*
 * Sends for message 'msg' the ERROR reply with the 'object' and, if not NULL, the token.
 * If not NULL, 'object' should be a valid JSON string.
 * Return 0 in case of success. Otherwise, returns -1 and set errno.
 */
static inline int afb_wsj1_reply_error_s(struct afb_wsj1_msg *msg, const char *object, const char *token)
{
	return afb_wsj1_reply_s(msg, object, token, 1);
}

/*
 * Sends for message 'msg' the ERROR reply with the 'object' and, if not NULL, the token.
 * 'object' can be NULL.
 * 'object' is dereferenced using 'json_object_put'. Use 'json_object_get' to keep it.
 * Return 0 in case of success. Otherwise, returns -1 and set errno.
 */
static inline int afb_wsj1_reply_error_j(struct afb_wsj1_msg *msg, struct json_object *object, const char *token)
{
	return afb_wsj1_reply_j(msg, object, token, 1);
}

/*
 * Increases by one the count of reference to 'msg'.
 * Should be called if callbacks stores the message.
 */
extern void afb_wsj1_msg_addref(struct afb_wsj1_msg *msg);

/*
 * Decreases by one the count of reference to 'msg'.
 * and if it falls to zero releases the used resources
 * and free the memory.
 * Should be called if 'afb_wsj1_msg_addref' was called.
 */
extern void afb_wsj1_msg_unref(struct afb_wsj1_msg *msg);

/*
 * Returns 1 if 'msg' is for a CALL
 * Otherwise returns 0.
 */
extern int afb_wsj1_msg_is_call(struct afb_wsj1_msg *msg);

/*
 * Returns 1 if 'msg' is for a REPLY of any kind
 * Otherwise returns 0.
 */
extern int afb_wsj1_msg_is_reply(struct afb_wsj1_msg *msg);

/*
 * Returns 1 if 'msg' is for a REPLY OK
 * Otherwise returns 0.
 */
extern int afb_wsj1_msg_is_reply_ok(struct afb_wsj1_msg *msg);

/*
 * Returns 1 if 'msg' is for a REPLY ERROR
 * Otherwise returns 0.
 */
extern int afb_wsj1_msg_is_reply_error(struct afb_wsj1_msg *msg);

/*
 * Returns 1 if 'msg' is for an EVENT
 * Otherwise returns 0.
 */
extern int afb_wsj1_msg_is_event(struct afb_wsj1_msg *msg);

/*
 * Returns the api of the call for 'msg'
 * Returns NULL if 'msg' is not for a CALL
 */
extern const char *afb_wsj1_msg_api(struct afb_wsj1_msg *msg);

/*
 * Returns the verb call for 'msg'
 * Returns NULL if 'msg' is not for a CALL
 */
extern const char *afb_wsj1_msg_verb(struct afb_wsj1_msg *msg);

/*
 * Returns the event name for 'msg'
 * Returns NULL if 'msg' is not for an EVENT
 */
extern const char *afb_wsj1_msg_event(struct afb_wsj1_msg *msg);

/*
 * Returns the token sent with 'msg' or NULL when no token was sent.
 */
extern const char *afb_wsj1_msg_token(struct afb_wsj1_msg *msg);

/*
 * Returns the wsj1 of 'msg'
 */
extern struct afb_wsj1 *afb_wsj1_msg_wsj1(struct afb_wsj1_msg *msg);

/*
 * Returns the string representation of the object received with 'msg'
 */
extern const char *afb_wsj1_msg_object_s(struct afb_wsj1_msg *msg);

/*
 * Returns the object received with 'msg'
 */
extern struct json_object *afb_wsj1_msg_object_j(struct afb_wsj1_msg *msg);

#endif /* _AFB_WSJ1_H */

