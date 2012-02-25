-- Configuration file for XSPS.

return {
	SRCPKGS_URL = "git://github.com/davehome/xsps-packages.git",
	SRCPKGS = "$HOME/src/xsps/srcpkgs",
	MASTERDIR = "$HOME/src/xsps/chroot",
	HOSTDIR = "$HOME/src/xsps/host",
	CFLAGS = "-O2 -pipe -mtune=generic",
	CXXFLAGS = "$CFLAGS",
	CCACHE = true,
	LDFLAGS = "-Wl,--as-needed",
	MAKEJOBS = 10,
	COMPRESS_CMD = "xz",
	COMPRESS_LEVEL = 9,
	PREFER_BINPKG_DEPS = true,
	USE_CAPABILITIES = true
}
