#!/usr/bin/lua

require "posix"

xsps = {}

xsps.argv = arg

xsps.show_help = function()
	local n = posix.basename(xsps.argv[0])
	local msg = [[
usage: %s [-h] [-c FILE] [<action> PACKAGE]
 -h		display this help message.
 -c FILE	load alternate configuration from FILE.

 <action>	is one of: `fetch', `verify', `extract',
		`configure', `build' or `install`.
		NOTE: only `test' is implemented right now.

PACKAGE		is the package template you would like to
		perform <action> on.]]
	print(string.format(msg, n))
	os.exit(1)
end

xsps.format = function(str, tbl)
	return string.gsub(str, "%$(%w+)", tbl)
end

-- currently based on dir xsps in run in
xsps.CONFIGDIR = xsps.format(posix.dirname(arg[0])
		.."/config", os.getenv)

xsps.getcfg = function(opt)
	local str = xsps.config[opt]
	str = xsps.format(str, os.getenv)
	str = xsps.format(str, xsps.config)
	return str
end

xsps.err = function(msg)
	if type(xsps.log) == "table" then
		xsps.log.err(msg)
	else
		print(msg)
	end
	os.exit(1)
end

xsps.inc = function(file)
	local status, err, func
	status, err = posix.access(file, "r")
	if not status then
		xsps.err(err)
	end
	func, err = loadfile(file)
	if err then
		errstring = "An error occurred while loading '%s': %s"
		xbps.err(string.format(errstring, file, err))
	end
	return func()
end

xsps.config = xsps.inc(xsps.CONFIGDIR.."/xsps.lua")

xsps.tool = function(t)
	local s = "%s/%s.lua"
	local tool = string.format(s, xsps.getcfg("TOOLSDIR"), t)
	return xsps.inc(tool)
end

xsps.load_tools = function(t)
	table.foreach(t, function(k,v)
		xsps[v] = xsps.tool(v)
	end)
end

xsps.load_tools({ "color", "log", "shell", "vinstall",
		"vmove", "load", "process" })

xsps.ni = function(msg)
	local err = "[%s] Not implemented yet!"
	xsps.log.err(string.format(err, msg))
end

xsps.tasks = {}

