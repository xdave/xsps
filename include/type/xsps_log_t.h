/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#ifndef XSPS_LOG_T_H
#define XSPS_LOG_T_H 1

#define XSPS_LOG_SIZE 2048

typedef struct xsps_log_t {
	int enable_debug;
	void (*info) (void*, const char*);
	void (*warn) (void*, const char*);
	void (*debug)(void*, const char*);
	void (*error)(void*, const char*);
} xsps_log_t;

#endif /* XSPS_LOG_T_H */
