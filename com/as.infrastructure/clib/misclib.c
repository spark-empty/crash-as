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
/* ============================ [ INCLUDES  ] ====================================================== */
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
/* ============================ [ MACROS    ] ====================================================== */
#if !defined(__weak) && defined(__GNUC__)
#define __weak __attribute__((weak))
#else
#define __weak
#endif

/*****************************************************************************/
/* Config */
/*****************************************************************************/
#define PINKIE_CFG_SSCANF_MAX_INT 8


/*****************************************************************************/
/* Defines */
/*****************************************************************************/
#if PINKIE_CFG_SSCANF_MAX_INT == 1
#  define PINKIE_SSCAN_CHAR_CNT 4
#  define PINKIE_SSCANF_INT_T int8_t
#  define PINKIE_SSCANF_UINT_T uint8_t
#endif

#if PINKIE_CFG_SSCANF_MAX_INT == 2
#  define PINKIE_SSCAN_CHAR_CNT 6
#  define PINKIE_SSCANF_INT_T int16_t
#  define PINKIE_SSCANF_UINT_T uint16_t
#endif

#if PINKIE_CFG_SSCANF_MAX_INT == 4
#  define PINKIE_SSCAN_CHAR_CNT 11
#  define PINKIE_SSCANF_INT_T int32_t
#  define PINKIE_SSCANF_UINT_T uint32_t
#endif

#if PINKIE_CFG_SSCANF_MAX_INT == 8
#  define PINKIE_SSCAN_CHAR_CNT 20
#  define PINKIE_SSCANF_INT_T int64_t
#  define PINKIE_SSCANF_UINT_T uint64_t
#endif

/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
static int _eval(const char **expr)
{
	int number=0;
	int result=0;
	char operator = '+';

	while(**expr != '\0')
	{
		if(**expr == '(')
		{
			(*expr)++;
			number = _eval(expr);
		}
		else
		{
			while((**expr != ')') && (**expr != '+') && (**expr != '-') && (**expr !=  '*') && (**expr != '/') && (**expr != '\0'))
			{
				number = number*10 + (**expr) - '0';
				(*expr)++;
			}
		}

		switch(operator)
		{
			case '+':
				result=result+number;
				break;
			case '-':
				result=result-number;
				break;
			case '*':
				result=result*number;
				break;
			case '/':
				result=result/number;
				break;
		}

		if(**expr == ')')
		{
			(*expr) ++;
			break;
		}

		if(**expr != '\0')
		{
			operator=**expr;
			(*expr) ++;
		}

		number = 0;
	}

	return result;
}
static uint32_t IntH(char chr)
{
	uint32_t v;
	if( (chr>='0') && (chr<='9'))
	{
		v= chr - '0';
	}
	else if( (chr>='A') && (chr<='F'))
	{
		v= chr - 'A' + 10;
	}
	else if( (chr>='a') && (chr<='f'))
	{
		v= chr - 'a' + 10;
	}
	else
	{
		v = (uint32_t)-1; /* -1 to indicate error */
	}

	return v;
}


/*****************************************************************************/

/*****************************************************************************/
/** Convert character to integer
 *
 * @returns number or -1 if not a number
 */
static int pinkie_c2i(
    const char chr,                             /**< character */
    unsigned int base                           /**< base */
)
{
    if (('0' <= chr) && ('9' >= chr)) {
        return (chr - '0');
    }

    if (16 == base) {
        if (('a' <= chr) && ('f' >= chr)) {
            return (chr - 'a' + 10);
        }

        if (('A' <= chr) && ('F' >= chr)) {
            return (chr - 'A' + 10);
        }
    }

    return -1;
}
/** String To Integer
 */
