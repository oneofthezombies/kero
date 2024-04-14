#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 50
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 24
#define ALIAS_COUNT 0
#define TOKEN_COUNT 16
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 7
#define MAX_ALIAS_SEQUENCE_LENGTH 11
#define PRODUCTION_ID_COUNT 14

enum ts_symbol_identifiers {
  sym_identifier = 1,
  anon_sym_SEMI = 2,
  anon_sym_LPAREN = 3,
  anon_sym_RPAREN = 4,
  anon_sym_if = 5,
  anon_sym_LBRACE = 6,
  anon_sym_RBRACE = 7,
  anon_sym_else = 8,
  anon_sym_bool = 9,
  sym_true = 10,
  sym_false = 11,
  sym_equal = 12,
  sym_not_equal = 13,
  sym_logical_and = 14,
  sym_logical_or = 15,
  sym_module = 16,
  sym__statement = 17,
  sym__expression_statement = 18,
  sym__expression = 19,
  sym_binary_expression = 20,
  sym__parenthesized_expression = 21,
  sym_if_statement = 22,
  aux_sym_module_repeat1 = 23,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_identifier] = "identifier",
  [anon_sym_SEMI] = ";",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [anon_sym_if] = "if",
  [anon_sym_LBRACE] = "{",
  [anon_sym_RBRACE] = "}",
  [anon_sym_else] = "else",
  [anon_sym_bool] = "bool",
  [sym_true] = "true",
  [sym_false] = "false",
  [sym_equal] = "equal",
  [sym_not_equal] = "not_equal",
  [sym_logical_and] = "logical_and",
  [sym_logical_or] = "logical_or",
  [sym_module] = "module",
  [sym__statement] = "_statement",
  [sym__expression_statement] = "_expression_statement",
  [sym__expression] = "_expression",
  [sym_binary_expression] = "binary_expression",
  [sym__parenthesized_expression] = "_parenthesized_expression",
  [sym_if_statement] = "if_statement",
  [aux_sym_module_repeat1] = "module_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [sym_identifier] = sym_identifier,
  [anon_sym_SEMI] = anon_sym_SEMI,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [anon_sym_if] = anon_sym_if,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [anon_sym_else] = anon_sym_else,
  [anon_sym_bool] = anon_sym_bool,
  [sym_true] = sym_true,
  [sym_false] = sym_false,
  [sym_equal] = sym_equal,
  [sym_not_equal] = sym_not_equal,
  [sym_logical_and] = sym_logical_and,
  [sym_logical_or] = sym_logical_or,
  [sym_module] = sym_module,
  [sym__statement] = sym__statement,
  [sym__expression_statement] = sym__expression_statement,
  [sym__expression] = sym__expression,
  [sym_binary_expression] = sym_binary_expression,
  [sym__parenthesized_expression] = sym__parenthesized_expression,
  [sym_if_statement] = sym_if_statement,
  [aux_sym_module_repeat1] = aux_sym_module_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [sym_identifier] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_SEMI] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_if] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_else] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_bool] = {
    .visible = true,
    .named = false,
  },
  [sym_true] = {
    .visible = true,
    .named = true,
  },
  [sym_false] = {
    .visible = true,
    .named = true,
  },
  [sym_equal] = {
    .visible = true,
    .named = true,
  },
  [sym_not_equal] = {
    .visible = true,
    .named = true,
  },
  [sym_logical_and] = {
    .visible = true,
    .named = true,
  },
  [sym_logical_or] = {
    .visible = true,
    .named = true,
  },
  [sym_module] = {
    .visible = true,
    .named = true,
  },
  [sym__statement] = {
    .visible = false,
    .named = true,
  },
  [sym__expression_statement] = {
    .visible = false,
    .named = true,
  },
  [sym__expression] = {
    .visible = false,
    .named = true,
  },
  [sym_binary_expression] = {
    .visible = true,
    .named = true,
  },
  [sym__parenthesized_expression] = {
    .visible = false,
    .named = true,
  },
  [sym_if_statement] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_module_repeat1] = {
    .visible = false,
    .named = false,
  },
};

