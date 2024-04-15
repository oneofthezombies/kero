/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

module.exports = grammar({
  name: "kero",

  word: ($) => $.identifier,

  precedences: ($) => [["binary_equality", "logical_and", "logical_or"]],

  rules: {
    module: ($) => optional(sep1($._statement, ";")),

    _statement: ($) =>
      choice($._expression_statement, $.if_statement, $.function_definition),

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
        prec.left(precedence, seq($._expression, operator, $._expression))
      );
      return choice(...rules);
    },

    _parenthesized_expression: ($) => seq("(", $._expression, ")"),

    if_statement: ($) =>
      seq("if", $.condition_expression, $.block, optional($.else_clause)),

    condition_expression: ($) => $._expression,

    else_clause: ($) => seq("else", choice($.if_statement, $.block)),

    function_definition: ($) =>
      seq(
        "fn",
        $.identifier,
        $.parameter_clause,
        optional($.return_clause),
        $.block
      ),

    parameter_clause: ($) => seq("(", optional(sep1($.parameter, ",")), ")"),

    parameter: ($) => seq($.identifier, ":", $.type),

    return_clause: ($) => seq("->", $.type),

    block: ($) => seq("{", optional(sep1($._statement, ";")), "}"),

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
