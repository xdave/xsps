public static xsps.Main xhp;

namespace xsps {

public class Main {
	public Args args;

	public GLib.FileStream log_file;
	public string log_filename;

	public Main(string[] argv) {
		this.args = new Args();
		this.args.parse(argv);
	}

	static int
	main(string[] argv)
	{
		xhp = new Main(argv);
		process_template();
		Process.exit(EXIT_SUCCESS);
	}


} // class Main

} // namespace xsps
