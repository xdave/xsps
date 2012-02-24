-- Main code for processing a template.

local process = function(tmpl, action)

	if (not action) or (action == "all")	then
	elseif	action == "pre_fetch"		then
	elseif	action == "fetch"		then
	elseif	action == "verify"		then
	elseif	action == "pre_configure"	then
	elseif	action == "configure"		then
	elseif	action == "post_configure"	then
	elseif	action == "pre_build"		then
	elseif	action == "build"		then
	elseif	action == "pre_install"		then
	elseif	action == "install"		then
	elseif	action == "post_install"	then
	end

	local pkg = xsps.load_template(tmpl)
	if not xsps.process_queue[pkg] then
		table.insert(xsps.process_queue, pkg)
	end
	

end

return process
