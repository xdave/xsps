using Gee;

namespace xsps {

public class Template : Object {
	private Json.Object root;

	public HashMap<string,string> globals;
	public Package[] packages;
	public DistFile[] distfiles;
	public string[] make_depends;
	public bool noextract;

	public string[]
	global_keys()
	{
		return { "source", "version", "revision", "homepage",
			"maintainer", "license", "description",
			"build_style", "required_abi" };
	}

	public
	Template(Json.Parser parser)
	{
		globals = new HashMap<string,string>();

		root = parser.get_root().get_object();
		root.foreach_member((o, name, node) => {
			foreach (string v in global_keys())
				if (name == v) 
					globals.set(name, node.get_string());
			if (name == "noextract")
				noextract = node.get_boolean();
			if (name == "make_depends") {
				Json.Array arr = node.get_array();
				uint arr_len = arr.get_length();
				make_depends = new string[arr_len];
				node.get_array()
					.foreach_element(set_make_depends);
			} else if (name == "distfiles") {
				Json.Array arr = node.get_array();
				uint arr_len = arr.get_length();
				distfiles = new DistFile[arr_len];
				node.get_array().foreach_element(set_distfiles);
			} else if (name == "packages") {
				/* TODO! */
			}
		});
	}

	public void
	set_make_depends(Json.Array deps, uint index, Json.Node node)
	{
		string dep = node.get_string();
		make_depends[index] = dep;
	}

	public void
	set_distfiles(Json.Array dfiles, uint index, Json.Node node)
	{
		Json.Object obj = node.get_object();
		string arch   = obj.get_member("arch").get_string();
		string uri    = obj.get_member("uri").get_string();
		string sha256 = obj.get_member("sha256").get_string();
		distfiles[index] = { arch, uri, sha256 };
	}
}

} // namespace xsps

