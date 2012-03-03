/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <stdlib.h>

#include "xsps_handle.h"
#include "xsps_log.h"
#include "xsps_arg.h"
#include "xsps_config.h"

xsps_handle_t* xsps_handle_new() {
	xsps_handle_t* xhp;
	xhp = malloc(sizeof(xsps_handle_t));
	xsps_log_init(xhp);
	xsps_arg_init(xhp);
	xsps_config_init(xhp);
	return xhp;
}

void xsps_handle_free(xsps_handle_t* xhp) {
	if (xhp->config != NULL) free(xhp->config);
	if (xhp->arg != NULL) free(xhp->arg);
	if (xhp->log != NULL) free(xhp->log);
	if (xhp != NULL) free(xhp);
}
