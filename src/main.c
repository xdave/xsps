/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * All rights reserved.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <stdlib.h>
#include <string.h>

#include "xsps.h"

int
main(int argc, char **argv)
{
	xhp_t *xhp = xhp_new(argc, argv);

	/* testing config args */
	log_debug(xhp, "%s", "Configuration:");
	log_debug(xhp, "masterdir = '%s'", xhp->config->masterdir);

	process_template(xhp);

	xhp_free(xhp);
	return (EXIT_SUCCESS);
}
