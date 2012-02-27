/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include "classes/Args.h"

int main(int argc, char **argv) {
	xsps::Args args(argc, argv);
	int ret = args.parse();
	/* TODO: validate the arguments and run specified actions */
	ret = args.validate();
	return ret;
}
