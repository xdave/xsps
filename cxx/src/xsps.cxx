#include <stdlib.h> // for EXIT_SUCCESS
#include <classes/Log.h>

using namespace xsps;

int main(int argc, char **argv) {
	Log log;
	log.print(Log::Info, "Hi there");
	log.print(Log::Debug, "some text", "foo context");
	log.print(Log::Err, "this is an error", "bar context");
	return EXIT_SUCCESS;
}
