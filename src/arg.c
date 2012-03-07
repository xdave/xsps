/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * All rights reserved.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "xsps.h"

void
arg_init(xhp_t *xhp, int argc, char **argv)
{
	xhp->arg = xmalloc(xhp, sizeof(arg_t));
	xhp->arg->argc = argc;
	xhp->arg->argv = argv;
	xhp->arg->debug = false;
	xhp->arg->config = xstrcpy(xhp, XSPS_CONFIG);
	xhp->arg->distdir = NULL;
	xhp->arg->masterdir = NULL;
	xhp->arg->option = NULL;
	xhp->arg->pkgname = NULL;
	xhp->arg->template_name = NULL;
	xhp->arg->template = NULL;
	xhp->arg->build = xstrcpy(xhp, "base-chroot");
	arg_parse(xhp);
}

void
arg_parse(xhp_t *xhp)
{
	int c, argc;
	char **argv;

	argc = xhp->arg->argc;
	argv = xhp->arg->argv;

	while ((c = getopt(argc, argv,"hdc:x:m:o:p:b:")) != EOF) {
		switch (c) {
		case 'd':
			xhp->arg->debug = true;
			log_debug(xhp, "+FLAG -%c", c);
			break;
		case 'c':
			xhp->arg->config = xstrcpy(xhp, optarg);
			log_debug(xhp, "+OPTION -%c: '%s'", c, optarg);
			break;
		case 'x':
			xhp->arg->distdir = xstrcpy(xhp, optarg);
			log_debug(xhp, "+OPTION -%c: '%s'", c, optarg);
			break;
		case 'm':
			xhp->arg->masterdir = xstrcpy(xhp, optarg);
			log_debug(xhp, "+OPTION -%c: '%s'", c, optarg);
			break;
		case 'o':
			xhp->arg->option = xstrcpy(xhp, optarg);
			log_debug(xhp, "+OPTION -%c: '%s'", c, optarg);
			break;
		case 'p':
			xhp->arg->pkgname = xstrcpy(xhp, optarg);
			log_debug(xhp, "+OPTION -%c: '%s'", c, optarg);
			break;
		case 'b':
			/* TODO: build action not implemented */
			xhp->arg->build = xstrcpy(xhp, optarg);
			log_debug(xhp, "+OPTION -%c: '%s'", c, optarg);
			break;
		case 'h':
		default:
			arg_print_usage(xhp);
			break;
		}
	}
	argc -= optind;
	argv += optind;

	if (argc != 1) {
		log_error(xhp, "%s", "You must specify a template.");
		arg_print_usage(xhp);
	}

	xhp->arg->template_name = argv[0];
}

void
arg_print_usage(xhp_t *xhp)
{
	fprintf(stderr,
"Usage: %s [-dh] [-c file] [-x dir] [-m dir] [-o prop] [-p pkgname] template\n"
"\n"
"  Flags:\n"
"    -h ............ display this message\n"
"    -d ............ display extra debugging messages\n"
"  Config:\n"
"    -c file ....... specifiy alternate config file\n"
"    -x dir ........ override distdir config setting\n"
"    -m dir ........ override master dir config setting\n"
"  Options:\n"
"    -p pkgname .... specify package name within a template\n"
"    -o prop ....... show property from package for selected template\n\n"
"  template ........ the source package template to use\n\n",
	    xhp->arg->argv[0]);
	xhp_free(xhp);
	exit(EXIT_FAILURE);
}
