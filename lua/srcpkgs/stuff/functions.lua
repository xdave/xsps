-- Function definitions for 'stuff'

return {

	pre_configure = function(xsps, pkg)
		xsps.ni("stuff pre_configure")
	end,

	subpkgs = {

		["libstuff"] = function(xsps, pkg)
			xsps.vinstall("usr/lib/*.so", "0755", "usr/lib")
		end,

		["libstuff-devel"] = function(xsps, pkg)
			xsps.vinstall("usr/lib/*.a", "0644", "usr/lib")
			xsps.vmove("usr/include", "usr")
		end

	}
}
