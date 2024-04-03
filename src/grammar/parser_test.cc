#include "gtest/gtest.h"

#include "./parser.h"

TEST(ParserTest, Empty) {
  auto parser{kero::grammar::Parser{""}};
  EXPECT_TRUE(parser.Parse());
}

TEST(ParserTest, Space) {
  auto parser{kero::grammar::Parser{" "}};
  EXPECT_TRUE(parser.Parse());
}

TEST(ParserTest, Space2) {
  auto parser{kero::grammar::Parser{"  "}};
  EXPECT_TRUE(parser.Parse());
}

TEST(ParserTest, Tab) {
  auto parser{kero::grammar::Parser{"\t"}};
  EXPECT_TRUE(parser.Parse());
}

TEST(ParserTest, Tab2) {
  auto parser{kero::grammar::Parser{"\t\t"}};
  EXPECT_TRUE(parser.Parse());
}

TEST(ParserTest, NewLine) {
  auto parser{kero::grammar::Parser{"\n"}};
  EXPECT_TRUE(parser.Parse());
}

TEST(ParserTest, NewLine2) {
  auto parser{kero::grammar::Parser{"\n\n"}};
  EXPECT_TRUE(parser.Parse());
}

TEST(ParserTest, CarriageReturn) {
  auto parser{kero::grammar::Parser{"\r"}};
  EXPECT_TRUE(parser.Parse());
}

TEST(ParserTest, CarriageReturn2) {
  auto parser{kero::grammar::Parser{"\r\r"}};
  EXPECT_TRUE(parser.Parse());
}

TEST(ParserTest, CarriageReturnNewLine) {
  auto parser{kero::grammar::Parser{"\r\n"}};
  EXPECT_TRUE(parser.Parse());
}

TEST(ParserTest, CarriageReturnNewLine2) {
  auto parser{kero::grammar::Parser{"\r\n\r\n"}};
  EXPECT_TRUE(parser.Parse());
}

TEST(ParserTest, IfTrue) {
  auto parser{kero::grammar::Parser{"if true then end"}};
  EXPECT_TRUE(parser.Parse());
}

TEST(ParserTest, IfFalse) {
  auto parser{kero::grammar::Parser{"if false then end"}};
  EXPECT_TRUE(parser.Parse());
}

TEST(ParserTest, IfNil) {
  auto parser{kero::grammar::Parser{"if nil then end"}};
  EXPECT_TRUE(parser.Parse());
}

TEST(ParserTest, IfTrueElse) {
  auto parser{kero::grammar::Parser{"if true then else end"}};
  EXPECT_TRUE(parser.Parse());
}

TEST(ParserTest, IfTrueElseifTrue) {
  auto parser{kero::grammar::Parser{"if true then elseif true then end"}};
  EXPECT_TRUE(parser.Parse());
}

TEST(ParserTest, IfTrueElseifTrueElse) {
  auto parser{kero::grammar::Parser{"if true then elseif true then else end"}};
  EXPECT_TRUE(parser.Parse());
}

TEST(ParserTest, IfTrueElseifTrueElseifTrue) {
  auto parser{kero::grammar::Parser{
      "if true then elseif true then elseif true then end"}};
  EXPECT_TRUE(parser.Parse());
}

TEST(ParserTest, SingleLineComment) {
  auto parser{kero::grammar::Parser{"--"}};
  EXPECT_TRUE(parser.Parse());
}

TEST(ParserTest, SingleLineCommentWithText) {
  auto parser{kero::grammar::Parser{"--comment"}};
  EXPECT_TRUE(parser.Parse());
}

TEST(ParserTest, MultiLineComment) {
  auto parser{kero::grammar::Parser{"--[[]]"}};
  EXPECT_TRUE(parser.Parse());
}

TEST(ParserTest, MultiLineCommentWithText) {
  auto parser{kero::grammar::Parser{"--[[comment]]"}};
  EXPECT_TRUE(parser.Parse());
}

TEST(ParserTest, MultiLineCommentWithNestedComment) {
  auto parser{kero::grammar::Parser{"--[[comment --[[nested]]]]"}};
  EXPECT_TRUE(parser.Parse());
}

TEST(ParserTest, IfTrueWithSingleLineComment) {
  auto parser{kero::grammar::Parser{"if true then --comment\n"
                                    "end"}};
  EXPECT_TRUE(parser.Parse());
}

TEST(ParserTest, IfTrueWithMultiLineComment) {
  auto parser{kero::grammar::Parser{"if true then --[[comment]]\n"
                                    "end"}};
  EXPECT_TRUE(parser.Parse());
}

TEST(ParserTest, IfTrueWithMultipleSingleLineComments) {
  auto parser{kero::grammar::Parser{"if true then --comment1\n"
                                    "--comment2\n"
                                    "end"}};
  EXPECT_TRUE(parser.Parse());
}
