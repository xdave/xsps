/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <stdio.h>

#include "type/xsps_handle_t.h"

#ifndef XSPS_LOG_H
#define XSPS_LOG_H 1

void xsps_log_info (void*, const char*);
void xsps_log_warn (void*, const char*);
void xsps_log_debug(void*, const char*);
void xsps_log_error(void*, const char*);

void xsps_log_all(xsps_handle_t*, int, FILE*, const char*, const char*);
void xsps_log_init(xsps_handle_t*);

#endif /* XSPS_LOG_H */
