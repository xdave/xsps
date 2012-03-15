namespace xsps {

public class Template : Object {
	private Json.Parser parser;

	public Json.Object root {
		get { return parser.get_root().get_object(); }
	}
	public string source {
		get { return get_string("source"); }
	}
	public string version {
		get { return get_string("version"); }
	}
	public int64 revision {
		get { return get_int("revision"); }
		set { set_int("revision", value); }
	}
	public string homepage {
		get { return get_string("homepage"); }
	}
	public string maintainer {
		get { return get_string("maintainer"); }
	}
	public string license {
		get { return get_string("license"); }
	}
	public string description {
		get { return get_string("description"); }
	}
	public string build_style {
		get { return get_string("build-style"); }
	}
	public string required_abi {
		get { return get_string("required-abi"); }
	}
	public bool noextract {
		get { return get_bool("noextract"); }
	}
	public Package[] packages	{ get; private set; } // TODO
	public DistFile[] distfiles	{ get; private set; } // TODO
	public string[] make_depends	{ get; private set; } // TODO

	public
	Template(Json.Parser parser)
	{
		this.parser = parser;

		/* Oooh, property change notification!
		 * 'revision_changed' is the "Slot" which is called when
		 * when the revision property changes. */
		this.notify["revision"].connect(revision_changed);
	}

	/* "Slot" which is called when the revision is changed. */
	private void
	revision_changed(Object source, ParamSpec param)
	{
		/* Could get this function to return a lambda of which it's
		 * execution is deferred (to display this message later). */
		int64 r = (source as Template).revision;
		stdout.printf("%s: changed to '%lld'.\n", param.name, r);
	}

	public unowned string
	get_string(string property)
	{
		return root.get_member(property).get_string();
	}

	public unowned int64
	get_int(string property)
	{
		return root.get_member(property).get_int();
	}

	public unowned bool
	get_bool(string property)
	{
		return root.get_member(property).get_boolean();
	}

	public void
	set_int(string property, int64 value)
	{
		root.get_member(property).set_int(value);
	}
}

} // namespace xsps

