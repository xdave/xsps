#include <common.h>
#include <Log.h>
#include <parse_args.h>
#include <classes/Args.h>

xsps::LogTypes LOG;

int main(int argc, char **argv) {
	xsps::Log(LOG.WARN, "This program is currently useless.", "FIXME");

	// This is a test
	xsps::Args a(argc, argv);
	for(auto item : a.args) {
		xsps::Log(LOG.DEBUG, item, "Args");
	}

	// parse_args will be deprecated soon.
	return xsps::parse_args(LOG, argc, argv);
	//return 0;
}
