/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * All rights reserved.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <stdlib.h>
#include <sys/utsname.h>

#include "xsps.h"

xhp_t*
xhp_new(int argc, char **argv)
{
	struct utsname u;
	xhp_t *xhp;
	xhp = malloc(sizeof(xhp_t));
	if (xhp == NULL) {
		fprintf(stderr, "%s:%d: Out of memory!", __FILE__, __LINE__);
		exit(EXIT_FAILURE);
	}
	str_init(xhp);
	arg_init(xhp, argc, argv);

	log_set_file(xhp, "test.log");

	config_init(xhp);

	uname(&u);
	setenv("XSPS_MACHINE", u.machine, 1);
	setenv("XSPS_VENDOR", "void", 1);
	setenv("XSPS_KERNEL", "linux", 1);
	setenv("XSPS_OS", "gnu", 1);
	setenv("XSPS_BUILD_TRIPLET", breplace(xhp,
	    "${XSPS_MACHINE}-${XSPS_VENDOR}-${XSPS_KERNEL}-${XSPS_OS}"), 1);

	log_debug(xhp, "Welcome to XSPS on %s!", getenv("XSPS_BUILD_TRIPLET"));

	return xhp;
}

void
xhp_free(xhp_t *xhp)
{
	str_free(xhp);

	if (xhp->config != NULL && xhp->config->cfg != NULL)
		cfg_free(xhp->config->cfg);

	if (xhp->config != NULL) free(xhp->config);
	if (xhp->arg != NULL) free(xhp->arg);

	log_close(xhp);

	free(xhp);
}
