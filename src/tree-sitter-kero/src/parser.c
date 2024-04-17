#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 70
#define LARGE_STATE_COUNT 2
#define SYMBOL_COUNT 50
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
  sym_argument_clause = 44,
  sym_block = 45,
  sym_type = 46,
  aux_sym_module_repeat1 = 47,
  aux_sym_parameter_clause_repeat1 = 48,
  aux_sym_argument_clause_repeat1 = 49,
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
  [sym_argument_clause] = "argument_clause",
  [sym_block] = "block",
  [sym_type] = "type",
  [aux_sym_module_repeat1] = "module_repeat1",
  [aux_sym_parameter_clause_repeat1] = "parameter_clause_repeat1",
  [aux_sym_argument_clause_repeat1] = "argument_clause_repeat1",
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
  [sym_argument_clause] = sym_argument_clause,
  [sym_block] = sym_block,
  [sym_type] = sym_type,
  [aux_sym_module_repeat1] = aux_sym_module_repeat1,
  [aux_sym_parameter_clause_repeat1] = aux_sym_parameter_clause_repeat1,
  [aux_sym_argument_clause_repeat1] = aux_sym_argument_clause_repeat1,
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
  [sym_argument_clause] = {
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
  [aux_sym_argument_clause_repeat1] = {
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
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(11);
      if (lookahead == '!') ADVANCE(6);
      if (lookahead == '"') ADVANCE(2);
      if (lookahead == '%') ADVANCE(15);
      if (lookahead == '&') ADVANCE(3);
      if (lookahead == '(') ADVANCE(23);
      if (lookahead == ')') ADVANCE(24);
      if (lookahead == '*') ADVANCE(13);
      if (lookahead == '+') ADVANCE(16);
      if (lookahead == ',') ADVANCE(25);
      if (lookahead == '-') ADVANCE(18);
      if (lookahead == '/') ADVANCE(14);
      if (lookahead == ':') ADVANCE(26);
      if (lookahead == ';') ADVANCE(12);
      if (lookahead == '=') ADVANCE(7);
      if (lookahead == '{') ADVANCE(28);
      if (lookahead == '|') ADVANCE(8);
      if (lookahead == '}') ADVANCE(29);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(0)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(30);
      END_STATE();
    case 1:
      if (lookahead == '!') ADVANCE(6);
      if (lookahead == '%') ADVANCE(15);
      if (lookahead == '&') ADVANCE(3);
      if (lookahead == '(') ADVANCE(23);
      if (lookahead == ')') ADVANCE(24);
      if (lookahead == '*') ADVANCE(13);
      if (lookahead == '+') ADVANCE(16);
      if (lookahead == ',') ADVANCE(25);
      if (lookahead == '-') ADVANCE(17);
      if (lookahead == '/') ADVANCE(14);
      if (lookahead == ';') ADVANCE(12);
      if (lookahead == '=') ADVANCE(7);
      if (lookahead == '{') ADVANCE(28);
      if (lookahead == '|') ADVANCE(8);
      if (('\t' <= lookahead && lookahead <= '\r') ||
          lookahead == ' ') SKIP(1)
      END_STATE();
    case 2:
      if (lookahead == '"') ADVANCE(31);
      if (lookahead != 0) ADVANCE(2);
      END_STATE();
    case 3:
      if (lookahead == '&') ADVANCE(21);
      END_STATE();
    case 4:
      if (lookahead == '.') ADVANCE(9);
      END_STATE();
    case 5:
      if (lookahead == '0') ADVANCE(4);
      if (lookahead == '>') ADVANCE(27);
      if (('1' <= lookahead && lookahead <= '9')) ADVANCE(33);
      END_STATE();
    case 6:
      if (lookahead == '=') ADVANCE(20);
      END_STATE();
    case 7:
      if (lookahead == '=') ADVANCE(19);
      END_STATE();
    case 8:
      if (lookahead == '|') ADVANCE(22);
      END_STATE();
    case 9:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(34);
      END_STATE();
    case 10:
      if (eof) ADVANCE(11);
      if (lookahead == '"') ADVANCE(2);
      if (lookahead == '(') ADVANCE(23);
      if (lookahead == ')') ADVANCE(24);
      if (lookahead == '-') ADVANCE(5);
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
      if (lookahead == '.') ADVANCE(9);
      END_STATE();
    case 33:
      ACCEPT_TOKEN(sym_number);
      if (lookahead == '.') ADVANCE(9);
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
  [4] = {.lex_state = 10},
  [5] = {.lex_state = 10},
  [6] = {.lex_state = 1},
  [7] = {.lex_state = 1},
  [8] = {.lex_state = 1},
  [9] = {.lex_state = 1},
  [10] = {.lex_state = 1},
  [11] = {.lex_state = 1},
  [12] = {.lex_state = 1},
  [13] = {.lex_state = 1},
  [14] = {.lex_state = 1},
  [15] = {.lex_state = 1},
  [16] = {.lex_state = 1},
  [17] = {.lex_state = 1},
  [18] = {.lex_state = 10},
  [19] = {.lex_state = 10},
  [20] = {.lex_state = 1},
  [21] = {.lex_state = 10},
  [22] = {.lex_state = 1},
  [23] = {.lex_state = 10},
  [24] = {.lex_state = 10},
  [25] = {.lex_state = 10},
  [26] = {.lex_state = 10},
  [27] = {.lex_state = 10},
  [28] = {.lex_state = 10},
  [29] = {.lex_state = 1},
  [30] = {.lex_state = 10},
  [31] = {.lex_state = 1},
  [32] = {.lex_state = 0},
  [33] = {.lex_state = 10},
  [34] = {.lex_state = 0},
  [35] = {.lex_state = 0},
  [36] = {.lex_state = 0},
  [37] = {.lex_state = 0},
  [38] = {.lex_state = 10},
  [39] = {.lex_state = 0},
  [40] = {.lex_state = 10},
  [41] = {.lex_state = 0},
  [42] = {.lex_state = 10},
  [43] = {.lex_state = 0},
  [44] = {.lex_state = 10},
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
    [sym_module] = STATE(68),
    [sym__statement] = STATE(58),
    [sym__expression_statement] = STATE(58),
    [sym__expression] = STATE(22),
    [sym_binary_expression] = STATE(22),
    [sym__parenthesized_expression] = STATE(22),
    [sym_if_statement] = STATE(58),
    [sym_function_definition] = STATE(58),
    [sym_extern_function_declaration] = STATE(58),
    [sym_call_expression] = STATE(22),
    [aux_sym_module_repeat1] = STATE(4),
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
  [0] = 11,
    ACTIONS(21), 1,
      sym_identifier,
    ACTIONS(24), 1,
      anon_sym_LPAREN,
    ACTIONS(27), 1,
      anon_sym_if,
    ACTIONS(30), 1,
      anon_sym_fn,
    ACTIONS(33), 1,
      anon_sym_extern,
    STATE(2), 1,
      aux_sym_module_repeat1,
    ACTIONS(19), 2,
      ts_builtin_sym_end,
      anon_sym_RBRACE,
    ACTIONS(36), 2,
      sym_string_literal,
      sym_number,
    ACTIONS(39), 2,
      sym_true,
      sym_false,
    STATE(22), 4,
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
  [44] = 11,
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
    ACTIONS(42), 1,
      anon_sym_RBRACE,
    STATE(2), 1,
      aux_sym_module_repeat1,
    ACTIONS(15), 2,
      sym_string_literal,
      sym_number,
    ACTIONS(17), 2,
      sym_true,
      sym_false,
    STATE(22), 4,
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
  [87] = 11,
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
    ACTIONS(44), 1,
      ts_builtin_sym_end,
    STATE(2), 1,
      aux_sym_module_repeat1,
    ACTIONS(15), 2,
      sym_string_literal,
      sym_number,
    ACTIONS(17), 2,
      sym_true,
      sym_false,
    STATE(22), 4,
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
  [130] = 11,
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
    ACTIONS(46), 1,
      anon_sym_RBRACE,
    STATE(3), 1,
      aux_sym_module_repeat1,
    ACTIONS(15), 2,
      sym_string_literal,
      sym_number,
    ACTIONS(17), 2,
      sym_true,
      sym_false,
    STATE(22), 4,
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
  [173] = 3,
    ACTIONS(50), 1,
      anon_sym_LPAREN,
    STATE(16), 1,
      sym_argument_clause,
    ACTIONS(48), 13,
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
  [195] = 1,
    ACTIONS(52), 13,
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
  [211] = 1,
    ACTIONS(54), 13,
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
  [227] = 5,
    ACTIONS(64), 1,
      anon_sym_AMP_AMP,
    ACTIONS(60), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(62), 2,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
    ACTIONS(58), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
    ACTIONS(56), 5,
      anon_sym_SEMI,
      anon_sym_PIPE_PIPE,
      anon_sym_RPAREN,
      anon_sym_COMMA,
      anon_sym_LBRACE,
  [251] = 4,
    ACTIONS(60), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(62), 2,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
    ACTIONS(58), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
    ACTIONS(56), 6,
      anon_sym_SEMI,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_RPAREN,
      anon_sym_COMMA,
      anon_sym_LBRACE,
  [273] = 3,
    ACTIONS(60), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(58), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
    ACTIONS(56), 8,
      anon_sym_SEMI,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
      anon_sym_AMP_AMP,
      anon_sym_PIPE_PIPE,
      anon_sym_RPAREN,
      anon_sym_COMMA,
      anon_sym_LBRACE,
  [293] = 2,
    ACTIONS(58), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
    ACTIONS(56), 10,
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
  [311] = 1,
    ACTIONS(56), 13,
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
  [327] = 1,
    ACTIONS(66), 13,
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
  [343] = 1,
    ACTIONS(68), 13,
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
  [359] = 1,
    ACTIONS(70), 13,
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
  [375] = 8,
    ACTIONS(64), 1,
      anon_sym_AMP_AMP,
    ACTIONS(72), 1,
      anon_sym_PIPE_PIPE,
    ACTIONS(74), 1,
      anon_sym_RPAREN,
    ACTIONS(76), 1,
      anon_sym_COMMA,
    STATE(47), 1,
      aux_sym_argument_clause_repeat1,
    ACTIONS(60), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(62), 2,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
    ACTIONS(58), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
  [404] = 6,
    ACTIONS(5), 1,
      sym_identifier,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(78), 1,
      anon_sym_RPAREN,
    ACTIONS(80), 2,
      sym_string_literal,
      sym_number,
    ACTIONS(82), 2,
      sym_true,
      sym_false,
    STATE(17), 4,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
      sym_call_expression,
  [428] = 6,
    ACTIONS(5), 1,
      sym_identifier,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    STATE(57), 1,
      sym_condition_expression,
    ACTIONS(84), 2,
      sym_string_literal,
      sym_number,
    ACTIONS(86), 2,
      sym_true,
      sym_false,
    STATE(29), 4,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
      sym_call_expression,
  [452] = 6,
    ACTIONS(64), 1,
      anon_sym_AMP_AMP,
    ACTIONS(72), 1,
      anon_sym_PIPE_PIPE,
    ACTIONS(60), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(62), 2,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
    ACTIONS(88), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
    ACTIONS(58), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
  [476] = 2,
    ACTIONS(19), 5,
      ts_builtin_sym_end,
      anon_sym_LPAREN,
      anon_sym_RBRACE,
      sym_string_literal,
      sym_number,
    ACTIONS(90), 6,
      anon_sym_if,
      anon_sym_fn,
      anon_sym_extern,
      sym_identifier,
      sym_true,
      sym_false,
  [492] = 6,
    ACTIONS(64), 1,
      anon_sym_AMP_AMP,
    ACTIONS(72), 1,
      anon_sym_PIPE_PIPE,
    ACTIONS(92), 1,
      anon_sym_SEMI,
    ACTIONS(60), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(62), 2,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
    ACTIONS(58), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
  [515] = 5,
    ACTIONS(5), 1,
      sym_identifier,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(94), 2,
      sym_string_literal,
      sym_number,
    ACTIONS(96), 2,
      sym_true,
      sym_false,
    STATE(13), 4,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
      sym_call_expression,
  [536] = 5,
    ACTIONS(5), 1,
      sym_identifier,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(98), 2,
      sym_string_literal,
      sym_number,
    ACTIONS(100), 2,
      sym_true,
      sym_false,
    STATE(12), 4,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
      sym_call_expression,
  [557] = 5,
    ACTIONS(5), 1,
      sym_identifier,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(102), 2,
      sym_string_literal,
      sym_number,
    ACTIONS(104), 2,
      sym_true,
      sym_false,
    STATE(11), 4,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
      sym_call_expression,
  [578] = 5,
    ACTIONS(5), 1,
      sym_identifier,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(106), 2,
      sym_string_literal,
      sym_number,
    ACTIONS(108), 2,
      sym_true,
      sym_false,
    STATE(10), 4,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
      sym_call_expression,
  [599] = 5,
    ACTIONS(5), 1,
      sym_identifier,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(110), 2,
      sym_string_literal,
      sym_number,
    ACTIONS(112), 2,
      sym_true,
      sym_false,
    STATE(9), 4,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
      sym_call_expression,
  [620] = 5,
    ACTIONS(5), 1,
      sym_identifier,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(114), 2,
      sym_string_literal,
      sym_number,
    ACTIONS(116), 2,
      sym_true,
      sym_false,
    STATE(20), 4,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
      sym_call_expression,
  [641] = 6,
    ACTIONS(64), 1,
      anon_sym_AMP_AMP,
    ACTIONS(72), 1,
      anon_sym_PIPE_PIPE,
    ACTIONS(118), 1,
      anon_sym_LBRACE,
    ACTIONS(60), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(62), 2,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
    ACTIONS(58), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
  [664] = 5,
    ACTIONS(5), 1,
      sym_identifier,
    ACTIONS(7), 1,
      anon_sym_LPAREN,
    ACTIONS(120), 2,
      sym_string_literal,
      sym_number,
    ACTIONS(122), 2,
      sym_true,
      sym_false,
    STATE(31), 4,
      sym__expression,
      sym_binary_expression,
      sym__parenthesized_expression,
      sym_call_expression,
  [685] = 6,
    ACTIONS(64), 1,
      anon_sym_AMP_AMP,
    ACTIONS(72), 1,
      anon_sym_PIPE_PIPE,
    ACTIONS(124), 1,
      anon_sym_RPAREN,
    ACTIONS(60), 2,
      anon_sym_PLUS,
      anon_sym_DASH,
    ACTIONS(62), 2,
      anon_sym_EQ_EQ,
      anon_sym_BANG_EQ,
    ACTIONS(58), 3,
      anon_sym_STAR,
      anon_sym_SLASH,
      anon_sym_PERCENT,
  [708] = 1,
    ACTIONS(126), 4,
      anon_sym_SEMI,
      anon_sym_RPAREN,
      anon_sym_COMMA,
      anon_sym_LBRACE,
  [715] = 4,
    ACTIONS(128), 1,
      anon_sym_DASH_GT,
    ACTIONS(130), 1,
      anon_sym_LBRACE,
    STATE(55), 1,
      sym_return_clause,
    STATE(65), 1,
      sym_block,
  [728] = 3,
    ACTIONS(130), 1,
      anon_sym_LBRACE,
    ACTIONS(132), 1,
      anon_sym_if,
    STATE(66), 2,
      sym_if_statement,
      sym_block,
  [739] = 3,
    ACTIONS(134), 1,
      anon_sym_RPAREN,
    ACTIONS(136), 1,
      anon_sym_COMMA,
    STATE(43), 1,
      aux_sym_parameter_clause_repeat1,
  [749] = 3,
    ACTIONS(138), 1,
      sym_identifier,
    ACTIONS(140), 1,
      anon_sym_RPAREN,
    STATE(35), 1,
      sym_parameter,
  [759] = 3,
    ACTIONS(142), 1,
      anon_sym_RPAREN,
    ACTIONS(144), 1,
      anon_sym_COMMA,
    STATE(37), 1,
      aux_sym_parameter_clause_repeat1,
  [769] = 1,
    ACTIONS(147), 3,
      anon_sym_SEMI,
      anon_sym_DASH_GT,
      anon_sym_LBRACE,
  [775] = 3,
    ACTIONS(88), 1,
      anon_sym_RPAREN,
    ACTIONS(149), 1,
      anon_sym_COMMA,
    STATE(39), 1,
      aux_sym_argument_clause_repeat1,
  [785] = 3,
    ACTIONS(128), 1,
      anon_sym_DASH_GT,
    ACTIONS(152), 1,
      anon_sym_SEMI,
    STATE(69), 1,
      sym_return_clause,
  [795] = 3,
    ACTIONS(154), 1,
      anon_sym_SEMI,
    ACTIONS(156), 1,
      anon_sym_else,
    STATE(61), 1,
      sym_else_clause,
  [805] = 1,
    ACTIONS(158), 3,
      anon_sym_SEMI,
      anon_sym_DASH_GT,
      anon_sym_LBRACE,
  [811] = 3,
    ACTIONS(136), 1,
      anon_sym_COMMA,
    ACTIONS(160), 1,
      anon_sym_RPAREN,
    STATE(37), 1,
      aux_sym_parameter_clause_repeat1,
  [821] = 1,
    ACTIONS(162), 3,
      anon_sym_SEMI,
      anon_sym_DASH_GT,
      anon_sym_LBRACE,
  [827] = 2,
    STATE(49), 1,
      sym_type,
    ACTIONS(164), 2,
      anon_sym_bool,
      anon_sym_number,
  [835] = 2,
    STATE(53), 1,
      sym_type,
    ACTIONS(164), 2,
      anon_sym_bool,
      anon_sym_number,
  [843] = 3,
    ACTIONS(76), 1,
      anon_sym_COMMA,
    ACTIONS(166), 1,
      anon_sym_RPAREN,
    STATE(39), 1,
      aux_sym_argument_clause_repeat1,
  [853] = 1,
    ACTIONS(168), 2,
      anon_sym_SEMI,
      anon_sym_else,
  [858] = 1,
    ACTIONS(170), 2,
      anon_sym_SEMI,
      anon_sym_LBRACE,
  [863] = 2,
    ACTIONS(172), 1,
      anon_sym_LPAREN,
    STATE(40), 1,
      sym_parameter_clause,
  [870] = 1,
    ACTIONS(174), 2,
      anon_sym_SEMI,
      anon_sym_else,
  [875] = 1,
    ACTIONS(142), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [880] = 1,
    ACTIONS(176), 2,
      anon_sym_RPAREN,
      anon_sym_COMMA,
  [885] = 2,
    ACTIONS(172), 1,
      anon_sym_LPAREN,
    STATE(33), 1,
      sym_parameter_clause,
  [892] = 2,
    ACTIONS(130), 1,
      anon_sym_LBRACE,
    STATE(60), 1,
      sym_block,
  [899] = 2,
    ACTIONS(138), 1,
      sym_identifier,
    STATE(52), 1,
      sym_parameter,
  [906] = 2,
    ACTIONS(130), 1,
      anon_sym_LBRACE,
    STATE(41), 1,
      sym_block,
  [913] = 1,
    ACTIONS(178), 1,
      anon_sym_SEMI,
  [917] = 1,
    ACTIONS(180), 1,
      sym_identifier,
  [921] = 1,
    ACTIONS(182), 1,
      anon_sym_SEMI,
  [925] = 1,
    ACTIONS(184), 1,
      anon_sym_SEMI,
  [929] = 1,
    ACTIONS(186), 1,
      anon_sym_fn,
  [933] = 1,
    ACTIONS(188), 1,
      anon_sym_COLON,
  [937] = 1,
    ACTIONS(190), 1,
      sym_string_literal,
  [941] = 1,
    ACTIONS(192), 1,
      anon_sym_SEMI,
  [945] = 1,
    ACTIONS(194), 1,
      anon_sym_SEMI,
  [949] = 1,
    ACTIONS(196), 1,
      sym_identifier,
  [953] = 1,
    ACTIONS(198), 1,
      ts_builtin_sym_end,
  [957] = 1,
    ACTIONS(200), 1,
      anon_sym_SEMI,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(2)] = 0,
  [SMALL_STATE(3)] = 44,
  [SMALL_STATE(4)] = 87,
  [SMALL_STATE(5)] = 130,
  [SMALL_STATE(6)] = 173,
  [SMALL_STATE(7)] = 195,
  [SMALL_STATE(8)] = 211,
  [SMALL_STATE(9)] = 227,
  [SMALL_STATE(10)] = 251,
  [SMALL_STATE(11)] = 273,
  [SMALL_STATE(12)] = 293,
  [SMALL_STATE(13)] = 311,
  [SMALL_STATE(14)] = 327,
  [SMALL_STATE(15)] = 343,
  [SMALL_STATE(16)] = 359,
  [SMALL_STATE(17)] = 375,
  [SMALL_STATE(18)] = 404,
  [SMALL_STATE(19)] = 428,
  [SMALL_STATE(20)] = 452,
  [SMALL_STATE(21)] = 476,
  [SMALL_STATE(22)] = 492,
  [SMALL_STATE(23)] = 515,
  [SMALL_STATE(24)] = 536,
  [SMALL_STATE(25)] = 557,
  [SMALL_STATE(26)] = 578,
  [SMALL_STATE(27)] = 599,
  [SMALL_STATE(28)] = 620,
  [SMALL_STATE(29)] = 641,
  [SMALL_STATE(30)] = 664,
  [SMALL_STATE(31)] = 685,
  [SMALL_STATE(32)] = 708,
  [SMALL_STATE(33)] = 715,
  [SMALL_STATE(34)] = 728,
  [SMALL_STATE(35)] = 739,
  [SMALL_STATE(36)] = 749,
  [SMALL_STATE(37)] = 759,
  [SMALL_STATE(38)] = 769,
  [SMALL_STATE(39)] = 775,
  [SMALL_STATE(40)] = 785,
  [SMALL_STATE(41)] = 795,
  [SMALL_STATE(42)] = 805,
  [SMALL_STATE(43)] = 811,
  [SMALL_STATE(44)] = 821,
  [SMALL_STATE(45)] = 827,
  [SMALL_STATE(46)] = 835,
  [SMALL_STATE(47)] = 843,
  [SMALL_STATE(48)] = 853,
  [SMALL_STATE(49)] = 858,
  [SMALL_STATE(50)] = 863,
  [SMALL_STATE(51)] = 870,
  [SMALL_STATE(52)] = 875,
  [SMALL_STATE(53)] = 880,
  [SMALL_STATE(54)] = 885,
  [SMALL_STATE(55)] = 892,
  [SMALL_STATE(56)] = 899,
  [SMALL_STATE(57)] = 906,
  [SMALL_STATE(58)] = 913,
  [SMALL_STATE(59)] = 917,
  [SMALL_STATE(60)] = 921,
  [SMALL_STATE(61)] = 925,
  [SMALL_STATE(62)] = 929,
  [SMALL_STATE(63)] = 933,
  [SMALL_STATE(64)] = 937,
  [SMALL_STATE(65)] = 941,
  [SMALL_STATE(66)] = 945,
  [SMALL_STATE(67)] = 949,
  [SMALL_STATE(68)] = 953,
  [SMALL_STATE(69)] = 957,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_module, 0),
  [5] = {.entry = {.count = 1, .reusable = false}}, SHIFT(6),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [9] = {.entry = {.count = 1, .reusable = false}}, SHIFT(19),
  [11] = {.entry = {.count = 1, .reusable = false}}, SHIFT(59),
  [13] = {.entry = {.count = 1, .reusable = false}}, SHIFT(64),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [17] = {.entry = {.count = 1, .reusable = false}}, SHIFT(22),
  [19] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_module_repeat1, 2),
  [21] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_module_repeat1, 2), SHIFT_REPEAT(6),
  [24] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_module_repeat1, 2), SHIFT_REPEAT(30),
  [27] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_module_repeat1, 2), SHIFT_REPEAT(19),
  [30] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_module_repeat1, 2), SHIFT_REPEAT(59),
  [33] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_module_repeat1, 2), SHIFT_REPEAT(64),
  [36] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_module_repeat1, 2), SHIFT_REPEAT(22),
  [39] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_module_repeat1, 2), SHIFT_REPEAT(22),
  [42] = {.entry = {.count = 1, .reusable = true}}, SHIFT(48),
  [44] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_module, 1),
  [46] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [48] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__expression, 1),
  [50] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [52] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_argument_clause, 4),
  [54] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_argument_clause, 3),
  [56] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binary_expression, 3),
  [58] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [60] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [62] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [64] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [66] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__parenthesized_expression, 3),
  [68] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_argument_clause, 2),
  [70] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call_expression, 2),
  [72] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [74] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [76] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [78] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [80] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [82] = {.entry = {.count = 1, .reusable = false}}, SHIFT(17),
  [84] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [86] = {.entry = {.count = 1, .reusable = false}}, SHIFT(29),
  [88] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_argument_clause_repeat1, 2),
  [90] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_module_repeat1, 2),
  [92] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__expression_statement, 1),
  [94] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [96] = {.entry = {.count = 1, .reusable = false}}, SHIFT(13),
  [98] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [100] = {.entry = {.count = 1, .reusable = false}}, SHIFT(12),
  [102] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [104] = {.entry = {.count = 1, .reusable = false}}, SHIFT(11),
  [106] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [108] = {.entry = {.count = 1, .reusable = false}}, SHIFT(10),
  [110] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [112] = {.entry = {.count = 1, .reusable = false}}, SHIFT(9),
  [114] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [116] = {.entry = {.count = 1, .reusable = false}}, SHIFT(20),
  [118] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_condition_expression, 1),
  [120] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [122] = {.entry = {.count = 1, .reusable = false}}, SHIFT(31),
  [124] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [126] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_type, 1),
  [128] = {.entry = {.count = 1, .reusable = true}}, SHIFT(45),
  [130] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [132] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [134] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [136] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
  [138] = {.entry = {.count = 1, .reusable = true}}, SHIFT(63),
  [140] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [142] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_parameter_clause_repeat1, 2),
  [144] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_parameter_clause_repeat1, 2), SHIFT_REPEAT(56),
  [147] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameter_clause, 4),
  [149] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_argument_clause_repeat1, 2), SHIFT_REPEAT(28),
  [152] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_extern_function_declaration, 5),
  [154] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_if_statement, 3),
  [156] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [158] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameter_clause, 2),
  [160] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [162] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameter_clause, 3),
  [164] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [166] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [168] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block, 3),
  [170] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_return_clause, 2),
  [172] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [174] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_block, 2),
  [176] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameter, 3),
  [178] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [180] = {.entry = {.count = 1, .reusable = true}}, SHIFT(54),
  [182] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_function_definition, 5),
  [184] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_if_statement, 4),
  [186] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [188] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [190] = {.entry = {.count = 1, .reusable = true}}, SHIFT(62),
  [192] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_function_definition, 4),
  [194] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_else_clause, 2),
  [196] = {.entry = {.count = 1, .reusable = true}}, SHIFT(50),
  [198] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [200] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_extern_function_declaration, 6),
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
