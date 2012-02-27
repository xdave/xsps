#include "classes/Args.h"

int main(int argc, char **argv) {
	xsps::Args a(argc, argv);
	return a.parse();
}
