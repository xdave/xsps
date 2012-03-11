[CCode (cheader_filename = "xsps_c.h")]
namespace xsps {
	[CCode (cname = "CONFIG_DIR")]
	public extern const string CONFIG_DIR;

	[CCode (cname = "CONFIG")]
	public extern const string CONFIG;

	[CCode (cname = "config_init")]
	public extern int config_init();

	[CCode (cname = "process_template")]
	public extern int process_template();
} /* namespace xsps */
