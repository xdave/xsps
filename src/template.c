#include "template.h"

void
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

void
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

void
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

cfg_t *
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

int
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

int
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

int
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

void
usage(const char *p)
{
	fprintf(stderr, "usage: %s [-o prop] [-p pkgname] template\n", p);
	exit(EXIT_FAILURE);
}

int
blah(int argc, char **argv)
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
	int rv, c;
	const char *progname, *pkgname = NULL, *option = NULL;

	progname = argv[0];

	while ((c = getopt(argc, argv, "ho:p:")) != -1) {
		switch (c) {
		case 'o':
			option = optarg;
			break;
		case 'p':
			pkgname = optarg;
			break;
		case 'h':
		default:
			usage(progname);
		}
	}
	argc -= optind;
	argv += optind;

	if (argc != 1)
		usage(progname);

	cfg = cfg_init(opts, CFGF_NONE);
	cfg_set_validate_func(cfg, "make-depends", validate_mkdeps_section);
	cfg_set_validate_func(cfg, "distfiles", validate_distfiles_section);

	rv = cfg_parse(cfg, argv[0]);
	if (rv == CFG_FILE_ERROR) {
		fprintf(stderr, "%s: cannot read %s (%s)\n",
		    progname, argv[0], strerror(errno));
		exit(EXIT_FAILURE);
	} else if (rv == CFG_PARSE_ERROR) {
		fprintf(stderr, "%s: failed to parse %s\n", progname, argv[0]);
		exit(EXIT_FAILURE);
	}
	/*
	 * Validate the "package" section, we need at least one.
	 */
	if (validate_pkg_section(cfg) == -1)
		exit(EXIT_FAILURE);

	if (pkgname) {
		cfgsec = match_pkg_by_name(cfg, pkgname);
		if (cfgsec == NULL) {
			fprintf(stderr, "%s: no such package `%s' in %s.\n",
			    progname, pkgname, argv[0]);
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
	exit(EXIT_SUCCESS);
}
