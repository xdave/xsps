/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <stdio.h>

#ifndef XSPS_LOG_OBJ_H
#define XSPS_LOG_OBJ_H 1

#define XSPS_LOG_SIZE 2048

typedef struct xsps_log_obj {
	const char* name;
	FILE* target;
	void (*info) (const char*);
	void (*warn) (const char*);
	void (*debug)(const char*);
	void (*error)(const char*);
} xsps_log_obj;

#endif /* XSPS_LOG_OBJ_H */
