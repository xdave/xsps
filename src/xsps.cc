#include <common.h>
#include <Log.h>
#include <classes/Args.h>

xsps::LogTypes LOG;

int main(int argc, char **argv) {
	xsps::Args a(argc, argv, LOG);
	return 0;
}
