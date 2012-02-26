module(..., package.seeall)

Action = class(function(self, template)
	log:err("Don't use the Action class directly, subclass it.",
		"Action")
	os.exit(1)
end)
