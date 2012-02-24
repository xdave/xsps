#!/usr/bin/lua

require "posix"

local argv = arg

xsps = {
	format = {
		env = function(str)
			return string.gsub(str, "%$(%w+)", os.getenv)
		end,
		tbl = function(str, t)
			return string.gsub(str, "%$(%w+)", t)
		end
	},
	CONFIGDIR = function()
		local working = posix.dirname(arg[0])
		return xsps.format.env(working.."/config")
	end,
	getcfg = function(opt)
		local str = xsps.format.env(xsps.config[opt])
		str = xsps.format.tbl(str, xsps.config)
		return str
	end
}

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

xsps.process_queue = {}

xsps.config = xsps.inc(xsps.CONFIGDIR().."/xsps.lua")
xsps.color = xsps.inc(xsps.getcfg("TOOLSDIR").."/misc/color.lua")
xsps.log = xsps.inc(xsps.getcfg("TOOLSDIR").."/misc/log.lua")
xsps.shell = xsps.inc(xsps.getcfg("TOOLSDIR").."/shell/shell.lua")
xsps.vinstall = xsps.inc(xsps.getcfg("TOOLSDIR").."/shell/vinstall.lua")
xsps.vmove = xsps.inc(xsps.getcfg("TOOLSDIR").."/shell/vmove.lua")
xsps.load_template = xsps.inc(xsps.getcfg("TOOLSDIR").."/tmpl/load.lua")
xsps.process = xsps.inc(xsps.getcfg("TOOLSDIR").."/tmpl/process.lua")

xsps.ni = function(msg)
	local err = "[%s] Not implemented yet!"
	xsps.log.err(string.format(err, msg))
end

