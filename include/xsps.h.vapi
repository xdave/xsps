namespace XSPS {
	[CCode (cname = "xhp_t", cheader_filename = "xsps.h")]
	public extern struct xhp_t {}
	[CCode (cname = "xhp_init", cheader_filename = "xsps.h")]
	public extern unowned xhp_t xsps_init(int argc, string[] argv);
	[CCode (cname = "xhp_free", cheader_filename = "xsps.h")]
	public extern unowned void xsps_free(xhp_t xhp);
	[CCode (cname = "log_all", cheader_filename = "xsps.h")]
	public static extern void log_all(int color, GLib.FileStream target,
					  string name, string fmt, ...);
	[CCode (cname = "process_template", cheader_filename = "xsps.h")]
	public extern void process_template();
}
