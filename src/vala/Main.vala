public static xsps.Main xhp;

namespace xsps {

public class Main {
	public Args args;
	public Config config;

	public GLib.FileStream log_file;
	public string log_filename;

	public
	Main(string[] argv)
	{
		this.args = new Args();
		this.config = new Config();
		this.args.parse(argv);
	}

	static int
	main(string[] argv)
	{
		xhp = new Main(argv);
		process_template();
		config_init();
		Process.exit(EXIT_SUCCESS);
	}


} // class Main

} // namespace xsps
