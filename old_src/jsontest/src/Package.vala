namespace xsps {

public class Package {
	Template top			{ get; set; }

	string pkgname			{ get; set; default = "EMPTY"; }
	string arch			{ get; set; default = "all"; }
	string desc			{ get; set; default = "EMPTY"; }
	bool noverifyrdeps		{ get; set; default = false; }
	bool nonfree			{ get; set; default = false; }

	string[] depends		{ get; set; }
	string[] replaces		{ get; set; }
	string[] conflicts		{ get; set; }
	string[] files			{ get; set; }
	string[] conf_files		{ get; set; }
	string[] gtk_iconcache_dirs	{ get; set; }
	string[] system_accounts	{ get; set; }
	string[] systemd_services	{ get; set; }

	public
	Package(Template from)
	{
		top = from;
	}
}

} // namespace 
