/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include "color.h"

#include <stdio.h>

#ifndef XSPS_LOG_H
#define XSPS_LOG_H 1

#define XSPS_LOG_SIZE 2048

typedef struct xsps_log_obj {
	const char* name;
	FILE* target;
	void (*info) (const char*);
	void (*warn) (const char*);
	void (*debug)(const char*);
	void (*error)(const char*);
} xsps_log_obj;

xsps_log_obj xsps_log;
int xsps_enable_debug_log;

void xsps_log_info (const char*);
void xsps_log_warn (const char*);
void xsps_log_debug(const char*);
void xsps_log_error(const char*);

void xsps_log_init();
void xsps_log_all(xsps_color, FILE*, const char*, const char*);

#endif /* XSPS_LOG_H */
