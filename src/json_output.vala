public void
print_root(Json.Node root, FileStream *target = stdout)
{
	print_node(root, target);
	target->printf("\n");
}

public void
print_any(Json.Parser parser, string name, FileStream *target = stdout)
{
	Json.Node node = parser.get_root().get_object().get_member(name);
	if (node == null) {
		stderr.printf("Error: Invalid section: '%s'\n", name);
		Process.exit(1);
	}
	print_node(node, target);
	target->printf("\n");
}

public void
print_node(Json.Node node, FileStream *target, int level = 0)
{
	Variant v = 0;
	Variant.Class vc = 0;
	Json.NodeType type = node.get_node_type();
	switch (type) {
	case Json.NodeType.NULL:
		target->printf("null");
		break;
	case Json.NodeType.VALUE:
		try { v = Json.gvariant_deserialize(node, null); }
		catch (Error error) {
			stderr.printf("Error!: %s\n", error.message);
			Process.exit(1);
		}
		vc = v.classify();
		if ((vc == Variant.Class.BOOLEAN) ||
		    (vc == Variant.Class.INT64)   ||
		    (vc == Variant.Class.INT32))
			target->printf("%s", v.print(false));
		if (vc == Variant.Class.STRING)
			target->printf("\"%s\"", v.get_string());
		break;
	case Json.NodeType.ARRAY:
		target->printf("[\n");
		print_array(node.get_array(), target, level + 1);
		print_indent(target, level);
		target->printf("]");
		break;
	case Json.NodeType.OBJECT:
		target->printf("{\n");
		print_object(node.get_object(), target, level + 1);
		print_indent(target, level);
		target->printf("}");
		break;
	}
}

public void
print_object(Json.Object obj, FileStream *target, int level = 0)
{
	uint objsize = obj.get_size();
	uint i = 0;
	obj.foreach_member((o, name, node) => {
		print_indent(target, level);
		target->printf("\"%s\": ", name);
		print_node(node, target, level);
		if (i < (objsize - 1)) { target->printf(","); }
		target->printf("\n");
		i++;
	});
}

public void
print_array(Json.Array arr, FileStream *target, int level = 0)
{
	uint arrsize = arr.get_length();
	arr.foreach_element((a, i, node) => {
		print_indent(target, level);
		print_node(node, target, level);
		if (i < (arrsize - 1)) { target->printf(","); }
		target->printf("\n");
	});
}

public void
print_indent(FileStream *target, int level)
{
	string indent = "";
	if (level > 0) {
		for (int i = 0; i < level; i++) {
			indent += "  ";
		}
	}
	target->printf(indent);
}
