/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * All rights reserved.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "xsps.h"

void
log_all(xhp_t *xhp, int c, FILE *tgt, const char *name, const char *fmt, ...)
{
	int	n;
	size_t	size = 100;
	ssize_t ret;
	char	*p, *np;
	va_list ap;

	if (name != NULL && xstreq(name, "DEBUG") && xhp->arg->debug == false)
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
	if (name != NULL) {
		fprintf(tgt, "%c[%dm%c[%dm[%s] => %s%c[%dm\n",
		    COLOR_ESC, COLOR_BOLD, COLOR_ESC, c,
		    name, p, COLOR_ESC, COLOR_OFF);
		if (xhp->log_file != NULL) {
			ret = fprintf(xhp->log_file, "[%s] => %s\n", name, p);
			if (ret < 0) {
				fprintf(stderr, "Can't write to log file '%s'"
						" (%s)", xhp->log_filename,
						strerror(errno));
			}
		}
	} else {
		fprintf(tgt, "%s\n", p);
		if (xhp->log_file != NULL) {
			ret = fprintf(xhp->log_file, "%s\n", p);
			if (ret < 0) {
				fprintf(stderr, "Can't write to log file '%s'"
						" (%s)", xhp->log_filename,
						strerror(errno));
			}
		}
	}

	free(p);
}

void
log_set_file(xhp_t *xhp, const char *filename)
{
	log_close(xhp);

	if (xhp->log_file == NULL) {
		if ((xhp->log_file = fopen(filename, "w")) == NULL) {
			DIE(xhp, "Cannot open log '%s' (%s)",
			    filename, strerror(errno));
		}
		xhp->log_filename = filename;
		log_debug(xhp, "Using log file '%s'", filename);
	}
}

void
log_close(xhp_t *xhp)
{
	if (xhp->log_file != NULL) {
		if((fflush(xhp->log_file)) != 0) {
			DIE(xhp, "Cannot flush existing log: '%s' (%s)",
			    xhp->log_filename, strerror(errno));
		}
		if ((fclose(xhp->log_file)) != 0) {
			DIE(xhp, "Cannot close existing log: '%s' (%s)",
			    xhp->log_filename, strerror(errno));
		}
		xhp->log_file = NULL;
	}
}
