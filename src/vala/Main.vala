public static xsps.Main xhp;

namespace xsps {

/* Program entry point */
private static int
main(string[] argv)
{
	int rv;
	xhp = new Main(argv);

	rv = config_init();
	if (rv == EXIT_FAILURE) Process.exit(rv);

	rv = process_template();
	if (rv == EXIT_FAILURE) Process.exit(rv);

	Process.exit(rv);
}

public class Main {
	public Args args;
	public Config config;

	public GLib.FileStream log_file;
	public string log_filename;

	public
	Main(string[] argv)
	{
		this.args = new Args();
		this.args.parse(argv);
		this.config = new Config();
	}
} // class Main

} // namespace xsps
