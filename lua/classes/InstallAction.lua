module(..., package.seeall)

InstallAction = class(function(self, base, template)
	log:info(template, "install")
	log:debug("Not implemented", "InstallAction")
end)
