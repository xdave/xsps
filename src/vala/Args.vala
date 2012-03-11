namespace xsps {

public class Args {

	public OptionContext context;
	public OptionEntry[] entries;
	public string usage_text;
	public string progname;

	public bool debug;
	public string config;
	public string distdir;
	public string masterdir;
	public string package;
	public string option;
	public string template;
	public string template_filename;

	/* Constructor */
	public
	Args()
	{
		debug = false;
		config = XSPS_CONFIG;

		usage_text = "[-d] [-c FILE] [-x DIR] [-m DIR]\n" +
			"	[-p PKG] [-o OPTION] TEMPLATE";
		entries = {
			OptionEntry() {
				long_name = "debug", short_name = 'd',
				arg_data = &debug,
				description = "Show debugging messages"
			}, OptionEntry() {
				long_name = "config", short_name = 'c',
				arg_data = &config, arg = OptionArg.STRING,
				description = "Specify configuration: FILE"
			}, OptionEntry() {
				long_name = "distdir", short_name = 'x',
				arg_data = &distdir, arg = OptionArg.STRING,
				description = "Specify distdir: DIR"
			}, OptionEntry() {
				long_name = "masterdir", short_name = 'm',
				arg_data = &masterdir, arg = OptionArg.STRING,
				description = "Specify masterdir: DIR"
			}, OptionEntry() {
				long_name = "package", short_name = 'p',
				arg_data = &package, arg = OptionArg.STRING,
				description = "Specify PKG to use for TEMPLATE"
			}, OptionEntry() {
				long_name = "option", short_name = 'o',
				arg_data = &option, arg = OptionArg.STRING,
				description = "Show OPTION from PKG/TEMPLATE"
			}, OptionEntry()
		}; // entries[]

		context = new OptionContext(usage_text);
		context.add_main_entries(entries, null);
	}

	public void
	parse(string[] argv)
	{
		progname = argv[0];
		try {
			context.parse(ref argv);
		} catch (OptionError error) {
			Log.error("%s error: %s", progname, error.message);
			usage();
		}

		if (argv.length > 1) {
			template = argv[1];
			template_filename = @"srcpkgs/$template/template";
			return;
		}

		Log.error("%s error: You must specify a TEMPLATE", progname);
		usage();
	}

	private void
	usage()
	{
		stderr.printf("%s", context.get_help(false, null));
		Process.exit(EXIT_FAILURE);
	}

} // class Args

} // naemspace Args
