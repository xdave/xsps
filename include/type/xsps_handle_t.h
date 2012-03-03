/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include "type/xsps_log_t.h"
#include "type/xsps_arg_t.h"
#include "type/xsps_config_t.h"

#ifndef XSPS_HANDLE_T_H
#define XSPS_HANDLE_T_H 1

typedef struct xsps_handle_t {
	xsps_log_t* log;
	xsps_arg_t* arg;
	xsps_config_t* config;
} xsps_handle_t;

#endif /* XSPS_HANDLE_T_H */
