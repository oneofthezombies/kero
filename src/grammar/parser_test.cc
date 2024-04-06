#include "gtest/gtest.h"

// #include "./parser_facade.h"

// TEST(ParserTest, Empty) {
//   auto parser{kero::ParserFacade{""}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, Space) {
//   auto parser{kero::ParserFacade{" "}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, Space2) {
//   auto parser{kero::ParserFacade{"  "}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, Tab) {
//   auto parser{kero::ParserFacade{"\t"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, Tab2) {
//   auto parser{kero::ParserFacade{"\t\t"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, NewLine) {
//   auto parser{kero::ParserFacade{"\n"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, NewLine2) {
//   auto parser{kero::ParserFacade{"\n\n"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, CarriageReturn) {
//   auto parser{kero::ParserFacade{"\r"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, CarriageReturn2) {
//   auto parser{kero::ParserFacade{"\r\r"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, CarriageReturnNewLine) {
//   auto parser{kero::ParserFacade{"\r\n"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, CarriageReturnNewLine2) {
//   auto parser{kero::ParserFacade{"\r\n\r\n"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, IfTrue) {
//   auto parser{kero::ParserFacade{"if true then end"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, IfFalse) {
//   auto parser{kero::ParserFacade{"if false then end"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, IfNil) {
//   auto parser{kero::ParserFacade{"if nil then end"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, IfTrueElse) {
//   auto parser{kero::ParserFacade{"if true then else end"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, IfTrueElseifTrue) {
//   auto parser{kero::ParserFacade{"if true then elseif true then end"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, IfTrueElseifTrueElse) {
//   auto parser{kero::ParserFacade{"if true then elseif true then else end "}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, IfTrueElseifTrueElseifTrue) {
//   auto parser{
//       kero::ParserFacade{"if true then elseif true then elseif true then
//       end"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, SingleLineComment) {
//   auto parser{kero::ParserFacade{"--"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, SingleLineCommentWithText) {
//   auto parser{kero::ParserFacade{"--comment"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, MultiLineComment) {
//   auto parser{kero::ParserFacade{"--[[]]"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, MultiLineCommentWithText) {
//   auto parser{kero::ParserFacade{"--[[comment]]"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, MultiLineCommentWithNestedComment) {
//   auto parser{kero::ParserFacade{"--[[comment --[[nested]]]]"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, IfTrueWithSingleLineComment) {
//   auto parser{kero::ParserFacade{"if true then --comment\n"
//                                  "end"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, IfTrueWithMultiLineComment) {
//   auto parser{kero::ParserFacade{"if true then --[[comment]]\n"
//                                  "end"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, IfTrueWithMultipleSingleLineComments) {
//   auto parser{kero::ParserFacade{"if true then --comment1\n"
//                                  "--comment2\n"
//                                  "end"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, FunctionDefinition) {
//   auto parser{kero::ParserFacade{"function a() end"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, FunctionDefinitionWithParameter) {
//   auto parser{kero::ParserFacade{"function a(b) end"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, FunctionDefinitionWithParameterAndWhitespace) {
//   auto parser{kero::ParserFacade{"function a (b) end"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, FunctionDefinitionWithParameterAndWhitespace2) {
//   auto parser{kero::ParserFacade{"function a( b) end"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, FunctionDefinitionWithParameterAndWhitespace3) {
//   auto parser{kero::ParserFacade{"function a(b ) end"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, FunctionDefinitionWithParameterAndWhitespace4) {
//   auto parser{kero::ParserFacade{"function a ( b) end"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, FunctionDefinitionWithParameterAndWhitespace5) {
//   auto parser{kero::ParserFacade{"function a (b ) end"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, FunctionDefinitionWithParameterAndWhitespace6) {
//   auto parser{kero::ParserFacade{"function a( b ) end"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, FunctionDefinitionWithParameterAndWhitespace7) {
//   auto parser{kero::ParserFacade{"function a ( b ) end"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, FunctionDefinitionWithMultipleParameters) {
//   auto parser{kero::ParserFacade{"function a(b, c) end"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, FunctionDefinitionWithBody) {
//   auto parser{kero::ParserFacade{"function a() b() end"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, FunctionDefinitionWithSingleLineComment) {
//   auto parser{kero::ParserFacade{"function a() --comment\n"
//                                  "end"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, FunctionCall) {
//   auto parser{kero::ParserFacade{"a()"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, FunctionCallWithParameter) {
//   auto parser{kero::ParserFacade{"a(b)"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, FunctionCallWithMultipleParameters) {
//   auto parser{kero::ParserFacade{"a(b, c)"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, FunctionCallWithWhitespace) {
//   auto parser{kero::ParserFacade{"a ()"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, FunctionCallWithWhitespace2) {
//   auto parser{kero::ParserFacade{"a( )"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, FunctionCallWithWhitespace3) {
//   auto parser{kero::ParserFacade{"a ( )"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, FunctionCallWithWhitespace4) {
//   auto parser{kero::ParserFacade{"a (b)"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, FunctionCallWithWhitespace5) {
//   auto parser{kero::ParserFacade{"a( b)"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, FunctionCallWithWhitespace6) {
//   auto parser{kero::ParserFacade{"a(b )"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, FunctionCallWithWhitespace7) {
//   auto parser{kero::ParserFacade{"a ( b)"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, FunctionCallWithWhitespace8) {
//   auto parser{kero::ParserFacade{"a (b )"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, FunctionCallWithWhitespace9) {
//   auto parser{kero::ParserFacade{"a( b )"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, FunctionCallWithWhitespace10) {
//   auto parser{kero::ParserFacade{"a ( b )"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, FunctionCallWithWhitespace11) {
//   auto parser{kero::ParserFacade{"a (b, c)"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, FunctionCallWithWhitespace12) {
//   auto parser{kero::ParserFacade{"a( b, c)"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, FunctionCallWithWhitespace13) {
//   auto parser{kero::ParserFacade{"a(b, c )"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, FunctionCallWithWhitespace14) {
//   auto parser{kero::ParserFacade{"a( b, c )"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, FunctionCallWithWhitespace15) {
//   auto parser{kero::ParserFacade{"a ( b, c )"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, FunctionCallWithWhitespace16) {
//   auto parser{kero::ParserFacade{"a (b, c )"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, Return) {
//   auto parser{kero::ParserFacade{"return"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, ReturnWithExpression) {
//   auto parser{kero::ParserFacade{"return a"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, ReturnWithMultipleExpressions) {
//   auto parser{kero::ParserFacade{"return a, b"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, ReturnWithParenthesesedExpression) {
//   auto parser{kero::ParserFacade{"return (a)"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, ReturnWithParenthesesedMultipleExpressions) {
//   auto parser{kero::ParserFacade{"return (a, b)"}};
//   EXPECT_TRUE(parser.Parse());
// }

// TEST(ParserTest, FunctionDefinitionWithReturn) {
//   auto parser{kero::ParserFacade{"function a() return end"}};
//   EXPECT_TRUE(parser.Parse());
// }
