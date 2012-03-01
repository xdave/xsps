#include "log.h"
#include "arg.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
	char *build = NULL;
	char *config = malloc(strlen(XSPS_CONFIG_DIR)+strlen("xsps.json")+3);
	sprintf(config, "%s/xsps.json", XSPS_CONFIG_DIR);

	xsps_log_init();
	xsps_args_parse(argc, argv, &xsps_enable_debug_log, &config, &build);

	free(config);

	return 0;
}
