public enum Color {
	OFF = 0, BOLD = 1, UNDERLINE = 4, ESC = 27, RED = 31, YELLOW = 33,
	BLUE = 34, MAGENTA = 35, CYAN = 36, WHITE = 37
}

namespace Log {

	public static void
	info(string fmt, ...)
	{
		var l = va_list();
		Log.all(Color.WHITE, stdout, "INFO ", fmt.vprintf(l));
	}

	public static void
	warn(string fmt, ...)
	{
		var l = va_list();
		Log.all(Color.YELLOW, stdout, "WARN ", fmt.vprintf(l));
	}

	public static void
	debug(string fmt, ...)
	{
		var l = va_list();
		if ((xhp.arg != null) && xhp.arg.debug)
			Log.all(Color.CYAN, stderr, "DEBUG", fmt.vprintf(l));
	}

	public static void
	error(string fmt, ...)
	{
		var l = va_list();
		Log.all(Color.RED, stderr, "ERROR", fmt.vprintf(l));
	}

	public static void
	plain(FileStream *target, string fmt, ...)
	{
		var l = va_list();
		target->vprintf(fmt, l);
	}

	public static void
	custom(string name, Color color, string fmt, ...)
	{
		var l = va_list();
		Log.all(color, stdout, name, fmt.vprintf(l));
	}

	public static void
	all(Color color, FileStream *target, string name, string message)
	{
		target->printf("%c[%dm%c[%dm[%s] => %s%c[%dm\n",
		    Color.ESC, Color.BOLD, Color.ESC, color,
		    name, message, Color.ESC, Color.OFF);
	}

} /* namespace Log */
