/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "xsps_log.h"
#include "xsps_arg.h"

void xsps_arg_init() {
	sprintf(xsps_options.config, "%s/xsps.conf", XSPS_CONFIG_DIR);
	sprintf(xsps_options.build,  "%s", "base-chroot");
}

int xsps_arg_parse(int argc, char** argv) {
	int c;
	extern char* optarg;
	char buffer[XSPS_LOG_SIZE];

	if (argc == 1) { return xsps_arg_print_usage(argv[0]); }

	while ((c = getopt(argc, argv, "hdc:b:")) != EOF) {
		switch (c) {
			case 'd':
				xsps_enable_debug_log = 1;
				xsps_log.debug("+FLAG -d");
				break;
			case 'c':
				sprintf(xsps_options.config, "%s", optarg);
				sprintf(buffer, "+OPTION -c: '%s'", optarg);
				xsps_log.debug(buffer);
				break;
			case 'b':
				sprintf(xsps_options.build, "%s", optarg);
				sprintf(buffer, "+OPTION -b: '%s'", optarg);
				xsps_log.debug(buffer);
				break;
			case 'h':
			default:
				return xsps_arg_print_usage(argv[0]);
				break;
		}
	}
	return 0;
}

int xsps_arg_print_usage(const char* progname) {
	char buffer[XSPS_LOG_SIZE/2];
	sprintf(buffer,
"Usage: %s [-h] [-d] [-c FILE] -b PACKAGE\n\n"
"	Options:\n"
"	  -h .............. display this message\n"
"	  -d .............. display extra debugging messages\n"
"	  -c FILE ......... specifiy alternate config FILE\n\n"
"	Actions:\n"
"	  -b PACKAGE ...... build a PACKAGE\n",
		progname);
	xsps_log.info(buffer);
	return 0;
}
