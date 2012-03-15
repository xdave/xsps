namespace xsps {

public string pkgname;
public string section;

int
main(string[] argv)
{
	Json.Parser parser;

	if (argv.length < 3) {
		stderr.printf("Usage: %s pkgname section\n", argv[0]);
		return 1;
	}

	pkgname = argv[1];
	section = argv[2];

	try {
		parser = new Json.Parser();
		parser.load_from_file(@"srcpkgs/$pkgname/template.json");
	} catch (Error error) {
		stdout.printf("Unable to parse `%s`: %s\n",
		    argv[1], error.message);
		return 1;
	}

	//var t = new Template(parser);

	print_any(parser, section);

	return 0;
}

} // namespace xsps
