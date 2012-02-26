#include <common.h>
#include <String.h>

using namespace xsps;

int main(int argc, char **argv) {
	LOG(log.Info, "I'd rather use libconfuse for templates/config");
	LOG(log.Info, "The template functions can stay in shell.");
	LOG(log.Debug, "some text", "foo context");
	LOG(log.Debug, "Plus I'm gonna try out some c++0x/11", "rofl");
	LOG(log.Warn, "This will be so much faster than Lua.");
	LOG(log.Err, "this is an error", "bar context");
	LOG(log.Info, "But it was a fake one.", "bye");

	return 0;
}
