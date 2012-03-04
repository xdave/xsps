/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <stdlib.h>
#include <string.h>

#include "xsps.h"

char* xstrcpy(xsps_handle_t* xhp, const char* src) {
	return xsps_strmgr_add(xhp->strmgr, src);
}

