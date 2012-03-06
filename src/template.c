/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * Copyright (c) 2012 Juan Romero Pardines.
 * All rights reserved.
 * Distributed under a modified BSD-style license.
 * See the COPYING file in the toplevel directory for license details. */

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/utsname.h>

#include "xsps.h"

#ifndef __arraycount
# define __arraycount(a) (sizeof(a) / sizeof(*(a)))
#endif

/*
 * Global section options.
 */
static const char *global_opts[] = {
	"bootstrap", "create-wrksrc", "disable-parallel-build", "wrksrc",
	"disable-as-needed", "noextract", "nofetch", "source", "description",
	"version", "revision", "homepage", "maintainer", "license",
	"build-style", "build-requires", "build-wrksrc", "configure-script",
	"configure-args", "make-args", "make-install-args", "patch-args",
	"required-abi", "fetch-depends", "distfiles", "distfiles-i686",
	"distfiles-x86_64", "make-depends", "make-depends-i686",
	"make-depends-x86_64", "package",
};
/*
 * package section options.
 */
static const char *package_opts[] = {
	"noarch", "nostrip", "noverifyrdeps", "nonfree", "preserve", "pkgname",
	"desc", "arch", "make-dirs", "sgml-catalogs", "sgml-entries",
	"xml-catalogs", "xml-entries", "conf-files", "files", "depends",
	"triggers", "replaces", "provides", "conflicts", "register-shell",
	"font-dirs", "gtk-iconcache-dirs", "systemd-services", "system-accounts",
};

static cfg_t *
match_pkg_by_name(cfg_t *cfg, const char *name)
{
	cfg_t *cfgsec = NULL;
	const char *pkgname;
	unsigned int i;

	for (i = 0; i < cfg_size(cfg, "package"); i++) {
		cfgsec = cfg_getnsec(cfg, "package", i);
		pkgname = cfg_getstr(cfgsec, "pkgname");
		if (xstreq(pkgname, name))
			break;

		cfgsec = NULL;
	}
	return cfgsec;
}

static void
print_option(cfg_opt_t *cfg_opt, bool showopt)
{
	unsigned int i;
	uint8_t size = 0;

	/* string list not set */
	if (cfg_opt->flags == 192)
		size = 1;

	/* ignore options not set */
	if (cfg_opt_size(cfg_opt) == size)
		return;

	if (showopt) {
		cfg_opt_print(cfg_opt, stdout);
	} else {
		for (i = 0; i < cfg_opt_size(cfg_opt); i++) {
			cfg_opt_nprint_var(cfg_opt, i, stdout);
			printf(" ");
		}
		printf("\n");
	}
}

static void
print_section(cfg_t *cfg, const char *pkgname, const char *option)
{
	cfg_t *cfgsec;
	cfg_opt_t *cfg_opt;
	const char *p = NULL;
	unsigned int i, j;
	bool showopt = true;

	if (option != NULL)
		showopt = false;

	/* print options from global section */
	for (i = 0; i < __arraycount(global_opts); i++) {
		p = global_opts[i];
		if (xstreq(p, "package"))
			continue;
		if ((option != NULL) && !xstreq(p, option))
			continue;
		cfg_opt = cfg_getopt(cfg, p);
		if (cfg_opt == NULL)
			continue;
		print_option(cfg_opt, showopt);
		if (option != NULL)
			return;
	}
	if (pkgname != NULL) {
		/* print options from specified package section */
		cfgsec = match_pkg_by_name(cfg, pkgname);
		if (cfgsec == NULL)
			return;
		for (i = 0; i < __arraycount(package_opts); i++) {
			p = package_opts[i];
			if ((option != NULL) && !xstreq(p, option))
				continue;
			cfg_opt = cfg_getopt(cfgsec, p);
			if (cfg_opt == NULL)
				continue;
			print_option(cfg_opt, showopt);
			if (option)
				return;
		}
	} else {
		/* print options from all package sections */
		for (i = 0; i < cfg_size(cfg, "package"); i++) {
			cfgsec = cfg_getnsec(cfg, "package", i);
			for (j = 0; j < __arraycount(package_opts); j++) {
				p = package_opts[j];
				cfg_opt = cfg_getopt(cfgsec, p);
				if (cfg_opt == NULL)
					continue;
				print_option(cfg_opt, true);
			}
		}
	}
}

static int
validate_pkg_section(cfg_t *cfg)
{
	if (cfg_getnsec(cfg, "package", 0) == NULL) {
		fprintf(stderr, "%s:%d incorrect build template: missing "
		    "'package' section, at least one must be defined.\n",
		    cfg->filename, cfg->line);
		return -1;
	}
	return 0;
}