static const char * pinkie_s2i(
    const char *str,                            /**< string */
    unsigned int width,                         /**< width = sizeof(type) */
    PINKIE_SSCANF_UINT_T num_max,               /**< max num value */
    void *val,                                  /**< value */
    unsigned int flg_neg,                       /**< negative flag */
    unsigned int base                           /**< base */
)
{
    PINKIE_SSCANF_UINT_T num = 0;               /* number */
    PINKIE_SSCANF_UINT_T mul = 1;               /* multiplicator */
    PINKIE_SSCANF_UINT_T cur;                   /* current number */
    unsigned int cnt = 0;                       /* counter */
    const char *str_end = NULL;                 /* number end */

    /* detect number type */
    if (0 == base) {
        if (((str[0]) && ('0' == str[0])) && ((str[1]) && ('x' == str[1]))) {
            base = 16;
            str += 2;
        } else {
            base = 10;
        }
    }

    /* count numbers */
    for (; (*str) && (-1 != pinkie_c2i(*str, base)); str++) {
        cnt++;
    }

    /* store number end */
    str_end = str;

    /* check if anything was detected */
    if (!cnt) {
        goto bail;
    }

    /* convert integers */
    while (cnt--) {
        str--;

        /* apply multiplicator to conv result */
        cur = (PINKIE_SSCANF_UINT_T) pinkie_c2i(*str, base) * mul;

        if ((num_max - cur) < num) {
            str_end = 0;
            goto bail;
        }

        num += cur;
        mul *= base;
    }

bail:
    /* convert result to given width */
    if (sizeof(uint8_t) == width) {
        *((uint8_t *) val) = (flg_neg) ? (uint8_t) -num : (uint8_t) num;
    }
#if PINKIE_CFG_SSCANF_MAX_INT >= 2
    else if (sizeof(uint16_t) == width) {
        *((uint16_t *) val) = (flg_neg) ? (uint16_t) -num : (uint16_t) num;
    }
#endif
#if PINKIE_CFG_SSCANF_MAX_INT >= 4
    else if (sizeof(uint32_t) == width) {
        *((uint32_t *) val) = (flg_neg) ? (uint32_t) -num : (uint32_t) num;
    }
#endif
#if PINKIE_CFG_SSCANF_MAX_INT >= 8
    else if (sizeof(uint64_t) == width) {
        *((uint64_t *) val) = (flg_neg) ? (uint64_t) -num : (uint64_t) num;
    }
#endif

    return str_end;
}
/* ============================ [ FUNCTIONS ] ====================================================== */
int eval(const char *expr)
{
	return _eval(&expr);
}
void * __weak memset (void *__s, int __c, size_t __n)
{
	size_t i;
	char* ptr = (char*) __s;

	for(i=0;i<__n;i++)
	{
		ptr[i] = (char)(__c&0xFFu);
	}

	return __s;
}

void *__weak memcpy (void* __to, const void* __from, size_t __size)
{
	size_t i;
	char* dst = (char*) __to;
	const char* src = (const char*) __from;

	for(i=0;i<__size;i++)
	{
		dst[i] = src[i];
	}

	return __to;
}

void* __weak memmove (void *dest, const void *src, size_t len)
{
	char *d = dest;
	const char *s = src;

	if (d < s)
	{
		while (len--)
		{
			*d++ = *s++;
		}
	}
	else
	{
		const char *lasts = s + (len-1);
		char *lastd = d + (len-1);
		while (len--)
		*lastd-- = *lasts--;
	}

	return dest;
}

char* __weak strcpy (char* __to, const char* __from)
{
	char* dst = (char*) __to;
	const char* src = (const char*) __from;
	while('\0' != *src)
	{
		*dst = * src;
		dst ++;
		src ++;
	}

	*dst = '\0';
	return __to;
}

char* __weak strcat (char* __to, const char* __from)
{
	char* dst = (char*) __to;
	const char* src = (const char*) __from;

	while('\0' != *dst) dst ++;;

	while('\0' != *src)
	{
		*dst = * src;
		dst ++;
		src ++;
	}

	*dst = '\0';
	return __to;
}

int __weak strcmp(const char *s1, const char *s2)
{
	for ( ; *s1 == *s2; s1++, s2++)
	if (*s1 == '\0')
	{
		return 0;
	}
	return ((*(unsigned char *)s1 < *(unsigned char *)s2) ? -1 : +1);
}

int __weak strncmp(const char *s1, const char *s2, size_t n)
{
	for ( ; (*s1 == *s2) && (n > 0); s1++, s2++, n--)
	if (*s1 == '\0')
	{
		return 0;
	}

	if(n ==0)
	{
		return 0;
	}
	return ((*(unsigned char *)s1 < *(unsigned char *)s2) ? -1 : +1);
}

int __weak memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char u1, u2;
	const char* p1 = (const char*)s1;
	const char* p2 = (const char*)s2;

	for ( ; n-- ; p1++, p2++) {
		u1 = * p1;
		u2 = * p2;
		if ( u1 != u2) {
			return (u1-u2);
		}
	}
	return 0;
}

