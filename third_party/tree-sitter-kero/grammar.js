/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

module.exports = grammar({
  name: "kero",
  rules: {
    source_file: ($) => repeat($._expression),

    identifier: ($) => /[a-zA-Z_]\w*/,

    _expression: ($) =>
      choice(
        $.identifier,
        $.unary_expression,
        $.binary_expression
        // ...
      ),

    unary_expression: ($) =>
      choice(
        seq("-", $._expression),
        seq("!", $._expression)
        // ...
      ),

    binary_expression: ($) =>
      choice(
        seq($._expression, "*", $._expression),
        seq($._expression, "+", $._expression)
        // ...
      ),
  },
});
