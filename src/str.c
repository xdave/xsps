/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * All rights reserved.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <stdlib.h>
#include <string.h>

#include "xsps.h"

/* creates a new strmgr */
void
str_init(xhp_t *xhp)
{
	xhp->str = xmalloc(xhp, sizeof(str_t));
	xhp->str->size = 0;
	xhp->str->items = NULL;
}

/* works like strcpy().. kinda */
char *
str_add(xhp_t *xhp, const char *item)
{
	str_t *s = xhp->str;
	size_t itemsize = strlen(item) + 1;
	s->size++;
	s->items = xrealloc(xhp, s->items, s->size * sizeof(char *));
	s->items[s->size-1] = xmalloc(xhp, itemsize);
	strncpy(s->items[s->size-1], item, itemsize);
	s->items[s->size-1][itemsize-1] = '\0';
	return s->items[s->size-1];
}

/* like str_add(), but takes an already alloc'd pointer.
 * item needs to be already NUL terminated. */
char *
str_add_nocopy(xhp_t *xhp, char *item)
{
	str_t *s = xhp->str;
	s->size++;
	s->items = xrealloc(xhp, s->items, s->size * sizeof(char *));
	s->items[s->size-1] = item;
	return s->items[s->size-1];
}

/* removes a string -- never call this directly; use xsps_strmgr_free(). */
static void
str_del(xhp_t *xhp)
{
	str_t *s = xhp->str;
	s->size--;
	if(s->items[s->size] != NULL) {
		free(s->items[s->size]);
		s->items[s->size] = NULL;
	}
	s->items = xrealloc(xhp, s->items, sizeof(char*) * s->size);
}

/* frees up all memory allocated by str */
void
str_free(xhp_t *xhp)
{
	str_t *s = xhp->str;
	if (s != NULL) {
		while(s->size > 0) str_del(xhp);
		free(s);
		s = NULL;
	}
}

/* easier to check */
bool
xstreq(const char *s1, const char *s2)
{
	return ((strcmp(s1, s2)) == 0);
}

/* wrapper around str_add() */
char *
xstrcpy(xhp_t *xhp, const char *src)
{
	return str_add(xhp, src);
}

/* format version of xstrcpy() */
char *
xstrfcpy(xhp_t *xhp, const char *fmt, ...)
{
	int	n;
	size_t	size = 100;
	char	*p, *np;
	va_list ap;

	p = xmalloc(xhp, size);

	while(1) {
		va_start(ap, fmt);
		n = vsnprintf(p, size, fmt, ap);
		va_end(ap);
		if(n > -1 && (size_t)n < size) break;
		if(n > -1) size = (size_t)n+1;
		np = xrealloc(xhp, p, size);
		p = np;
	}

	return str_add_nocopy(xhp, p);
}

/* Replaces all occurrences of pat with repl in orig. */
char *
str_replace(xhp_t *xhp, const char *orig, const char *pat, const char *repl)
{
	size_t orilen = strlen(orig);
	size_t patlen = strlen(pat);
	size_t replen = strlen(repl);
	size_t patcnt = 0;
	size_t skplen;
	size_t retlen;

	const char *oriptr = orig;
	const char *patloc;
	char *returned;
	char *retptr;

	/* Copy input to output if this is a useless call */
	if (xstreq(pat, repl))
	    return xstrcpy(xhp, orig);

	/* find how many times the pattern occurs in the original string */
	for (; (patloc = strstr(oriptr, pat)); oriptr = patloc + patlen)
		patcnt++;

	/* allocate memory for the new string */
	retlen = orilen + patcnt * (replen - patlen);
	returned = xmalloc(xhp, retlen + 1);

	if (returned != NULL) {
		/* copy the original string,
		 * replacing all the instances of the pattern */
		retptr = returned;
		oriptr = orig;
		for (; (patloc = strstr(oriptr, pat))
		     ; oriptr = patloc + patlen) {
			skplen = (size_t)(patloc - oriptr);
			/* copy the section until the occurence of pattern*/
			strncpy(retptr, oriptr, skplen);
			retptr += skplen;
			/* copy the replacement */
			strncpy(retptr, repl, replen);
			retptr += replen;
		}
		/* copy the rest of the string. */
		strcpy(retptr, oriptr);
		returned[retlen] = '\0';
	}
	return str_add_nocopy(xhp, returned);
}

/* Works like getenv(), but on vars with ${braces} around them. */
const char *
getbenv(xhp_t *xhp, const char *input)
{
	size_t size;
	const char *result;
	char *tmp;
	size = strlen(input);
	tmp = xmalloc(xhp, size - 2);
	tmp = strncpy(tmp, input + 2, size - 3);
	tmp[size - 3] = '\0';
	result = getenv(tmp);
	if (result == NULL) result = input;
	free(tmp);
	return result;
}

/* Extracts all ${FOO} vars from 'src' and stores them in 'dst' */
void
bvars(xhp_t *xhp, str_t *dst, const char *src)
{
	size_t i, len = 0;
	const char *start = NULL, *end = NULL;

	while (((start = strchr(src, '$')) != NULL) &&
	       ((end   = strchr(src, '}')) != NULL)) {
		len = (strlen(start) - strlen(end + 1));
		if (len > 0 && start[1] == '{') {
			i = dst->size;
			dst->items = xrealloc(xhp, dst->items,
			    sizeof(char*)*(i+1));
			dst->items[i] = xmalloc(xhp, len + 1);
			dst->items[i] = strncpy(dst->items[i], start, len);
			dst->items[i][len] = '\0';
			dst->size++;
		}
		src = (end + 1);
	}
}

/* Returns new string with all ${FOO} vars replaced from getbenv() */
char *
breplace(xhp_t *xhp, const char *input)
{
	size_t i, input_len, tmp_len;
	const char *env;
	char *item, *tmp = NULL, *replacement = NULL;

	/* Copy input to output if this is a useless call */
	if ((strstr(input, "${") == NULL))
	    return xstrcpy(xhp, input);

	str_t to_replace;
	to_replace.size = 0;
	to_replace.items = xmalloc(xhp, sizeof(char *) * to_replace.size);

	bvars(xhp, &to_replace, input);
	input_len = strlen(input);
	replacement = xmalloc(xhp, input_len + 1);
	replacement = strncpy(replacement, input, input_len);
	replacement[input_len] = '\0';

	if (to_replace.size > 0) {
		for (i = 0; i < to_replace.size; i++) {
			item = to_replace.items[i];
			env = getbenv(xhp, item);
			tmp = str_replace(xhp, replacement, item, env);
			tmp_len = strlen(tmp);
			free(replacement);
			replacement = xmalloc(xhp, tmp_len + 1);
			replacement = strncpy(replacement, tmp, tmp_len);
			replacement[tmp_len] = '\0';
			/* NOTE: 'tmp' is free()'d by the strmgr. */
			free(item);
		}
	}
	free(to_replace.items);
	return str_add_nocopy(xhp, replacement);
}
