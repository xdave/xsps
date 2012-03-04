/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "xsps.h"

void*
xmalloc(xsps_handle_t* xhp, size_t size)
{
	void* ptr;

	ptr = malloc(size);
	if (ptr == NULL && size != 0) {
		XENOMEM;
	}

	return ptr;
}

void*
xcalloc(xsps_handle_t* xhp, size_t nmemb, size_t size) 
{
	void* ptr;

	ptr = calloc(nmemb, size);
	if (ptr == NULL && size != 0) {
		XENOMEM;
	}

	return ptr;
}

void*
xrealloc(xsps_handle_t* xhp, void *old_ptr, size_t size)
{
	void* ptr;

	ptr = realloc(old_ptr, size);
	if (ptr == NULL && size != 0) {
		XENOMEM;
	}

	return ptr;
}
