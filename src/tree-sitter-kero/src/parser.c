#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 72
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 49
#define ALIAS_COUNT 0
#define TOKEN_COUNT 29
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 0
#define MAX_ALIAS_SEQUENCE_LENGTH 6
#define PRODUCTION_ID_COUNT 1

enum ts_symbol_identifiers {
  sym_identifier = 1,
  anon_sym_SEMI = 2,
  anon_sym_STAR = 3,
  anon_sym_SLASH = 4,
  anon_sym_PERCENT = 5,
  anon_sym_PLUS = 6,
  anon_sym_DASH = 7,
  anon_sym_EQ_EQ = 8,
  anon_sym_BANG_EQ = 9,
  anon_sym_AMP_AMP = 10,
  anon_sym_PIPE_PIPE = 11,
  anon_sym_LPAREN = 12,
  anon_sym_RPAREN = 13,
  anon_sym_if = 14,
  anon_sym_else = 15,
  anon_sym_fn = 16,
  anon_sym_extern = 17,
  anon_sym_COMMA = 18,
  anon_sym_COLON = 19,
  anon_sym_DASH_GT = 20,
  anon_sym_LBRACE = 21,
  anon_sym_RBRACE = 22,
  anon_sym_bool = 23,
  anon_sym_number = 24,
  sym_string_literal = 25,
  sym_number = 26,
  sym_true = 27,
  sym_false = 28,
  sym_module = 29,
  sym__statement = 30,
  sym__expression_statement = 31,
  sym__expression = 32,
  sym_binary_expression = 33,
  sym__parenthesized_expression = 34,
  sym_if_statement = 35,
  sym_condition_expression = 36,
  sym_else_clause = 37,
  sym_function_definition = 38,
  sym_extern_function_declaration = 39,
  sym_parameter_clause = 40,
  sym_parameter = 41,
  sym_return_clause = 42,
  sym_call_expression = 43,
  sym_block = 44,
  sym_type = 45,
  aux_sym_module_repeat1 = 46,
  aux_sym_parameter_clause_repeat1 = 47,
  aux_sym_call_expression_repeat1 = 48,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_identifier] = "identifier",
  [anon_sym_SEMI] = ";",
  [anon_sym_STAR] = "*",
  [anon_sym_SLASH] = "/",
  [anon_sym_PERCENT] = "%",
  [anon_sym_PLUS] = "+",
  [anon_sym_DASH] = "-",
  [anon_sym_EQ_EQ] = "==",
  [anon_sym_BANG_EQ] = "!=",
  [anon_sym_AMP_AMP] = "&&",
  [anon_sym_PIPE_PIPE] = "||",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [anon_sym_if] = "if",
  [anon_sym_else] = "else",
  [anon_sym_fn] = "fn",
  [anon_sym_extern] = "extern",
  [anon_sym_COMMA] = ",",
  [anon_sym_COLON] = ":",
  [anon_sym_DASH_GT] = "->",
  [anon_sym_LBRACE] = "{",
  [anon_sym_RBRACE] = "}",
  [anon_sym_bool] = "bool",
  [anon_sym_number] = "number",
  [sym_string_literal] = "string_literal",
  [sym_number] = "number",
  [sym_true] = "true",
  [sym_false] = "false",
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
  [sym_extern_function_declaration] = "extern_function_declaration",
  [sym_parameter_clause] = "parameter_clause",
  [sym_parameter] = "parameter",
  [sym_return_clause] = "return_clause",
  [sym_call_expression] = "call_expression",
  [sym_block] = "block",
  [sym_type] = "type",
  [aux_sym_module_repeat1] = "module_repeat1",
  [aux_sym_parameter_clause_repeat1] = "parameter_clause_repeat1",
  [aux_sym_call_expression_repeat1] = "call_expression_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [sym_identifier] = sym_identifier,
  [anon_sym_SEMI] = anon_sym_SEMI,
  [anon_sym_STAR] = anon_sym_STAR,
  [anon_sym_SLASH] = anon_sym_SLASH,
  [anon_sym_PERCENT] = anon_sym_PERCENT,
  [anon_sym_PLUS] = anon_sym_PLUS,
  [anon_sym_DASH] = anon_sym_DASH,
  [anon_sym_EQ_EQ] = anon_sym_EQ_EQ,
  [anon_sym_BANG_EQ] = anon_sym_BANG_EQ,
  [anon_sym_AMP_AMP] = anon_sym_AMP_AMP,
  [anon_sym_PIPE_PIPE] = anon_sym_PIPE_PIPE,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [anon_sym_if] = anon_sym_if,
  [anon_sym_else] = anon_sym_else,
  [anon_sym_fn] = anon_sym_fn,
  [anon_sym_extern] = anon_sym_extern,
  [anon_sym_COMMA] = anon_sym_COMMA,
  [anon_sym_COLON] = anon_sym_COLON,
  [anon_sym_DASH_GT] = anon_sym_DASH_GT,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [anon_sym_bool] = anon_sym_bool,
  [anon_sym_number] = anon_sym_number,
  [sym_string_literal] = sym_string_literal,
  [sym_number] = sym_number,
  [sym_true] = sym_true,
  [sym_false] = sym_false,
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
  [sym_extern_function_declaration] = sym_extern_function_declaration,
  [sym_parameter_clause] = sym_parameter_clause,
  [sym_parameter] = sym_parameter,
  [sym_return_clause] = sym_return_clause,
  [sym_call_expression] = sym_call_expression,
  [sym_block] = sym_block,
  [sym_type] = sym_type,
  [aux_sym_module_repeat1] = aux_sym_module_repeat1,
  [aux_sym_parameter_clause_repeat1] = aux_sym_parameter_clause_repeat1,
  [aux_sym_call_expression_repeat1] = aux_sym_call_expression_repeat1,
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
  [anon_sym_STAR] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SLASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PERCENT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PLUS] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_EQ_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_BANG_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_AMP_AMP] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PIPE_PIPE] = {
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
  [anon_sym_extern] = {
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
  [anon_sym_number] = {
    .visible = true,
    .named = false,
  },
  [sym_string_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_number] = {
    .visible = true,
    .named = true,
  },
  [sym_true] = {
    .visible = true,
    .named = true,
  },
  [sym_false] = {
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
  [sym_extern_function_declaration] = {
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
  [sym_call_expression] = {
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
  [aux_sym_call_expression_repeat1] = {
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
  [52] = 52,
  [53] = 53,
  [54] = 54,
  [55] = 55,
  [56] = 56,
  [57] = 57,
  [58] = 58,
  [59] = 59,
  [60] = 60,
  [61] = 61,
  [62] = 62,
  [63] = 63,
  [64] = 64,
  [65] = 65,
  [66] = 66,
  [67] = 67,
  [68] = 68,
  [69] = 69,
  [70] = 70,
  [71] = 71,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(11);
      if (lookahead == '!') ADVANCE(5);
      if (lookahead == '"') ADVANCE(1);
      if (lookahead == '%') ADVANCE(15);
      if (lookahead == '&') ADVANCE(2);
      if (lookahead == '(') ADVANCE(23);
      if (lookahead == ')') ADVANCE(24);
      if (lookahead == '*') ADVANCE(13);
      if (lookahead == '+') ADVANCE(16);
      if (lookahead == ',') ADVANCE(25);
      if (lookahead == '-') ADVANCE(18);
      if (lookahead == '/') ADVANCE(14);
      if (lookahead == ':') ADVANCE(26);
      if (lookahead == ';') ADVANCE(12);
      if (lookahead == '=') ADVANCE(6);
      if (lookahead == '{') ADVANCE(28);
      if (lookahead == '|') ADVANCE(7);
      if (lookahead == '}') ADVANCE(29);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(30);
      END_STATE();
    case 1:
      if (lookahead == '"') ADVANCE(31);
      if (lookahead != 0) ADVANCE(1);
      END_STATE();
    case 2:
      if (lookahead == '&') ADVANCE(21);
      END_STATE();
    case 3:
      if (lookahead == '.') ADVANCE(8);
      END_STATE();
    case 4:
      if (lookahead == '0') ADVANCE(3);
      if (lookahead == '>') ADVANCE(27);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(33);
      END_STATE();
    case 5:
      if (lookahead == '=') ADVANCE(20);
      END_STATE();
    case 6:
      if (lookahead == '=') ADVANCE(19);
      END_STATE();
    case 7:
      if (lookahead == '|') ADVANCE(22);
      END_STATE();
    case 8:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(34);
      END_STATE();
    case 9:
      if (eof) ADVANCE(11);
      if (lookahead == '!') ADVANCE(5);
      if (lookahead == '%') ADVANCE(15);
      if (lookahead == '&') ADVANCE(2);
      if (lookahead == '(') ADVANCE(23);
      if (lookahead == ')') ADVANCE(24);
      if (lookahead == '*') ADVANCE(13);
      if (lookahead == '+') ADVANCE(16);
      if (lookahead == ',') ADVANCE(25);
      if (lookahead == '-') ADVANCE(17);
      if (lookahead == '/') ADVANCE(14);
      if (lookahead == ';') ADVANCE(12);
      if (lookahead == '=') ADVANCE(6);
      if (lookahead == '{') ADVANCE(28);
      if (lookahead == '|') ADVANCE(7);
      if (lookahead == '}') ADVANCE(29);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(9)
      END_STATE();
    case 10:
      if (eof) ADVANCE(11);
      if (lookahead == '"') ADVANCE(1);
      if (lookahead == '(') ADVANCE(23);
      if (lookahead == ')') ADVANCE(24);
      if (lookahead == '-') ADVANCE(4);
      if (lookahead == '0') ADVANCE(32);
      if (lookahead == ';') ADVANCE(12);
      if (lookahead == '{') ADVANCE(28);
      if (lookahead == '}') ADVANCE(29);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(10)
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(33);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(30);
      END_STATE();
    case 11:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 12:
      ACCEPT_TOKEN(anon_sym_SEMI);
      END_STATE();
    case 13:
      ACCEPT_TOKEN(anon_sym_STAR);
      END_STATE();
    case 14:
      ACCEPT_TOKEN(anon_sym_SLASH);
      END_STATE();
    case 15:
      ACCEPT_TOKEN(anon_sym_PERCENT);
      END_STATE();
    case 16:
      ACCEPT_TOKEN(anon_sym_PLUS);
      END_STATE();
    case 17:
      ACCEPT_TOKEN(anon_sym_DASH);
      END_STATE();
    case 18:
      ACCEPT_TOKEN(anon_sym_DASH);
      if (lookahead == '>') ADVANCE(27);
      END_STATE();
    case 19:
      ACCEPT_TOKEN(anon_sym_EQ_EQ);
      END_STATE();
    case 20:
      ACCEPT_TOKEN(anon_sym_BANG_EQ);
      END_STATE();
    case 21:
      ACCEPT_TOKEN(anon_sym_AMP_AMP);
      END_STATE();
    case 22:
      ACCEPT_TOKEN(anon_sym_PIPE_PIPE);
      END_STATE();
    case 23:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 24:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 25:
      ACCEPT_TOKEN(anon_sym_COMMA);
      END_STATE();
    case 26:
      ACCEPT_TOKEN(anon_sym_COLON);
      END_STATE();
    case 27:
      ACCEPT_TOKEN(anon_sym_DASH_GT);
      END_STATE();
    case 28:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 29:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 30:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(30);
      END_STATE();
    case 31:
      ACCEPT_TOKEN(sym_string_literal);
      END_STATE();
    case 32:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '.') ADVANCE(8);
      END_STATE();
    case 33:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '.') ADVANCE(8);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(33);
      END_STATE();
    case 34:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(34);
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
      if (lookahead == 'n') ADVANCE(5);
      if (lookahead == 't') ADVANCE(6);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0)
      END_STATE();
    case 1:
      if (lookahead == 'o') ADVANCE(7);
      END_STATE();
    case 2:
      if (lookahead == 'l') ADVANCE(8);
      if (lookahead == 'x') ADVANCE(9);
      END_STATE();
    case 3:
      if (lookahead == 'a') ADVANCE(10);
      if (lookahead == 'n') ADVANCE(11);
      END_STATE();
    case 4:
      if (lookahead == 'f') ADVANCE(12);
      END_STATE();
    case 5:
      if (lookahead == 'u') ADVANCE(13);
      END_STATE();
    case 6:
      if (lookahead == 'r') ADVANCE(14);
      END_STATE();
    case 7:
      if (lookahead == 'o') ADVANCE(15);
      END_STATE();
    case 8:
      if (lookahead == 's') ADVANCE(16);
      END_STATE();
    case 9:
      if (lookahead == 't') ADVANCE(17);
      END_STATE();
    case 10:
      if (lookahead == 'l') ADVANCE(18);
      END_STATE();
    case 11:
      ACCEPT_TOKEN(anon_sym_fn);
      END_STATE();
    case 12:
      ACCEPT_TOKEN(anon_sym_if);
      END_STATE();
    case 13:
      if (lookahead == 'm') ADVANCE(19);
      END_STATE();
    case 14:
      if (lookahead == 'u') ADVANCE(20);
      END_STATE();
    case 15:
      if (lookahead == 'l') ADVANCE(21);
      END_STATE();
    case 16:
      if (lookahead == 'e') ADVANCE(22);
      END_STATE();
    case 17:
      if (lookahead == 'e') ADVANCE(23);
      END_STATE();
    case 18:
      if (lookahead == 's') ADVANCE(24);
      END_STATE();
    case 19:
      if (lookahead == 'b') ADVANCE(25);
      END_STATE();
    case 20:
      if (lookahead == 'e') ADVANCE(26);
      END_STATE();
    case 21:
      ACCEPT_TOKEN(anon_sym_bool);
      END_STATE();
    case 22:
      ACCEPT_TOKEN(anon_sym_else);
      END_STATE();
    case 23:
      if (lookahead == 'r') ADVANCE(27);
      END_STATE();
    case 24:
      if (lookahead == 'e') ADVANCE(28);
      END_STATE();
    case 25:
      if (lookahead == 'e') ADVANCE(29);
      END_STATE();
    case 26:
      ACCEPT_TOKEN(sym_true);
      END_STATE();
    case 27:
      if (lookahead == 'n') ADVANCE(30);
      END_STATE();
    case 28:
      ACCEPT_TOKEN(sym_false);
      END_STATE();
    case 29:
      if (lookahead == 'r') ADVANCE(31);
      END_STATE();
    case 30:
      ACCEPT_TOKEN(anon_sym_extern);
      END_STATE();
    case 31:
      ACCEPT_TOKEN(anon_sym_number);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 10},
  [2] = {.lex_state = 10},
  [3] = {.lex_state = 10},
  [4] = {.lex_state = 9},
  [5] = {.lex_state = 9},
  [6] = {.lex_state = 9},
  [7] = {.lex_state = 9},
  [8] = {.lex_state = 9},
  [9] = {.lex_state = 9},
  [10] = {.lex_state = 9},
  [11] = {.lex_state = 9},
  [12] = {.lex_state = 9},
  [13] = {.lex_state = 9},
  [14] = {.lex_state = 9},
  [15] = {.lex_state = 9},
  [16] = {.lex_state = 10},
  [17] = {.lex_state = 9},
  [18] = {.lex_state = 10},
  [19] = {.lex_state = 10},
  [20] = {.lex_state = 10},
  [21] = {.lex_state = 10},
  [22] = {.lex_state = 10},
  [23] = {.lex_state = 10},
  [24] = {.lex_state = 10},
  [25] = {.lex_state = 9},
  [26] = {.lex_state = 9},
  [27] = {.lex_state = 10},
  [28] = {.lex_state = 0},
  [29] = {.lex_state = 10},
  [30] = {.lex_state = 10},
  [31] = {.lex_state = 10},
  [32] = {.lex_state = 0},
  [33] = {.lex_state = 10},
  [34] = {.lex_state = 0},
  [35] = {.lex_state = 0},
  [36] = {.lex_state = 0},
  [37] = {.lex_state = 0},
  [38] = {.lex_state = 10},
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
  [52] = {.lex_state = 0},
  [53] = {.lex_state = 0},
  [54] = {.lex_state = 0},
  [55] = {.lex_state = 0},
  [56] = {.lex_state = 0},
  [57] = {.lex_state = 0},
  [58] = {.lex_state = 0},
  [59] = {.lex_state = 0},
  [60] = {.lex_state = 0},
  [61] = {.lex_state = 0},
  [62] = {.lex_state = 0},
  [63] = {.lex_state = 0},
  [64] = {.lex_state = 0},
  [65] = {.lex_state = 0},
  [66] = {.lex_state = 0},
  [67] = {.lex_state = 0},
  [68] = {.lex_state = 0},
  [69] = {.lex_state = 0},
  [70] = {.lex_state = 0},
  [71] = {.lex_state = 0},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym_identifier] = ACTIONS(1),
    [anon_sym_SEMI] = ACTIONS(1),
    [anon_sym_STAR] = ACTIONS(1),
    [anon_sym_SLASH] = ACTIONS(1),
    [anon_sym_PERCENT] = ACTIONS(1),
    [anon_sym_PLUS] = ACTIONS(1),
    [anon_sym_DASH] = ACTIONS(1),
    [anon_sym_EQ_EQ] = ACTIONS(1),
    [anon_sym_BANG_EQ] = ACTIONS(1),
    [anon_sym_AMP_AMP] = ACTIONS(1),
    [anon_sym_PIPE_PIPE] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [anon_sym_if] = ACTIONS(1),
    [anon_sym_else] = ACTIONS(1),
    [anon_sym_fn] = ACTIONS(1),
    [anon_sym_extern] = ACTIONS(1),
    [anon_sym_COMMA] = ACTIONS(1),
    [anon_sym_COLON] = ACTIONS(1),
    [anon_sym_DASH_GT] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_bool] = ACTIONS(1),
    [anon_sym_number] = ACTIONS(1),
    [sym_string_literal] = ACTIONS(1),
    [sym_true] = ACTIONS(1),
    [sym_false] = ACTIONS(1),
  },
  [1] = {
    [sym_module] = STATE(71),
    [sym__statement] = STATE(46),
    [sym__expression_statement] = STATE(46),
    [sym__expression] = STATE(14),
    [sym_binary_expression] = STATE(14),
    [sym__parenthesized_expression] = STATE(14),
    [sym_if_statement] = STATE(46),
    [sym_function_definition] = STATE(46),
    [sym_extern_function_declaration] = STATE(46),
    [sym_call_expression] = STATE(14),
    [ts_builtin_sym_end] = ACTIONS(3),
    [sym_identifier] = ACTIONS(5),
    [anon_sym_LPAREN] = ACTIONS(7),
    [anon_sym_if] = ACTIONS(9),
    [anon_sym_fn] = ACTIONS(11),
    [anon_sym_extern] = ACTIONS(13),
    [sym_string_literal] = ACTIONS(15),
    [sym_number] = ACTIONS(15),
    [sym_true] = ACTIONS(17),
    [sym_false] = ACTIONS(17),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 10,
    ACTIONS(5), 1,
      sym_identifier,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(9), 1,
      anon_sym_if,
    ACTIONS(11), 1,
      anon_sym_fn,
    ACTIONS(13), 1,
      anon_sym_extern,
    ACTIONS(19), 1,
      anon_sym_RBRACE,
    ACTIONS(15), 2,
      sym_string_literal,
      sym_number,
    ACTIONS(17), 2,
      sym_true,
      sym_false,
    STATE(14), 4,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
      sym_call_expression,
    STATE(58), 5,
      sym__statement,
      sym__expression_statement,
      sym_if_statement,
      sym_function_definition,
      sym_extern_function_declaration,
  [40] = 9,
    ACTIONS(5), 1,
      sym_identifier,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(9), 1,
      anon_sym_if,
    ACTIONS(11), 1,
      anon_sym_fn,
    ACTIONS(13), 1,
      anon_sym_extern,
    ACTIONS(15), 2,
      sym_string_literal,
      sym_number,
    ACTIONS(17), 2,
      sym_true,
      sym_false,
    STATE(14), 4,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
      sym_call_expression,
    STATE(53), 5,
      sym__statement,
      sym__expression_statement,
      sym_if_statement,
      sym_function_definition,
      sym_extern_function_declaration,
  [77] = 2,
    ACTIONS(23), 1,
      anon_sym_LPAREN,
    ACTIONS(21), 15,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_RPAREN,
      anon_sym_COMMA,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
  [98] = 1,
    ACTIONS(25), 15,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_RPAREN,
      anon_sym_COMMA,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
  [116] = 1,
    ACTIONS(27), 15,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_RPAREN,
      anon_sym_COMMA,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
  [134] = 5,
    ACTIONS(37), 1,
      anon_sym_AMP_AMP,
    ACTIONS(33), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(35), 2,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
    ACTIONS(31), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
    ACTIONS(29), 7,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_PIPE_PIPE,
      anon_sym_RPAREN,
      anon_sym_COMMA,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
  [160] = 4,
    ACTIONS(33), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(35), 2,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
    ACTIONS(31), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
    ACTIONS(29), 8,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_RPAREN,
      anon_sym_COMMA,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
  [184] = 3,
    ACTIONS(33), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(31), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
    ACTIONS(29), 10,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_RPAREN,
      anon_sym_COMMA,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
  [206] = 2,
    ACTIONS(31), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
    ACTIONS(29), 12,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_RPAREN,
      anon_sym_COMMA,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
  [226] = 1,
    ACTIONS(29), 15,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_RPAREN,
      anon_sym_COMMA,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
  [244] = 1,
    ACTIONS(39), 15,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_RPAREN,
      anon_sym_COMMA,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
  [262] = 1,
    ACTIONS(41), 15,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
      anon_sym_PLUS,
      anon_sym_DASH,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_RPAREN,
      anon_sym_COMMA,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
  [280] = 6,
    ACTIONS(37), 1,
      anon_sym_AMP_AMP,
    ACTIONS(45), 1,
      anon_sym_PIPE_PIPE,
    ACTIONS(33), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(35), 2,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
    ACTIONS(31), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
    ACTIONS(43), 3,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [305] = 8,
    ACTIONS(37), 1,
      anon_sym_AMP_AMP,
    ACTIONS(45), 1,
      anon_sym_PIPE_PIPE,
    ACTIONS(47), 1,
      anon_sym_RPAREN,
    ACTIONS(49), 1,
      anon_sym_COMMA,
    STATE(51), 1,
      aux_sym_call_expression_repeat1,
    ACTIONS(33), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(35), 2,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
    ACTIONS(31), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
  [334] = 6,
    ACTIONS(5), 1,
      sym_identifier,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    STATE(63), 1,
      sym_condition_expression,
    ACTIONS(51), 2,
      sym_string_literal,
      sym_number,
    ACTIONS(53), 2,
      sym_true,
      sym_false,
    STATE(25), 4,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
      sym_call_expression,
  [358] = 6,
    ACTIONS(37), 1,
      anon_sym_AMP_AMP,
    ACTIONS(45), 1,
      anon_sym_PIPE_PIPE,
    ACTIONS(33), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(35), 2,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
    ACTIONS(55), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
    ACTIONS(31), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
  [382] = 6,
    ACTIONS(5), 1,
      sym_identifier,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(57), 1,
      anon_sym_RPAREN,
    ACTIONS(59), 2,
      sym_string_literal,
      sym_number,
    ACTIONS(61), 2,
      sym_true,
      sym_false,
    STATE(15), 4,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
      sym_call_expression,
  [406] = 5,
    ACTIONS(5), 1,
      sym_identifier,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(63), 2,
      sym_string_literal,
      sym_number,
    ACTIONS(65), 2,
      sym_true,
      sym_false,
    STATE(10), 4,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
      sym_call_expression,
  [427] = 5,
    ACTIONS(5), 1,
      sym_identifier,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(67), 2,
      sym_string_literal,
      sym_number,
    ACTIONS(69), 2,
      sym_true,
      sym_false,
    STATE(11), 4,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
      sym_call_expression,
  [448] = 5,
    ACTIONS(5), 1,
      sym_identifier,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(71), 2,
      sym_string_literal,
      sym_number,
    ACTIONS(73), 2,
      sym_true,
      sym_false,
    STATE(9), 4,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
      sym_call_expression,
  [469] = 5,
    ACTIONS(5), 1,
      sym_identifier,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(75), 2,
      sym_string_literal,
      sym_number,
    ACTIONS(77), 2,
      sym_true,
      sym_false,
    STATE(8), 4,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
      sym_call_expression,
  [490] = 5,
    ACTIONS(5), 1,
      sym_identifier,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(79), 2,
      sym_string_literal,
      sym_number,
    ACTIONS(81), 2,
      sym_true,
      sym_false,
    STATE(7), 4,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
      sym_call_expression,
  [511] = 5,
    ACTIONS(5), 1,
      sym_identifier,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(83), 2,
      sym_string_literal,
      sym_number,
    ACTIONS(85), 2,
      sym_true,
      sym_false,
    STATE(17), 4,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
      sym_call_expression,
  [532] = 6,
    ACTIONS(37), 1,
      anon_sym_AMP_AMP,
    ACTIONS(45), 1,
      anon_sym_PIPE_PIPE,
    ACTIONS(87), 1,
      anon_sym_LBRACE,
    ACTIONS(33), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(35), 2,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
    ACTIONS(31), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
  [555] = 6,
    ACTIONS(37), 1,
      anon_sym_AMP_AMP,
    ACTIONS(45), 1,
      anon_sym_PIPE_PIPE,
    ACTIONS(89), 1,
      anon_sym_RPAREN,
    ACTIONS(33), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(35), 2,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
    ACTIONS(31), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
  [578] = 5,
    ACTIONS(5), 1,
      sym_identifier,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(91), 2,
      sym_string_literal,
      sym_number,
    ACTIONS(93), 2,
      sym_true,
      sym_false,
    STATE(26), 4,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
      sym_call_expression,
  [599] = 1,
    ACTIONS(95), 6,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      anon_sym_COMMA,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
  [608] = 1,
    ACTIONS(97), 5,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_DASH_GT,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
  [616] = 1,
    ACTIONS(99), 5,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_DASH_GT,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
  [624] = 3,
    ACTIONS(103), 1,
      anon_sym_DASH_GT,
    STATE(43), 1,
      sym_return_clause,
    ACTIONS(101), 3,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [636] = 3,
    ACTIONS(107), 1,
      anon_sym_else,
    STATE(56), 1,
      sym_else_clause,
    ACTIONS(105), 3,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [648] = 1,
    ACTIONS(109), 5,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_DASH_GT,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
  [656] = 1,
    ACTIONS(111), 4,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
  [663] = 3,
    ACTIONS(113), 1,
      anon_sym_if,
    ACTIONS(115), 1,
      anon_sym_LBRACE,
    STATE(54), 2,
      sym_if_statement,
      sym_block,
  [674] = 3,
    ACTIONS(119), 1,
      anon_sym_SEMI,
    STATE(36), 1,
      aux_sym_module_repeat1,
    ACTIONS(117), 2,
      ts_builtin_sym_end,
      anon_sym_RBRACE,
  [685] = 1,
    ACTIONS(122), 4,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_else,
      anon_sym_RBRACE,
  [692] = 4,
    ACTIONS(103), 1,
      anon_sym_DASH_GT,
    ACTIONS(115), 1,
      anon_sym_LBRACE,
    STATE(47), 1,
      sym_block,
    STATE(62), 1,
      sym_return_clause,
  [705] = 1,
    ACTIONS(124), 4,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_else,
      anon_sym_RBRACE,
  [712] = 1,
    ACTIONS(126), 4,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_else,
      anon_sym_RBRACE,
  [719] = 3,
    ACTIONS(128), 1,
      anon_sym_SEMI,
    ACTIONS(130), 1,
      anon_sym_RBRACE,
    STATE(36), 1,
      aux_sym_module_repeat1,
  [729] = 1,
    ACTIONS(132), 3,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [735] = 1,
    ACTIONS(134), 3,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [741] = 3,
    ACTIONS(136), 1,
      anon_sym_RPAREN,
    ACTIONS(138), 1,
      anon_sym_COMMA,
    STATE(57), 1,
      aux_sym_parameter_clause_repeat1,
  [751] = 2,
    STATE(34), 1,
      sym_type,
    ACTIONS(140), 2,
      anon_sym_bool,
      anon_sym_number,
  [759] = 3,
    ACTIONS(128), 1,
      anon_sym_SEMI,
    ACTIONS(142), 1,
      ts_builtin_sym_end,
    STATE(50), 1,
      aux_sym_module_repeat1,
  [769] = 1,
    ACTIONS(144), 3,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [775] = 3,
    ACTIONS(55), 1,
      anon_sym_RPAREN,
    ACTIONS(146), 1,
      anon_sym_COMMA,
    STATE(48), 1,
      aux_sym_call_expression_repeat1,
  [785] = 3,
    ACTIONS(149), 1,
      anon_sym_RPAREN,
    ACTIONS(151), 1,
      anon_sym_COMMA,
    STATE(49), 1,
      aux_sym_parameter_clause_repeat1,
  [795] = 3,
    ACTIONS(128), 1,
      anon_sym_SEMI,
    ACTIONS(154), 1,
      ts_builtin_sym_end,
    STATE(36), 1,
      aux_sym_module_repeat1,
  [805] = 3,
    ACTIONS(49), 1,
      anon_sym_COMMA,
    ACTIONS(156), 1,
      anon_sym_RPAREN,
    STATE(48), 1,
      aux_sym_call_expression_repeat1,
  [815] = 3,
    ACTIONS(158), 1,
      sym_identifier,
    ACTIONS(160), 1,
      anon_sym_RPAREN,
    STATE(44), 1,
      sym_parameter,
  [825] = 1,
    ACTIONS(117), 3,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [831] = 1,
    ACTIONS(162), 3,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [837] = 2,
    STATE(65), 1,
      sym_type,
    ACTIONS(140), 2,
      anon_sym_bool,
      anon_sym_number,
  [845] = 1,
    ACTIONS(164), 3,
      ts_builtin_sym_end,
      anon_sym_SEMI,
      anon_sym_RBRACE,
  [851] = 3,
    ACTIONS(138), 1,
      anon_sym_COMMA,
    ACTIONS(166), 1,
      anon_sym_RPAREN,
    STATE(49), 1,
      aux_sym_parameter_clause_repeat1,
  [861] = 3,
    ACTIONS(128), 1,
      anon_sym_SEMI,
    ACTIONS(168), 1,
      anon_sym_RBRACE,
    STATE(41), 1,
      aux_sym_module_repeat1,
  [871] = 2,
    ACTIONS(170), 1,
      anon_sym_LPAREN,
    STATE(31), 1,
      sym_parameter_clause,
  [878] = 2,
    ACTIONS(170), 1,
      anon_sym_LPAREN,
    STATE(38), 1,
      sym_parameter_clause,
  [885] = 2,
    ACTIONS(158), 1,
      sym_identifier,
    STATE(64), 1,
      sym_parameter,
  [892] = 2,
    ACTIONS(115), 1,
      anon_sym_LBRACE,
    STATE(42), 1,
      sym_block,
  [899] = 2,
    ACTIONS(115), 1,
      anon_sym_LBRACE,
    STATE(32), 1,
      sym_block,
  [906] = 1,
    ACTIONS(149), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [911] = 1,
    ACTIONS(172), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [916] = 1,
    ACTIONS(174), 1,
      sym_identifier,
  [920] = 1,
    ACTIONS(176), 1,
      sym_string_literal,
  [924] = 1,
    ACTIONS(178), 1,
      sym_identifier,
  [928] = 1,
    ACTIONS(180), 1,
      anon_sym_COLON,
  [932] = 1,
    ACTIONS(182), 1,
      anon_sym_fn,
  [936] = 1,
    ACTIONS(184), 1,
      ts_builtin_sym_end,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 40,
  [SMALL_STATE(4)] = 77,
  [SMALL_STATE(5)] = 98,
  [SMALL_STATE(6)] = 116,
  [SMALL_STATE(7)] = 134,
  [SMALL_STATE(8)] = 160,
  [SMALL_STATE(9)] = 184,
  [SMALL_STATE(10)] = 206,
  [SMALL_STATE(11)] = 226,
  [SMALL_STATE(12)] = 244,
  [SMALL_STATE(13)] = 262,
  [SMALL_STATE(14)] = 280,
  [SMALL_STATE(15)] = 305,
  [SMALL_STATE(16)] = 334,
  [SMALL_STATE(17)] = 358,
  [SMALL_STATE(18)] = 382,
  [SMALL_STATE(19)] = 406,
  [SMALL_STATE(20)] = 427,
  [SMALL_STATE(21)] = 448,
  [SMALL_STATE(22)] = 469,
  [SMALL_STATE(23)] = 490,
  [SMALL_STATE(24)] = 511,
  [SMALL_STATE(25)] = 532,
  [SMALL_STATE(26)] = 555,
  [SMALL_STATE(27)] = 578,
  [SMALL_STATE(28)] = 599,
  [SMALL_STATE(29)] = 608,
  [SMALL_STATE(30)] = 616,
  [SMALL_STATE(31)] = 624,
  [SMALL_STATE(32)] = 636,
  [SMALL_STATE(33)] = 648,
  [SMALL_STATE(34)] = 656,
  [SMALL_STATE(35)] = 663,
  [SMALL_STATE(36)] = 674,
  [SMALL_STATE(37)] = 685,
  [SMALL_STATE(38)] = 692,
  [SMALL_STATE(39)] = 705,
  [SMALL_STATE(40)] = 712,
  [SMALL_STATE(41)] = 719,
  [SMALL_STATE(42)] = 729,
  [SMALL_STATE(43)] = 735,
  [SMALL_STATE(44)] = 741,
  [SMALL_STATE(45)] = 751,
  [SMALL_STATE(46)] = 759,
  [SMALL_STATE(47)] = 769,
  [SMALL_STATE(48)] = 775,
  [SMALL_STATE(49)] = 785,
  [SMALL_STATE(50)] = 795,
  [SMALL_STATE(51)] = 805,
  [SMALL_STATE(52)] = 815,
  [SMALL_STATE(53)] = 825,
  [SMALL_STATE(54)] = 831,
  [SMALL_STATE(55)] = 837,
  [SMALL_STATE(56)] = 845,
  [SMALL_STATE(57)] = 851,
  [SMALL_STATE(58)] = 861,
  [SMALL_STATE(59)] = 871,
  [SMALL_STATE(60)] = 878,
  [SMALL_STATE(61)] = 885,
  [SMALL_STATE(62)] = 892,
  [SMALL_STATE(63)] = 899,
  [SMALL_STATE(64)] = 906,
  [SMALL_STATE(65)] = 911,
  [SMALL_STATE(66)] = 916,
  [SMALL_STATE(67)] = 920,
  [SMALL_STATE(68)] = 924,
  [SMALL_STATE(69)] = 928,
  [SMALL_STATE(70)] = 932,
  [SMALL_STATE(71)] = 936,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_module, 0),
  [5] = {.entry = {.count = 1, .reusable = false}}, SHIFT(4),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [9] = {.entry = {.count = 1, .reusable = false}}, SHIFT(16),
  [11] = {.entry = {.count = 1, .reusable = false}}, SHIFT(68),
  [13] = {.entry = {.count = 1, .reusable = false}}, SHIFT(67),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [17] = {.entry = {.count = 1, .reusable = false}}, SHIFT(14),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
  [21] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__expression, 1),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [25] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call_expression, 5),
  [27] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call_expression, 4),
  [29] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binary_expression, 3),
  [31] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [33] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [35] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [37] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [39] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call_expression, 3),
  [41] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__parenthesized_expression, 3),
  [43] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__expression_statement, 1),
  [45] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [47] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [49] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [51] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [53] = {.entry = {.count = 1, .reusable = false}}, SHIFT(25),
  [55] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_call_expression_repeat1, 2),
  [57] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [59] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [61] = {.entry = {.count = 1, .reusable = false}}, SHIFT(15),
  [63] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [65] = {.entry = {.count = 1, .reusable = false}}, SHIFT(10),
  [67] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [69] = {.entry = {.count = 1, .reusable = false}}, SHIFT(11),
  [71] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [73] = {.entry = {.count = 1, .reusable = false}}, SHIFT(9),
  [75] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [77] = {.entry = {.count = 1, .reusable = false}}, SHIFT(8),
  [79] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [81] = {.entry = {.count = 1, .reusable = false}}, SHIFT(7),
  [83] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [85] = {.entry = {.count = 1, .reusable = false}}, SHIFT(17),
  [87] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_condition_expression, 1),
  [89] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [91] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [93] = {.entry = {.count = 1, .reusable = false}}, SHIFT(26),
  [95] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type, 1),
  [97] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameter_clause, 2),
  [99] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameter_clause, 4),
  [101] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_extern_function_declaration, 5),
  [103] = {.entry = {.count = 1, .reusable = true}}, SHIFT(45),
  [105] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_if_statement, 3),
  [107] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [109] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameter_clause, 3),
  [111] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_return_clause, 2),
  [113] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [115] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [117] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_module_repeat1, 2),
  [119] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_module_repeat1, 2), SHIFT_REPEAT(3),
  [122] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block, 4),
  [124] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block, 2),
  [126] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block, 3),
  [128] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [130] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [132] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_function_definition, 5),
  [134] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_extern_function_declaration, 6),
  [136] = {.entry = {.count = 1, .reusable = true}}, SHIFT(33),
  [138] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [140] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [142] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_module, 1),
  [144] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_function_definition, 4),
  [146] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_call_expression_repeat1, 2), SHIFT_REPEAT(24),
  [149] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_parameter_clause_repeat1, 2),
  [151] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_parameter_clause_repeat1, 2), SHIFT_REPEAT(61),
  [154] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_module, 2),
  [156] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [158] = {.entry = {.count = 1, .reusable = true}}, SHIFT(69),
  [160] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [162] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_else_clause, 2),
  [164] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_if_statement, 4),
  [166] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [168] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [170] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [172] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameter, 3),
  [174] = {.entry = {.count = 1, .reusable = true}}, SHIFT(59),
  [176] = {.entry = {.count = 1, .reusable = true}}, SHIFT(70),
  [178] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [180] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [182] = {.entry = {.count = 1, .reusable = true}}, SHIFT(66),
  [184] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
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
