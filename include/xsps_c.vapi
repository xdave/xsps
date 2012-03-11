[CCode (cname = "XSPS_CONFIG_DIR", cheader_filename = "xsps_c.h")]
public extern const string XSPS_CONFIG_DIR;

[CCode (cname = "XSPS_CONFIG", cheader_filename = "xsps_c.h")]
public extern const string XSPS_CONFIG;

[CCode (cname = "struct config_t", cheader_filename = "xsps_c.h")]
public extern struct config_t {
	public string distdir;
	public string repourl;
	public string masterdir;
	public string hostdir;
	public string cflags;
	public string cxxflags;
	public string ldflags;
	public string compress_cmd;
	public bool ccache;
	public uint16 compress_level;
	public uint16 makejobs;
}

[CCode (cname = "process_template", cheader_filename = "xsps_c.h")]
public extern void process_template();

/* Misc system stuff (will reorganize this later */
[CCode (cheader_filename = "stdlib.h", cname = "EXIT_SUCCESS")]
public extern int EXIT_SUCCESS;

[CCode (cheader_filename = "stdlib.h", cname = "EXIT_FAILURE")]
public extern int EXIT_FAILURE;
