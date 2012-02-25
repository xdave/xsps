require "tools/lapp/lapp"
module(...,package.seeall)

function lapp.callback(parm,arg,args)
	log:debug("+"..parm..": "..arg)
end

Args = class(function(a)
	a.items = lapp [[usage: xsps.lua [-c file] action template
 -c,--config	(default ./config/xsps.lua)	Config file to use
 <action>	(string)			Action to perform
 <template>	(default bootstrap)		Template
]]
end)