enum ts_field_identifiers {
  field_else_body = 1,
  field_else_if_statement = 2,
  field_if_body = 3,
  field_if_condition = 4,
  field_left = 5,
  field_operator = 6,
  field_right = 7,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_else_body] = "else_body",
  [field_else_if_statement] = "else_if_statement",
  [field_if_body] = "if_body",
  [field_if_condition] = "if_condition",
  [field_left] = "left",
  [field_operator] = "operator",
  [field_right] = "right",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 3},
  [2] = {.index = 3, .length = 1},
  [3] = {.index = 4, .length = 2},
  [4] = {.index = 6, .length = 2},
  [5] = {.index = 8, .length = 3},
  [6] = {.index = 11, .length = 3},
  [7] = {.index = 14, .length = 2},
  [8] = {.index = 16, .length = 4},
  [9] = {.index = 20, .length = 3},
  [10] = {.index = 23, .length = 3},
  [11] = {.index = 26, .length = 4},
  [12] = {.index = 30, .length = 4},
  [13] = {.index = 34, .length = 5},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_left, 0},
    {field_operator, 1},
    {field_right, 2},
  [3] =
    {field_if_condition, 1},
  [4] =
    {field_if_body, 3},
    {field_if_condition, 1},
  [6] =
    {field_else_if_statement, 5},
    {field_if_condition, 1},
  [8] =
    {field_if_body, 3},
    {field_if_body, 4},
    {field_if_condition, 1},
  [11] =
    {field_else_if_statement, 6},
    {field_if_body, 3},
    {field_if_condition, 1},
  [14] =
    {field_else_body, 6},
    {field_if_condition, 1},
  [16] =
    {field_else_if_statement, 7},
    {field_if_body, 3},
    {field_if_body, 4},
    {field_if_condition, 1},
  [20] =
    {field_else_body, 6},
    {field_else_body, 7},
    {field_if_condition, 1},
  [23] =
    {field_else_body, 7},
    {field_if_body, 3},
    {field_if_condition, 1},
  [26] =
    {field_else_body, 7},
    {field_else_body, 8},
    {field_if_body, 3},
    {field_if_condition, 1},
  [30] =
    {field_else_body, 8},
    {field_if_body, 3},
    {field_if_body, 4},
    {field_if_condition, 1},
  [34] =
    {field_else_body, 8},
    {field_else_body, 9},
    {field_if_body, 3},
    {field_if_body, 4},
    {field_if_condition, 1},
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static const uint16_t ts_non_terminal_alias_map[] = {
  0,
};

