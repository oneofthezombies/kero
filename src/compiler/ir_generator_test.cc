#include "gtest/gtest.h"

#include "compiler/ir_generator.h"
#include "compiler/parser_builder.h"

TEST(IrGeneratorTest, Empty) {
  if (auto result = kero::compiler::IrVisitor::Builder{}.Build();
      result.IsErr()) {
    FAIL() << static_cast<int32_t>(result.Err());
  } else {
    const auto ir_visitor = result.TakeOk();
    if (auto result = kero::compiler::ParserBuilder{}.Build(); result.IsErr()) {
      FAIL() << static_cast<int32_t>(result.Err());
    } else {
      auto parser = result.TakeOk();
      auto tree = parser.ParseString(ts::Tree::Null(), "true == false");
      kero::compiler::IrGenerator ir_generator{ir_visitor};
      ir_generator.Generate(std::move(tree));
    }
  }
}
