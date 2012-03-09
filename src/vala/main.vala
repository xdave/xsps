using GLib;

void
main(string[] argv)
{
	//xsps.args(argv);
	xsps.init(argv.length, argv);
	xsps.process_template();
	xsps.free();
}
