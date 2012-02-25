module(..., package.seeall)

-- global
Color = class(function(self)
	self.off = 0 self.bold = 1 self.italic = 3 self.underline = 4
	self.inverse = 7 self.hidden = 8 self.black = 30 self.red = 31
	self.green = 32 self.yellow = 33 self.blue = 34 self.magenta = 35
	self.cyan = 36 self.white = 37 self.black_bg = 40 self.red_bg = 41
	self.green_bg = 42 self.yellow_bg = 43 self.blue_bg = 44
	self.magenta_bg = 45 self.cyan_bg = 46 self.white_bg = 47
end)

function Color:get(color)
	return string.format("%s%s%s%s",
		string.char(27), "[", self[color], "m")
end
