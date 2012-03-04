/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <string.h>

#include "xsps.h"

bool
xsps_streq(const char* s1, const char* s2)
{
	return ((strcmp(s1, s2)) == 0);
}

char*
xstrcpy(xsps_handle_t* xhp, const char* src)
{
	return xsps_strmgr_add(xhp->strmgr, src);
}
