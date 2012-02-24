#!/usr/bin/lua

require "posix"

-- This is the toplevel scope
xsps = {}

-- Store program arguments for later
xsps.argv = arg

-- Show command line usage
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

-- Takes a string formatted with $var items, finds
-- their corresponding value in the provided table,
-- and replaces those values in the string.
-- Returns the replacement string.
xsps.format = function(str, tbl)
	return string.gsub(str, "%$(%w+)", tbl)
end

-- Gets the configuration directory
-- currently based on dir xsps in run in
xsps.CONFIGDIR = xsps.format(posix.dirname(xsps.argv[0])
		.."/config", os.getenv)

-- Uses xsps.format to find env vars and
-- Vars within the config itself to format
-- the configuration.  Returns requested
-- config option
xsps.getcfg = function(opt)
	local str = xsps.config[opt]
	str = xsps.format(str, os.getenv)
	str = xsps.format(str, xsps.config)
	return str
end

-- Prints out an error and exits.  Uses the
-- available logging API if available.
xsps.err = function(msg)
	if type(xsps.log) == "table" then
		xsps.log.err(msg)
	else
		print(msg)
	end
	os.exit(1)
end

-- Includes a lua file and stores whatever
-- value it returns into the return value
-- of this function. Checks for errors.
xsps.inc = function(file)
	local status, err, func
	status, err = posix.access(file, "r")
	if not status then
		xsps.err(err)
	end
	func, err = loadfile(file)
	if err then
		errstring = "An error occurred while loading '%s': %s"
		xsps.err(string.format(errstring, file, err))
	end
	return func()
end

-- Load the configuration
xsps.config = xsps.inc(xsps.CONFIGDIR.."/xsps.lua")

-- Loads a tool using xsps.inc() from the
-- current tools dir specified in the config.
xsps.tool = function(t)
	local s = "%s/%s.lua"
	local tool = string.format(s, xsps.getcfg("TOOLSDIR"), t)
	return xsps.inc(tool)
end

-- Loads several tools specified in an 'array'.
xsps.load_tools = function(t)
	table.foreach(t, function(k,v)
		xsps[v] = xsps.tool(v)
	end)
end

-- An 'array' of tools to load
xsps.load_tools({ "color", "log", "shell", "vinstall",
		"vmove", "load", "process" })

-- Dummy function to remind me to implement certain
-- features.
xsps.ni = function(msg)
	local err = "[%s] Not implemented yet!"
	xsps.log.err(string.format(err, msg))
end

-- This table will get filled up as a queue
-- of tasks to perform.
xsps.tasks = {}

