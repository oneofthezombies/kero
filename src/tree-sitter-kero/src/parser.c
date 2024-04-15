#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 52
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 37
#define ALIAS_COUNT 0
#define TOKEN_COUNT 20
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 0
#define MAX_ALIAS_SEQUENCE_LENGTH 5
#define PRODUCTION_ID_COUNT 1

enum ts_symbol_identifiers {
  sym_identifier = 1,
  anon_sym_SEMI = 2,
  anon_sym_LPAREN = 3,
  anon_sym_RPAREN = 4,
  anon_sym_if = 5,
  anon_sym_else = 6,
  anon_sym_fn = 7,
  anon_sym_COMMA = 8,
  anon_sym_COLON = 9,
  anon_sym_DASH_GT = 10,
  anon_sym_LBRACE = 11,
  anon_sym_RBRACE = 12,
  anon_sym_bool = 13,
  sym_true = 14,
  sym_false = 15,
  sym_equal = 16,
  sym_not_equal = 17,
  sym_logical_and = 18,
  sym_logical_or = 19,
  sym_module = 20,
  sym__statement = 21,
  sym__expression_statement = 22,
  sym__expression = 23,
  sym_binary_expression = 24,
  sym__parenthesized_expression = 25,
  sym_if_statement = 26,
  sym_condition_expression = 27,
  sym_else_clause = 28,
  sym_function_definition = 29,
  sym_parameter_clause = 30,
  sym_parameter = 31,
  sym_return_clause = 32,
  sym_block = 33,
  sym_type = 34,
  aux_sym_module_repeat1 = 35,
  aux_sym_parameter_clause_repeat1 = 36,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_identifier] = "identifier",
  [anon_sym_SEMI] = ";",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [anon_sym_if] = "if",
  [anon_sym_else] = "else",
  [anon_sym_fn] = "fn",
  [anon_sym_COMMA] = ",",
  [anon_sym_COLON] = ":",
  [anon_sym_DASH_GT] = "->",
  [anon_sym_LBRACE] = "{",
  [anon_sym_RBRACE] = "}",
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
  [sym_condition_expression] = "condition_expression",
  [sym_else_clause] = "else_clause",
  [sym_function_definition] = "function_definition",
  [sym_parameter_clause] = "parameter_clause",
  [sym_parameter] = "parameter",
  [sym_return_clause] = "return_clause",
  [sym_block] = "block",
  [sym_type] = "type",
  [aux_sym_module_repeat1] = "module_repeat1",
  [aux_sym_parameter_clause_repeat1] = "parameter_clause_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [sym_identifier] = sym_identifier,
  [anon_sym_SEMI] = anon_sym_SEMI,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [anon_sym_if] = anon_sym_if,
  [anon_sym_else] = anon_sym_else,
  [anon_sym_fn] = anon_sym_fn,
  [anon_sym_COMMA] = anon_sym_COMMA,
  [anon_sym_COLON] = anon_sym_COLON,
  [anon_sym_DASH_GT] = anon_sym_DASH_GT,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
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
  [sym_condition_expression] = sym_condition_expression,
  [sym_else_clause] = sym_else_clause,
  [sym_function_definition] = sym_function_definition,
  [sym_parameter_clause] = sym_parameter_clause,
  [sym_parameter] = sym_parameter,
  [sym_return_clause] = sym_return_clause,
  [sym_block] = sym_block,
  [sym_type] = sym_type,
  [aux_sym_module_repeat1] = aux_sym_module_repeat1,
  [aux_sym_parameter_clause_repeat1] = aux_sym_parameter_clause_repeat1,
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
  [anon_sym_else] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_fn] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COMMA] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COLON] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DASH_GT] = {
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
  [sym_condition_expression] = {
    .visible = true,
    .named = true,
  },
  [sym_else_clause] = {
    .visible = true,
    .named = true,
  },
  [sym_function_definition] = {
    .visible = true,
    .named = true,
  },
  [sym_parameter_clause] = {
    .visible = true,
    .named = true,
  },
  [sym_parameter] = {
    .visible = true,
    .named = true,
  },
  [sym_return_clause] = {
    .visible = true,
    .named = true,
  },
  [sym_block] = {
    .visible = true,
    .named = true,
  },
  [sym_type] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_module_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_parameter_clause_repeat1] = {
    .visible = false,
    .named = false,
  },
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
  [50] = 50,
  [51] = 51,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(6);
      ADVANCE_MAP(
        '!', 2,
        '&', 1,
        '(', 8,
        ')', 9,
        ',', 10,
        '-', 4,
        ':', 11,
        ';', 7,
        '=', 3,
        '{', 13,
        '|', 5,
        '}', 14,
      );
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(15);
      END_STATE();
    case 1:
      if (lookahead == '&') ADVANCE(18);
      END_STATE();
    case 2:
      if (lookahead == '=') ADVANCE(17);
      END_STATE();
    case 3:
      if (lookahead == '=') ADVANCE(16);
      END_STATE();
    case 4:
      if (lookahead == '>') ADVANCE(12);
      END_STATE();
    case 5:
      if (lookahead == '|') ADVANCE(19);
      END_STATE();
    case 6:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 7:
      ACCEPT_TOKEN(anon_sym_SEMI);
      END_STATE();
    case 8:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 9:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 10:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 11:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 12:
      ACCEPT_TOKEN(anon_sym_DASH_GT);
      END_STATE();
    case 13:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 14:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 15:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(15);
      END_STATE();
    case 16:
      ACCEPT_TOKEN(sym_equal);
      END_STATE();
    case 17:
      ACCEPT_TOKEN(sym_not_equal);
      END_STATE();
    case 18:
      ACCEPT_TOKEN(sym_logical_and);
      END_STATE();
    case 19:
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
          lookahead == ' ') SKIP(0);
      END_STATE();
    case 1:
      if (lookahead == 'o') ADVANCE(6);
      END_STATE();
    case 2:
      if (lookahead == 'l') ADVANCE(7);
      END_STATE();
    case 3:
      if (lookahead == 'a') ADVANCE(8);
      if (lookahead == 'n') ADVANCE(9);
      END_STATE();
    case 4:
      if (lookahead == 'f') ADVANCE(10);
      END_STATE();
    case 5:
      if (lookahead == 'r') ADVANCE(11);
      END_STATE();
    case 6:
      if (lookahead == 'o') ADVANCE(12);
      END_STATE();
    case 7:
      if (lookahead == 's') ADVANCE(13);
      END_STATE();
    case 8:
      if (lookahead == 'l') ADVANCE(14);
      END_STATE();
    case 9:
      ACCEPT_TOKEN(anon_sym_fn);
      END_STATE();
    case 10:
      ACCEPT_TOKEN(anon_sym_if);
      END_STATE();
    case 11:
      if (lookahead == 'u') ADVANCE(15);
      END_STATE();
    case 12:
      if (lookahead == 'l') ADVANCE(16);
      END_STATE();
    case 13:
      if (lookahead == 'e') ADVANCE(17);
      END_STATE();
    case 14:
      if (lookahead == 's') ADVANCE(18);
      END_STATE();
    case 15:
      if (lookahead == 'e') ADVANCE(19);
      END_STATE();
    case 16:
      ACCEPT_TOKEN(anon_sym_bool);
      END_STATE();
    case 17:
      ACCEPT_TOKEN(anon_sym_else);
      END_STATE();
    case 18:
      if (lookahead == 'e') ADVANCE(20);
      END_STATE();
    case 19:
      ACCEPT_TOKEN(sym_true);
      END_STATE();
    case 20:
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
  [50] = {.lex_state = 0},
  [51] = {.lex_state = 0},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym_identifier] = ACTIONS(1),
    [anon_sym_SEMI] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [anon_sym_if] = ACTIONS(1),
    [anon_sym_else] = ACTIONS(1),
    [anon_sym_fn] = ACTIONS(1),
    [anon_sym_COMMA] = ACTIONS(1),
    [anon_sym_COLON] = ACTIONS(1),
    [anon_sym_DASH_GT] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_bool] = ACTIONS(1),
    [sym_true] = ACTIONS(1),
    [sym_false] = ACTIONS(1),
    [sym_equal] = ACTIONS(1),
    [sym_not_equal] = ACTIONS(1),
    [sym_logical_and] = ACTIONS(1),
    [sym_logical_or] = ACTIONS(1),
  },
  [1] = {
    [sym_module] = STATE(48),
    [sym__statement] = STATE(25),
    [sym__expression_statement] = STATE(25),
    [sym__expression] = STATE(13),
    [sym_binary_expression] = STATE(13),
    [sym__parenthesized_expression] = STATE(13),
    [sym_if_statement] = STATE(25),
    [sym_function_definition] = STATE(25),
    [ts_builtin_sym_end] = ACTIONS(3),
    [sym_identifier] = ACTIONS(5),
    [anon_sym_LPAREN] = ACTIONS(7),
    [anon_sym_if] = ACTIONS(9),
    [anon_sym_fn] = ACTIONS(11),
    [sym_true] = ACTIONS(5),
    [sym_false] = ACTIONS(5),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 7,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(9), 1,
      anon_sym_if,
    ACTIONS(11), 1,
      anon_sym_fn,
    ACTIONS(13), 1,
      anon_sym_RBRACE,
    ACTIONS(5), 3,
      sym_identifier,
      sym_true,
      sym_false,
    STATE(13), 3,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
    STATE(28), 4,
      sym__statement,
      sym__expression_statement,
      sym_if_statement,
      sym_function_definition,
  [29] = 6,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(9), 1,
      anon_sym_if,
    ACTIONS(11), 1,
      anon_sym_fn,
    ACTIONS(5), 3,
      sym_identifier,
      sym_true,
      sym_false,
    STATE(13), 3,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
    STATE(31), 4,
      sym__statement,
      sym__expression_statement,
      sym_if_statement,
      sym_function_definition,
  [55] = 3,
    ACTIONS(19), 1,
      sym_logical_and,
    ACTIONS(17), 2,
      sym_equal,
      sym_not_equal,
    ACTIONS(15), 6,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      sym_logical_or,
  [71] = 2,
    ACTIONS(17), 2,
      sym_equal,
      sym_not_equal,
    ACTIONS(15), 7,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      sym_logical_and,
      sym_logical_or,
  [85] = 1,
    ACTIONS(15), 9,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      sym_equal,
      sym_not_equal,
      sym_logical_and,
      sym_logical_or,
  [97] = 1,
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
  [109] = 4,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    STATE(43), 1,
      sym_condition_expression,
    ACTIONS(23), 3,
      sym_identifier,
      sym_true,
      sym_false,
    STATE(14), 3,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
  [126] = 3,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(25), 3,
      sym_identifier,
      sym_true,
      sym_false,
    STATE(6), 3,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
  [140] = 3,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(27), 3,
      sym_identifier,
      sym_true,
      sym_false,
    STATE(15), 3,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
  [154] = 3,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(29), 3,
      sym_identifier,
      sym_true,
      sym_false,
    STATE(5), 3,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
  [168] = 3,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(31), 3,
      sym_identifier,
      sym_true,
      sym_false,
    STATE(4), 3,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
  [182] = 4,
    ACTIONS(19), 1,
      sym_logical_and,
    ACTIONS(35), 1,
      sym_logical_or,
    ACTIONS(17), 2,
      sym_equal,
      sym_not_equal,
    ACTIONS(33), 3,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [198] = 4,
    ACTIONS(19), 1,
      sym_logical_and,
    ACTIONS(35), 1,
      sym_logical_or,
    ACTIONS(37), 1,
      anon_sym_LBRACE,
    ACTIONS(17), 2,
      sym_equal,
      sym_not_equal,
  [212] = 4,
    ACTIONS(19), 1,
      sym_logical_and,
    ACTIONS(35), 1,
      sym_logical_or,
    ACTIONS(39), 1,
      anon_sym_RPAREN,
    ACTIONS(17), 2,
      sym_equal,
      sym_not_equal,
  [226] = 3,
    ACTIONS(43), 1,
      anon_sym_else,
    STATE(23), 1,
      sym_else_clause,
    ACTIONS(41), 3,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [238] = 3,
    ACTIONS(47), 1,
      anon_sym_SEMI,
    STATE(17), 1,
      aux_sym_module_repeat1,
    ACTIONS(45), 2,
      ts_builtin_sym_end,
      anon_sym_RBRACE,
  [249] = 1,
    ACTIONS(50), 4,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_else,
      anon_sym_RBRACE,
  [256] = 1,
    ACTIONS(52), 4,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_else,
      anon_sym_RBRACE,
  [263] = 3,
    ACTIONS(54), 1,
      anon_sym_if,
    ACTIONS(56), 1,
      anon_sym_LBRACE,
    STATE(34), 2,
      sym_if_statement,
      sym_block,
  [274] = 4,
    ACTIONS(56), 1,
      anon_sym_LBRACE,
    ACTIONS(58), 1,
      anon_sym_DASH_GT,
    STATE(36), 1,
      sym_block,
    STATE(38), 1,
      sym_return_clause,
  [287] = 1,
    ACTIONS(60), 4,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_else,
      anon_sym_RBRACE,
  [294] = 1,
    ACTIONS(62), 3,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [300] = 3,
    ACTIONS(64), 1,
      ts_builtin_sym_end,
    ACTIONS(66), 1,
      anon_sym_SEMI,
    STATE(17), 1,
      aux_sym_module_repeat1,
  [310] = 3,
    ACTIONS(66), 1,
      anon_sym_SEMI,
    ACTIONS(68), 1,
      ts_builtin_sym_end,
    STATE(24), 1,
      aux_sym_module_repeat1,
  [320] = 3,
    ACTIONS(70), 1,
      anon_sym_RPAREN,
    ACTIONS(72), 1,
      anon_sym_COMMA,
    STATE(26), 1,
      aux_sym_parameter_clause_repeat1,
  [330] = 1,
    ACTIONS(75), 3,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [336] = 3,
    ACTIONS(66), 1,
      anon_sym_SEMI,
    ACTIONS(77), 1,
      anon_sym_RBRACE,
    STATE(35), 1,
      aux_sym_module_repeat1,
  [346] = 1,
    ACTIONS(79), 3,
      anon_sym_RPAREN,
      anon_sym_COMMA,
      anon_sym_LBRACE,
  [352] = 3,
    ACTIONS(81), 1,
      sym_identifier,
    ACTIONS(83), 1,
      anon_sym_RPAREN,
    STATE(33), 1,
      sym_parameter,
  [362] = 1,
    ACTIONS(45), 3,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [368] = 3,
    ACTIONS(85), 1,
      anon_sym_RPAREN,
    ACTIONS(87), 1,
      anon_sym_COMMA,
    STATE(26), 1,
      aux_sym_parameter_clause_repeat1,
  [378] = 3,
    ACTIONS(87), 1,
      anon_sym_COMMA,
    ACTIONS(89), 1,
      anon_sym_RPAREN,
    STATE(32), 1,
      aux_sym_parameter_clause_repeat1,
  [388] = 1,
    ACTIONS(91), 3,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [394] = 3,
    ACTIONS(66), 1,
      anon_sym_SEMI,
    ACTIONS(93), 1,
      anon_sym_RBRACE,
    STATE(17), 1,
      aux_sym_module_repeat1,
  [404] = 1,
    ACTIONS(95), 3,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [410] = 1,
    ACTIONS(97), 2,
      anon_sym_DASH_GT,
      anon_sym_LBRACE,
  [415] = 2,
    ACTIONS(56), 1,
      anon_sym_LBRACE,
    STATE(27), 1,
      sym_block,
  [422] = 2,
    ACTIONS(99), 1,
      anon_sym_bool,
    STATE(45), 1,
      sym_type,
  [429] = 1,
    ACTIONS(101), 2,
      anon_sym_DASH_GT,
      anon_sym_LBRACE,
  [434] = 2,
    ACTIONS(81), 1,
      sym_identifier,
    STATE(46), 1,
      sym_parameter,
  [441] = 2,
    ACTIONS(99), 1,
      anon_sym_bool,
    STATE(50), 1,
      sym_type,
  [448] = 2,
    ACTIONS(56), 1,
      anon_sym_LBRACE,
    STATE(16), 1,
      sym_block,
  [455] = 2,
    ACTIONS(103), 1,
      anon_sym_LPAREN,
    STATE(21), 1,
      sym_parameter_clause,
  [462] = 1,
    ACTIONS(105), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [467] = 1,
    ACTIONS(70), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [472] = 1,
    ACTIONS(107), 2,
      anon_sym_DASH_GT,
      anon_sym_LBRACE,
  [477] = 1,
    ACTIONS(109), 1,
      ts_builtin_sym_end,
  [481] = 1,
    ACTIONS(111), 1,
      anon_sym_COLON,
  [485] = 1,
    ACTIONS(113), 1,
      anon_sym_LBRACE,
  [489] = 1,
    ACTIONS(115), 1,
      sym_identifier,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 29,
  [SMALL_STATE(4)] = 55,
  [SMALL_STATE(5)] = 71,
  [SMALL_STATE(6)] = 85,
  [SMALL_STATE(7)] = 97,
  [SMALL_STATE(8)] = 109,
  [SMALL_STATE(9)] = 126,
  [SMALL_STATE(10)] = 140,
  [SMALL_STATE(11)] = 154,
  [SMALL_STATE(12)] = 168,
  [SMALL_STATE(13)] = 182,
  [SMALL_STATE(14)] = 198,
  [SMALL_STATE(15)] = 212,
  [SMALL_STATE(16)] = 226,
  [SMALL_STATE(17)] = 238,
  [SMALL_STATE(18)] = 249,
  [SMALL_STATE(19)] = 256,
  [SMALL_STATE(20)] = 263,
  [SMALL_STATE(21)] = 274,
  [SMALL_STATE(22)] = 287,
  [SMALL_STATE(23)] = 294,
  [SMALL_STATE(24)] = 300,
  [SMALL_STATE(25)] = 310,
  [SMALL_STATE(26)] = 320,
  [SMALL_STATE(27)] = 330,
  [SMALL_STATE(28)] = 336,
  [SMALL_STATE(29)] = 346,
  [SMALL_STATE(30)] = 352,
  [SMALL_STATE(31)] = 362,
  [SMALL_STATE(32)] = 368,
  [SMALL_STATE(33)] = 378,
  [SMALL_STATE(34)] = 388,
  [SMALL_STATE(35)] = 394,
  [SMALL_STATE(36)] = 404,
  [SMALL_STATE(37)] = 410,
  [SMALL_STATE(38)] = 415,
  [SMALL_STATE(39)] = 422,
  [SMALL_STATE(40)] = 429,
  [SMALL_STATE(41)] = 434,
  [SMALL_STATE(42)] = 441,
  [SMALL_STATE(43)] = 448,
  [SMALL_STATE(44)] = 455,
  [SMALL_STATE(45)] = 462,
  [SMALL_STATE(46)] = 467,
  [SMALL_STATE(47)] = 472,
  [SMALL_STATE(48)] = 477,
  [SMALL_STATE(49)] = 481,
  [SMALL_STATE(50)] = 485,
  [SMALL_STATE(51)] = 489,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_module, 0, 0, 0),
  [5] = {.entry = {.count = 1, .reusable = false}}, SHIFT(13),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [9] = {.entry = {.count = 1, .reusable = false}}, SHIFT(8),
  [11] = {.entry = {.count = 1, .reusable = false}}, SHIFT(51),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [15] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binary_expression, 3, 0, 0),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [21] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__parenthesized_expression, 3, 0, 0),
  [23] = {.entry = {.count = 1, .reusable = false}}, SHIFT(14),
  [25] = {.entry = {.count = 1, .reusable = false}}, SHIFT(6),
  [27] = {.entry = {.count = 1, .reusable = false}}, SHIFT(15),
  [29] = {.entry = {.count = 1, .reusable = false}}, SHIFT(5),
  [31] = {.entry = {.count = 1, .reusable = false}}, SHIFT(4),
  [33] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__expression_statement, 1, 0, 0),
  [35] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [37] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_condition_expression, 1, 0, 0),
  [39] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [41] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_if_statement, 3, 0, 0),
  [43] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [45] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_module_repeat1, 2, 0, 0),
  [47] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_module_repeat1, 2, 0, 0), SHIFT_REPEAT(3),
  [50] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block, 4, 0, 0),
  [52] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block, 3, 0, 0),
  [54] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [56] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [58] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [60] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block, 2, 0, 0),
  [62] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_if_statement, 4, 0, 0),
  [64] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_module, 2, 0, 0),
  [66] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [68] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_module, 1, 0, 0),
  [70] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_parameter_clause_repeat1, 2, 0, 0),
  [72] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_parameter_clause_repeat1, 2, 0, 0), SHIFT_REPEAT(41),
  [75] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_function_definition, 5, 0, 0),
  [77] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [79] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type, 1, 0, 0),
  [81] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [83] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [85] = {.entry = {.count = 1, .reusable = true}}, SHIFT(47),
  [87] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [89] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [91] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_else_clause, 2, 0, 0),
  [93] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [95] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_function_definition, 4, 0, 0),
  [97] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameter_clause, 2, 0, 0),
  [99] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [101] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameter_clause, 3, 0, 0),
  [103] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [105] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameter, 3, 0, 0),
  [107] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameter_clause, 4, 0, 0),
  [109] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [111] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
  [113] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_return_clause, 2, 0, 0),
  [115] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
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

TS_PUBLIC const TSLanguage *tree_sitter_kero(void) {
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
