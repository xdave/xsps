/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "xsps.h"

void xsps_arg_init(xsps_handle_t* xhp) {
	xhp->arg = malloc(sizeof(xsps_arg_t));
	xstrcpy(&xhp->arg->config, XSPS_CONFIG);
	xstrcpy(&xhp->arg->build, "base-chroot");
}

int xsps_arg_parse(xsps_handle_t* xhp, int argc, char** argv) {
	int c;
	/*extern char* optarg;*/
	char buffer[XSPS_LOG_SIZE];

	if (argc == 1) { return xsps_arg_print_usage(xhp, argv[0]); }

	while ((c = getopt(argc, argv, "hdc:m:b:")) != EOF) {
		switch (c) {
			case 'd':
				xhp->log->enable_debug = 1;
				xhp->log->debug(xhp, "+FLAG -d");
				break;
			case 'c':
				xstrcpy(&xhp->arg->config, optarg);
				sprintf(buffer, "+OPTION -c: '%s'", optarg);
				xhp->log->debug(xhp, buffer);
				break;
			case 'm':
				xstrcpy(&xhp->config->masterdir, optarg);
				sprintf(buffer, "+OPTION -m: '%s'", optarg);
				xhp->log->debug(xhp, buffer);
				break;
			case 'b':
				xstrcpy(&xhp->arg->build, optarg);
				sprintf(buffer, "+OPTION -b: '%s'", optarg);
				xhp->log->debug(xhp, buffer);
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
	char buffer[XSPS_LOG_SIZE/2];
	sprintf(buffer,
"Usage: %s [-h] [-d] [-c FILE] [-m DIR] -b PACKAGE\n\n"
"	Options:\n"
"	  -h .............. display this message\n"
"	  -d .............. display extra debugging messages\n"
"	  -c FILE ......... specifiy alternate config FILE\n"
"	  -m DIR .......... override MASTERDIR config setting\n\n"
"	Actions:\n"
"	  -b PACKAGE ...... build a PACKAGE\n",
		progname);
	xhp->log->info(xhp, buffer);
	return 0;
}
