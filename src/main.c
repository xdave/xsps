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

	/* testing config */
	log_debug(xhp, "%s", "Configuration:");
	log_debug(xhp, "file         = '%s'", xhp->arg->config);
	log_debug(xhp, "distdir      = '%s'", xhp->config->distdir);
	log_debug(xhp, "repourl      = '%s'", xhp->config->repourl);
	log_debug(xhp, "masterdir    = '%s'", xhp->config->masterdir);
	log_debug(xhp, "hostdir      = '%s'", xhp->config->hostdir);
	log_debug(xhp, "cflags       = '%s'", xhp->config->cflags);
	log_debug(xhp, "cxxflags     = '%s'", xhp->config->cxxflags);
	log_debug(xhp, "ldflags      = '%s'", xhp->config->ldflags);
	log_debug(xhp, "compress_cmd = '%s'", xhp->config->compress_cmd);
	log_debug(xhp, "ccache       = '%d'", xhp->config->ccache);
	log_debug(xhp, "makejobs     = '%d'", xhp->config->makejobs);

	process_template(xhp);

	xhp_free(xhp);
	return (EXIT_SUCCESS);
}
