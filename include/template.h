/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Copyright (c) 2012 Juan Romero Pardines.
 * All rights reserved.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include <confuse.h>
#include <sys/utsname.h>

#ifndef TEMPLATE_H
#define TEMPLATE_H 1

typedef enum confopt {
	OPT_INT = 1,
	OPT_STR,
	OPT_STR_LIST,
	OPT_BOOL,
	OPT_SEC,
} cfopt_t;

struct sect_opts {
	const char *name;
	cfopt_t type;
};

/*
 * global section options.
 */
struct sect_opts tmpl_opts[] = {
	{ "bootstrap", OPT_BOOL },
	{ "create-wrksrc", OPT_BOOL },
	{ "disable-parallel-build", OPT_BOOL },
	{ "disable-as-needed", OPT_BOOL },
	{ "noextract", OPT_BOOL },
	{ "nofetch", OPT_BOOL },
	{ "source", OPT_STR },
	{ "version", OPT_STR },
	{ "revision", OPT_STR },
	{ "homepage", OPT_STR },
	{ "maintainer", OPT_STR },
	{ "license", OPT_STR },
	{ "description", OPT_STR },
	{ "build-style", OPT_STR },
	{ "build-requires", OPT_STR },
	{ "wrksrc", OPT_STR },
	{ "build-wrksrc", OPT_STR },
	{ "configure-script", OPT_STR },
	{ "configure-args", OPT_STR_LIST },
	{ "make-args", OPT_STR_LIST },
	{ "make-install-args", OPT_STR_LIST },
	{ "patch-args", OPT_STR },
	{ "required-abi", OPT_STR },
	{ "fetch-depends", OPT_STR_LIST },
	{ "distfiles", OPT_SEC },
	{ "make-depends", OPT_SEC },
	{ "package", OPT_SEC },
	{ NULL, 0 }
};

/*
 * package section options.
 */
struct sect_opts pkg_tmpl_opts[] = {
	{ "noarch", OPT_BOOL },
	{ "nostrip", OPT_BOOL },
	{ "noverifyrdeps", OPT_BOOL },
	{ "nonfree", OPT_BOOL },
	{ "preserve", OPT_BOOL },
	{ "pkgname", OPT_STR },
	{ "desc", OPT_STR },
	{ "arch", OPT_STR },
	{ "make-dirs", OPT_STR },
	{ "sgml-catalogs", OPT_STR },
	{ "sgml-entries", OPT_STR },
	{ "xml-catalogs", OPT_STR },
	{ "xml-entries", OPT_STR },
	{ "conf-files", OPT_STR_LIST },
	{ "files", OPT_STR_LIST },
	{ "depends", OPT_STR_LIST },
	{ "triggers", OPT_STR_LIST },
	{ "replaces", OPT_STR_LIST },
	{ "provides", OPT_STR_LIST },
	{ "conflicts", OPT_STR_LIST },
	{ "register-shell", OPT_STR_LIST },
	{ "font-dirs", OPT_STR_LIST },
	{ "gtk-iconcache-dirs", OPT_STR_LIST },
	{ "systemd-services", OPT_STR_LIST },
	{ "system-accounts", OPT_STR_LIST },
	{ NULL, 0 }
};

/*
 * distfiles section options.
 */
struct sect_opts dfiles_tmpl_opts[] = {
	{ "source", OPT_STR_LIST },
	{ "sha256", OPT_STR_LIST },
	{ NULL, 0 }
};

/*
 * make-depends section options.
 */
struct sect_opts mkdeps_tmpl_opts[] = {
	{ "all", OPT_STR_LIST },
	{ "i686", OPT_STR_LIST },
	{ "x86_64", OPT_STR_LIST },
	{ NULL, 0 }
};

/*
 * Mapping between section name and options structure associated with it.
 */
struct section {
	const char *name;
	struct sect_opts *sopts;
} sections[] = {
	{ "distfiles", dfiles_tmpl_opts },
	{ "make-depends", mkdeps_tmpl_opts },
	{ "package", pkg_tmpl_opts },
	{ "", tmpl_opts },
	{ NULL, NULL }
};

void printopt(cfg_t*, struct sect_opts*, const char*, bool);
void print_all_options(cfg_t*, const char*, const char*);
void print_one_option(cfg_t*, const char*, const char*);
cfg_t * match_pkg_by_name(cfg_t*, const char*);
int validate_mkdeps_section(cfg_t*, cfg_opt_t*);
int validate_distfiles_section(cfg_t*, cfg_opt_t*);
int validate_pkg_section(cfg_t*);
void usage(const char*);
int blah(int, char**);

#endif /* TEMPLATE_H */
