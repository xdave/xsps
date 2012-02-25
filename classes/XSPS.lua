module(..., package.seeall)

-- global
XSPS = class(function(self)
	self.actions = { install = "InstallAction" }
end)

function XSPS:action(action, template)
	if self.actions[action] then
		local c = self.actions[action]
		-- TODO: load template here and pass to new()
		local a = new(c, get_class("Action"), template)
		return a
	else
		log:err("unknown action `"..action.."'. aborting.")
		os.exit(1)
	end
end

function XSPS:format(str, tbl)
	str = string.gsub(str, "%${(%w+)}", os.getenv)
	str = string.gsub(str, "%$(%w+)", os.getenv)
	str = string.gsub(str, "%${(%w+)}", tbl)
	str = string.gsub(str, "%$(%w+)", tbl)
	return str
end

function XSPS:set_config(file)
	local res, err, conf
	log:debug("using configuration file `"..file.."'")
	if not posix.access(file, "r") then
		log:err("cannot open configuration file `"..file.."'")
		os.exit(1)
	else
		res, err = loadfile(file)
		if err then
			log:err("an error occurred while reading `"..file.."'")
			os.exit(1)
		end
	end
	conf = res()
	self.config = {}
	table.foreach(conf, function(k,v)
		if type(v) == "string" then
			local value = self:format(v, conf)
			self.config[k] = value
		end
	end)
end
