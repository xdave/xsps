public static xsps.Main xhp;

namespace xsps {

/* Program entry point */
private static int
main(string[] argv)
{
	xhp = new Main(argv);
	config_init();
	process_template();
	Process.exit(EXIT_SUCCESS);
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
