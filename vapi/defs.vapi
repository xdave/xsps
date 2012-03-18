/* 
 * Defined as compiler flags 
 */

/* Program name */
[CCode (cname = "XSPS_NAME")]
public extern const string XSPS_NAME;

/* Major version number */
[CCode (cname = "XSPS_MAJOR")]
public extern const string XSPS_MAJOR;

/* Minor version number */
[CCode (cname = "XSPS_MINOR")]
public extern const string XSPS_MINOR;

/* Compile-time determined global configuration directory */
[CCode (cname = "XSPS_CONFIG_DIR")]
public extern const string XSPS_CONFIG_DIR;

/* Compile-time determined global configuration file */
[CCode (cname = "XSPS_CONFIG")]
public extern const string XSPS_CONFIG;
