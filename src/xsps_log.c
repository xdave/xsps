/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "type/xsps_color.h"
#include "xsps_log.h"

void xsps_log_info(const char *msg) {
	xsps_log_all(COLOR_WHITE, stdout, "INFO ", msg);
}

void xsps_log_warn(const char *msg) {
	xsps_log_all(COLOR_YELLOW, stdout, "WARN ", msg);
}

void xsps_log_debug(const char *msg) {
	if(xsps_enable_debug_log == 1)
		xsps_log_all(COLOR_CYAN, stderr, "DEBUG", msg);
}

void xsps_log_error(const char *msg) {
	xsps_log_all(COLOR_RED, stderr, "ERROR", msg);
}

void xsps_log_all(int c, FILE* target,
		  const char *name, const char *msg) {
	int	error;
	char	color[COLOR_SIZE],
		bold[COLOR_SIZE],
		off[COLOR_SIZE],
		buf[XSPS_LOG_SIZE];

	error = errno;
	errno = 0;

	sprintf(color, "%c[%dm", COLOR_ESC, c);
	sprintf(bold,  "%c[%dm", COLOR_ESC, COLOR_BOLD);
	sprintf(off,   "%c[%dm", COLOR_ESC, COLOR_OFF);

	fprintf(target, "%s%s[%s] => %s%s\n", bold, color, name, msg, off);

	if (error > 0) {
		strerror_r(error, buf, XSPS_LOG_SIZE);
		xsps_log_error(buf);
	}
}

void xsps_log_init() {
	xsps_enable_debug_log = 0;
	xsps_log.info  = xsps_log_info;
	xsps_log.warn  = xsps_log_warn;
	xsps_log.debug = xsps_log_debug;
	xsps_log.error = xsps_log_error;
}
