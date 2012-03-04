/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "xsps.h"

void
arg_init(xhp_t* xhp, int argc, char** argv)
{
	xhp->arg = xmalloc(xhp, sizeof(arg_t));
	xhp->arg->argc = argc;
	xhp->arg->argv = argv;
	xhp->arg->debug = false;
	xhp->arg->config = xstrcpy(xhp, XSPS_CONFIG);
	xhp->arg->build = xstrcpy(xhp, "base-chroot");
	arg_parse(xhp);
}

int
arg_parse(xhp_t* xhp)
{
	int c;

	if (xhp->arg->argc == 1)
		arg_print_usage(xhp);

	while ((c = getopt(xhp->arg->argc,xhp->arg->argv,"hdc:m:b:")) != EOF) {
		switch (c) {
			case 'd':
				xhp->arg->debug = true;
				log_debug(xhp, "+FLAG -%c", c);
				break;
			case 'c':
				xhp->arg->config = xstrcpy(xhp, optarg);
				log_debug(xhp, "+OPTION -%c: '%s'", c, optarg);
				break;
			case 'm':
				xhp->arg->masterdir = xstrcpy(xhp, optarg);
				log_debug(xhp, "+OPTION -%c: '%s'", c, optarg);
				break;
			case 'b':
				xhp->arg->build = xstrcpy(xhp, optarg);
				log_debug(xhp, "+OPTION -%c: '%s'", c, optarg);
				break;
			case 'h':
			default:
				arg_print_usage(xhp);
				break;
		}
	}
	return 0;
}

void
arg_print_usage(xhp_t* xhp)
{
	log_info(xhp,
"Usage: %s [-h] [-d] [-c FILE] [-m DIR] -b PACKAGE\n\n"
"	Options:\n"
"	  -h .............. display this message\n"
"	  -d .............. display extra debugging messages\n"
"	  -c FILE ......... specifiy alternate config FILE\n"
"	  -m DIR .......... override MASTERDIR config setting\n\n"
"	Actions:\n"
"	  -b PACKAGE ...... build a PACKAGE\n",
		xhp->arg->argv[0]);
	xhp_free(xhp);
	exit(1);
}
