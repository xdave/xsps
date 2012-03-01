/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include "log.h"
#include "arg.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int xsps_args_print_usage(const char* progname) {
	char buffer[XSPS_LOG_SIZE];
	sprintf( buffer, "Usage: %s [-h] [-d] [-c FILE] -b PACKAGE\n"
		"Options:\n"
		" -h .......... display this message\n"
		" -d .......... display extra debugging messages\n"
		" -c FILE ..... specifiy alternate config FILE\n"
		"Actions:\n"
		" -b PACKAGE .. build a PACKAGE",
	progname);
	xsps_log.info(buffer);
	return 0;
}

int xsps_args_parse(int argc, char** argv,
		    int* debug, char** config, char** build) {
	int c;
	extern char* optarg;
	char buffer[XSPS_LOG_SIZE];

	if (argc == 1) { return xsps_args_print_usage(argv[0]); }

	while ((c = getopt(argc, argv, "hdc:b:")) != EOF) {
		switch (c) {
			case 'd':
				*debug = 1;
				xsps_log.debug("+FLAG -d");
				break;
			case 'c':
				if (*config != NULL) free(*config);
				*config = malloc(strlen(optarg)+1);
				sprintf(*config, "%s", optarg);
				sprintf(buffer, "+OPTION -c: '%s'", optarg);
				xsps_log.debug(buffer);
				break;
			case 'b':
				if (*build != NULL) free(*build);
				*build = malloc(strlen(optarg)+1);
				sprintf(*build, "%s", optarg);
				sprintf(buffer, "+OPTION -b: '%s'", optarg);
				xsps_log.debug(buffer);
				break;
			case 'h':
			default:
				return xsps_args_print_usage(argv[0]);
				break;
		}
	}
	return 0;
}

