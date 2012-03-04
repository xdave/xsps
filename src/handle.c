/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Copyright (c) 2012 Juan Romero Pardines.
 * All rights reserved.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <stdlib.h>

#include "xsps.h"

xhp_t*
xhp_new(int argc, char** argv)
{
	xhp_t* xhp;
	xhp = malloc(sizeof(xhp_t));
	if (xhp == NULL) {
		fprintf(stderr, "%s:%d: Out of memory!", __FILE__, __LINE__);
		exit(EXIT_FAILURE);
	}
	str_init(xhp);
	arg_init(xhp, argc, argv);
	config_init(xhp);
	return xhp;
}

void
xhp_free(xhp_t* xhp)
{
	str_free(xhp);

	if (xhp->config != NULL && xhp->config->cfg != NULL)
		cfg_free(xhp->config->cfg);

	if (xhp->config != NULL) free(xhp->config);
	if (xhp->arg != NULL) free(xhp->arg);

	free(xhp);
}
