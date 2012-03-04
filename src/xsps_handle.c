/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <stdlib.h>

#include "xsps.h"

xsps_handle_t* xsps_handle_new(int argc, char** argv) {
	xsps_handle_t* xhp;
	xhp = malloc(sizeof(xsps_handle_t));
	if (xhp == NULL) {
		fprintf(stderr, "%s:%d: Out of memory!", __FILE__, __LINE__);
		exit(1);
	}
	xsps_strmgr_init(xhp);
	xsps_arg_init(xhp, argc, argv);
	xsps_config_init(xhp);
	return xhp;
}

void xsps_handle_free(xsps_handle_t* xhp) {
	xsps_strmgr_free(xhp);

	if (xhp->config != NULL && xhp->config->cfg != NULL)
		cfg_free(xhp->config->cfg);

	if (xhp->config != NULL) free(xhp->config);
	if (xhp->arg != NULL) free(xhp->arg);

	free(xhp);
}
