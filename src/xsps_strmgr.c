/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <stdlib.h>
#include <string.h>

#include "xsps.h"

/* creates a new strmgr */
void
xsps_strmgr_init(xsps_handle_t* xhp)
{
	xhp->strmgr = xmalloc(xhp, sizeof(xsps_strmgr_t));
	xhp->strmgr->size = 0;
	xhp->strmgr->items = NULL;
}

/* works like strcpy().. kinda */
char*
xsps_strmgr_add(xsps_handle_t* xhp, const char* item)
{
	xsps_strmgr_t* s = xhp->strmgr;
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
xsps_strmgr_del(xsps_handle_t* xhp)
{
	xsps_strmgr_t* s = xhp->strmgr;
	s->size--;
	if(s->items[s->size] != NULL) {
		free(s->items[s->size]);
		s->items[s->size] = NULL;
	}
	s->items = xrealloc(xhp, s->items, sizeof(char*) * s->size);
}

/* frees up all memory allocated by strmgr */
void
xsps_strmgr_free(xsps_handle_t* xhp)
{
	xsps_strmgr_t* s = xhp->strmgr;
	if (s != NULL) {
		while(s->size > 0) xsps_strmgr_del(xhp);
		free(s);
		s = NULL;
	}
}

/* easier to check */
bool
xsps_streq(const char* s1, const char* s2)
{
	return ((strcmp(s1, s2)) == 0);
}

/* wrapper around xsps_strmgr_add() */
char*
xstrcpy(xsps_handle_t* xhp, const char* src)
{
	return xsps_strmgr_add(xhp, src);
}
