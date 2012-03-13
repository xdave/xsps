namespace xsps {

	public struct Package {
		string pkgname;
		string arch;
		string desc;
		bool noverifyrdeps;
		bool nonfree;
		string[] depends;
		string[] replaces;
		string[] conflicts;
		string[] files;
		string[] conf_files;
		string[] gtk_iconcache_dirs;
		string[] system_accounts;
		string[] systemd_services;
	}

} // namespace 
