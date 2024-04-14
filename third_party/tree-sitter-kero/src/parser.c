#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 18
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 19
#define ALIAS_COUNT 0
#define TOKEN_COUNT 12
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 3
#define MAX_ALIAS_SEQUENCE_LENGTH 3
#define PRODUCTION_ID_COUNT 2

enum ts_symbol_identifiers {
  sym_identifier = 1,
  anon_sym_SEMI = 2,
  anon_sym_LPAREN = 3,
  anon_sym_RPAREN = 4,
  anon_sym_bool = 5,
  sym_true = 6,
  sym_false = 7,
  sym_equal = 8,
  sym_not_equal = 9,
  sym_logical_and = 10,
  sym_logical_or = 11,
  sym_module = 12,
  sym__statement = 13,
  sym__expression_statement = 14,
  sym__expression = 15,
  sym_binary_expression = 16,
  sym__parenthesized_expression = 17,
  aux_sym_module_repeat1 = 18,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_identifier] = "identifier",
  [anon_sym_SEMI] = ";",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
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
  [aux_sym_module_repeat1] = "module_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [sym_identifier] = sym_identifier,
  [anon_sym_SEMI] = anon_sym_SEMI,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
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
  [aux_sym_module_repeat1] = {
    .visible = false,
    .named = false,
  },
};

