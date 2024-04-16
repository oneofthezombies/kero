#include "gtest/gtest.h"

#include "compiler/ir_generator.h"
#include "compiler/parser_builder.h"

TEST(IrGeneratorTest, Empty) {
  auto ir_visitor_result = kero::compiler::IrVisitor::Builder{}.Build();
  if (ir_visitor_result.IsErr()) {
    FAIL() << ir_visitor_result.TakeErr();
  }

  const auto ir_visitor = ir_visitor_result.TakeOk();
  auto parser_result = kero::compiler::ParserBuilder{}.Build();
  if (parser_result.IsErr()) {
    FAIL() << parser_result.TakeErr();
  }

  auto parser = parser_result.TakeOk();
  const std::string_view source = "123";
  auto tree = parser.ParseString(ts::Tree::Null(), source);
  std::cout << tree << std::endl;
  kero::compiler::IrGenerator ir_generator{ir_visitor};
  if (auto result = ir_generator.Generate(source, std::move(tree));
      result.IsErr()) {
    FAIL() << result.TakeErr();
  }
}
