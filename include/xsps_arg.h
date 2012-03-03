/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include "type/xsps_handle_t.h"

#ifndef XSPS_ARG_H
#define XSPS_ARG_H 1

void xsps_arg_init(xsps_handle_t*);
int xsps_arg_parse(xsps_handle_t*, int, char**);
int xsps_arg_print_usage(xsps_handle_t*, const char*);

#endif /* XSPS_ARG_H */
