#include "gtest/gtest.h"

#include "compiler/parser_builder.h"

auto MatchString(const std::string_view source, const std::string_view s_expr)
    -> void {
  if (auto result = kero::compiler::ParserBuilder{}.Build(); result.IsErr()) {
    FAIL() << std::move(result.Err());
  } else {
    const auto parser = std::move(result.Ok());
    auto tree = parser.ParseString(ts::Tree::Null(), source);
    auto root_node = tree.RootNode();
    auto string = root_node.String();
    EXPECT_EQ(string.StringView(), s_expr);
  }
}

TEST(ParserTest, Empty) { MatchString("", "(module)"); }

TEST(ParserTest, True) {
  MatchString("true", "(module (true))");
  MatchString("true ", "(module (true))");
  MatchString(" true", "(module (true))");
  MatchString(" true ", "(module (true))");
  MatchString("(true)", "(module (true))");
}
