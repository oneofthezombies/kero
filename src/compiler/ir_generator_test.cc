#include "gtest/gtest.h"

#include "compiler/ir_generator.h"
#include "compiler/parser_builder.h"

TEST(IrGeneratorTest, Empty) {
  if (auto result = kero::compiler::IrVisitor::Builder{}.Build();
      result.IsErr()) {
    FAIL() << result.TakeErr();
  } else {
    const auto ir_visitor = result.TakeOk();
    if (auto result = kero::compiler::ParserBuilder{}.Build(); result.IsErr()) {
      FAIL() << result.TakeErr();
    } else {
      auto parser = result.TakeOk();
      auto tree = parser.ParseString(ts::Tree::Null(), "tru == false");
      std::cout << tree << std::endl;
      kero::compiler::IrGenerator ir_generator{ir_visitor};
      if (auto result = ir_generator.Generate(std::move(tree));
          result.IsErr()) {
        FAIL() << result.TakeErr();
      }
    }
  }
}
