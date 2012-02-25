module(..., package.seeall)

-- private
local formats = {
	info = { "white", "INFO " },
	warn = { "yellow", "WARN " },
	debug = { "cyan", "DEBUG" },
	err = { "red", "ERROR" }
}

-- global
Log = class(function(log)
	log.me = log
	log.color = new("Color")
	log.mapping = formats 
end)

function Log:all(kind, msg)
	local fmt = "%s[%s] => %s%s"
	local c = self.color:get(self.mapping[kind][1])
	local b = self.color:get("bold")
	local o = self.color:get("off")
	local h = self.mapping[kind][2]
	print(string.format(fmt, c..b, h, msg, o))
end

function Log:info(msg) self:all("info", msg) end

function Log:warn(msg) self:all("warn", msg) end

function Log:debug(msg)
	if DEBUG == true then
		self:all("debug", msg)
	end
end

function Log:err(msg) self:all("err", msg) end

