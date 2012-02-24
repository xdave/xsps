-- log functions

log = {
	info = function(msg)
		log.all(xsps.color("white"), "INFO ", msg)
	end,

	warn = function(msg)
		log.all(xsps.color("yellow"), "WARN ", msg)
	end,

	err = function(msg)
		log.all(xsps.color("red"), "ERROR", msg)
	end,

	all = function(c, kind, msg)
		local bold = xsps.color("bold")
		local off = xsps.color("off")
		local s = "%s%s[%s] => %s%s"
		print(string.format(s, bold, c, kind, msg, off))
	end
}

return log
