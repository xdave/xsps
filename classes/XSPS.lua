module(..., package.seeall)

-- global
XSPS = class(function(x)
	
end)

function XSPS:set_config(file)
	log:info("using configuration file `"..file.."'")
	if not posix.access(file, "r") then
		log:err("cannot open configuration file `"..file.."'")
		os.exit(1)
	end
	log:debug("XSPS:set_config() half-implemented.")
end
