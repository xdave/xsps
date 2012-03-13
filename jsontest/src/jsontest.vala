namespace xsps {

int
main(string[] argv)
{
	Json.Parser parser;
	Template template;

	if (argv.length < 2) {
		stderr.printf("Usage: %s <path/template.json>\n", argv[0]);
		return 1;
	}

	try {
		parser = new Json.Parser();
		parser.load_from_file(argv[1]);
	} catch (Error error) {
		stdout.printf("Unable to parse `%s`: %s\n",
		    argv[1], error.message);
		return 1;
	}

	print_root(parser.get_root(), stdout);
	//print_root(parser.get_root().get_object().get_member("packages"), stdout);

	return 0;
}

} // namespace xsps
