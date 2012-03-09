[CCode (cheader_filename = "xsps.h")]
namespace xsps {
	[CCode (cname = "xhp_t")]
	public extern struct xhp_t {
		int init;
	}
	[CCode (cname = "xhp")]
	public extern xhp_t xhp;
	[CCode (cname = "xhp_init")]
	public extern void init(int argc, string[] argv);
	[CCode (cname = "xhp_free")]
	public extern void free();
	[CCode (cname = "log_all")]
	public static extern void log_all(int color, GLib.FileStream target,
					  string name, string fmt, ...);
	[CCode (cname = "process_template")]
	public extern void process_template();
}
