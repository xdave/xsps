-- Template file for 'stuff'

return {
	name = "stuff", 
	version = "0.0.1",
	revision = 2,
	homepage = "http://example.com",
	license = "GPL-3",
	maintainer = "davehome <davehome@redthumb.info.tm>",
	summary = "This is the stuff program",
	description = "The stuff program lorem ipsum blah blah blah and stuff liek"
			.. " that or somethign like that. And all that kind of stuff"
			.. " like that.",
	distfiles = { "$homepage/$name-$version.tar.xz" },
	checksums = { "d99089a63a6cfc1a6a4a026be9278028d47d224088d24b1853acb67e95683a15" },
	deps = {
		build = { "libfoo-devel", "this", "should", "print", "in", "order!" },
		run = { "libfoo.so.3" },
		full = { "hicolor-icon-theme", "desktop-file-utils" }
	},
	buildstyle = "gnu",
	options = {
		subpackages = { "libstuff", "libstuff-devel" },
		gtk_iconcache_dirs = "/usr/share/icons/hicolor",
		configure_args = [[--with-foo=blah]]
	}
	
}

