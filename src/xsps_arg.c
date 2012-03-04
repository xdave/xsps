/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "xsps.h"

void xsps_arg_init(xsps_handle_t* xhp) {
	xhp->arg = malloc(sizeof(xsps_arg_t));
	xhp->arg->config = xstrcpy(xhp, XSPS_CONFIG);
	xhp->arg->build = xstrcpy(xhp, "base-chroot");
}

int xsps_arg_parse(xsps_handle_t* xhp, int argc, char** argv) {
	int c;

	if (argc == 1) { return xsps_arg_print_usage(xhp, argv[0]); }

	while ((c = getopt(argc, argv, "hdc:m:b:")) != EOF) {
		switch (c) {
			case 'd':
				/* TODO: ENABLE DEBUG LOGGING HERE */
				xsps_log_debug(xhp, "+FLAG -%c", c);
				break;
			case 'c':
				xhp->arg->config = xstrcpy(xhp, optarg);
				xsps_log_debug(xhp, "+OPTION -%c: '%s'",
						c, optarg);
				break;
			case 'm':
				xhp->arg->masterdir = xstrcpy(xhp, optarg);
				xsps_log_debug(xhp, "+OPTION -%c: '%s'",
						c, optarg);
				break;
			case 'b':
				xhp->arg->build = xstrcpy(xhp, optarg);
				xsps_log_debug(xhp, "+OPTION -%c: '%s'",
						c, optarg);
				break;
			case 'h':
			default:
				return xsps_arg_print_usage(xhp, argv[0]);
				break;
		}
	}
	return 0;
}

int xsps_arg_print_usage(xsps_handle_t* xhp, const char* progname) {
	xsps_log_info(xhp,
"Usage: %s [-h] [-d] [-c FILE] [-m DIR] -b PACKAGE\n\n"
"	Options:\n"
"	  -h .............. display this message\n"
"	  -d .............. display extra debugging messages\n"
"	  -c FILE ......... specifiy alternate config FILE\n"
"	  -m DIR .......... override MASTERDIR config setting\n\n"
"	Actions:\n"
"	  -b PACKAGE ...... build a PACKAGE\n",
		progname);
	return 0;
}
