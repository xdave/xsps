/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "xsps.h"

void
xsps_log_all(xsps_handle_t* xhp, int c, FILE* target,
		const char *name, const char *fmt, ...)
{
	int	n;
	size_t	size = 100;
	char	*p, *np;
	va_list ap;

	p = xmalloc(xhp, size);

	while(1) {
		va_start(ap, fmt);
		n = vsnprintf(p, size, fmt, ap);
		va_end(ap);
		if(n > -1 && (size_t)n < size) break;
		if(n > -1) size = (size_t)n+1;
		np = xrealloc(xhp, p, size);
		p = np;
	}

	fprintf(target, "%c[%dm%c[%dm[%s] => %s%c[%dm\n",
		COLOR_ESC, COLOR_BOLD, COLOR_ESC, c,
		name, p, COLOR_ESC, COLOR_OFF);

	free(p);
}
