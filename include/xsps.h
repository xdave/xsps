/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Copyright (c) 2012 Juan Romero Pardines.
 * All rights reserved.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <confuse.h>
#include <inttypes.h>

#ifndef XSPS_H
#define XSPS_H 1

#ifndef __arraycount
# define __arraycount(a) (sizeof(a) / sizeof(*(a)))
#endif

#define XENOMEM "Out of memory!"

#define DIE(xhp, fmt, ...)						\
do {									\
	fprintf(stderr, "Error (at %s:%d): ", __FILE__, __LINE__);	\
	fprintf(stderr, fmt, __VA_ARGS__);				\
	if(xhp != NULL) xhp_free(xhp);					\
	exit(EXIT_FAILURE);						\
} while (0)

#define log(xhp, fmt, ...) log_all(xhp, 0, stdout, NULL, fmt, __VA_ARGS__)
#define log_info(xhp, fmt, ...) \
	log_all(xhp, COLOR_WHITE, stdout, "INFO ", fmt, __VA_ARGS__)
#define log_warn(xhp, fmt, ...) \
	log_all(xhp, COLOR_YELLOW, stdout, "WARN ", fmt, __VA_ARGS__)
#define log_debug(xhp, fmt, ...) \
	log_all(xhp, COLOR_CYAN, stderr, "DEBUG", fmt, __VA_ARGS__)
#define log_error(xhp, fmt, ...) \
	log_all(xhp, COLOR_RED, stderr, "ERROR", fmt, __VA_ARGS__)

#define XSPS_CONFIG XSPS_CONFIG_DIR "/xsps.conf"

/* ANSI Colors
 * Used in logging functions. */
typedef enum {
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
	int  argc;		/* from main() */
	char **argv;		/* from main() */
	bool debug;		/* enabled with -d, optional */
	char *config;		/* enabled with -c, optional */
	char *distdir;		/* enabled with -x, optional */
	char *masterdir;	/* enabled with -m, optional */
	char *option;		/* enabled with -o, optional */
	char *pkgname;		/* enabled with -p, optional */
	char *template_name;	/* last argument,   required */
	char *template;
	char *build;		/* TODO: not implemented */
} arg_t;

/* configuration */
typedef struct config_t {
	char *distdir;		 /* XSPS_DISTDIR */
	char *repourl;		 /* XSPS_SRCPKGS_REPOURL */
	char *masterdir;	 /* XSPS_MASTERDIR */
	char *hostdir;		 /* XSPS_HOSTDIR */
	char *cflags;		 /* XSPS_CFLAGS */
	char *cxxflags;		 /* XSPS_CXXFLAGS */
	char *ldflags;		 /* XSPS_LDFLAGS */
	char *compress_cmd;	 /* XSPS_COMPRESS_CMD */
	bool ccache;		 /* XSPS_CCACHE */
	uint16_t compress_level; /* XSPS_COMPRESS_LEVEL */
	uint16_t makejobs;	 /* XSPS_MAKEJOBS */
	cfg_t *cfg;
} config_t;

/* string manager */
typedef struct str_t {
	size_t size;	/* How many strings are we keeping track of? */
	char **items;	/* Pointers which will be free()'d */
} str_t;

/* main xsps handle */
typedef struct xhp_t {
	str_t *str;		/* String manager */
	arg_t *arg;		/* Arguments parser */
	config_t *config;	/* Configuration loader */
	FILE *log_file;
	const char *log_filename;
} xhp_t;

xhp_t *xhp_new(int, char **);	/* Create a new xsps handle */
void xhp_free(xhp_t *);		/* Free all memory xalloc()'d */

/* safe memory allocation funcs */
void *xmalloc (xhp_t *, size_t);
void *xcalloc (xhp_t *, size_t, size_t);
void *xrealloc(xhp_t *, void *, size_t);

/* logging */
void log_all(xhp_t *, int, FILE *, const char *, const char *, ...);
void log_set_file(xhp_t *, const char *);
void log_close(xhp_t *);

/* command line arguments */
void arg_init(xhp_t *, int, char **);
void arg_parse(xhp_t *);
void arg_print_usage(xhp_t *);

/* configuration*/
void config_init(xhp_t *);

/* string managment*/
void str_init(xhp_t *);
void str_free(xhp_t *);
char *str_add(xhp_t *, const char *);
char *str_add_nocopy(xhp_t *, char *);
bool xstreq(const char *, const char *);
char *xstrcpy(xhp_t *, const char *);
char *xstrfcpy(xhp_t *, const char *, ...);
char *str_replace(xhp_t *, const char *, const char *, const char *);

/* Functions dealing with ${FOO} strings */
const char *getbenv(xhp_t *, const char *);
void bvars(xhp_t *, str_t *, const char *);
char *breplace(xhp_t *, const char *);

/* template processing */
int process_template(xhp_t *);

#endif /* XSPS_H */
