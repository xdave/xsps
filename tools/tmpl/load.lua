-- Loads a template

function load_template(name)
	local tmpl = xsps.inc("srcpkgs/"..name.."/template.lua")
	tmpl.func = xsps.inc("srcpkgs/"..name.."/functions.lua")
	table.foreach(xsps.tmpl_funcs, function(fname, tfunc)
		if not tmpl.func[fname] then
			tmpl.func[fname] = tfunc
		end
	end)
	return tmpl
end

return load_template
