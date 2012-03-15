namespace xsps {

public class DistFile {
	Template top		{ get; set; }

	public string arch	{ get; set; default = "all"; }
	public string uri	{ get; set; default = "http://NULL/"; }
	public string sha256	{ get; set; default = "EMPTY"; }

	public
	DistFile(Template from)
	{
		top = from;
	}
}

} // namespace xsps
