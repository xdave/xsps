#include <stdlib.h> // for EXIT_SUCCESS
#include <classes/Log.h>

using namespace xsps;

int main(int argc, char **argv) {
	Log log;
	log.print(Log::Info, "Hi there");
	log.print(Log::Info, "some text", "foo");
	log.print(Log::Err, "this is an error");
	return EXIT_SUCCESS;
}
