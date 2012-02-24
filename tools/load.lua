-- Loads a template

function load_template(name)
	local srcpkgs = xsps.getcfg("SRCPKGS")
	local tmpl = {
		pkg = xsps.inc(srcpkgs.."/"..name.."/template.lua"),
		func = xsps.inc(srcpkgs.."/"..name.."/functions.lua")
	}
	return tmpl
end

return load_template
