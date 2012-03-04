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

#define XENOMEM(xhp)							\
	fprintf(stderr, "%s:%d: Out of memory!", __FILE__, __LINE__);	\
	xhp_free(xhp);							\
	exit(EXIT_FAILURE)

#define log_info(xhp, fmt, ...) \
	log_all(xhp, COLOR_WHITE, stdout, "INFO ", fmt, ##__VA_ARGS__)
#define log_warn(xhp, fmt, ...) \
	log_all(xhp, COLOR_YELLOW, stdout, "WARN ", fmt, ##__VA_ARGS__)
#define log_debug(xhp, fmt, ...) \
	log_all(xhp, COLOR_CYAN, stderr, "DEBUG", fmt, ##__VA_ARGS__)
#define log_error(xhp, fmt, ...) \
	log_all(xhp, COLOR_RED, stderr, "ERROR", fmt, ##__VA_ARGS__)

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
} color_t;

/* command line arguments */
typedef struct arg_t {
	int    argc;
	char** argv;
	bool   debug;
	char*  config;
	char*  masterdir;
	char*  build;
} arg_t;

/* configuration */
typedef struct config_t {
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
} config_t;

/* string manager */
typedef struct str_t {
	size_t size;
	char** items;
} str_t;

/* main xsps handle */
typedef struct xhp_t {
	str_t* str;
	arg_t* arg;
	config_t* config;
} xhp_t;

xhp_t* xhp_new(int, char**);
void xhp_free(xhp_t*);

/* safe memory allocation */
void *xmalloc(xhp_t*, size_t size);
void *xcalloc(xhp_t*, size_t nmemb, size_t size);
void *xrealloc(xhp_t*, void *ptr, size_t size);

/* logging */
void log_all(xhp_t*, int, FILE*, const char*, const char*, ...);

/* command line arguments */
void arg_init(xhp_t*, int, char**);
void arg_parse(xhp_t*);
void arg_print_usage(xhp_t*);

/* configuration*/
void config_init(xhp_t*);

/* string managment*/
void	str_init(xhp_t*);
void	str_free(xhp_t*);
char*	str_add(xhp_t*, const char*);
bool	xstreq(const char*, const char*);
char*	xstrcpy(xhp_t*, const char*);

#endif /* XSPS_H */
