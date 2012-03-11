
namespace xsps {

public static string?
getenv(string name)
{
	return Environment.get_variable(name);
}

public static bool
setenv(string name, string value, bool overwrite)
{
	return Environment.set_variable(name, value, overwrite);
}


} // namespace xsps
