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

function Log:all(kind, msg, context)
	local context = context or "main"
	local fmt = "%s[%s] => [%s] %s%s"
	local c = self.color:get(self.mapping[kind][1])
	local b = self.color:get("bold")
	local o = self.color:get("off")
	local h = self.mapping[kind][2]
	print(string.format(fmt, c..b, h, context, msg, o))
end

function Log:info(msg, context) self:all("info", msg, context) end

function Log:warn(msg, context) self:all("warn", msg, context) end

function Log:debug(msg, context)
	if DEBUG == true then
		self:all("debug", msg, context)
	end
end

function Log:err(msg, context) self:all("err", msg, context) end

