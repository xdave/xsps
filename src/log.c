/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Copyright (c) 2012 Juan Romero Pardines.
 * All rights reserved.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "xsps.h"

void
log_all(xhp_t* xhp, int c, FILE* tgt, const char *name, const char *fmt, ...)
{
	int	n;
	size_t	size = 100;
	char	*p, *np;
	va_list ap;

	if (xstreq(name, "DEBUG") && xhp->arg->debug == false)
		return;

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

	fprintf(tgt, "%c[%dm%c[%dm[%s] => %s%c[%dm\n",
		COLOR_ESC, COLOR_BOLD, COLOR_ESC, c,
		name, p, COLOR_ESC, COLOR_OFF);

	free(p);
}
