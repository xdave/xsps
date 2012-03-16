public class Arg {

private OptionContext context;
private OptionGroup config_group;
private OptionGroup display_group;
private OptionGroup repo_group;
private OptionGroup package_group;
private string utext;
public string config;
public bool debug;
public string show;
public bool json;
public bool make_repoidx;
public string package_repo;
public bool xbps;
public bool fetch;
public bool verify;
public bool extract;
public bool configure;
public bool build;
public bool install_destdir;
public bool remove_destdir;
public string[] templates;

public
Arg()
{
	string ver = @"$(XSPS_MAJOR).$(XSPS_MINOR).$(XSPS_PATCH)";
	debug = false;
	json = false;

	utext = @"PACKAGE... (The X Source Packaging System v$(ver))\n\n" +

		"  Copyright (c) 2012 The AUTHORS. See the AUTHORS file.\n" +
		"  See the COPYING file for license/distribution details.\n\n" +

		"  You may override any configuration option by setting an\n" +
		"  environment variable for any option you wish to change.\n" +
		@"  [see $(XSPS_CONFIG) for available options]";

	config_group = new OptionGroup("config", "Configuration Options:",
	    "Show configuration options");
	display_group = new OptionGroup("display", "Display Options:",
	    "Show display options");
	repo_group = new OptionGroup("repo", "Repository Options:",
	    "Show repository options");
	package_group = new OptionGroup("package", "Packaging Options:",
	    "Show packaging options");
	
	create_entries();

	context = new OptionContext(utext);
	context.add_group((owned) config_group);
	context.add_group((owned) display_group);
	context.add_group((owned) repo_group);
	context.add_group((owned) package_group);
}

public void
create_entries()
{
	config_group.add_entries({
		OptionEntry() {
			long_name = "config", short_name = 'c',
			arg_data = &config, arg = OptionArg.FILENAME,
			description = "Specify alternate configuration file",
			arg_description = "FILENAME"
		}, OptionEntry()
	});

	display_group.add_entries({
		OptionEntry() {
			long_name = "show", short_name = 's',
			arg_data = &show, arg = OptionArg.STRING,
			description = "Show property from PACKAGE(s)",
			arg_description = "PROPERTY"
		}, OptionEntry() {
			long_name = "json", arg_data = &json,
			description = "Display parsable JSON output for --show"
		}, OptionEntry() {
			long_name = "debug", arg_data = &debug,
			description = "Display extra debugging messages"
		}, OptionEntry()
	});

	repo_group.add_entries({
		OptionEntry() {
			long_name = "make-repoidx", short_name = 'M',
			arg_data = &make_repoidx,
			description = "Build pkg index for local repository"
		}, OptionEntry() {
			long_name = "pkgrepo", short_name = 'p',
			arg = OptionArg.STRING, arg_data = &package_repo,
			description = "Use REPOSITORY for the -M option",
			arg_description = "REPOSITORY"
		}, OptionEntry()
	});

	package_group.add_entries({
		OptionEntry() {
			long_name = "fetch", short_name = 'F',
			arg_data = &fetch,
			description = "Fetch the distfiles for PACKAGE"
		}, OptionEntry() {
			long_name = "verify", short_name = 'V',
			arg_data = &verify,
			description = "Verify the distfiles for PACKAGE"
		}, OptionEntry() {
			long_name = "extract", short_name = 'E',
			arg_data = &extract,
			description = "Extract the distfiles for PACKAGE"
		}, OptionEntry() {
			long_name = "configure", short_name = 'C',
			arg_data = &configure,
			description = "Run the 'configure' action on PACKAGE"
		}, OptionEntry() {
			long_name = "build", short_name = 'B',
			arg_data = &build,
			description = "Run the 'build' action on PACKAGE"
		}, OptionEntry() {
			long_name = "install-destdir", short_name = 'I',
			arg_data = &install_destdir,
			description = "Install PACKAGE into its destdir only"
		}, OptionEntry() {
			long_name = "remove-destdir", short_name = 'R',
			arg_data = &remove_destdir,
			description = "Remove PACKAGE from its destdir only"
		}, OptionEntry() {
			long_name = "xbps", short_name = 'X', arg_data = &xbps,
			description = "Run all of the above and " +
					"Build an XBPS package"
		}, OptionEntry()
	});
}

public void
parse(string[] argv)
{
	try {
		context.parse(ref argv);
	} catch (OptionError error) {
		Log.error("%s error: %s", XSPS_NAME, error.message);
		usage();
	}

	if (argv.length > 1) {
		templates = new string[argv.length-1];
		for (int i = 1; i < argv.length; i++) {
			templates[i-1] = argv[i];
		}
		return;
	}

	Log.error("%s error: You must specify at least one PACKAGE", XSPS_NAME);
	Log.error("Type --help-all for help regarding options");
	usage();
}

private void
usage()
{
	stdout.printf("%s", context.get_help(true, null));
	exit(EXIT_FAILURE);
}


} /* class Arg */
