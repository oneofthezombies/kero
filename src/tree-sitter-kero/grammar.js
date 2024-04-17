/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

module.exports = grammar({
  name: "kero",

  word: ($) => $.identifier,

  precedences: ($) => [
    ["multiplicative", "additive", "equality", "logical_and", "logical_or"],
  ],

  rules: {
    module: ($) => optional(sep1($._statement, ";")),

    _statement: ($) =>
      choice(
        $._expression_statement,
        $.if_statement,
        $.extern_function_declaration,
        $.function_definition
      ),

    _expression_statement: ($) => $._expression,

    _expression: ($) =>
      choice(
        $._parenthesized_expression,
        $.binary_expression,
        $.identifier,
        $.string_literal,
        $.number,
        $.true,
        $.false,
        $.call_expression
      ),

    binary_expression: ($) => {
      const precedence_operators = [
        { precedence: "multiplicative", operator: "*" },
        { precedence: "multiplicative", operator: "/" },
        { precedence: "multiplicative", operator: "%" },
        { precedence: "additive", operator: "+" },
        { precedence: "additive", operator: "-" },
        { precedence: "equality", operator: "==" },
        { precedence: "equality", operator: "!=" },
        { precedence: "logical_and", operator: "&&" },
        { precedence: "logical_or", operator: "||" },
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

    extern_function_declaration: ($) =>
      seq(
        "extern",
        $.string_literal,
        "fn",
        $.identifier,
        $.parameter_clause,
        optional($.return_clause)
      ),

    parameter_clause: ($) => seq("(", optional(sep1($.parameter, ",")), ")"),

    parameter: ($) => seq($.identifier, ":", $.type),

    return_clause: ($) => seq("->", $.type),

    call_expression: ($) => seq($.identifier, $.argument_clause),

    argument_clause: ($) => seq("(", optional(sep1($._expression, ",")), ")"),

    block: ($) => seq("{", optional(sep1($._statement, ";")), "}"),

    type: ($) => choice("bool", "number"),

    identifier: ($) => /[a-zA-Z_][a-zA-Z0-9_]*/,

    string_literal: ($) => /"[^"]*"/,

    number: ($) =>
      token(
        choice(
          /0|[1-9][0-9]*/,
          /0\.[0-9]+/,
          /[1-9][0-9]*\.[0-9]+/,
          /-[1-9][0-9]*/,
          /-0\.[0-9]+/,
          /-[1-9][0-9]*\.[0-9]+/
        )
      ),

    // Keywords
    // --------
    true: ($) => "true",
    false: ($) => "false",
  },
});

function sep1(rule, sep) {
  return seq(rule, repeat(seq(sep, rule)));
}
