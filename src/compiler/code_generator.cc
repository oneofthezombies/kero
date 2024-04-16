#include "code_generator.h"

using namespace kero::compiler;

kero::compiler::CodeGenerator::CodeGenerator(
    kero::compiler::Parser &&parser) noexcept
    : parser_(std::move(parser)),
      context_(std::make_unique<llvm::LLVMContext>()),
      module_(std::make_unique<llvm::Module>("kero", *context_)),
      builder_(std::make_unique<llvm::IRBuilder<>>(*context_)) {}

auto kero::compiler::CodeGenerator::Generate() noexcept -> void {}

auto kero::compiler::CodeGenerator::Register(const std::string_view type,
                                             const bool named,
                                             Visitor &&visitor) noexcept
    -> bool {
  const auto symbol = parser_.Symbol(type, named);
  if (visitors_.find(symbol) != visitors_.end()) {
    return false;
  }
}
