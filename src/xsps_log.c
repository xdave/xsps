/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "xsps.h"

void xsps_log_info(void* xhp, const char *msg) {
	xsps_log_all((xsps_handle_t*)xhp, COLOR_WHITE, stdout, "INFO ", msg);
}

void xsps_log_warn(void* xhp, const char *msg) {
	xsps_log_all((xsps_handle_t*)xhp, COLOR_YELLOW, stdout, "WARN ", msg);
}

void xsps_log_debug(void* x, const char *msg) {
	xsps_handle_t* xhp = (xsps_handle_t*)x;
	if(xhp->log->enable_debug == 1)
		xsps_log_all(xhp, COLOR_CYAN, stderr, "DEBUG", msg);
}

void xsps_log_error(void* xhp, const char *msg) {
	xsps_log_all((xsps_handle_t*)xhp, COLOR_RED, stderr, "ERROR", msg);
}

void xsps_log_all(xsps_handle_t* xhp, int c, FILE* target,
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
		xsps_log_error(xhp, buf);
	}
}

void xsps_log_init(xsps_handle_t* xhp) {
	xhp->log = malloc(sizeof(xsps_log_t));
	xhp->log->enable_debug = 0;
	xhp->log->info  = xsps_log_info;
	xhp->log->warn  = xsps_log_warn;
	xhp->log->debug = xsps_log_debug;
	xhp->log->error = xsps_log_error;
}
