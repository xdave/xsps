/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include "xsps_init.h"
#include "xsps_log.h"
#include "xsps_arg.h"

void xsps_init() {
	xsps_log_init();
	xsps_arg_init();
}
