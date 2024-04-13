/// <reference types="tree-sitter-cli/dsl" />
// @ts-check

module.exports = grammar({
  name: "kero",

  word: ($) => $.identifier,

  precedences: ($) => [["binary_equality", "logical_and", "logical_or"]],

  rules: {
    module: ($) => sep($._statement, ";"),

    _statement: ($) => choice($._expression_statement),
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
      const prece_ops = [
        { prece: "binary_equality", op: $.equal },
        { prece: "binary_equality", op: $.not_equal },
        { prece: "logical_and", op: $.logical_and },
        { prece: "logical_or", op: $.logical_or },
      ];
      const rules = prece_ops.map(({ prece, op }) =>
        prec.left(
          prece,
          seq(
            field("lhs", $._expression),
            field("op", op),
            field("rhs", $._expression)
          )
        )
      );
      return choice(...rules);
    },

    _parenthesized_expression: ($) => seq("(", $._expression, ")"),

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
