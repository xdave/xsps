-- GNU configure build style

return {

	do_fetch = function(xsps, pkg)
		xsps.ni("gnu_configure do_fetch")
	end,

	do_extract = function(xsps, pkg)
		xsps.ni("gnu_configure do_extract")
	end,

	do_configure = function(xsps, pkg)
		xsps.ni("gnu_configure do_configure")
	end,

	do_build = function(xsps, pkg)
		xsps.ni("gnu_configure do_build")
	end,

	do_install = function(xsps, pkg)
		xsps.ni("gnu_configure do_install")
	end
}
