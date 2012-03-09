namespace XSPS {

	int
	main(string[] argv)
	{
		xhp_t xhp;
		xhp = xsps_init(argv.length, argv);
		log_all(36, stderr, "DEBUG", "This is a test!");
		process_template();
		xsps_free(xhp);
		return 0;
	}
}
