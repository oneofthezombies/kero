#include "ir_generator.h"

using namespace kero::compiler;

kero::compiler::IrContext::IrContext(const IrVisitor &ir_visitor) noexcept
    : ir_visitor{std::move(ir_visitor)},
      llvm_context{std::make_unique<llvm::LLVMContext>()},
      module{std::make_unique<llvm::Module>("kero", *llvm_context)},
      builder{std::make_unique<llvm::IRBuilder<>>(*llvm_context)} {}

kero::compiler::IrGenerator::IrGenerator(const IrVisitor &ir_visitor) noexcept
    : ir_context_{ir_visitor} {}

auto kero::compiler::IrGenerator::Generate(ts::Tree &&tree) noexcept
    -> IrVisitResult {
  const auto root_node = tree.RootNode();
  return ir_context_.ir_visitor.Visit(ir_context_, root_node);
}
