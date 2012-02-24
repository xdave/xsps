shell = function(cmd, tmpl)
	-- change working directory to template's srcdir here
	local status, ret = pcall(os.execute, cmd)
	if ret == 0 then
		return ret
	else
		xsps.log.err("Error executing '"..cmd.."'.")
		xsps.log.err("Return code: "..ret)
	end
	return ret
end

return shell
