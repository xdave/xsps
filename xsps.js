#!/usr/bin/node

/* Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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
