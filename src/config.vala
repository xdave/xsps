using Gee;

public class Config {

private Json.Parser parser;

public string file;
public HashMap<string,string> map;

public
Config()
{
	file = XSPS_CONFIG;
	parser = new Json.Parser();
}

public void
load()
{
	if (xhp.arg.config != null) {
		file = xhp.arg.config;
		Log.info("Using alternate configuration file: `%s'...", file);
	}

	try {
		parser.load_from_file(file);
	} catch (Error error) {
		Log.error("[CONFIG] %s", error.message);
		exit(EXIT_FAILURE);
	}

	map = new HashMap<string,string>();
	parser.get_root().get_object().foreach_member((o, name, node) => {
		string repl = null;
		string value = node.get_string();
		if (value == null) {
			Log.error("[CONFIG] `%s' is not set! Exiting...", name);
			exit(EXIT_FAILURE);
		}
		repl = xhp.env.convert(name, value);
		Log.debug("[CONFIG] %s = %s", name, repl);
		map.set(name, repl);
	});

}

} /* class Config */
