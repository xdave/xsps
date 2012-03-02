/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include "type/xsps_opt.h"

#ifndef XSPS_ARG_H
#define XSPS_ARG_H 1

xsps_opt xsps_options;

void xsps_arg_init();
int  xsps_arg_parse(int, char**);
int  xsps_arg_print_usage(const char*);

#endif /* XSPS_ARG_H */
