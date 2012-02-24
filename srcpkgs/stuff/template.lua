-- Template file for 'stuff'

return {
	name = "stuff", 
	version = "0.0.1",
	revision = 2,
	homepage = "http://stellarbox.co.cc",
	license = "GPL-3",
	maintainer = "davehome <davehome@redthumb.info.tm>",
	summary = "This is the stuff program",
	description = { "The stuff program lorem ipsum blah blah blah and stuff liek",
			"that or somethign like that. And all that kind of stuff",
			"like that."
	},
	distfiles = { "$homepage/$name-$version.tar.xz" },
	patches = { "fix_stuff.patch" },
	checksums = {
		"d99089a63a6cfc1a6a4a026be9278028d47d224088d24b1853acb67e95683a15",
		"89a63a6cfc1a6a4a026be9278028d47d2249278028d47d224088d24b1853acbe"
	},
	deps = {
		build = { "sed", "coreutils", "libfoo-devel", "libbar-devel" },
		run = { "libfoo.so.3", "libbar.so.1", "ld-linux.so.2", "libc.so.6" },
		full = { "hicolor-icon-theme", "desktop-file-utils" }
	},
	build_options = {
		build_style = "gnu_configure",
		subpackages = { "libstuff", "libstuff-devel" },
		gtk_iconcache_dirs = "$USR_SHARE/icons/hicolor",
		configure_args = "--with-foo=blah"
	}
}

