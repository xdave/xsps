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

#define DIE(fmt, ...)						\
do {									\
	fprintf(stderr, "Error (at %s:%d): ", __FILE__, __LINE__);	\
	fprintf(stderr, fmt, __VA_ARGS__);				\
	if(xhp != NULL) xhp_free();					\
	exit(EXIT_FAILURE);						\
} while (0)

#define log(fmt, ...) log_all(0, stdout, NULL, fmt, __VA_ARGS__)
#define log_info(fmt, ...) \
	log_all(COLOR_WHITE, stdout, "INFO ", fmt, __VA_ARGS__)
#define log_warn(fmt, ...) \
	log_all(COLOR_YELLOW, stdout, "WARN ", fmt, __VA_ARGS__)
#define log_debug(fmt, ...) \
	log_all(COLOR_CYAN, stderr, "DEBUG", fmt, __VA_ARGS__)
#define log_error(fmt, ...) \
	log_all(COLOR_RED, stderr, "ERROR", fmt, __VA_ARGS__)

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
} config_t;

/* string manager */
typedef struct str_t {
	size_t size;	/* How many strings are we keeping track of? */
	char **items;	/* Pointers which will be free()'d */
} str_t;

/* main xsps handle */
typedef struct xhp_t {
	int init;
	str_t *str;		/* String manager */
	arg_t *arg;		/* Arguments parser */
	config_t *config;	/* Configuration loader */
	FILE *log_file;
	const char *log_filename;
} xhp_t;

/* Global xhp_t instance */
/*xhp_t *xhp;*/

/* Functions for dealing with global xhp_t instance */
void xhp_init(int, char **);	/* Initialize the xsps handle */
void xhp_free();		/* Free all memory xalloc()'d in xhp_t */

/* safe memory allocation funcs */
void *xmalloc (size_t);
void *xcalloc (size_t, size_t);
void *xrealloc(void *, size_t);

/* logging */
void log_all(int, FILE *, const char *, const char *, ...);
void log_set_file(const char *);
void log_close();

/* command line arguments */
void arg_init(int, char **);
void arg_parse();
void arg_print_usage();

/* configuration*/
void config_init();

/* string managment*/
void str_init();
void str_free();
char *str_add(const char *);
char *str_add_nocopy(char *);
bool xstreq(const char *, const char *);
char *xstrcpy(const char *);
char *xstrfcpy(const char *, ...);
char *str_replace(const char *, const char *, const char *);

/* Functions dealing with ${FOO} strings */
const char *getbenv(const char *);
void bvars(str_t *, const char *);
char *breplace(const char *);

/* template processing */
int process_template();

#endif /* XSPS_H */