/* ========================== [ cpoy from glib/gstrfuncs.c ] ===================== */
/**
 * strlcpy:
 * @dest: destination buffer
 * @src: source buffer
 * @dest_size: length of @dest in bytes
 *
 * Portability wrapper that calls strlcpy() on systems which have it,
 * and emulates strlcpy() otherwise. Copies @src to @dest; @dest is
 * guaranteed to be nul-terminated; @src must be nul-terminated;
 * @dest_size is the buffer size, not the number of bytes to copy.
 *
 * At most @dest_size - 1 characters will be copied. Always nul-terminates
 * (unless @dest_size is 0). This function does not allocate memory. Unlike
 * strncpy(), this function doesn't pad @dest (so it's often faster). It
 * returns the size of the attempted result, strlen (src), so if
 * @retval >= @dest_size, truncation occurred.
 *
 * Caveat: strlcpy() is supposedly more secure than strcpy() or strncpy(),
 * but if you really want to avoid screwups, g_strdup() is an even better
 * idea.
 *
 * Returns: length of @src
 */
size_t __weak strlcpy (char       *dest,
           const char *src,
           size_t        dest_size)
{
	char *d = dest;
	const char *s = src;
	size_t n = dest_size;

	/* Copy as many bytes as will fit */
	if (n != 0 && --n != 0) 
	{
		do {
			char c = *s++;

			*d++ = c;
			if (c == 0)
				break;
		} while (--n != 0);
	}

	/* If not enough room in dest, add NUL and traverse rest of src */
	if (n == 0)
    {
		if (dest_size != 0)
		{
			*d = 0;
		}
		while (*s++)
			;
    }

	return s - src - 1;  /* count does not include NUL */
}

char * __weak strncpy (char * __dest,
		      const char * __src, size_t __n)
{
	strlcpy(__dest, __src, __n+1);

	return __dest;
}

/**
 * strlcat:
 * @dest: destination buffer, already containing one nul-terminated string
 * @src: source buffer
 * @dest_size: length of @dest buffer in bytes (not length of existing string
 *     inside @dest)
 *
 * Portability wrapper that calls strlcat() on systems which have it,
 * and emulates it otherwise. Appends nul-terminated @src string to @dest,
 * guaranteeing nul-termination for @dest. The total size of @dest won't
 * exceed @dest_size.
 *
 * At most @dest_size - 1 characters will be copied. Unlike strncat(),
 * @dest_size is the full size of dest, not the space left over. This
 * function does not allocate memory. It always nul-terminates (unless
 * @dest_size == 0 or there were no nul characters in the @dest_size
 * characters of dest to start with).
 *
 * Caveat: this is supposedly a more secure alternative to strcat() or
 * strncat(), but for real security g_strconcat() is harder to mess up.
 *
 * Returns: size of attempted result, which is MIN (dest_size, strlen
 *     (original dest)) + strlen (src), so if retval >= dest_size,
 *     truncation occurred.
 */
size_t __weak strlcat (char       *dest,
           const char *src,
           size_t        dest_size)
{
	char *d = dest;
	const char *s = src;
	size_t bytes_left = dest_size;
	size_t dlength;  /* Logically, MIN (strlen (d), dest_size) */

	/* Find the end of dst and adjust bytes left but don't go past end */
	while (*d != 0 && bytes_left-- != 0) 
	{
		d++;
	}
	dlength = d - dest;
	bytes_left = dest_size - dlength;

	if (bytes_left == 0)
	{
		return dlength + strlen (s);
	}
	while (*s != 0)
    {
		if (bytes_left != 1)
        {
			*d++ = *s;
			bytes_left--;
        }
		s++;
    }
	*d = 0;

	return dlength + (s - src);  /* count does not include NUL */
}

unsigned long int __weak strtoul(const char* string, char ** tailptr, int base)
{
	unsigned long int result;
	uint32_t v;

	result = 0;

	const char *s = string;

	while (*s != 0)
	{
		v = IntH(*s);
		if((uint32_t)-1 == v)
		{
			break;
		}
		result = result*base + v;
		s++;
	}

	if(tailptr != NULL)
	{
		*tailptr = (char*)s;
	}

	return result;
}

size_t __weak strnlen(const char* s, size_t maxlen)
{
	const char *sc;

	for (sc = s; *sc != '\0'; ++sc)
	{
		if((sc-s) >= maxlen)
		{
			break;
		}
	}

	return sc - s;
}

char* __weak strrchr (const char * s, int c)
{
	while(*s != '\0')
	{
		s++;
		if(*s == c)
		{
			return (char*)s;
		}
	}

	return NULL;
}

