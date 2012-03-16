public struct XHP {

public Env? env;
public Arg? arg;
public Config? config;

public
XHP()
{
	env = new Env();
	arg = new Arg();
	config = new Config();
}

} /* struct XHP */

/* global access */
public XHP xhp; 
