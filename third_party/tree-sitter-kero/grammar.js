/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

module.exports = grammar({
  name: "kero",

  rules: {
    // TODO: add the actual grammar rules
    source_file: ($) => "hello",
    source_file2: ($) => "world",
  },
});
