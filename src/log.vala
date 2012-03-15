public enum Color {
	OFF = 0, BOLD = 1, UNDERLINE = 4, ESC = 27, RED = 31, YELLOW = 33,
	BLUE = 34, MAGENTA = 35, CYAN = 36, WHITE = 37
}

namespace Log {

	public static void
	info(string fmt, ...)
	{
		Log.all(Color.WHITE, stdout, "INFO ", fmt.vprintf(va_list()));
	}

	public static void
	warn(string fmt, ...)
	{
		Log.all(Color.YELLOW, stdout, "WARN ", fmt.vprintf(va_list()));
	}

	public static void
	debug(string fmt, ...)
	{
		if ((xhp.arg != null) && xhp.arg.debug)
			Log.all(Color.CYAN, stderr, "DEBUG",
			    fmt.vprintf(va_list()));
	}

	public static void
	error(string fmt, ...)
	{
		Log.all(Color.RED, stderr, "ERROR", fmt.vprintf(va_list()));
	}

	public static void
	plain(FileStream *target, string fmt, ...)
	{
		target->vprintf(fmt, va_list());
	}

	public static void
	custom(string name, Color color, string fmt, ...)
	{
		Log.all(color, stdout, name, fmt.vprintf(va_list()));
	}

	public static void
	all(Color color, FileStream *target, string name, string message)
	{
		target->printf("%c[%dm%c[%dm[%s] => %s%c[%dm\n",
		    Color.ESC, Color.BOLD, Color.ESC, color,
		    name, message, Color.ESC, Color.OFF);
	}

} /* namespace Log */
