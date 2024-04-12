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
      prec(
        3,
        choice(
          seq("-", $._expression),
          seq("!", $._expression)
          // ...
        )
      ),

    binary_expression: ($) =>
      choice(
        prec.left(2, seq($._expression, "*", $._expression)),
        prec.left(1, seq($._expression, "+", $._expression))
        // ...
      ),
  },
});
