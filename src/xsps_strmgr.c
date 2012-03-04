/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <stdlib.h>
#include <string.h>

#include "xsps.h"

/* creates a new strmgr */
xsps_strmgr_t* xsps_strmgr_new() {
	xsps_strmgr_t* s = malloc(sizeof(xsps_strmgr_t));
	s->size = 0;
	s->items = NULL;
	return s;
}

/* frees up all memory allocated by strmgr */
void xsps_strmgr_free(xsps_strmgr_t* s) {
	if (s != NULL) {
		while(s->size > 0) xsps_strmgr_del(s);
		free(s);
		s = NULL;
	}
}

/* works like strcpy() */
char* xsps_strmgr_add(xsps_strmgr_t* s, const char* item) {
	size_t itemsize = strlen(item) + 1;
	s->size++;
	s->items = realloc(s->items, s->size * sizeof(char*));
	s->items[s->size-1] = malloc(itemsize);
	strncpy(s->items[s->size-1], item, itemsize);
	if(itemsize > 0) s->items[s->size-1][itemsize-1] = '\0';
	return s->items[s->size-1];
}

/* removes a string -- never call this directly; use xsps_strmgr_t_free(). */
void xsps_strmgr_del(xsps_strmgr_t* s) {
	if(s->size > 0) {
		s->size--;
		if(s->items[s->size] != NULL) {
			free(s->items[s->size]);
			s->items[s->size] = NULL;
		}
		s->items = realloc(s->items, sizeof(char*) * s->size);
	}
}
