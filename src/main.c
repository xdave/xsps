/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <stdlib.h>
#include <string.h>

#include "xsps.h"

int
main(int argc, char** argv)
{
	xhp_t* xhp = xhp_new(argc, argv);

	log_info(xhp, "%s -- %s!!!", "test", "hello");
	log_warn(xhp, "%c %s %x %d", '!', "hi", (size_t)&main, 50);

	xhp_free(xhp);
	return 0;
}
