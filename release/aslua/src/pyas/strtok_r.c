/*
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#if !defined(__weak) && defined(__GNUC__)
#define __weak __attribute__((weak))
#else
#define __weak
#endif

char * __weak _strtok_r( char *s, const char *delim, char **lasts, int skip_leading_delim )
{
	register char *spanp;
	register int c, sc;
	char *tok;


	if (s == NULL && (s = *lasts) == NULL)
		return (NULL);

	/*
	 * Skip (span) leading delimiters (s += strspn(s, delim), sort of).
	 */
cont:
	c = *s++;
	for (spanp = (char *)delim; (sc = *spanp++) != 0;) {
		if (c == sc) {
			if (skip_leading_delim) {
				goto cont;
			}
			else {
				*lasts = s;
				s[-1] = 0;
				return (s - 1);
			}
		}
	}

	if (c == 0) {		/* no non-delimiter characters */
		*lasts = NULL;
		return (NULL);
	}
	tok = s - 1;

	/*
	 * Scan token (scan for delimiters: s += strcspn(s, delim), sort of).
	 * Note that delim must have one NUL; we stop if we see that, too.
	 */
	for (;;) {
		c = *s++;
		spanp = (char *)delim;
		do {
			if ((sc = *spanp++) == c) {
				if (c == 0)
					s = NULL;
				else
					s[-1] = 0;
				*lasts = s;
				return (tok);
			}
		} while (sc != 0);
	}
	/* NOTREACHED */
}

char * __weak strtok_r (char *s, const char *delim, char **lasts)
{
	return _strtok_r (s, delim, lasts, 1);
}

char* stpcpy(char* __to, const char* __from)
{
	char* dst = (char*) __to;
	const char* src = (const char*) __from;
	while('\0' != *dst)
	{
		*dst = * src;
		dst ++;
		src ++;
	}

	*dst = '\0';

	return dst;
}

int vasprintf(char **ret, const char *format, va_list ap)
{
	size_t size;
	int len;
	va_list aq;

	__va_copy(aq, ap);
	len = vsnprintf(NULL, 0, format, aq);
	va_end(aq);
	if (len < 0 || (*ret = malloc(size = len + 1)) == NULL)
		return -1;
	return vsnprintf(*ret, size, format, ap);
}
#ifndef MINGW_HAS_SECURE_API
char* strncpy_s(char* __to, size_t dsize, const char* __from, size_t doSz)
{
	size_t sz = 0;
	char* dst = (char*) __to;
	const char* src = (const char*) __from;
	while('\0' != *src)
	{
		*dst = * src;
		dst ++;
		src ++;
		sz ++;
		if( (sz >= doSz) || (sz >= dsize))
		{
			break;
		}
	}

	if(sz < dsize)
	{
		*dst = '\0';
	}

	return __to;
}
#endif
