#include "gtest/gtest.h"

#include "ParserFacade.h"

TEST(ParserTest, Empty) {
  EXPECT_TRUE(kero::compile::ParserFacade{""}.parse());
}

TEST(ParserTest, WhiteSpace) {
  EXPECT_TRUE(kero::compile::ParserFacade{" "}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"  "}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"\t"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"\t\t"}.parse());
}

TEST(ParserTest, LineTerminator) {
  EXPECT_TRUE(kero::compile::ParserFacade{"\n"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"\n\n"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"\r"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"\r\r"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"\r\n"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"\r\n\r\n"}.parse());
}

TEST(ParserTest, WhiteSpaceAndLineTerminator) {
  EXPECT_TRUE(kero::compile::ParserFacade{" \n"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"\t\n"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{" \r"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"\t\r"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{" \r\n"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"\t\r\n"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"\n "}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"\n\t"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"\r "}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"\r\t"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"\r\n "}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"\r\n\t"}.parse());
}

TEST(ParserTest, SingleLineComment) {
  EXPECT_TRUE(kero::compile::ParserFacade{"//"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"// comment"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"// comment\n"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"// comment\r"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"// comment\r\n"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{" // comment"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"\t// comment"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"\n// comment"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"\r// comment"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"\r\n// comment"}.parse());
}

TEST(ParserTest, MultiLineComment) {
  EXPECT_TRUE(kero::compile::ParserFacade{"/**/"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"/* */"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"/*/*/"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"/*/**/"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"/* comment */"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"/* comment\n*/"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"/* comment\r*/"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"/* comment\r\n*/"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"/* comment */\n"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"/* comment */\r"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"/* comment */\r\n"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{" /* comment */"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"\t/* comment */"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"\n/* comment */"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"\r/* comment */"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"\r\n/* comment */"}.parse());
}

TEST(ParserTest, IfStatement) {
  EXPECT_TRUE(kero::compile::ParserFacade{"if (true) {}"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"if (false) {}"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"if (true) {\n}"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"if (true) {//\n}"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"if//\n(true) {}"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"if(true) {}"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"if(//\ntrue) {}"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"if(true//\n) {}"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"if(true)//\n{}"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"if(true){//\n}"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"if(true){}//\n"}.parse());
  EXPECT_TRUE(
      kero::compile::ParserFacade{"if (true) {} else if (true)//\n{}"}.parse());
  EXPECT_TRUE(kero::compile::ParserFacade{"if (true) {} else//\n{}"}.parse());
}
