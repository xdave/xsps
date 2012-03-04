#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <confuse.h>
#include <sys/utsname.h>

struct source_section {
	bool bootstrap;			/* optional */
	bool create_wrksrc;		/* optional */
	bool disable_pbuild;		/* optional */
	bool disable_asneeded;		/* optional */
	bool noextract;			/* optional */
	bool nofetch;			/* optional */
	const char *source;
	const char *version;
	const char *revision;
	const char *homepage;
	const char *maintainer;
	const char *license;
	const char *description;
	const char *build_style;	/* optional */
	const char *build_requires;	/* optional */
	const char *wrksrc;		/* optional */
	const char *build_wrksrc;	/* optional */
	const char *conf_script;	/* optional */
	const char *patch_args;		/* optional */
	const char *required_abi;	/* optional */
};

struct pkg_section {
	bool noarch;			/* optional */
	bool nostrip;			/* optional */
	bool nonfree;			/* optional */
	bool noverifyrdeps;		/* optional */
	bool preserve;			/* optional */
	const char *pkgname;
	const char *desc;
	const char *arch;		/* optional */
	const char *makedirs;		/* optional */
	/* package specific */
	const char *sgml_catalogs;	/* optional */
	const char *xml_catalogs;	/* optional */
	const char *sgml_entries;	/* optional */
	const char *xml_entries;	/* optional */
};

static bool
get_bool(cfg_t *cfg, const char *name)
{
	bool prop;

	prop = cfg_getbool(cfg, name);
	if (prop)
		printf("%s: %s\n", name, prop ? "true" : "false");

	return prop;
}

static const char *
get_string(cfg_t *cfg, const char *name, bool mandatory)
{
	const char *prop;

	prop = cfg_getstr(cfg, name);
	if (mandatory && prop == NULL) {
		fprintf(stderr, "%s string is undefined!\n", name);
		exit(EXIT_FAILURE);
	} else if (prop) {
		printf("%s: %s\n", name, prop);
		return prop;
	}

	return NULL;
}

static void
print_strlist(cfg_t *cfg, const char *name, bool show_name)
{
	unsigned int i, size;

	size = cfg_size(cfg, name);
	if (size > 0) {
		if (show_name) printf("%s: ", name);
		for (i = 0; i < size; i++)
			printf("%s ", cfg_getnstr(cfg, name, i));
		if (show_name) printf("\n");
	}
}

