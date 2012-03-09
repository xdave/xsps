using GLib;

namespace xsps {

public void
usage(ref OptionContext context)
{
	stdout.printf("%s", context.get_help(false, null));
}

public void
args(string[] argv)
{
	bool d = false;
	OptionContext context;

	OptionEntry entries[2] = {
		OptionEntry() {
			long_name = "debug", short_name = 'd', arg_data = &d,
			description = "Show debug msgs"
		}, OptionEntry()
	};

	context = new OptionContext("- Build XBPS Binary packages");
	context.add_main_entries(entries, null);

	try {
		context.parse(ref argv);
	} catch (OptionError error) {
		stdout.printf("%s: %s\n", argv[0], error.message);
		usage(ref context);
	}

	if (argv.length == 1) usage(ref context);
}

} // namespace XSPS
