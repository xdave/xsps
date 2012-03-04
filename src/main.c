/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Copyright (c) 2012 Juan Romero Pardines.
 * All rights reserved.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <stdlib.h>
#include <string.h>

#include "xsps.h"
#include "template.h"

int
main(int argc, char** argv)
{
	xhp_t* xhp = xhp_new(argc, argv);

	/*
	 * Test!
	 */
	process_template(argc, argv);

	xhp_free(xhp);
	return (EXIT_SUCCESS);
}
