namespace xsps {
	[CCode (cheader_filename = "xsps_c.h", cname = "CONFIG_DIR")]
	public extern const string CONFIG_DIR;

	[CCode (cheader_filename = "xsps_c.h", cname = "CONFIG")]
	public extern const string CONFIG;

	[CCode (cheader_filename = "xsps_c.h", cname = "config_init")]
	public extern int config_init();

	[CCode (cheader_filename = "xsps_c.h", cname = "process_template")]
	public extern int process_template();
} /* namespace xsps */
