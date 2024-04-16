#include "ir_generator.h"

using namespace kero::compiler;

kero::compiler::IrContext::IrContext(
    const IrVisitor &ir_visitor,
    const std::unique_ptr<llvm::LLVMContext> &llvm_context,
    const std::unique_ptr<llvm::Module> &module,
    const std::unique_ptr<llvm::IRBuilder<>> &builder,
    const std::string_view source) noexcept
    : ir_visitor{ir_visitor}, llvm_context{llvm_context}, module{module},
      builder{builder}, source{source} {}

kero::compiler::IrGenerator::IrGenerator(const IrVisitor &ir_visitor) noexcept
    : ir_visitor_{ir_visitor},
      llvm_context_{std::make_unique<llvm::LLVMContext>()},
      module_{std::make_unique<llvm::Module>("kero", *llvm_context_)},
      builder_{std::make_unique<llvm::IRBuilder<>>(*llvm_context_)} {}

auto kero::compiler::IrGenerator::Generate(const std::string_view source,
                                           ts::Tree &&tree) noexcept
    -> IrVisitResult {
  const auto root_node = tree.RootNode();
  const auto ir_context =
      IrContext{ir_visitor_, llvm_context_, module_, builder_, source};
  return ir_visitor_.Visit(ir_context, root_node);
}
