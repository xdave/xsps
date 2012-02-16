#!/usr/bin/env node

// These are Node's standard stuff
var fs = require('fs');
var util = require('util');
var path = require('path');

var XSPS = {
	check_error: function(err) {
		if (err) {
			console.log(err.message);
			process.exit(1);
		}
	},
	process_args: function() {
		//TODO
		console.log(this.ARGS);
	},
};

XSPS.RUN_PATH = __dirname;
XSPS.CONFIG_PATH = path.join(XSPS.RUN_PATH, "config");
XSPS.SPEC_PATH = path.join(XSPS.CONFIG_PATH, "spec");
XSPS.DEFAULT_SPEC = path.join(XSPS.SPEC_PATH, "void.json");
XSPS.SRCPKGS = path.join(XSPS.RUN_PATH, "srcpkgs");
XSPS.ARGS = process.argv.splice(2);

// test...
var foo_dir = path.join(XSPS.SRCPKGS, "foo"); 

var foo = {
	template: JSON.parse(fs.readFileSync(foo_dir + "/template.json")),
	funcs: require(foo_dir + "/functions")
};

// show the parsed result
console.log(util.inspect(foo.template, false, 10, true));
console.log(util.inspect(foo.funcs, false, 10, true));
