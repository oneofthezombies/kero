#include "gtest/gtest.h"

#include "compiler/parser.h"

auto MatchString(const std::string_view source, const std::string_view s_expr)
    -> void {
  auto parser = kero::compiler::Parser::Builder{}
                    // .SetConsoleLogger()
                    // .SetPrintDotGraphsToStdout()
                    .Build();
  EXPECT_TRUE(parser.has_value());
  auto tree = parser->Parse(source);
  EXPECT_TRUE(tree.has_value());
  auto root_node = tree->RootNode();
  auto string = root_node.String();
  EXPECT_EQ(string.StringView(), s_expr);
  std::cout << *tree << std::endl;
}

TEST(ParserTest, Empty) { MatchString("", "(module)"); }

TEST(ParserTest, True) {
  MatchString("true", "(module (true))");
  MatchString("true ", "(module (true))");
  MatchString(" true", "(module (true))");
  MatchString(" true ", "(module (true))");
  MatchString("(true)", "(module (true))");
}
