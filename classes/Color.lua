module(..., package.seeall)

-- global
Color = class(function(c)
	c.off = 0 c.bold = 1 c.italic = 3 c.underline = 4
	c.inverse = 7 c.hidden = 8 c.black = 30 c.red = 31
	c.green = 32 c.yellow = 33 c.blue = 34 c.magenta = 35
	c.cyan = 36 c.white = 37 c.black_bg = 40 c.red_bg = 41
	c.green_bg = 42 c.yellow_bg = 43 c.blue_bg = 44
	c.magenta_bg = 45 c.cyan_bg = 46 c.white_bg = 47
end)

function Color:get(color)
	return string.format("%s%s%s%s",
		string.char(27), "[", self[color], "m")
end
