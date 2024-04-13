/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

module.exports = grammar({
  name: "kero",

  word: ($) => $.identifier,

  precedences: ($) => [["binary_equality"]],

  rules: {
    module: ($) => sep($._statement, ";"),

    _statement: ($) => choice($._expression_statement),
    _expression_statement: ($) => $._expression,
    _expression: ($) =>
      choice(
        $.parenthesized_expression,
        $.binary_expression,
        $.identifier,
        $.true,
        $.false
      ),

    binary_expression: ($) =>
      choice(
        prec.left(
          "binary_equality",
          seq(
            field("left", $._expression),
            field("operator", "=="),
            field("right", $._expression)
          )
        ),
        prec.left(
          "binary_equality",
          seq(
            field("left", $._expression),
            field("operator", "!="),
            field("right", $._expression)
          )
        )
      ),

    parenthesized_expression: ($) => seq("(", $._expression, ")"),

    type: ($) => choice("bool"),

    identifier: ($) => /[a-zA-Z_][a-zA-Z0-9_]*/,
    true: ($) => "true",
    false: ($) => "false",
  },
});

function sep1(rule, sep) {
  return seq(rule, repeat(seq(sep, rule)));
}

function sep(rule, sep) {
  return optional(sep1(rule, sep));
}
