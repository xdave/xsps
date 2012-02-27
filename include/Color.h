/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <cstddef>

#ifndef XSPS_COLOR_H
#define XSPS_COLOR_H 1

namespace xsps {

	namespace Color {

		static const size_t SIZE = 8;

		enum {
			OFF = 0,
			BOLD = 1,
			UNDERLINE = 4,
			INVERSE = 7,
			ESC = 27,
			RED = 31,
			GREEN = 32,
			YELLOW = 33,
			BLUE = 34,
			MAGENTA = 35,
			CYAN = 36,
			WHITE = 37
		};

	} // namespace Color

} // namespace xsps


#endif // XSPS_COLOR_H
