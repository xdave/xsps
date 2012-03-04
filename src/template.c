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


static void
printopt(cfg_t *cfg, struct sect_opts *sopts, const char *indent, bool showopt)
{
	cfg_t *cfgsec;
	struct section *sect;
	struct sect_opts *nsopts;
	unsigned int size, i;
	const char *optstr;
	bool optbool;
	size_t optint;

	switch (sopts->type) {
	case OPT_BOOL:
		optbool = cfg_getbool(cfg, sopts->name);
		if (!optbool)
			return;
		if (showopt)
			printf("%s%s: ", indent, sopts->name);

		printf("true\n");
		return;
	case OPT_INT:
		optint = (size_t)cfg_getint(cfg, sopts->name);
		if (optint <= 0)
			return;
		if (showopt)
			printf("%s%s: ", indent, sopts->name);

		printf("%zu\n", optint);
		return;
	case OPT_STR:
		optstr = cfg_getstr(cfg, sopts->name);
		if (optstr == NULL)
			return;
		if (showopt)
			printf("%s%s: ", indent, sopts->name);

		printf("%s\n", optstr);
		return;
	case OPT_STR_LIST:
		size = cfg_size(cfg, sopts->name);
		if (size == 0)
			return;
		if (showopt)
			printf("%s%s: ", indent, sopts->name);
		for (i = 0; i < size; i++)
			printf("%s ", cfg_getnstr(cfg, sopts->name, i));

		printf("\n");
		return;
	case OPT_SEC:
		size = cfg_size(cfg, sopts->name);
		if (size == 0)
			return;

		for (i = 0; i < size; i++) {
			if (showopt)
				printf("%s[%s]\n", indent, sopts->name);
			cfgsec = cfg_getnsec(cfg, sopts->name, i);
			nsopts = sopts;
			for (sect = sections; sect->name; sect++) {
				if (strcmp(sect->name, sopts->name) == 0) {
					nsopts = sect->sopts;
					break;
				}
			}
			for (; nsopts->name; nsopts++)
				printopt(cfgsec, nsopts, "  ", showopt);
		}
		return;
	}
}

static void
print_all_options(cfg_t *cfg, const char *section, const char *indent)
{
	struct sect_opts *sopts;
	struct section *sect;

	if (section == NULL) {
		for (sopts = tmpl_opts; sopts->name; sopts++)
			printopt(cfg, sopts, indent, true);
	} else {
		for (sect = sections; sect->name; sect++) {
			if (strcmp(sect->name, section))
				continue;
			for (sopts = sect->sopts; sopts->name; sopts++)
				printopt(cfg, sopts, indent, true);
		}
	}
}

static void
print_one_option(cfg_t *cfg, const char *option, const char *indent)
{
	struct sect_opts *sopts;
	struct section *sect;
	bool found = false;

	for (sect = sections; sect->name; sect++) {
		for (sopts = sect->sopts; sopts->name; sopts++) {
			if (strcmp(sopts->name, option) == 0) {
				printopt(cfg, sopts, indent, false);
				found = true;
				break;
			}
		}
		if (found)
			break;
	}
}

static cfg_t *
match_pkg_by_name(cfg_t *cfg, const char *name)
{
	cfg_t *cfgsec = NULL;
	const char *pkgname;
	unsigned int i;

	for (i = 0; i < cfg_size(cfg, "package"); i++) {
		cfgsec = cfg_getnsec(cfg, "package", i);
		pkgname = cfg_getstr(cfgsec, "pkgname");
		if (strcmp(pkgname, name) == 0)
			break;

		cfgsec = NULL;
	}
	return cfgsec;
}

static int
validate_mkdeps_section(cfg_t *cfg, cfg_opt_t *opt)
{
	cfg_t *cfgsec;
	unsigned int i;
	bool found = false;

	(void)opt;

	for (i = 0; i < cfg_size(cfg, "make-depends"); i++) {
		cfgsec = cfg_getnsec(cfg, "make-depends", i);
		if (cfg_size(cfgsec, "all")) {
			found =  true;
			break;
		}
	}
	if (!found) {
		fprintf(stderr, "%s:%d incorrect build template: missing 'all' "
		    "string list in make-depends section.\n",
		    cfg->filename, cfg->line);
		return -1;
	}
	return 0;
}

static int
validate_distfiles_section(cfg_t *cfg, cfg_opt_t *opt)
{
	cfg_t *cfgsec;
	unsigned int i;
	bool found_src = false, found_hash = false;

	(void)opt;

	for (i = 0; i < cfg_size(cfg, "distfiles"); i++) {
		cfgsec = cfg_getnsec(cfg, "distfiles", i);
		if (cfg_size(cfgsec, "source"))
			found_src =  true;
		if (cfg_size(cfgsec, "sha256"))
			found_hash = true;
	}
	if (!found_src || !found_hash) {
		fprintf(stderr, "%s:%d incorrect build template: missing "
		    "'%s' string in distfiles section.\n",
		    cfg->filename, cfg->line, !found_src ? "source" : "sha256");
		return -1;
	}
	return 0;
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

/*static void
usage(const char *p)
{
	fprintf(stderr, "usage: %s [-o prop] [-p pkgname] template\n", p);
	exit(EXIT_FAILURE);
}*/

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
	/* distfiles section */
	cfg_opt_t cfg_distfiles_opts[] = {
		CFG_STR_LIST("source", NULL, CFGF_NONE),
		CFG_STR_LIST("sha256", NULL, CFGF_NONE),
		CFG_END()
	};
	/* make-depends section */
	cfg_opt_t cfg_mkdeps_opts[] = {
		CFG_STR_LIST("all", NULL, CFGF_NONE),
		CFG_STR_LIST("i686", NULL, CFGF_NONE),
		CFG_STR_LIST("x86_64", NULL, CFGF_NONE),
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
		CFG_SEC("distfiles", cfg_distfiles_opts, CFGF_NONE),
		CFG_SEC("make-depends", cfg_mkdeps_opts, CFGF_NONE),
		CFG_SEC("package", cfg_pkg_opts, CFGF_MULTI),
		CFG_END()
	};
	cfg_t *cfg, *cfgsec;
	int rv;
	const char *option, *pkgname, *template;

	option = xhp->arg->option;
	pkgname = xhp->arg->pkgname;
	template = xstrf(xhp, "%s/srcpkgs/%s/template",
	    xhp->config->distdir, xhp->arg->template_name);

	cfg = cfg_init(opts, CFGF_NONE);
	cfg_set_validate_func(cfg, "make-depends", validate_mkdeps_section);
	cfg_set_validate_func(cfg, "distfiles", validate_distfiles_section);

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

	if (pkgname) {
		cfgsec = match_pkg_by_name(cfg, pkgname);
		if (cfgsec == NULL) {
			log_error(xhp, "%s: no such package `%s' in %s.",
			    xhp->arg->argv[0], pkgname, template);
			cfg_free(cfg);
			xhp_free(xhp);
			exit(EXIT_FAILURE);
		}
		if (option)
			print_one_option(cfgsec, option, "");
		else
			print_all_options(cfgsec, "package", "");
	} else {
		if (option)
			print_one_option(cfg, option, "");
		else
			print_all_options(cfg, NULL, "");
	}

	cfg_free(cfg);
	return (EXIT_SUCCESS);
}
