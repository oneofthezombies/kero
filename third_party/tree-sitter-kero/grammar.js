/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

module.exports = grammar({
  name: "kero",

  word: ($) => $.identifier,

  precedences: ($) => [["binary_equality", "logical_and", "logical_or"]],

  rules: {
    module: ($) => sep($._statement, ";"),

    _statement: ($) => choice($._expression_statement, $.if_statement),
    _expression_statement: ($) => $._expression,
    _expression: ($) =>
      choice(
        $._parenthesized_expression,
        $.binary_expression,
        $.identifier,
        $.true,
        $.false
      ),

    binary_expression: ($) => {
      const precedence_operators = [
        { precedence: "binary_equality", operator: $.equal },
        { precedence: "binary_equality", operator: $.not_equal },
        { precedence: "logical_and", operator: $.logical_and },
        { precedence: "logical_or", operator: $.logical_or },
      ];
      const rules = precedence_operators.map(({ precedence, operator }) =>
        prec.left(
          precedence,
          seq(
            field("left", $._expression),
            field("operator", operator),
            field("right", $._expression)
          )
        )
      );
      return choice(...rules);
    },

    _parenthesized_expression: ($) => seq("(", $._expression, ")"),

    if_statement: ($) =>
      seq(
        "if",
        field("if_condition", $._expression),
        "{",
        field("if_body", sep($._statement, ";")),
        "}",
        optional(
          seq(
            "else",
            choice(
              seq("{", field("else_body", sep($._statement, ";")), "}"),
              field("else_if_statement", $.if_statement)
            )
          )
        )
      ),

    type: ($) => choice("bool"),

    identifier: ($) => /[a-zA-Z_][a-zA-Z0-9_]*/,

    // Keywords
    // --------
    true: ($) => "true",
    false: ($) => "false",

    // Punctuators
    // --------
    equal: ($) => "==",
    not_equal: ($) => "!=",
    logical_and: ($) => "&&",
    logical_or: ($) => "||",
  },
});

function sep1(rule, sep) {
  return seq(rule, repeat(seq(sep, rule)));
}

function sep(rule, sep) {
  return optional(sep1(rule, sep));
}
