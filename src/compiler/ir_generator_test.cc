#include "gtest/gtest.h"

#include "compiler/ir_generator.h"
#include "compiler/parser_builder.h"

TEST(IrGeneratorTest, Empty) {
  auto ir_visitor_result = kero::compiler::IrVisitor::Builder{}.Build();
  if (ir_visitor_result.IsErr()) {
    FAIL() << std::move(ir_visitor_result.Err());
  }

  const auto ir_visitor = std::move(ir_visitor_result.Ok());
  auto parser_result = kero::compiler::ParserBuilder{}.Build();
  if (parser_result.IsErr()) {
    FAIL() << std::move(parser_result.Err());
  }

  auto parser = std::move(parser_result.Ok());
  const std::string_view source = "123";
  auto tree = parser.ParseString(ts::Tree::Null(), source);
  std::cout << tree << std::endl;
  kero::compiler::IrGenerator ir_generator{ir_visitor};
  if (auto result = ir_generator.Generate(source, std::move(tree));
      result.IsErr()) {
    FAIL() << std::move(result.Err());
  }
}
