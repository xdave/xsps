/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <confuse.h>
#include <inttypes.h>

#ifndef XSPS_H
#define XSPS_H 1

#define XENOMEM fprintf(stderr, "%s:%d: Out of memory!", __FILE__, __LINE__); \
	xsps_handle_free(xhp);						      \
	exit(1)

#define XSPS_LOG_SIZE 2048
#define xsps_log_info(xhp, fmt, ...) \
	xsps_log_all(xhp, COLOR_WHITE, stdout, "INFO ", fmt, ##__VA_ARGS__)
#define xsps_log_warn(xhp, fmt, ...) \
	xsps_log_all(xhp, COLOR_YELLOW, stdout, "WARN ", fmt, ##__VA_ARGS__)
#define xsps_log_debug(xhp, fmt, ...) \
	xsps_log_all(xhp, COLOR_CYAN, stderr, "DEBUG", fmt, ##__VA_ARGS__)
#define xsps_log_error(xhp, fmt, ...) \
	xsps_log_all(xhp, COLOR_RED, stderr, "ERROR", fmt, ##__VA_ARGS__)

#define XSPS_CONFIG XSPS_CONFIG_DIR "/xsps.conf"

/* color */
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
} xsps_color_t;

/* command line arguments */
typedef struct xsps_arg_t {
	int    argc;
	char** argv;
	bool   debug;
	char*  config;
	char*  masterdir;
	char*  build;
} xsps_arg_t;

/* configuration */
typedef struct xsps_config_t {
	char* distdir;
	char* repourl;
	char* hostdir;
	char* cflags;
	char* cxxflags;
	char* ldflags;
	char* compress_cmd;
	bool ccache;
	uint16_t compress_level;
	uint16_t makejobs;
	cfg_t* cfg;
} xsps_config_t;

/* string manager */
typedef struct xsps_strmgr_t {
	size_t size;
	char** items;
} xsps_strmgr_t;

/* main xsps handle */
typedef struct xsps_handle_t {
	xsps_strmgr_t* strmgr;
	xsps_arg_t* arg;
	xsps_config_t* config;
} xsps_handle_t;

xsps_handle_t* xsps_handle_new(int, char**);
void xsps_handle_free(xsps_handle_t*);

/* safe memory allocation */
void *xmalloc(xsps_handle_t*, size_t size);
void *xcalloc(xsps_handle_t*, size_t nmemb, size_t size);
void *xrealloc(xsps_handle_t*, void *ptr, size_t size);

/* logging */
void xsps_log_all(xsps_handle_t*,int,FILE*,const char*,const char*, ...);

/* command line arguments */
void xsps_arg_init(xsps_handle_t*, int, char**);
int  xsps_arg_parse(xsps_handle_t*);
void xsps_arg_print_usage(xsps_handle_t*);

/* configuration*/
void xsps_config_init(xsps_handle_t*);

/* string managment*/
void	xsps_strmgr_init(xsps_handle_t *);
void	xsps_strmgr_free(xsps_handle_t*);
char*	xsps_strmgr_add(xsps_handle_t*, const char*);
bool	xstreq(const char*, const char*);
char*	xstrcpy(xsps_handle_t*, const char*);

#endif /* XSPS_H */
