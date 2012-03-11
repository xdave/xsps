[CCode (cname = "CONFIG_DIR", cheader_filename = "xsps_c.h")]
public extern const string CONFIG_DIR;

[CCode (cname = "CONFIG", cheader_filename = "xsps_c.h")]
public extern const string CONFIG;

[CCode (cname = "config_init", cheader_filename = "xsps_c.h")]
public extern int config_init();

[CCode (cname = "process_template", cheader_filename = "xsps_c.h")]
public extern void process_template();

/* Misc system stuff (will reorganize this later */
[CCode (cheader_filename = "stdlib.h", cname = "EXIT_SUCCESS")]
public extern int EXIT_SUCCESS;

[CCode (cheader_filename = "stdlib.h", cname = "EXIT_FAILURE")]
public extern int EXIT_FAILURE;
