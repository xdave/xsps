/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <cstring>
#include "common.h"

namespace xsps {

	bool streq(const char* s1, const char* s2) {
		if(strcmp(s1, s2) == 0) return true;
		else return false;
	}

}
