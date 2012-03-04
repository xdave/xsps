/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <stdlib.h>
#include <string.h>

#include "xsps.h"

/* creates a new strmgr */
void
str_init(xhp_t* xhp)
{
	xhp->str = xmalloc(xhp, sizeof(str_t));
	xhp->str->size = 0;
	xhp->str->items = NULL;
}

/* works like strcpy().. kinda */
char*
str_add(xhp_t* xhp, const char* item)
{
	str_t* s = xhp->str;
	size_t itemsize = strlen(item) + 1;
	s->size++;
	s->items = xrealloc(xhp, s->items, s->size * sizeof(char*));
	s->items[s->size-1] = xmalloc(xhp, itemsize);
	strncpy(s->items[s->size-1], item, itemsize);
	s->items[s->size-1][itemsize-1] = '\0';
	return s->items[s->size-1];
}

/* removes a string -- never call this directly; use xsps_strmgr_free(). */
static void
str_del(xhp_t* xhp)
{
	str_t* s = xhp->str;
	s->size--;
	if(s->items[s->size] != NULL) {
		free(s->items[s->size]);
		s->items[s->size] = NULL;
	}
	s->items = xrealloc(xhp, s->items, sizeof(char*) * s->size);
}

/* frees up all memory allocated by str */
void
str_free(xhp_t* xhp)
{
	str_t* s = xhp->str;
	if (s != NULL) {
		while(s->size > 0) str_del(xhp);
		free(s);
		s = NULL;
	}
}

/* easier to check */
bool
xstreq(const char* s1, const char* s2)
{
	return ((strcmp(s1, s2)) == 0);
}

/* wrapper around str_add() */
char*
xstrcpy(xhp_t* xhp, const char* src)
{
	return str_add(xhp, src);
}
