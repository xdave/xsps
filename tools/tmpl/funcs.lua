return {
	fetch = function()
		xsps.ni("fetch")
	end,
	verify = function() xsps.ni("verify") end,
	extract = function() xsps.ni("extract") end,
	pre_configure = function() xsps.ni("pre_configure") end,
	configure = function() xsps.ni("configure") end,
	post_configure = function() xsps.ni("post_configure") end,
	pre_build = function() xsps.ni("pre_build") end,
	build = function() xsps.ni("build") end,
	post_build = function() xsps.ni("post_build") end,
	pre_install = function() xsps.ni("pre_install") end,
	install = function() xsps.ni("install") end,
	post_install = function() xsps.ni("post_install") end
}