static int
validate_mkdeps_section(cfg_t *cfg, cfg_opt_t *opt)
{
	cfg_t *cfgsec;
	unsigned int i;
	bool found = false;

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

	for (i = 0; i < cfg_size(cfg, "distfiles"); i++) {
		cfgsec = cfg_getnsec(cfg, "distfiles", i);
		if (cfg_size(cfgsec, "source") > 0)
			found_src =  true;
		if (cfg_size(cfgsec, "sha256") > 0)
			found_hash = true;
	}
	if (!found_src || !found_hash) {
		fprintf(stderr, "%s:%d incorrect build template: missing "
		    "'%s' list in distfiles section.\n",
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

int
main(int argc, char **argv)
{
	/* package sections */
	cfg_opt_t pkg_opts[] = {
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
		CFG_STR_LIST("shlib-depends", NULL, CFGF_NONE),
		CFG_STR_LIST("register-shell", NULL, CFGF_NONE),
		CFG_STR_LIST("font-dirs", NULL, CFGF_NONE),
		CFG_STR_LIST("gtk-iconcache-dirs", NULL, CFGF_NONE),
		CFG_STR_LIST("systemd-services", NULL, CFGF_NONE),
		CFG_STR_LIST("system-accounts", NULL, CFGF_NONE),
		CFG_END()
	};
	/* distfiles section */
	cfg_opt_t distfiles_opts[] = {
		CFG_STR_LIST("source", NULL, CFGF_NONE),
		CFG_STR_LIST("sha256", NULL, CFGF_NONE),
		CFG_END()
	};
	/* make-depends section */
	cfg_opt_t mkdeps_opts[] = {
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
		CFG_STR("version", NULL, CFGF_NONE),
		CFG_STR("revision", NULL, CFGF_NONE),
		CFG_STR("homepage", NULL, CFGF_NONE),
		CFG_STR("maintainer", NULL, CFGF_NONE),
		CFG_STR("license", NULL, CFGF_NONE),
		CFG_STR("description", NULL, CFGF_NONE),
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
		CFG_SEC("distfiles", distfiles_opts, CFGF_NONE),
		CFG_SEC("make-depends", mkdeps_opts, CFGF_NONE),
		CFG_SEC("package", pkg_opts, CFGF_MULTI),
		CFG_END()
	};
	cfg_t *cfg, *cfgsec;
	struct utsname un;
	struct source_section s;
	struct pkg_section p;
	unsigned int i;
	int rv;

	if (argc != 2) {
		fprintf(stderr, "usage: %s file.xct\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	cfg = cfg_init(opts, CFGF_NONE);
	cfg_set_validate_func(cfg, "make-depends", validate_mkdeps_section);
	cfg_set_validate_func(cfg, "distfiles", validate_distfiles_section);

	rv = cfg_parse(cfg, argv[1]);
	if (rv == CFG_FILE_ERROR) {
		fprintf(stderr, "%s: cannot read %s (%s)\n",
		    argv[0], argv[1], strerror(errno));
		exit(EXIT_FAILURE);
	} else if (rv == CFG_PARSE_ERROR) {
		fprintf(stderr, "%s: failed to parse %s\n", argv[0], argv[1]);
		exit(EXIT_FAILURE);
	}
	/*
	 * Validate the "package" section, we need at least one.
	 */
	if (validate_pkg_section(cfg) == -1)
		exit(EXIT_FAILURE);

	memset(&s, 0, sizeof(s));
	memset(&p, 0, sizeof(p));
	/* 
	 * Parse mandatory properties in global scope.
	 */
	s.source = get_string(cfg, "source", true);
	s.version = get_string(cfg, "version", true);
	s.revision = get_string(cfg, "revision", true);
	s.homepage = get_string(cfg, "homepage", true);
	s.maintainer = get_string(cfg, "maintainer", true);
	s.license = get_string(cfg, "license", true);
	s.description = get_string(cfg, "description", true);
	/*
	 * Optional properties.
	 */
        s.bootstrap = get_bool(cfg, "bootstrap");
	s.create_wrksrc = get_bool(cfg, "create-wrksrc");
	s.disable_pbuild = get_bool(cfg, "disable-parallel-build");
	s.disable_asneeded = get_bool(cfg, "disable-as-needed");
	s.noextract = get_bool(cfg, "noextract");
	s.nofetch = get_bool(cfg, "nofetch");

	s.build_style = get_string(cfg, "build-style", false);
	s.build_requires = get_string(cfg, "build-requires", false);
	s.wrksrc = get_string(cfg, "wrksrc", false);
	s.build_wrksrc = get_string(cfg, "build-wrksrc", false);
	s.patch_args = get_string(cfg, "patch-args", false);
	s.required_abi = get_string(cfg, "required-abi", false);
	s.conf_script = get_string(cfg, "configure-script", false);
	/*
	 * Optional string lists.
	 */
	print_strlist(cfg, "configure-args", true);
	print_strlist(cfg, "make-args", true);
	print_strlist(cfg, "make-install-args", true);
	/*
	 * Optional sections.
	 */
	uname(&un);
	printf("make-depends: ");
	for (i = 0; i < cfg_size(cfg, "make-depends"); i++) {
		cfgsec = cfg_getnsec(cfg, "make-depends", i);
		print_strlist(cfgsec, "all", false);
		print_strlist(cfgsec, un.machine, false);
	}
	printf("\n");
	printf("distfiles: ");
	for (i = 0; i < cfg_size(cfg, "distfiles"); i++) {
		cfgsec = cfg_getnsec(cfg, "distfiles", i);
		print_strlist(cfgsec, "source", false);
		print_strlist(cfgsec, "sha256", false);
	}
	printf("\n");
	/*
	 * Package sections (at least one must be present).
	 */
	for (i = 0; i < cfg_size(cfg, "package"); i++) {
		cfgsec = cfg_getnsec(cfg, "package", i);
		p.pkgname = get_string(cfgsec, "pkgname", true);
		p.desc = get_string(cfgsec, "desc", true);
		p.arch = get_string(cfgsec, "arch", false);
		p.noarch = get_bool(cfgsec, "noarch");
		p.nostrip = get_bool(cfgsec, "nostrip");
		p.noverifyrdeps = get_bool(cfgsec, "noverifyrdeps");
		p.nonfree = get_bool(cfgsec, "nonfree");
		p.preserve = get_bool(cfgsec, "preserve");
		p.makedirs = get_string(cfgsec, "make-dirs", false);
		p.sgml_catalogs = get_string(cfgsec, "sgml-catalogs", false);
		p.sgml_entries = get_string(cfgsec, "sgml-entries", false);
		p.xml_catalogs = get_string(cfgsec, "xml-catalogs", false);
		p.xml_entries = get_string(cfgsec, "xml-entries", false);
		print_strlist(cfgsec, "conf-files", true);
		print_strlist(cfgsec, "files", true);
		print_strlist(cfgsec, "depends", true);
		print_strlist(cfgsec, "triggers", true);
		print_strlist(cfgsec, "replaces", true);
		print_strlist(cfgsec, "provides", true);
		print_strlist(cfgsec, "conflicts", true);
		print_strlist(cfgsec, "shlib-depends", true);
		print_strlist(cfgsec, "register-shell", true);
		print_strlist(cfgsec, "font-dirs", true);
		print_strlist(cfgsec, "gtk-iconcache-dirs", true);
		print_strlist(cfgsec, "systemd-services", true);
		print_strlist(cfgsec, "system-accounts", true);
	}

	cfg_free(cfg);
	exit(EXIT_SUCCESS);
}
