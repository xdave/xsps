int
main(string[] argv)
{
	xhp = XHP();
	xhp.arg.parse(argv);
	xhp.config.load();
	return (EXIT_SUCCESS);
}
