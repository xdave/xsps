public class Env {

public string pattern;
public Regex regex;
public MatchInfo info;

public
Env()
{
	info = null;

	try {
		regex = new Regex("{(.[^{}]*)}",
			RegexCompileFlags.DOTALL	|
			RegexCompileFlags.OPTIMIZE	|
			RegexCompileFlags.EXTENDED	|
			RegexCompileFlags.MULTILINE);
	} catch (RegexError error) {
		stderr.printf("[ENV-REGEX] %s\n", error.message);
		exit(EXIT_FAILURE);
	}

}

public static string
get(string key)
{
	return Environment.get_variable(key);
}

public static void
set(string key, string value)
{
	Environment.set_variable(key, value, true);
}

public string
replace(string input)
{
	string tmp = input;
	string[] matches = null;
	string key = null;
	string env = null;
	string repl = null;

	regex.match(tmp, RegexMatchFlags.NEWLINE_ANY, out info);

	/* stderr.printf("[DEBUG] [ENV-REPL] INPUT: %s\n", input); */

	try {
		while (info.matches()) {
			matches = info.fetch_all();
			key = matches[0];
			env = get(matches[1]);
			repl = (env != null) ? env : ("$" + key);
			tmp = tmp.replace("$" + key, repl);
			matches = null;
			info.next();
		}

	} catch (RegexError error) {
		stderr.printf("[ENV-REPL] %s\n", error.message);
		exit(EXIT_FAILURE);
	}

	/* stderr.printf("[DEBUG] [ENV-REPL] OUTPUT: %s\n", tmp); */

	return (tmp != null) ? tmp : input;
}

public string
convert(string name, string value)
{
	Env.set(name, xhp.env.replace(value));
	return xhp.env.replace(Env.get(name));
}

} /* class Env */
