#include "gtest/gtest.h"

#include "compiler/parser.h"

auto match_string(const std::string_view source, const std::string_view s_expr)
    -> void {
  auto parser = kero::compiler::Parser::Builder{}.build();
  EXPECT_TRUE(!!parser);
  auto tree = parser->parse(source);
  EXPECT_TRUE(!!tree);
  auto root_node_opt = tree->root_node();
  EXPECT_TRUE(!!root_node_opt);
  auto &root_node = *root_node_opt;
  auto string = root_node.string();
  EXPECT_EQ(string.string_view(), s_expr);
}

TEST(ParserTest, Empty) { match_string("", "(module)"); }

TEST(ParserTest, Bool) {
  match_string("true", "(module (true))");
  match_string("false", "(module (false))");
}

TEST(ParserTest, BinaryExpressionEqual) {
  match_string("true == true", "(module (binary_expression lhs: (true) op: "
                               "(equal) rhs: (true)))");
  match_string("true == false", "(module (binary_expression lhs: (true) op: "
                                "(equal) rhs: (false)))");
  match_string("false == true", "(module (binary_expression lhs: (false) op: "
                                "(equal) rhs: (true)))");
}

TEST(ParserTest, BinaryExpressionNotEqual) {
  match_string("true != true", "(module (binary_expression lhs: (true) op: "
                               "(not_equal) rhs: (true)))");
  match_string("true != false", "(module (binary_expression lhs: (true) op: "
                                "(not_equal) rhs: (false)))");
  match_string("false != true", "(module (binary_expression lhs: (false) op: "
                                "(not_equal) rhs: (true)))");
}

TEST(ParserTest, ParenthesizedExpression) {
  match_string("(true)", "(module (true))");
  match_string("(false)", "(module (false))");
  match_string("((true))", "(module (true))");
  match_string("((false))", "(module (false))");
}

TEST(ParserTest, ParenthesizedExpressionBinaryExpression) {
  match_string("(true == true)", "(module (binary_expression lhs: (true) op: "
                                 "(equal) rhs: (true)))");
  match_string("((true == true))", "(module (binary_expression lhs: (true) op: "
                                   "(equal) rhs: (true)))");
  match_string("((true) == (true))",
               "(module (binary_expression lhs: (true) op: "
               "(equal) rhs: (true)))");
  match_string("((true) == true)", "(module (binary_expression lhs: (true) op: "
                                   "(equal) rhs: (true)))");
  match_string("(true == (true))", "(module (binary_expression lhs: (true) op: "
                                   "(equal) rhs: (true)))");
}

TEST(ParserTest, MultipleBinaryExpressions) {
  match_string("true == true == true",
               "(module (binary_expression lhs: (binary_expression lhs: (true) "
               "op: (equal) rhs: (true)) op: (equal) rhs: (true)))");
  match_string("(true == true) == true",
               "(module (binary_expression lhs: (binary_expression lhs: (true) "
               "op: (equal) rhs: (true)) op: (equal) rhs: (true)))");
  match_string("true == (true == true)",
               "(module (binary_expression lhs: (true) op: (equal) rhs: "
               "(binary_expression lhs: (true) op: (equal) rhs: (true))))");
  match_string("(true == true) == (true == true)",
               "(module (binary_expression lhs: (binary_expression lhs: (true) "
               "op: (equal) rhs: (true)) op: (equal) rhs: (binary_expression "
               "lhs: (true) "
               "op: (equal) rhs: (true))))");
  match_string("(true == true) == ((true == true) == true)",
               "(module (binary_expression lhs: (binary_expression lhs: (true) "
               "op: (equal) rhs: (true)) op: (equal) rhs: (binary_expression "
               "lhs: (binary_expression lhs: (true) op: (equal) rhs: (true)) "
               "op: (equal) rhs: (true))))");
}
