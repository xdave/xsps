/* 
 * Misc system stuff
 */

[CCode (cheader_filename = "stdlib.h", cname = "exit")]
public extern void exit(int status);

[CCode (cheader_filename = "stdlib.h", cname = "EXIT_SUCCESS")]
public extern const int EXIT_SUCCESS;

[CCode (cheader_filename = "stdlib.h", cname = "EXIT_FAILURE")]
public extern const int EXIT_FAILURE;
