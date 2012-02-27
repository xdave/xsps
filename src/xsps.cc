#include "classes/Args.h"

int main(int argc, char **argv) {
	xsps::Args args(argc, argv);
	int ret = args.parse();
	/* TODO: validate the arguments and run specified actions */
	ret = args.validate();
	return ret;
}
