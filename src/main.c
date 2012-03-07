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
	xhp_init(argc, argv);

	/* testing config */
	log_debug("%s", "Configuration:");
	log_debug("file         = '%s'", xhp->arg->config);
	log_debug("distdir      = '%s'", xhp->config->distdir);
	log_debug("repourl      = '%s'", xhp->config->repourl);
	log_debug("masterdir    = '%s'", xhp->config->masterdir);
	log_debug("hostdir      = '%s'", xhp->config->hostdir);
	log_debug("cflags       = '%s'", xhp->config->cflags);
	log_debug("cxxflags     = '%s'", xhp->config->cxxflags);
	log_debug("ldflags      = '%s'", xhp->config->ldflags);
	log_debug("compress_cmd = '%s'", xhp->config->compress_cmd);
	log_debug("ccache       = '%d'", xhp->config->ccache);
	log_debug("makejobs     = '%d'", xhp->config->makejobs);

	process_template();

	xhp_free();
	return (EXIT_SUCCESS);
}
