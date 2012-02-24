-- Function definitions for 'stuff'

return {

	pre_configure = function(xsps, pkg)
		local custom_message ="[%s] This is just a test to show how this works."

		xsps.log.info(string.format(custom_message, pkg.name))
		xsps.log.warn("This is a warning message that can be triggered anywhere")

	end,

	subpackages = {

		["libstuff"] = function(xsps, pkg)
			xsps.vinstall("usr/lib/*.so", "0755", "usr/lib")
		end,

		["libstuff_devel"] = function(xsps, pkg)
			xsps.vinstall("usr/lib/*.a", "0644", "usr/lib")
			xsps.vmove("usr/include", "usr")
		end

	}
}
