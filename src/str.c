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

	/* find how many times the pattern occurs in the original string */
	for (; (patloc = strstr(oriptr, pat)); oriptr = patloc + patlen)
		patcnt++;

	/* allocate memory for the new string */
	retlen = orilen + patcnt * (replen - patlen);
	returned = xmalloc(xhp, sizeof(char) * (retlen + 1));

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
	}
	return str_add_nocopy(xhp, returned);
}
