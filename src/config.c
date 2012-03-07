/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * All rights reserved.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "xsps.h"

void
config_init(xhp_t *xhp)
{
	cfg_opt_t opts[] = {
		CFG_STR("XSPS_DISTDIR", ".", CFGF_NONE),
		CFG_STR("XSPS_SRCPKGS_REPOURL",
		    "git://github.com/davehome/xsps.git", CFGF_NONE),
		CFG_STR("XSPS_MASTERDIR", "${XSPS_DISTDIR}/chroot", CFGF_NONE),
		CFG_STR("XSPS_HOSTDIR", "${XSPS_DISTDIR}/host", CFGF_NONE),
		CFG_STR("XSPS_CFLAGS", "-O2 -pipe -mtune=generic", CFGF_NONE),
		CFG_STR("XSPS_CXXFLAGS", "${XSPS_CFLAGS}", CFGF_NONE),
		CFG_BOOL("XSPS_CCACHE", false, CFGF_NONE),
		CFG_STR("XSPS_LDFLAGS", "-Wl,--as-needed", CFGF_NONE),
		CFG_INT("XSPS_MAKEJOBS", 0, CFGF_NONE),
		CFG_STR("XSPS_COMPRESS_CMD", "xz", CFGF_NONE),
		CFG_INT("XSPS_COMPRESS_LEVEL", 9, CFGF_NONE),
		CFG_END()
	};

	int  error;
	char error_buffer[256];

	xhp->config = xmalloc(xhp, sizeof(config_t));
	xhp->config->cfg = cfg_init(opts, CFGF_NONE);

	switch(cfg_parse(xhp->config->cfg, xhp->arg->config)) {
	case CFG_FILE_ERROR:
		error = errno;
		strerror_r(error, error_buffer, 256);
		log_warn(xhp, "Can't read config file '%s': %s.",
		    xhp->arg->config, error_buffer);
		log_warn(xhp, "%s", "Using defaults.");
		break;
	case CFG_PARSE_ERROR:
		xhp_free(xhp);
		exit(EXIT_FAILURE);
		break;
	case CFG_SUCCESS:
	default:
		break;
	}

	/* TODO: Make this better */

	if (xhp->arg->distdir == NULL) {
		xhp->config->distdir = breplace(xhp,
		    cfg_getstr(xhp->config->cfg, "XSPS_DISTDIR"));
	} else {
		xhp->config->distdir = xhp->arg->distdir;
	}
	setenv("XSPS_DISTDIR", xhp->config->distdir, 1);
	xhp->config->repourl = breplace(xhp,
	    cfg_getstr(xhp->config->cfg, "XSPS_SRCPKGS_REPOURL"));
	setenv("XSPS_SRCPKGS_REPOURL", xhp->config->repourl, 1);
	if (xhp->arg->masterdir == NULL) {
		xhp->config->masterdir = breplace(xhp,
		    cfg_getstr(xhp->config->cfg, "XSPS_MASTERDIR"));
	} else {
		xhp->config->masterdir = xhp->arg->masterdir;
	}
	setenv("XSPS_MASTERDIR", xhp->config->masterdir, 1);
	xhp->config->hostdir = breplace(xhp,
	    cfg_getstr(xhp->config->cfg, "XSPS_HOSTDIR"));
	setenv("XSPS_HOSTDIR", xhp->config->hostdir, 1);
	xhp->config->cflags = breplace(xhp,
	    cfg_getstr(xhp->config->cfg, "XSPS_CFLAGS"));
	setenv("XSPS_CFLAGS", xhp->config->cflags, 1);
	xhp->config->cxxflags = breplace(xhp,
	    cfg_getstr(xhp->config->cfg, "XSPS_CXXFLAGS"));
	setenv("XSPS_CXXFLAGS", xhp->config->cxxflags, 1);
	xhp->config->ldflags = breplace(xhp,
	    cfg_getstr(xhp->config->cfg, "XSPS_LDFLAGS"));
	setenv("XSPS_LDFLAGS", xhp->config->ldflags, 1);
	xhp->config->compress_cmd = breplace(xhp,
	    cfg_getstr(xhp->config->cfg, "XSPS_COMPRESS_CMD"));
	setenv("XSPS_COMPRESS_CMD", xhp->config->compress_cmd, 1);

	/* TODO: Make these work with setenv() */
	xhp->config->ccache = cfg_getbool(xhp->config->cfg, "XSPS_CCACHE");
	xhp->config->makejobs =
	    (uint16_t)cfg_getint(xhp->config->cfg, "XSPS_MAKEJOBS");
	xhp->config->compress_level =
	    (uint16_t)cfg_getint(xhp->config->cfg, "XSPS_COMPRESS_LEVEL");
}
