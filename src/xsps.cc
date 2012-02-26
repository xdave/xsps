#include <common.h>
#include <Log.h>
#include <parse_args.h>
#include <classes/Args.h>

int main(int argc, char **argv) {
	// This is a test
	xsps::Args args(argc, argv);
	for(auto item : args.args) {
		fprintf(stdout, "%s\n", item);
	}

	xsps::LogTypes LOG;
	xsps::Log(LOG.WARN, "This program is currently useless.", "FIXME");
	return xsps::parse_args(LOG, argc, argv);
}
