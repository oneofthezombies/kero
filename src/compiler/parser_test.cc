#include "gtest/gtest.h"

#include "compiler/parser.h"

auto match_string(const std::string_view source, const std::string_view s_expr)
    -> void {
  auto parser = kero::compiler::Parser::Builder{}
                    //.set_console_logger()
                    //.set_print_dot_graphs_to_stdout()
                    .build();
  EXPECT_TRUE(parser.has_value());
  auto tree = parser->parse(source);
  EXPECT_TRUE(tree.has_value());
  auto root_node = tree->root_node();
  auto string = root_node.string();
  EXPECT_EQ(string.string_view(), s_expr);
}

TEST(ParserTest, Empty) { match_string("", "(module)"); }

TEST(ParserTest, Bool) {
  match_string("true", "(module (true))");
  match_string("false", "(module (false))");
}

TEST(ParserTest, BinaryExpressionEqual) {
  match_string("true == true",
               "(module (binary_expression left: (true) operator: "
               "(equal) right: (true)))");
  match_string("true == false",
               "(module (binary_expression left: (true) operator: "
               "(equal) right: (false)))");
  match_string("false == true",
               "(module (binary_expression left: (false) operator: "
               "(equal) right: (true)))");
}

TEST(ParserTest, BinaryExpressionNotEqual) {
  match_string("true != true",
               "(module (binary_expression left: (true) operator: "
               "(not_equal) right: (true)))");
  match_string("true != false",
               "(module (binary_expression left: (true) operator: "
               "(not_equal) right: (false)))");
  match_string("false != true",
               "(module (binary_expression left: (false) operator: "
               "(not_equal) right: (true)))");
}

TEST(ParserTest, ParenthesizedExpression) {
  match_string("(true)", "(module (true))");
  match_string("(false)", "(module (false))");
  match_string("((true))", "(module (true))");
  match_string("((false))", "(module (false))");
}

TEST(ParserTest, ParenthesizedExpressionBinaryExpression) {
  match_string("(true == true)",
               "(module (binary_expression left: (true) operator: "
               "(equal) right: (true)))");
  match_string("((true == true))",
               "(module (binary_expression left: (true) operator: "
               "(equal) right: (true)))");
  match_string("((true) == (true))",
               "(module (binary_expression left: (true) operator: "
               "(equal) right: (true)))");
  match_string("((true) == true)",
               "(module (binary_expression left: (true) operator: "
               "(equal) right: (true)))");
  match_string("(true == (true))",
               "(module (binary_expression left: (true) operator: "
               "(equal) right: (true)))");
}

TEST(ParserTest, MultipleBinaryExpressions) {
  match_string(
      "true == true == true",
      "(module (binary_expression left: (binary_expression left: (true) "
      "operator: (equal) right: (true)) operator: (equal) right: (true)))");
  match_string(
      "(true == true) == true",
      "(module (binary_expression left: (binary_expression left: (true) "
      "operator: (equal) right: (true)) operator: (equal) right: (true)))");
  match_string(
      "true == (true == true)",
      "(module (binary_expression left: (true) operator: (equal) right: "
      "(binary_expression left: (true) operator: (equal) right: (true))))");
  match_string(
      "(true == true) == (true == true)",
      "(module (binary_expression left: (binary_expression left: (true) "
      "operator: (equal) right: (true)) operator: (equal) right: "
      "(binary_expression "
      "left: (true) "
      "operator: (equal) right: (true))))");
  match_string(
      "(true == true) == ((true == true) == true)",
      "(module (binary_expression left: (binary_expression left: (true) "
      "operator: (equal) right: (true)) operator: (equal) right: "
      "(binary_expression "
      "left: (binary_expression left: (true) operator: (equal) right: (true)) "
      "operator: (equal) right: (true))))");
}

TEST(ParserTest, LogicalAnd) {
  match_string("true && true",
               "(module (binary_expression left: (true) operator: "
               "(logical_and) right: (true)))");
  match_string("true && false",
               "(module (binary_expression left: (true) operator: "
               "(logical_and) right: (false)))");
  match_string("false && true",
               "(module (binary_expression left: (false) operator: "
               "(logical_and) right: (true)))");
}

TEST(ParserTest, LogicalOr) {
  match_string("true || true",
               "(module (binary_expression left: (true) operator: "
               "(logical_or) right: (true)))");
  match_string("true || false",
               "(module (binary_expression left: (true) operator: "
               "(logical_or) right: (false)))");
  match_string("false || true",
               "(module (binary_expression left: (false) operator: "
               "(logical_or) right: (true)))");
}

TEST(ParserTest, LogicalAndWithLogicalOr) {
  match_string(
      "true && true || true",
      "(module (binary_expression left: (binary_expression left: (true) "
      "operator: (logical_and) right: (true)) operator: (logical_or) right: "
      "(true)))");
  match_string(
      "true || true && true",
      "(module (binary_expression left: (true) operator: (logical_or) right: "
      "(binary_expression left: (true) operator: (logical_and) right: "
      "(true))))");
}

TEST(ParserTest, ParenthesizedExpressionLogicalAndWithLogicalOr) {
  match_string(
      "(true || true) && true",
      "(module (binary_expression left: (binary_expression left: (true) "
      "operator: (logical_or) right: (true)) operator: (logical_and) right: "
      "(true)))");
  match_string(
      "true && (true || true)",
      "(module (binary_expression left: (true) operator: (logical_and) right: "
      "(binary_expression left: (true) operator: (logical_or) right: "
      "(true))))");
}

TEST(ParserTest, IfStatement) {
  match_string("if true {}", "(module (if_statement if_condition: (true)))");
  match_string("if true { true }",
               "(module (if_statement if_condition: (true) if_body: (true)))");
  match_string("if true == (true != true) {}",
               "(module (if_statement if_condition: (binary_expression left: "
               "(true) operator: (equal) right: (binary_expression left: "
               "(true) operator: (not_equal) right: (true)))))");
  match_string("if true { true } else {}",
               "(module (if_statement if_condition: (true) if_body: (true)))");
  match_string("if true { true } else { false }",
               "(module (if_statement if_condition: (true) if_body: (true) "
               "else_body: (false)))");
  match_string("if true { true } else if true { false }",
               "(module (if_statement if_condition: (true) if_body: (true) "
               "else_if_statement: (if_statement if_condition: (true) if_body: "
               "(false))))");
  match_string("if true { true } else if true { false } else {}",
               "(module (if_statement if_condition: (true) if_body: (true) "
               "else_if_statement: (if_statement if_condition: (true) if_body: "
               "(false))))");
  match_string("if true == true { true } else if true != true { false }",
               "(module (if_statement if_condition: (binary_expression left: "
               "(true) operator: (equal) right: (true)) if_body: (true) "
               "else_if_statement: (if_statement if_condition: "
               "(binary_expression left: (true) operator: (not_equal) right: "
               "(true)) if_body: (false))))");
}
