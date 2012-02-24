#!/usr/bin/lua

require "posix"

local argv = arg

local show_help = function()
	local n = posix.basename(arg[0])
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

local load_config = function(f)
	print("TODO: load config: "..f)
end

local tasks = {}

local options = {
	["-h"] = show_help,
	["-c"] = load_config,
	["test"] = "process_template"
}

if not arg[1] then show_help() end

for i, opt in ipairs(arg) do
	local option = options[opt]
	if option then
		if option == load_config then
			if arg[i+1] then
				option(arg[i+1])
				table.remove(arg, i)
				table.remove(arg, i+1)
			else
				show_help()
			end
		end
		if option == show_help then
			show_help()
		end
		if option == "process_template" then
			if arg[i+1] then
				table.insert(tasks, { action = "test", tmpl = arg[i+1] })
				table.remove(arg, i)
				table.remove(arg, i+1)
			end
		end
	else
		show_help()
	end
end

table.foreach(tasks, function(k,v)
	print(k, v.action, v.tmpl)
end)

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
		-- currently based on dir xsps in run in
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

xsps.process_queue = {}


