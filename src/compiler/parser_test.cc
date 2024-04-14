#include "gtest/gtest.h"

#include "compiler/parser.h"

auto match_string(const std::string_view source, const std::string_view s_expr)
    -> void {
  auto parser = kero::compiler::Parser::Builder{}.build();
  EXPECT_TRUE(parser.has_value());
  auto tree = parser->parse(source);
  EXPECT_TRUE(tree.has_value());
  auto root_node = tree->root_node();
  EXPECT_TRUE(root_node.has_value());
  auto string = root_node->string();
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

TEST(ParserTest, LogicalAnd) {
  match_string("true && true", "(module (binary_expression lhs: (true) op: "
                               "(logical_and) rhs: (true)))");
  match_string("true && false", "(module (binary_expression lhs: (true) op: "
                                "(logical_and) rhs: (false)))");
  match_string("false && true", "(module (binary_expression lhs: (false) op: "
                                "(logical_and) rhs: (true)))");
}

TEST(ParserTest, LogicalOr) {
  match_string("true || true", "(module (binary_expression lhs: (true) op: "
                               "(logical_or) rhs: (true)))");
  match_string("true || false", "(module (binary_expression lhs: (true) op: "
                                "(logical_or) rhs: (false)))");
  match_string("false || true", "(module (binary_expression lhs: (false) op: "
                                "(logical_or) rhs: (true)))");
}

TEST(ParserTest, LogicalAndWithLogicalOr) {
  match_string("true && true || true",
               "(module (binary_expression lhs: (binary_expression lhs: (true) "
               "op: (logical_and) rhs: (true)) op: (logical_or) rhs: (true)))");
  match_string(
      "true || true && true",
      "(module (binary_expression lhs: (true) op: (logical_or) rhs: "
      "(binary_expression lhs: (true) op: (logical_and) rhs: (true))))");
}

TEST(ParserTest, ParenthesizedExpressionLogicalAndWithLogicalOr) {
  match_string("(true || true) && true",
               "(module (binary_expression lhs: (binary_expression lhs: (true) "
               "op: (logical_or) rhs: (true)) op: (logical_and) rhs: (true)))");
  match_string(
      "true && (true || true)",
      "(module (binary_expression lhs: (true) op: (logical_and) rhs: "
      "(binary_expression lhs: (true) op: (logical_or) rhs: (true))))");
}
