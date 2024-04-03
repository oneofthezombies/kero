#include "gtest/gtest.h"

#include "grammar/parser.h"

TEST(ParserTest, Parse) {
  auto parser{kero::grammar::Parser{"# hello\n1"}};
  parser.Parse();
}
