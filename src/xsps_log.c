/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "xsps.h"

void xsps_log_all(xsps_handle_t* xhp, int c, FILE* target,
		  const char *name, const char *fmt, ...) {
	int error;
	int	n;
	size_t	size = 100;
	char	buf[256];
	char	*p, *np;
	va_list ap;

	errno = 0;
	p = malloc(size);
	if(errno > 0) {
		strerror_r(errno, buf, 256);
		fputs(buf, stderr); putchar('\n');
		xsps_handle_free(xhp);
		exit(1);
	}

	while(1) {
		va_start(ap, fmt);
		n = vsnprintf(p, size, fmt, ap);
		va_end(ap);
		if(n > -1 && (size_t)n < size) break;
		if(n > -1) size = (size_t)n+1;
		np = realloc(p, size);
		if(errno > 0) {
			strerror_r(errno, buf, 256);
			free(p);
			fputs(buf, stderr); putchar('\n');
			xsps_handle_free(xhp);
			exit(1);
		} else {
			p = np;
		}
	}

	error = errno;
	errno = 0;

	fprintf(target, "%c[%dm%c[%dm[%s] => %s%c[%dm\n",
		COLOR_ESC, COLOR_BOLD, COLOR_ESC, c,
		name, p, COLOR_ESC, COLOR_OFF);

	if (error > 0) {
		strerror_r(error, buf, 256);
		xsps_log_error(xhp, "%s", buf);
		xsps_handle_free(xhp);
		exit(1);
	}
}
