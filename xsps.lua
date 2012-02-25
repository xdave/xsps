#!/usr/bin/lua
require "tools/class"
posix = require "posix"

-- Globals 
DEBUG = true
xsps = new("XSPS")
log = new("Log")
args = new("Args")

-- test
xsps:set_config(args.items.config)
log:info(args.items.action.."ing `"..args.items.template.."'")


--- weee
log:err("i can't do anything yet! ohno!")

local rpipe, wpipe = posix.pipe()
posix.write(wpipe, "test")
local bytes, data = posix.read(rpipe, 4)
assert(data == "test")
posix.close(rpipe)
posix.close(wpipe)

print(data, bytes)
