/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <stdbool.h>
#include <confuse.h>

#ifndef XSPS_CONFIG_T_H
#define XSPS_CONFIG_T_H 1

#define XSPS_CONFIG XSPS_CONFIG_DIR "/xsps.conf"

typedef struct xsps_config_t {
	char distdir[80];
	char repourl[80];
	char masterdir[80];
	char hostdir[80];
	char cflags[80];
	char cxxflags[80];
	char ldflags[80];
	char compress_cmd[80];
	bool ccache;
	int compress_level;
	int makejobs;
	cfg_t* cfg;
	cfg_opt_t* opts;
} xsps_config_t;

#endif /* XSPS_CONFIG_T_H */
