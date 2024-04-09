#include "gtest/gtest.h"

#include "parser.h"

TEST(ParserTest, Empty) {
  auto parser{kero::grammar::Parser{""}};
  EXPECT_TRUE(parser.parse());
}

TEST(ParserTest, WhiteSpace) {
  EXPECT_TRUE(kero::grammar::Parser{" "}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"  "}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"\t"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"\t\t"}.parse());
}

TEST(ParserTest, LineTerminator) {
  EXPECT_TRUE(kero::grammar::Parser{"\n"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"\n\n"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"\r"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"\r\r"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"\r\n"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"\r\n\r\n"}.parse());
}

TEST(ParserTest, WhiteSpaceAndLineTerminator) {
  EXPECT_TRUE(kero::grammar::Parser{" \n"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"\t\n"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{" \r"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"\t\r"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{" \r\n"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"\t\r\n"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"\n "}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"\n\t"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"\r "}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"\r\t"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"\r\n "}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"\r\n\t"}.parse());
}

TEST(ParserTest, SingleLineComment) {
  EXPECT_TRUE(kero::grammar::Parser{"//"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"// comment"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"// comment\n"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"// comment\r"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"// comment\r\n"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{" // comment"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"\t// comment"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"\n// comment"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"\r// comment"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"\r\n// comment"}.parse());
}

TEST(ParserTest, MultiLineComment) {
  EXPECT_TRUE(kero::grammar::Parser{"/**/"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"/* */"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"/*/*/"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"/*/**/"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"/* comment */"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"/* comment\n*/"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"/* comment\r*/"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"/* comment\r\n*/"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"/* comment */\n"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"/* comment */\r"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"/* comment */\r\n"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{" /* comment */"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"\t/* comment */"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"\n/* comment */"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"\r/* comment */"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"\r\n/* comment */"}.parse());
}

TEST(ParserTest, IfStatement) {
  EXPECT_TRUE(kero::grammar::Parser{"if (true) {}"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"if (false) {}"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"if (true) {\n}"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"if (true) {//\n}"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"if//\n(true) {}"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"if(true) {}"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"if(//\ntrue) {}"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"if(true//\n) {}"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"if(true)//\n{}"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"if(true){//\n}"}.parse());
  EXPECT_TRUE(kero::grammar::Parser{"if(true){}//\n"}.parse());
}
