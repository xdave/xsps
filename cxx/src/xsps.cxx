#include <common.h>
#include <Log.h>

using namespace xsps;

int main(int argc, char **argv) {
	LogTypes l;

	Log(l.INFO, "Should use confuse/JSON for templates/config");
	Log(l.INFO, "The template functions can stay in shell.");
	Log(l.DEBUG, "some text", "foo context");
	Log(l.DEBUG, "Plus I'm gonna try out some c++0x/11", "rofl");
	Log(l.WARN, "This will be so much faster than Lua.");
	Log(l.ERROR, "this is an error", "bar context");
	Log(l.INFO, "But it was a fake one.", "bye");

	return 0;
}
