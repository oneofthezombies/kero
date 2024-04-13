#include "gtest/gtest.h"

#include "compiler/parser.h"

TEST(ParserTest, Empty) {
  auto parser = kero::compiler::Parser::Builder{}.build();
  EXPECT_TRUE(!!parser);
  auto tree = parser->parse("true == true");
  EXPECT_TRUE(!!tree);
  auto root_node_opt = tree->root_node();
  EXPECT_TRUE(!!root_node_opt);
  auto &root_node = *root_node_opt;
  auto string = root_node.string();
  EXPECT_EQ(string.string_view(), "(source_file)");
}
