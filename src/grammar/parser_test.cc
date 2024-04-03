#include "gtest/gtest.h"

#include "./parser.h"

TEST(ParserTest, Parse) {
  auto parser{kero::grammar::Parser{"# hello\n1"}};
  parser.Parse();
}
