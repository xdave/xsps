local lapp = require "tools/lapp/lapp"
module(...,package.seeall)

function lapp.callback(parm,arg,args)
	log:debug("+"..parm..": "..arg)
end

Args = class(function(a)
	a.items = lapp [[Usage: xsps.lua [options].. ACTION [TEMPLATE]
Options:
  -c,--config	(default ./config/xsps.lua) ==> Config file to use
  <action>	(string) ==> One of 'install', 'remove', 'clean'
  <template>	(default bootstrap) ==> Template

  Use -h or --help to display this message.
]]
end)