enum ts_field_identifiers {
  field_left = 1,
  field_operator = 2,
  field_right = 3,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_left] = "left",
  [field_operator] = "operator",
  [field_right] = "right",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 3},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_left, 0},
    {field_operator, 1},
    {field_right, 2},
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
      if (lookahead == '|') ADVANCE(4);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(9);
      END_STATE();
    case 1:
      if (lookahead == '&') ADVANCE(12);
      END_STATE();
    case 2:
      if (lookahead == '=') ADVANCE(11);
      END_STATE();
    case 3:
      if (lookahead == '=') ADVANCE(10);
      END_STATE();
    case 4:
      if (lookahead == '|') ADVANCE(13);
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
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(9);
      END_STATE();
    case 10:
      ACCEPT_TOKEN(sym_equal);
      END_STATE();
    case 11:
      ACCEPT_TOKEN(sym_not_equal);
      END_STATE();
    case 12:
      ACCEPT_TOKEN(sym_logical_and);
      END_STATE();
    case 13:
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
      if (lookahead == 'f') ADVANCE(2);
      if (lookahead == 't') ADVANCE(3);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0)
      END_STATE();
    case 1:
      if (lookahead == 'o') ADVANCE(4);
      END_STATE();
    case 2:
      if (lookahead == 'a') ADVANCE(5);
      END_STATE();
    case 3:
      if (lookahead == 'r') ADVANCE(6);
      END_STATE();
    case 4:
      if (lookahead == 'o') ADVANCE(7);
      END_STATE();
    case 5:
      if (lookahead == 'l') ADVANCE(8);
      END_STATE();
    case 6:
      if (lookahead == 'u') ADVANCE(9);
      END_STATE();
    case 7:
      if (lookahead == 'l') ADVANCE(10);
      END_STATE();
    case 8:
      if (lookahead == 's') ADVANCE(11);
      END_STATE();
    case 9:
      if (lookahead == 'e') ADVANCE(12);
      END_STATE();
    case 10:
      ACCEPT_TOKEN(anon_sym_bool);
      END_STATE();
    case 11:
      if (lookahead == 'e') ADVANCE(13);
      END_STATE();
    case 12:
      ACCEPT_TOKEN(sym_true);
      END_STATE();
    case 13:
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
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym_identifier] = ACTIONS(1),
    [anon_sym_SEMI] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [anon_sym_bool] = ACTIONS(1),
    [sym_true] = ACTIONS(1),
    [sym_false] = ACTIONS(1),
    [sym_equal] = ACTIONS(1),
    [sym_not_equal] = ACTIONS(1),
    [sym_logical_and] = ACTIONS(1),
    [sym_logical_or] = ACTIONS(1),
  },
  [1] = {
    [sym_module] = STATE(17),
    [sym__statement] = STATE(13),
    [sym__expression_statement] = STATE(13),
    [sym__expression] = STATE(11),
    [sym_binary_expression] = STATE(11),
    [sym__parenthesized_expression] = STATE(11),
    [ts_builtin_sym_end] = ACTIONS(3),
    [sym_identifier] = ACTIONS(5),
    [anon_sym_LPAREN] = ACTIONS(7),
    [sym_true] = ACTIONS(5),
    [sym_false] = ACTIONS(5),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 4,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    STATE(16), 2,
      sym__statement,
      sym__expression_statement,
    ACTIONS(5), 3,
      sym_identifier,
      sym_true,
      sym_false,
    STATE(11), 3,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
  [18] = 3,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(9), 3,
      sym_identifier,
      sym_true,
      sym_false,
    STATE(12), 3,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
  [32] = 3,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(11), 3,
      sym_identifier,
      sym_true,
      sym_false,
    STATE(8), 3,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
  [46] = 3,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(13), 3,
      sym_identifier,
      sym_true,
      sym_false,
    STATE(9), 3,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
  [60] = 3,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(15), 3,
      sym_identifier,
      sym_true,
      sym_false,
    STATE(10), 3,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
  [74] = 1,
    ACTIONS(17), 7,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      sym_equal,
      sym_not_equal,
      sym_logical_and,
      sym_logical_or,
  [84] = 1,
    ACTIONS(19), 7,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      sym_equal,
      sym_not_equal,
      sym_logical_and,
      sym_logical_or,
  [94] = 2,
    ACTIONS(21), 2,
      sym_equal,
      sym_not_equal,
    ACTIONS(19), 5,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      sym_logical_and,
      sym_logical_or,
  [106] = 3,
    ACTIONS(23), 1,
      sym_logical_and,
    ACTIONS(21), 2,
      sym_equal,
      sym_not_equal,
    ACTIONS(19), 4,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      sym_logical_or,
  [120] = 4,
    ACTIONS(23), 1,
      sym_logical_and,
    ACTIONS(27), 1,
      sym_logical_or,
    ACTIONS(21), 2,
      sym_equal,
      sym_not_equal,
    ACTIONS(25), 2,
      ts_builtin_sym_end,
      anon_sym_SEMI,
  [135] = 4,
    ACTIONS(23), 1,
      sym_logical_and,
    ACTIONS(27), 1,
      sym_logical_or,
    ACTIONS(29), 1,
      anon_sym_RPAREN,
    ACTIONS(21), 2,
      sym_equal,
      sym_not_equal,
  [149] = 3,
    ACTIONS(31), 1,
      ts_builtin_sym_end,
    ACTIONS(33), 1,
      anon_sym_SEMI,
    STATE(14), 1,
      aux_sym_module_repeat1,
  [159] = 3,
    ACTIONS(33), 1,
      anon_sym_SEMI,
    ACTIONS(35), 1,
      ts_builtin_sym_end,
    STATE(15), 1,
      aux_sym_module_repeat1,
  [169] = 3,
    ACTIONS(37), 1,
      ts_builtin_sym_end,
    ACTIONS(39), 1,
      anon_sym_SEMI,
    STATE(15), 1,
      aux_sym_module_repeat1,
  [179] = 1,
    ACTIONS(37), 2,
      ts_builtin_sym_end,
      anon_sym_SEMI,
  [184] = 1,
    ACTIONS(42), 1,
      ts_builtin_sym_end,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 18,
  [SMALL_STATE(4)] = 32,
  [SMALL_STATE(5)] = 46,
  [SMALL_STATE(6)] = 60,
  [SMALL_STATE(7)] = 74,
  [SMALL_STATE(8)] = 84,
  [SMALL_STATE(9)] = 94,
  [SMALL_STATE(10)] = 106,
  [SMALL_STATE(11)] = 120,
  [SMALL_STATE(12)] = 135,
  [SMALL_STATE(13)] = 149,
  [SMALL_STATE(14)] = 159,
  [SMALL_STATE(15)] = 169,
  [SMALL_STATE(16)] = 179,
  [SMALL_STATE(17)] = 184,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_module, 0),
  [5] = {.entry = {.count = 1, .reusable = false}}, SHIFT(11),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [9] = {.entry = {.count = 1, .reusable = false}}, SHIFT(12),
  [11] = {.entry = {.count = 1, .reusable = false}}, SHIFT(8),
  [13] = {.entry = {.count = 1, .reusable = false}}, SHIFT(9),
  [15] = {.entry = {.count = 1, .reusable = false}}, SHIFT(10),
  [17] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__parenthesized_expression, 3),
  [19] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binary_expression, 3, .production_id = 1),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [25] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__expression_statement, 1),
  [27] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [29] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [31] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_module, 1),
  [33] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [35] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_module, 2),
  [37] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_module_repeat1, 2),
  [39] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_module_repeat1, 2), SHIFT_REPEAT(2),
  [42] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
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
