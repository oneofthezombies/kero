#include "gtest/gtest.h"

#include "compiler/parser.h"

TEST(ParserTest, Empty) {
  auto parser = kero::compiler::Parser::Builder{}.build();
  EXPECT_TRUE(!!parser);
  auto tree = parser->parse("");
  EXPECT_TRUE(!!tree);
}
