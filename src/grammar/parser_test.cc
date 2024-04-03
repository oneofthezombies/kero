#include "gtest/gtest.h"

#include "grammar/parser.h"

TEST(ParserTest, Parse) {
  auto parser{kero::grammar::Parser{}};
  parser.parse();
}
