using Confuse;

public Option STR(string k, string d) {
	return Option() {
		name = (char[])k, type = Confuse.Type.STR,
		def = DefaultValue() { str = (char[])d }
	};
}

public Option END() {
	return Option() { name = null };
}

int
main(string[] argv)
{
	string f = "fictional.conf";
	string HOME = Environment.get_variable("HOME");

	Option[] opts = {
		STR("XSPS_DISTDIR", @"$HOME/xsps"),
		END()
	};

	Config cfg = new Config(opts, Flag.NONE);

	switch (cfg.parse(f)) {
	case CFG_FILE_ERROR:
		stderr.printf("%s WARNING: '%s' not found.\n", argv[0], f);
		break;
	case CFG_PARSE_ERROR:
		return 1;
	case CFG_SUCCESS:
	default:
		break;
	}

	for (int i = 0; opts[i].name != null; i++) {
		string name = (string)opts[i].name;
		stdout.printf("%s = %s\n", name, cfg.getstr(name));
	}

	return 0;
}
