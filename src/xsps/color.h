/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#ifndef COLOR_H
#define COLOR_H 1

typedef enum {
	COLOR_SIZE = 8,
	COLOR_OFF = 0,
	COLOR_BOLD = 1,
	COLOR_UNDERLINE = 4,
	COLOR_INVERSE = 7,
	COLOR_ESC = 27,
	COLOR_RED = 31,
	COLOR_GREEN = 32,
	COLOR_YELLOW = 33,
	COLOR_BLUE = 34,
	COLOR_MAGENTA = 35,
	COLOR_CYAN = 36,
	COLOR_WHITE = 37
} xsps_color;

#endif /* COLOR_H */
