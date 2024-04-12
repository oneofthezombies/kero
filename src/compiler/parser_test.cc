#include "gtest/gtest.h"

#include "compiler/parser.h"

TEST(ParserTest, Empty) {
  auto parser = kero::compiler::Parser::Builder{}.build();
  EXPECT_TRUE(!!parser);
  auto tree = parser->parse("");
  EXPECT_TRUE(!!tree);
  auto root_node = tree->root_node();
  EXPECT_TRUE(!!root_node);
  auto string = root_node->string();
  EXPECT_EQ(string.string_view(), "(source_file)");
}