char* __weak strstr(const char *s1, const char *s2)
{
	int l1, l2;

	l2 = strlen(s2);
	if (!l2)
		return (char *)s1;
	l1 = strlen(s1);
	while (l1 >= l2)
	{
		l1 --;
		if (!memcmp(s1, s2, l2))
			return (char *)s1;
		s1 ++;
	}

	return NULL;
}

int __weak atoi (const char *s)
{
	return strtoul(s, NULL, 10);
}



/*****************************************************************************/
/** Pinkie Just Enough Sscanf To Work
 *
 * Supports the following formatters:
 *   - %i and %u, both with ll and hh modifiers
 *   - %n
 *   https://github.com/sven/pinkie_sscanf
 */
int __weak sscanf(
    const char *str,                            /**< input string */
    const char *fmt,                            /**< format string */
    ...                                         /**< variable arguments */
)
{
    va_list ap;                                 /* variable argument list */
    unsigned int flg_format = 0;                /* format flag */
    unsigned int int_width = 0;                 /* integer width */
    const char *str_beg = str;                  /* string begin */
    int args = 0;                               /* parsed arguments counter */
    unsigned int flg_neg = 0;                   /* negative flag */

    va_start(ap, fmt);
    for (; (*fmt) && (*str); fmt++) {

        if (flg_format) {

            /* length field */
            if ('h' == *fmt) {
                int_width = (!int_width) ? sizeof(short) : sizeof(char);
                continue;
            }

            if ('l' == *fmt) {
                int_width = (!int_width) ? sizeof(long) : sizeof(long long);
                continue;
            }

            /* handle conversion */
            switch (*fmt) {

                case 'i':

                    /* detect negative sign */
                    if ('-' == *str) {
                        flg_neg = 1;
                        fmt--;
                        str++;
                        continue;
                    }

                    /* fallthrough to convert number */

                case 'x':
                case 'u':
                    /* unsigned integer */
                    if (!int_width) {
                        str = pinkie_s2i(str, sizeof(unsigned int), UINT_MAX, va_arg(ap, unsigned int *), flg_neg, ('x' == *fmt) ? 16 : 0);
                    }
                    else if (sizeof(uint8_t) == int_width) {
                        str = pinkie_s2i(str, sizeof(uint8_t), UINT8_MAX, va_arg(ap, uint8_t *), flg_neg, ('x' == *fmt) ? 16 : 0);
                    }
#if (PINKIE_CFG_SSCANF_MAX_INT >= 2) && (UINT16_MAX != UINT_MAX)
                    else if (sizeof(uint16_t) == int_width) {
                        str = pinkie_s2i(str, sizeof(uint16_t), UINT16_MAX, va_arg(ap, uint16_t *), flg_neg, ('x' == *fmt) ? 16 : 0);
                    }
#endif
#if (PINKIE_CFG_SSCANF_MAX_INT >= 4) && (UINT32_MAX != UINT_MAX)
                    else if (sizeof(uint32_t) == int_width) {
                        str = pinkie_s2i(str, sizeof(uint32_t), UINT32_MAX, va_arg(ap, uint32_t *), flg_neg, ('x' == *fmt) ? 16 : 0);
                    }
#endif
#if (PINKIE_CFG_SSCANF_MAX_INT >= 8) && (UINT64_MAX != UINT_MAX)
                    else if (sizeof(uint64_t) == int_width) {
                        str = pinkie_s2i(str, sizeof(uint64_t), UINT64_MAX, va_arg(ap, uint64_t *), flg_neg, ('x' == *fmt) ? 16 : 0);
                    }
#endif

                    /* reset integer width */
                    int_width = 0;

                    /* update args */
                    args++;

                    break;

                case '%':
                    /* percent char */
                    flg_format = 0;
                    goto pinkie_sscanf_match;

                case 'n':
                    /* position */
                    *(va_arg(ap, int *)) = (int) (str - str_beg);
                    break;
            }

            flg_format = 0;
            flg_neg = 0;
            continue;
        }

        if ('%' == *fmt) {
            flg_format = 1;
            continue;
        }

pinkie_sscanf_match:
        /* string content must match format */
        if (*fmt != *str++) {
            break;
        }
    }
    va_end(ap);

    return args;
}
#ifdef __WINDOWS__
int  ffs(int v)
{
	int i;
	int r = 0;
	for(i=0;i<32;i++)
	{
		if(v&(1<<i))
		{
			r = i+1;
			break;
		}
	}

	return r;
}
#endif
