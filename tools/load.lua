-- Loads a template using xsps.inc()
-- Stores the template vars as 'pkg' and
-- it's related functions into 'func' in a
-- table and returns the table.
function load_template(name)
	local srcpkgs = xsps.getcfg("SRCPKGS")
	local tmpl = {
		pkg = xsps.inc(srcpkgs.."/"..name.."/template.lua"),
		func = xsps.inc(srcpkgs.."/"..name.."/functions.lua")
	}
	return tmpl
end

return load_template