static const TSStateId ts_primary_state_ids[STATE_COUNT] = {
  [0] = 0,
  [1] = 1,
  [2] = 2,
  [3] = 3,
  [4] = 4,
  [5] = 5,
  [6] = 6,
  [7] = 7,
  [8] = 8,
  [9] = 9,
  [10] = 10,
  [11] = 11,
  [12] = 12,
  [13] = 13,
  [14] = 14,
  [15] = 15,
  [16] = 16,
  [17] = 17,
  [18] = 18,
  [19] = 19,
  [20] = 20,
  [21] = 21,
  [22] = 22,
  [23] = 23,
  [24] = 24,
  [25] = 25,
  [26] = 26,
  [27] = 27,
  [28] = 28,
  [29] = 29,
  [30] = 30,
  [31] = 31,
  [32] = 32,
  [33] = 33,
  [34] = 34,
  [35] = 35,
  [36] = 36,
  [37] = 37,
  [38] = 38,
  [39] = 39,
  [40] = 40,
  [41] = 41,
  [42] = 42,
  [43] = 43,
  [44] = 44,
  [45] = 45,
  [46] = 46,
  [47] = 47,
  [48] = 48,
  [49] = 49,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(5);
      if (lookahead == '!') ADVANCE(2);
      if (lookahead == '&') ADVANCE(1);
      if (lookahead == '(') ADVANCE(7);
      if (lookahead == ')') ADVANCE(8);
      if (lookahead == ';') ADVANCE(6);
      if (lookahead == '=') ADVANCE(3);
      if (lookahead == '{') ADVANCE(9);
      if (lookahead == '|') ADVANCE(4);
      if (lookahead == '}') ADVANCE(10);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(11);
      END_STATE();
    case 1:
      if (lookahead == '&') ADVANCE(14);
      END_STATE();
    case 2:
      if (lookahead == '=') ADVANCE(13);
      END_STATE();
    case 3:
      if (lookahead == '=') ADVANCE(12);
      END_STATE();
    case 4:
      if (lookahead == '|') ADVANCE(15);
      END_STATE();
    case 5:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 6:
      ACCEPT_TOKEN(anon_sym_SEMI);
      END_STATE();
    case 7:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 8:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 9:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 10:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 11:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(11);
      END_STATE();
    case 12:
      ACCEPT_TOKEN(sym_equal);
      END_STATE();
    case 13:
      ACCEPT_TOKEN(sym_not_equal);
      END_STATE();
    case 14:
      ACCEPT_TOKEN(sym_logical_and);
      END_STATE();
    case 15:
      ACCEPT_TOKEN(sym_logical_or);
      END_STATE();
    default:
      return false;
  }
}