int
process_template(xhp_t *xhp)
{
	/* package sections */
	cfg_opt_t cfg_pkg_opts[] = {
		CFG_BOOL("noarch", false, CFGF_NONE),
		CFG_BOOL("nostrip", false, CFGF_NONE),
		CFG_BOOL("nonfree", false, CFGF_NONE),
		CFG_BOOL("preserve", false, CFGF_NONE),
		CFG_BOOL("noverifyrdeps", false, CFGF_NONE),
		CFG_STR("pkgname", NULL, CFGF_NONE),
		CFG_STR("desc", NULL, CFGF_NONE),
		CFG_STR("arch", NULL, CFGF_NONE),
		CFG_STR("make-dirs", NULL, CFGF_NONE),
		CFG_STR("sgml-catalogs", NULL, CFGF_NONE),
		CFG_STR("sgml-entries", NULL, CFGF_NONE),
		CFG_STR("xml-catalogs", NULL, CFGF_NONE),
		CFG_STR("xml-entries", NULL, CFGF_NONE),
		CFG_STR_LIST("conf-files", NULL, CFGF_NONE),
		CFG_STR_LIST("files", NULL, CFGF_NONE),
		CFG_STR_LIST("depends", NULL, CFGF_NONE),
		CFG_STR_LIST("triggers", NULL, CFGF_NONE),
		CFG_STR_LIST("replaces", NULL, CFGF_NONE),
		CFG_STR_LIST("provides", NULL, CFGF_NONE),
		CFG_STR_LIST("conflicts", NULL, CFGF_NONE),
		CFG_STR_LIST("register-shell", NULL, CFGF_NONE),
		CFG_STR_LIST("font-dirs", NULL, CFGF_NONE),
		CFG_STR_LIST("gtk-iconcache-dirs", NULL, CFGF_NONE),
		CFG_STR_LIST("systemd-services", NULL, CFGF_NONE),
		CFG_STR_LIST("system-accounts", NULL, CFGF_NONE),
		CFG_END()
	};
	/* global section */
	cfg_opt_t opts[] = {
		CFG_BOOL("bootstrap", false, CFGF_NONE),
		CFG_BOOL("create-wrksrc", false, CFGF_NONE),
		CFG_BOOL("disable-parallel-build", false, CFGF_NONE),
		CFG_BOOL("disable-as-needed", false, CFGF_NONE),
		CFG_BOOL("noextract", false, CFGF_NONE),
		CFG_BOOL("nofetch", false, CFGF_NONE),
		CFG_STR("source", NULL, CFGF_NONE),
		CFG_STR("description", NULL, CFGF_NONE),
		CFG_STR("version", NULL, CFGF_NONE),
		CFG_STR("revision", NULL, CFGF_NONE),
		CFG_STR("homepage", NULL, CFGF_NONE),
		CFG_STR("maintainer", NULL, CFGF_NONE),
		CFG_STR("license", NULL, CFGF_NONE),
		CFG_STR("build-style", NULL, CFGF_NONE),
		CFG_STR("build-requires", NULL, CFGF_NONE),
		CFG_STR("wrksrc", NULL, CFGF_NONE),
		CFG_STR("build-wrksrc", NULL, CFGF_NONE),
		CFG_STR("required-abi", NULL, CFGF_NONE),
		CFG_STR("patch-args", NULL, CFGF_NONE),
		CFG_STR("configure-script", NULL, CFGF_NONE),
		CFG_STR_LIST("configure-args", NULL, CFGF_NONE),
		CFG_STR_LIST("make-args", NULL, CFGF_NONE),
		CFG_STR_LIST("make-install-args", NULL, CFGF_NONE),
		CFG_STR_LIST("fetch-depends", NULL, CFGF_NONE),
		CFG_STR_LIST("distfiles", NULL, CFGF_NONE),
		CFG_STR_LIST("distfiles-i686", NULL, CFGF_NONE),
		CFG_STR_LIST("distfiles-x86_64", NULL, CFGF_NONE),
		CFG_STR_LIST("make-depends", NULL, CFGF_NONE),
		CFG_STR_LIST("make-depends-i686", NULL, CFGF_NONE),
		CFG_STR_LIST("make-depends-x86_64", NULL, CFGF_NONE),
		CFG_SEC("package", cfg_pkg_opts, CFGF_MULTI),
		CFG_END()
	};
	cfg_t *cfg;
	int rv;
	const char *option, *pkgname, *template;

	option = xhp->arg->option;
	pkgname = xhp->arg->pkgname;
	template = xstrfcpy(xhp, "%s/srcpkgs/%s/template",
	    xhp->config->distdir, xhp->arg->template_name);

	cfg = cfg_init(opts, CFGF_NONE);
	rv = cfg_parse(cfg, template);
	if (rv == CFG_FILE_ERROR) {
		log_error(xhp, "%s: cannot read %s (%s)", xhp->arg->argv[0],
		    template, strerror(errno));
		cfg_free(cfg);
		xhp_free(xhp);
		exit(EXIT_FAILURE);
	} else if (rv == CFG_PARSE_ERROR) {
		log_error(xhp, "%s: failed to parse %s", xhp->arg->argv[0],
		    template);
		cfg_free(cfg);
		xhp_free(xhp);
		exit(EXIT_FAILURE);
	}
	/*
	 * Validate the "package" section, we need at least one.
	 */
	if (validate_pkg_section(cfg) == -1) {
		cfg_free(cfg);
		xhp_free(xhp);
		exit(EXIT_FAILURE);
	}
	print_section(cfg, pkgname, option);
	cfg_free(cfg);
	return 0;
}
