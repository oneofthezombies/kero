#include "gtest/gtest.h"

#include "parser.h"

TEST(ParserTest, Empty) {
  auto parser{kero::grammar::Parser{""}};
  EXPECT_TRUE(parser.parse());
}

TEST(ParserTest, Space) {
  auto parser{kero::grammar::Parser{" "}};
  EXPECT_TRUE(parser.parse());
}

TEST(ParserTest, Space2) {
  auto parser{kero::grammar::Parser{"  "}};
  EXPECT_TRUE(parser.parse());
}

TEST(ParserTest, Tab) {
  auto parser{kero::grammar::Parser{"\t"}};
  EXPECT_TRUE(parser.parse());
}

TEST(ParserTest, Tab2) {
  auto parser{kero::grammar::Parser{"\t\t"}};
  EXPECT_TRUE(parser.parse());
}

TEST(ParserTest, NewLine) {
  auto parser{kero::grammar::Parser{"\n"}};
  EXPECT_TRUE(parser.parse());
}

TEST(ParserTest, NewLine2) {
  auto parser{kero::grammar::Parser{"\n\n"}};
  EXPECT_TRUE(parser.parse());
}

TEST(ParserTest, CarriageReturn) {
  auto parser{kero::grammar::Parser{"\r"}};
  EXPECT_TRUE(parser.parse());
}

TEST(ParserTest, CarriageReturn2) {
  auto parser{kero::grammar::Parser{"\r\r"}};
  EXPECT_TRUE(parser.parse());
}

TEST(ParserTest, CarriageReturnNewLine) {
  auto parser{kero::grammar::Parser{"\r\n"}};
  EXPECT_TRUE(parser.parse());
}

TEST(ParserTest, CarriageReturnNewLine2) {
  auto parser{kero::grammar::Parser{"\r\n\r\n"}};
  EXPECT_TRUE(parser.parse());
}

TEST(ParserTest, SingleLineComment) {
  auto parser{kero::grammar::Parser{"//"}};
  EXPECT_TRUE(parser.parse());
}

TEST(ParserTest, SingleLineComment2) {
  auto parser{kero::grammar::Parser{"// comment"}};
  EXPECT_TRUE(parser.parse());
}

TEST(ParserTest, SingleLineComment3) {
  auto parser{kero::grammar::Parser{"//\n"}};
  EXPECT_TRUE(parser.parse());
}

TEST(ParserTest, MultiLineComment) {
  auto parser{kero::grammar::Parser{"/**/"}};
  EXPECT_TRUE(parser.parse());
}

TEST(ParserTest, MultiLineComment2) {
  auto parser{kero::grammar::Parser{"/***/"}};
  EXPECT_TRUE(parser.parse());
}

TEST(ParserTest, MultiLineComment3) {
  auto parser{kero::grammar::Parser{"/* comment */"}};
  EXPECT_TRUE(parser.parse());
}

TEST(ParserTest, MultiLineComment4) {
  auto parser{kero::grammar::Parser{"/*\n*/"}};
  EXPECT_TRUE(parser.parse());
}

TEST(ParserTest, MultiLineComment5) {
  auto parser{kero::grammar::Parser{"/*\n*/\n"}};
  EXPECT_TRUE(parser.parse());
}
