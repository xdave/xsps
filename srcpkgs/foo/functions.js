module.exports = {

	pre_configure: function() {
		// etc...
	},

	// common functions like this could be done
	// somewhere else for this build style

	configure: function() {
		// pseudoexample.. rofl	
		XSPS.exec(this, "./configure " + this.configure_args);
	},

	build: function() {
		XSPS.exec(this, "make -j" + this.MAKEJOBS);
	},

	install: function() {
		XSPS.exec(this, "make -j" + this.MAKEJOBS + " DESTDIR=" + this.DESTDIR + " install");
	},

	subpkgs: {
		"libfoo": {
			install: function() {
				// another pseudo-example
				XSPS.vinstall("usr/lib/*.so", "0755", "usr/lib");
			}
		},
		"libfoo-devel": {
			install: function() {
				XSPS.vinstall("usr/lib/*.a", "usr/lib");
				XSPS.vmove("usr/include", "usr");
				XSPS.vmove("usr/lib/pkgconfig", "usr/lib");
			}
		}
	}

};
