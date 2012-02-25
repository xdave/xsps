#!/usr/bin/lua

-- Globals 
-- Creates the globals: 'class', 'get_class', and 'new'
require "tools/class"
-- Creates the global: 'posix'
require "posix"
DEBUG = true
xsps = new("XSPS")
log = new("Log")
args = new("Args")

-- test
xsps:set_config(args.items.config)
xsps:action(args.items.action, args.items.template)


