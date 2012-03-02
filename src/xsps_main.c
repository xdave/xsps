/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include "xsps_arg.h"
#include "xsps_init.h"

#include <string.h>
#include <stdio.h>

int main(int argc, char** argv) {
	xsps_init();
	return xsps_arg_parse(argc, argv);
}
