[CCode (cheader = "confuse.h")]
namespace Confuse {
	[SimpleType]
	[CCode (cname = "struct cfg_t")]
	public extern struct Cfg {
		public extern string name;
		public Cfg();
	}
	[SimpleType]
	[CCode (cname = "struct cfg_opt_t")]
	public extern struct Opt {
		public extern string name;
		public Opt();
	}
} /* namespace Confuse */
