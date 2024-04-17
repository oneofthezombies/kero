#include "gtest/gtest.h"

#include "compiler/code_generator.h"
#include "compiler/parser_builder.h"

TEST(CodeGenVisitorFacadeBuilderTest, Build) {
  auto _ = kero::compiler::CodeGenVisitorFacadeBuilder{}.Build();
}

TEST(CodeGeneratorTest, Empty) {
  auto visitor = kero::compiler::CodeGenVisitorFacadeBuilder{}.Build();
  auto parser_result = kero::compiler::ParserBuilder{}.Build();
  if (parser_result.IsErr()) {
    FAIL() << std::move(parser_result.Err());
  }

  auto parser = std::move(parser_result.Ok());
  const std::string_view source = "123";
  auto tree = parser.ParseString(ts::Tree::Null(), source);
  std::cout << tree << std::endl;
  kero::compiler::CodeGenerator generator{visitor};
  if (auto result = generator.Generate(source, std::move(tree));
      result.IsErr()) {
    FAIL() << std::move(result.Err());
  }
}
