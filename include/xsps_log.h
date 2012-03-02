/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <stdio.h>

#include "type/xsps_log_obj.h"

#ifndef XSPS_LOG_H
#define XSPS_LOG_H 1

xsps_log_obj xsps_log;
int xsps_enable_debug_log;

void xsps_log_info (const char*);
void xsps_log_warn (const char*);
void xsps_log_debug(const char*);
void xsps_log_error(const char*);

void xsps_log_all(int, FILE*, const char*, const char*);
void xsps_log_init();

#endif /* XSPS_LOG_H */
