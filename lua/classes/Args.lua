local lapp = require "tools/lapp/lapp"
module(...,package.seeall)

function lapp.callback(parm, arg, args)
	log:debug("+"..parm..": "..arg)
end

Args = class(function(self)
	local str = [[Usage: xsps.lua [options].. ACTION [TEMPLATE]
Options:
  -c,--config	(default config/xsps.lua)	Config file to use
  <action>	(string)			One of 'install', 'remove',
							or 'clean'
  <template>	(default bootstrap)		Template

  Use -h or --help to display this message.
]]
	local help_text = string.format(str, PROGNAME)
	self.items = lapp(help_text)
end)

