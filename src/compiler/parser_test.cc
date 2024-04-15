#include "gtest/gtest.h"

#include "compiler/parser.h"

auto match_string(const std::string_view source, const std::string_view s_expr)
    -> void {
  auto parser = kero::compiler::Parser::Builder{}
                    // .set_console_logger()
                    // .set_print_dot_graphs_to_stdout()
                    .build();
  EXPECT_TRUE(parser.has_value());
  auto tree = parser->parse(source);
  EXPECT_TRUE(tree.has_value());
  auto root_node = tree->RootNode();
  auto string = root_node.String();
  EXPECT_EQ(string.StringView(), s_expr);
}

TEST(ParserTest, Empty) { match_string("", "(module)"); }
