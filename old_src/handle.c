/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * All rights reserved.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <stdlib.h>
#include <sys/utsname.h>

#include "xsps_c.h"
#include "xsps.h"

void
xhp_init(int argc, char **argv)
{
	struct utsname u;
	if (xhp == NULL) {
		xhp = malloc(sizeof(xhp_t));
		if (xhp == NULL && sizeof(xhp_t) > 0) {
			fprintf(stderr, "%s:%d: Out of memory!",
					__FILE__, __LINE__);
			exit(EXIT_FAILURE);
		}
		xhp->init = 1;
		xhp->log_file = NULL;
		uname(&u);
		str_init();
		arg_init(argc, argv);
		log_set_file("test.log");
		xhp->config = NULL;
		config_init();
		setenv("XSPS_MACHINE", u.machine, 1);
		setenv("XSPS_VENDOR", "void", 1);
		setenv("XSPS_KERNEL", "linux", 1);
		setenv("XSPS_OS", "gnu", 1);
		setenv("XSPS_BUILD_TRIPLET", breplace(
		    "${XSPS_MACHINE}-${XSPS_VENDOR}-"
		    "${XSPS_KERNEL}-${XSPS_OS}"), 1);
		log_debug("Welcome to XSPS on %s!",
		    getenv("XSPS_BUILD_TRIPLET"));
	}
}

void
xhp_free()
{
	if (xhp != NULL) {
		xhp->init = 0;
		if (xhp->str != NULL) str_free();
		if (xhp->config != NULL) free(xhp->config);
		if (xhp->arg != NULL) free(xhp->arg);

		log_close();

		free(xhp);
	}
}
