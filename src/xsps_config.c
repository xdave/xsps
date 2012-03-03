/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <confuse.h>

#include "xsps_config.h"
#include "xsps_arg.h"
#include "xsps_log.h"

void xsps_config_init(xsps_handle_t* xhp) {
	cfg_opt_t opts[] = {
		CFG_STR("XSPS_DISTDIR", "$HOME/src/xsps", CFGF_NONE),
		CFG_STR("XSPS_REPOURL", "git://github.com/davehome/xsps.git",
			CFGF_NONE),
		CFG_STR("XSPS_MASTERDIR", "$XSPS_DISTDIR/chroot", CFGF_NONE),
		CFG_STR("XSPS_HOSTDIR", "$XSPS_DISTDIR/host", CFGF_NONE),
		CFG_STR("XSPS_CFLAGS", "-O2 -pipe -mtune=generic", CFGF_NONE),
		CFG_STR("XSPS_CXXFLAGS", "$XSPS_CFLAGS", CFGF_NONE),
		CFG_BOOL("XSPS_CCACHE", true, CFGF_NONE),
		CFG_STR("XSPS_LDFLAGS", "-Wl,--as-needed", CFGF_NONE),
		CFG_INT("XSPS_MAKEJOBS", 4, CFGF_NONE),
		CFG_STR("XSPS_COMPRESS_CMD", "xz", CFGF_NONE),
		CFG_INT("XSPS_COMPRESS_LEVEL", 9, CFGF_NONE),
		CFG_END()
	};

	xhp->config = malloc(sizeof(xsps_config_t));
	xhp->config->cfg = cfg_init(opts, CFGF_NONE);

	if(cfg_parse(xhp->config->cfg, xhp->arg->config) == CFG_PARSE_ERROR) {
		xhp->log->error(xhp, "[config] parse error");
		cfg_free(xhp->config->cfg);
		return;
	}

	strcpy(xhp->config->distdir,
		cfg_getstr(xhp->config->cfg, "XSPS_DISTDIR"));
	strcpy(xhp->config->repourl,
		cfg_getstr(xhp->config->cfg, "XSPS_REPOURL"));
	strcpy(xhp->config->masterdir,
		cfg_getstr(xhp->config->cfg, "XSPS_MASTERDIR"));
	strcpy(xhp->config->hostdir,
		cfg_getstr(xhp->config->cfg, "XSPS_HOSTDIR"));
	strcpy(xhp->config->cflags,
		cfg_getstr(xhp->config->cfg, "XSPS_CFLAGS"));
	strcpy(xhp->config->cxxflags,
		cfg_getstr(xhp->config->cfg, "XSPS_CXXFLAGS"));
	strcpy(xhp->config->ldflags,
		cfg_getstr(xhp->config->cfg, "XSPS_LDFLAGS"));
	strcpy(xhp->config->compress_cmd,
		cfg_getstr(xhp->config->cfg, "XSPS_COMPRESS_CMD"));

	xhp->config->ccache = cfg_getbool(xhp->config->cfg, "XSPS_CCACHE");
	xhp->config->makejobs = cfg_getint(xhp->config->cfg, "XSPS_MAKEJOBS");
	xhp->config->compress_level = cfg_getint(xhp->config->cfg,
							"XSPS_COMPRESS_LEVEL");
	
	cfg_free(xhp->config->cfg);
}