static bool ts_lex_keywords(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (lookahead == 'b') ADVANCE(1);
      if (lookahead == 'e') ADVANCE(2);
      if (lookahead == 'f') ADVANCE(3);
      if (lookahead == 'i') ADVANCE(4);
      if (lookahead == 't') ADVANCE(5);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0)
      END_STATE();
    case 1:
      if (lookahead == 'o') ADVANCE(6);
      END_STATE();
    case 2:
      if (lookahead == 'l') ADVANCE(7);
      END_STATE();
    case 3:
      if (lookahead == 'a') ADVANCE(8);
      END_STATE();
    case 4:
      if (lookahead == 'f') ADVANCE(9);
      END_STATE();
    case 5:
      if (lookahead == 'r') ADVANCE(10);
      END_STATE();
    case 6:
      if (lookahead == 'o') ADVANCE(11);
      END_STATE();
    case 7:
      if (lookahead == 's') ADVANCE(12);
      END_STATE();
    case 8:
      if (lookahead == 'l') ADVANCE(13);
      END_STATE();
    case 9:
      ACCEPT_TOKEN(anon_sym_if);
      END_STATE();
    case 10:
      if (lookahead == 'u') ADVANCE(14);
      END_STATE();
    case 11:
      if (lookahead == 'l') ADVANCE(15);
      END_STATE();
    case 12:
      if (lookahead == 'e') ADVANCE(16);
      END_STATE();
    case 13:
      if (lookahead == 's') ADVANCE(17);
      END_STATE();
    case 14:
      if (lookahead == 'e') ADVANCE(18);
      END_STATE();
    case 15:
      ACCEPT_TOKEN(anon_sym_bool);
      END_STATE();
    case 16:
      ACCEPT_TOKEN(anon_sym_else);
      END_STATE();
    case 17:
      if (lookahead == 'e') ADVANCE(19);
      END_STATE();
    case 18:
      ACCEPT_TOKEN(sym_true);
      END_STATE();
    case 19:
      ACCEPT_TOKEN(sym_false);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 0},
  [2] = {.lex_state = 0},
  [3] = {.lex_state = 0},
  [4] = {.lex_state = 0},
  [5] = {.lex_state = 0},
  [6] = {.lex_state = 0},
  [7] = {.lex_state = 0},
  [8] = {.lex_state = 0},
  [9] = {.lex_state = 0},
  [10] = {.lex_state = 0},
  [11] = {.lex_state = 0},
  [12] = {.lex_state = 0},
  [13] = {.lex_state = 0},
  [14] = {.lex_state = 0},
  [15] = {.lex_state = 0},
  [16] = {.lex_state = 0},
  [17] = {.lex_state = 0},
  [18] = {.lex_state = 0},
  [19] = {.lex_state = 0},
  [20] = {.lex_state = 0},
  [21] = {.lex_state = 0},
  [22] = {.lex_state = 0},
  [23] = {.lex_state = 0},
  [24] = {.lex_state = 0},
  [25] = {.lex_state = 0},
  [26] = {.lex_state = 0},
  [27] = {.lex_state = 0},
  [28] = {.lex_state = 0},
  [29] = {.lex_state = 0},
  [30] = {.lex_state = 0},
  [31] = {.lex_state = 0},
  [32] = {.lex_state = 0},
  [33] = {.lex_state = 0},
  [34] = {.lex_state = 0},
  [35] = {.lex_state = 0},
  [36] = {.lex_state = 0},
  [37] = {.lex_state = 0},
  [38] = {.lex_state = 0},
  [39] = {.lex_state = 0},
  [40] = {.lex_state = 0},
  [41] = {.lex_state = 0},
  [42] = {.lex_state = 0},
  [43] = {.lex_state = 0},
  [44] = {.lex_state = 0},
  [45] = {.lex_state = 0},
  [46] = {.lex_state = 0},
  [47] = {.lex_state = 0},
  [48] = {.lex_state = 0},
  [49] = {.lex_state = 0},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym_identifier] = ACTIONS(1),
    [anon_sym_SEMI] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [anon_sym_if] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_else] = ACTIONS(1),
    [anon_sym_bool] = ACTIONS(1),
    [sym_true] = ACTIONS(1),
    [sym_false] = ACTIONS(1),
    [sym_equal] = ACTIONS(1),
    [sym_not_equal] = ACTIONS(1),
    [sym_logical_and] = ACTIONS(1),
    [sym_logical_or] = ACTIONS(1),
  },
  [1] = {
    [sym_module] = STATE(49),
    [sym__statement] = STATE(39),
    [sym__expression_statement] = STATE(39),
    [sym__expression] = STATE(12),
    [sym_binary_expression] = STATE(12),
    [sym__parenthesized_expression] = STATE(12),
    [sym_if_statement] = STATE(39),
    [ts_builtin_sym_end] = ACTIONS(3),
    [sym_identifier] = ACTIONS(5),
    [anon_sym_LPAREN] = ACTIONS(7),
    [anon_sym_if] = ACTIONS(9),
    [sym_true] = ACTIONS(5),
    [sym_false] = ACTIONS(5),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 6,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(9), 1,
      anon_sym_if,
    ACTIONS(11), 1,
      anon_sym_RBRACE,
    ACTIONS(5), 3,
      sym_identifier,
      sym_true,
      sym_false,
    STATE(12), 3,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
    STATE(36), 3,
      sym__statement,
      sym__expression_statement,
      sym_if_statement,
  [25] = 6,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(9), 1,
      anon_sym_if,
    ACTIONS(13), 1,
      anon_sym_RBRACE,
    ACTIONS(5), 3,
      sym_identifier,
      sym_true,
      sym_false,
    STATE(12), 3,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
    STATE(45), 3,
      sym__statement,
      sym__expression_statement,
      sym_if_statement,
  [50] = 6,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(9), 1,
      anon_sym_if,
    ACTIONS(15), 1,
      anon_sym_RBRACE,
    ACTIONS(5), 3,
      sym_identifier,
      sym_true,
      sym_false,
    STATE(12), 3,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
    STATE(38), 3,
      sym__statement,
      sym__expression_statement,
      sym_if_statement,
  [75] = 6,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(9), 1,
      anon_sym_if,
    ACTIONS(17), 1,
      anon_sym_RBRACE,
    ACTIONS(5), 3,
      sym_identifier,
      sym_true,
      sym_false,
    STATE(12), 3,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
    STATE(31), 3,
      sym__statement,
      sym__expression_statement,
      sym_if_statement,
  [100] = 5,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(9), 1,
      anon_sym_if,
    ACTIONS(5), 3,
      sym_identifier,
      sym_true,
      sym_false,
    STATE(12), 3,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
    STATE(29), 3,
      sym__statement,
      sym__expression_statement,
      sym_if_statement,
  [122] = 1,
    ACTIONS(19), 9,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      sym_equal,
      sym_not_equal,
      sym_logical_and,
      sym_logical_or,
  [134] = 1,
    ACTIONS(21), 9,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      sym_equal,
      sym_not_equal,
      sym_logical_and,
      sym_logical_or,
  [146] = 2,
    ACTIONS(23), 2,
      sym_equal,
      sym_not_equal,
    ACTIONS(21), 7,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      sym_logical_and,
      sym_logical_or,
  [160] = 3,
    ACTIONS(25), 1,
      sym_logical_and,
    ACTIONS(23), 2,
      sym_equal,
      sym_not_equal,
    ACTIONS(21), 6,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      sym_logical_or,
  [176] = 3,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(27), 3,
      sym_identifier,
      sym_true,
      sym_false,
    STATE(18), 3,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
  [190] = 4,
    ACTIONS(25), 1,
      sym_logical_and,
    ACTIONS(31), 1,
      sym_logical_or,
    ACTIONS(23), 2,
      sym_equal,
      sym_not_equal,
    ACTIONS(29), 3,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [206] = 3,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(33), 3,
      sym_identifier,
      sym_true,
      sym_false,
    STATE(8), 3,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
  [220] = 3,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(35), 3,
      sym_identifier,
      sym_true,
      sym_false,
    STATE(9), 3,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
  [234] = 3,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(37), 3,
      sym_identifier,
      sym_true,
      sym_false,
    STATE(10), 3,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
  [248] = 3,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(39), 3,
      sym_identifier,
      sym_true,
      sym_false,
    STATE(17), 3,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
  [262] = 4,
    ACTIONS(25), 1,
      sym_logical_and,
    ACTIONS(31), 1,
      sym_logical_or,
    ACTIONS(41), 1,
      anon_sym_RPAREN,
    ACTIONS(23), 2,
      sym_equal,
      sym_not_equal,
  [276] = 4,
    ACTIONS(25), 1,
      sym_logical_and,
    ACTIONS(31), 1,
      sym_logical_or,
    ACTIONS(43), 1,
      anon_sym_LBRACE,
    ACTIONS(23), 2,
      sym_equal,
      sym_not_equal,
  [290] = 2,
    ACTIONS(47), 1,
      anon_sym_else,
    ACTIONS(45), 3,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [299] = 2,
    ACTIONS(51), 1,
      anon_sym_else,
    ACTIONS(49), 3,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [308] = 3,
    ACTIONS(55), 1,
      anon_sym_SEMI,
    STATE(21), 1,
      aux_sym_module_repeat1,
    ACTIONS(53), 2,
      ts_builtin_sym_end,
      anon_sym_RBRACE,
  [319] = 2,
    ACTIONS(60), 1,
      anon_sym_else,
    ACTIONS(58), 3,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [328] = 3,
    ACTIONS(62), 1,
      anon_sym_if,
    ACTIONS(64), 1,
      anon_sym_LBRACE,
    STATE(27), 1,
      sym_if_statement,
  [338] = 3,
    ACTIONS(66), 1,
      anon_sym_SEMI,
    ACTIONS(68), 1,
      anon_sym_RBRACE,
    STATE(21), 1,
      aux_sym_module_repeat1,
  [348] = 3,
    ACTIONS(66), 1,
      anon_sym_SEMI,
    ACTIONS(70), 1,
      anon_sym_RBRACE,
    STATE(21), 1,
      aux_sym_module_repeat1,
  [358] = 1,
    ACTIONS(72), 3,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [364] = 1,
    ACTIONS(74), 3,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [370] = 3,
    ACTIONS(62), 1,
      anon_sym_if,
    ACTIONS(76), 1,
      anon_sym_LBRACE,
    STATE(33), 1,
      sym_if_statement,
  [380] = 1,
    ACTIONS(53), 3,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [386] = 1,
    ACTIONS(78), 3,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [392] = 3,
    ACTIONS(66), 1,
      anon_sym_SEMI,
    ACTIONS(80), 1,
      anon_sym_RBRACE,
    STATE(24), 1,
      aux_sym_module_repeat1,
  [402] = 3,
    ACTIONS(66), 1,
      anon_sym_SEMI,
    ACTIONS(82), 1,
      ts_builtin_sym_end,
    STATE(21), 1,
      aux_sym_module_repeat1,
  [412] = 1,
    ACTIONS(84), 3,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [418] = 3,
    ACTIONS(62), 1,
      anon_sym_if,
    ACTIONS(86), 1,
      anon_sym_LBRACE,
    STATE(40), 1,
      sym_if_statement,
  [428] = 1,
    ACTIONS(88), 3,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [434] = 3,
    ACTIONS(66), 1,
      anon_sym_SEMI,
    ACTIONS(90), 1,
      anon_sym_RBRACE,
    STATE(25), 1,
      aux_sym_module_repeat1,
  [444] = 1,
    ACTIONS(92), 3,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [450] = 3,
    ACTIONS(66), 1,
      anon_sym_SEMI,
    ACTIONS(94), 1,
      anon_sym_RBRACE,
    STATE(43), 1,
      aux_sym_module_repeat1,
  [460] = 3,
    ACTIONS(66), 1,
      anon_sym_SEMI,
    ACTIONS(96), 1,
      ts_builtin_sym_end,
    STATE(32), 1,
      aux_sym_module_repeat1,
  [470] = 1,
    ACTIONS(98), 3,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [476] = 1,
    ACTIONS(100), 3,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [482] = 1,
    ACTIONS(102), 3,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [488] = 3,
    ACTIONS(66), 1,
      anon_sym_SEMI,
    ACTIONS(104), 1,
      anon_sym_RBRACE,
    STATE(21), 1,
      aux_sym_module_repeat1,
  [498] = 1,
    ACTIONS(106), 3,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [504] = 3,
    ACTIONS(66), 1,
      anon_sym_SEMI,
    ACTIONS(108), 1,
      anon_sym_RBRACE,
    STATE(48), 1,
      aux_sym_module_repeat1,
  [514] = 1,
    ACTIONS(110), 3,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [520] = 1,
    ACTIONS(112), 3,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [526] = 3,
    ACTIONS(66), 1,
      anon_sym_SEMI,
    ACTIONS(114), 1,
      anon_sym_RBRACE,
    STATE(21), 1,
      aux_sym_module_repeat1,
  [536] = 1,
    ACTIONS(116), 1,
      ts_builtin_sym_end,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 25,
  [SMALL_STATE(4)] = 50,
  [SMALL_STATE(5)] = 75,
  [SMALL_STATE(6)] = 100,
  [SMALL_STATE(7)] = 122,
  [SMALL_STATE(8)] = 134,
  [SMALL_STATE(9)] = 146,
  [SMALL_STATE(10)] = 160,
  [SMALL_STATE(11)] = 176,
  [SMALL_STATE(12)] = 190,
  [SMALL_STATE(13)] = 206,
  [SMALL_STATE(14)] = 220,
  [SMALL_STATE(15)] = 234,
  [SMALL_STATE(16)] = 248,
  [SMALL_STATE(17)] = 262,
  [SMALL_STATE(18)] = 276,
  [SMALL_STATE(19)] = 290,
  [SMALL_STATE(20)] = 299,
  [SMALL_STATE(21)] = 308,
  [SMALL_STATE(22)] = 319,
  [SMALL_STATE(23)] = 328,
  [SMALL_STATE(24)] = 338,
  [SMALL_STATE(25)] = 348,
  [SMALL_STATE(26)] = 358,
  [SMALL_STATE(27)] = 364,
  [SMALL_STATE(28)] = 370,
  [SMALL_STATE(29)] = 380,
  [SMALL_STATE(30)] = 386,
  [SMALL_STATE(31)] = 392,
  [SMALL_STATE(32)] = 402,
  [SMALL_STATE(33)] = 412,
  [SMALL_STATE(34)] = 418,
  [SMALL_STATE(35)] = 428,
  [SMALL_STATE(36)] = 434,
  [SMALL_STATE(37)] = 444,
  [SMALL_STATE(38)] = 450,
  [SMALL_STATE(39)] = 460,
  [SMALL_STATE(40)] = 470,
  [SMALL_STATE(41)] = 476,
  [SMALL_STATE(42)] = 482,
  [SMALL_STATE(43)] = 488,
  [SMALL_STATE(44)] = 498,
  [SMALL_STATE(45)] = 504,
  [SMALL_STATE(46)] = 514,
  [SMALL_STATE(47)] = 520,
  [SMALL_STATE(48)] = 526,
  [SMALL_STATE(49)] = 536,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_module, 0),
  [5] = {.entry = {.count = 1, .reusable = false}}, SHIFT(12),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [9] = {.entry = {.count = 1, .reusable = false}}, SHIFT(11),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [19] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__parenthesized_expression, 3),
  [21] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binary_expression, 3, .production_id = 1),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [25] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [27] = {.entry = {.count = 1, .reusable = false}}, SHIFT(18),
  [29] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__expression_statement, 1),
  [31] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [33] = {.entry = {.count = 1, .reusable = false}}, SHIFT(8),
  [35] = {.entry = {.count = 1, .reusable = false}}, SHIFT(9),
  [37] = {.entry = {.count = 1, .reusable = false}}, SHIFT(10),
  [39] = {.entry = {.count = 1, .reusable = false}}, SHIFT(17),
  [41] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [43] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [45] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_if_statement, 6, .production_id = 5),
  [47] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [49] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_if_statement, 5, .production_id = 3),
  [51] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [53] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_module_repeat1, 2),
  [55] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_module_repeat1, 2), SHIFT_REPEAT(6),
  [58] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_if_statement, 4, .production_id = 2),
  [60] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [62] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [64] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [66] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [68] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [70] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [72] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_if_statement, 11, .production_id = 13),
  [74] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_if_statement, 6, .production_id = 4),
  [76] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [78] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_if_statement, 7, .production_id = 2),
  [80] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [82] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_module, 2),
  [84] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_if_statement, 7, .production_id = 6),
  [86] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [88] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_if_statement, 8, .production_id = 7),
  [90] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [92] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_if_statement, 8, .production_id = 3),
  [94] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [96] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_module, 1),
  [98] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_if_statement, 8, .production_id = 8),
  [100] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_if_statement, 9, .production_id = 9),
  [102] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_if_statement, 9, .production_id = 10),
  [104] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [106] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_if_statement, 9, .production_id = 5),
  [108] = {.entry = {.count = 1, .reusable = true}}, SHIFT(47),
  [110] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_if_statement, 10, .production_id = 11),
  [112] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_if_statement, 10, .production_id = 12),
  [114] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [116] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef TREE_SITTER_HIDE_SYMBOLS
#define TS_PUBLIC
#elif defined(_WIN32)
#define TS_PUBLIC __declspec(dllexport)
#else
#define TS_PUBLIC __attribute__((visibility("default")))
#endif

TS_PUBLIC const TSLanguage *tree_sitter_kero() {
  static const TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .state_count = STATE_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .production_id_count = PRODUCTION_ID_COUNT,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .parse_table = &ts_parse_table[0][0],
    .small_parse_table = ts_small_parse_table,
    .small_parse_table_map = ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .symbol_names = ts_symbol_names,
    .field_names = ts_field_names,
    .field_map_slices = ts_field_map_slices,
    .field_map_entries = ts_field_map_entries,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
    .keyword_lex_fn = ts_lex_keywords,
    .keyword_capture_token = sym_identifier,
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
