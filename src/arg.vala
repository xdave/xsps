public class Arg {

private OptionContext context;
private OptionGroup config_group;
private OptionGroup display_group;
private string utext;
public string config;
public string distdir;
public string masterdir;
public bool debug;
public string show;
public bool json;
public string[] templates;
public string[] template_filenames;

public
Arg()
{
	string ver = @"$(XSPS_MAJOR).$(XSPS_MINOR).$(XSPS_PATCH)";
	debug = false;
	json = false;

	utext = @"PACKAGE... - X Source Packaging System (v" + ver + ")\n\n" +
		 "  Copyright (c) 2012 The AUTHORS. See the AUTHORS file.\n" +
		 "  See the COPYING file for license/distribution details.";

	config_group = new OptionGroup("config", "Configuration Options:",
	    "Show configuration options");
	display_group = new OptionGroup("display", "Display Options:",
	    "Show display options");
	
	create_entries();

	context = new OptionContext(utext);
	context.add_group((owned) config_group);
	context.add_group((owned) display_group);
}

public void
create_entries()
{
	config_group.add_entries({
		OptionEntry() {
			long_name = "config", short_name = 'C',
			arg_data = &config, arg = OptionArg.FILENAME,
			description = "Specify alternate configuration file",
			arg_description = "FILENAME"
		}, OptionEntry() {
			long_name = "distdir", short_name = 'D',
			arg_data = &distdir, arg = OptionArg.FILENAME,
			description = "Override XSPS_DISTDIR config setting",
			arg_description = "DIRECTORY"
		}, OptionEntry() {
			long_name = "masterdir", short_name = 'm',
			arg_data = &masterdir, arg = OptionArg.FILENAME,
			description = "Override XSPS_MASTERDIR config setting",
			arg_description = "DIRECTORY"
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
		template_filenames = new string[templates.length];
		for (int i = 1; i < argv.length; i++) {
			templates[i-1] = argv[i];
			template_filenames[i-1]
				= @"srcpkgs/$(templates[i-1])/template.json";
		}
		return;
	}

	Log.error("%s error: You must specify at least one PACKAGE", XSPS_NAME);
	usage();
}

private void
usage()
{
	stdout.printf("%s", context.get_help(false, null));
	exit(EXIT_FAILURE);
}


} /* class Arg */
