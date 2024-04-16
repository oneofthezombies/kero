#include "ir_generator.h"

using namespace kero::compiler;

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
      IrVisitorContext{ir_visitor_, llvm_context_, module_, builder_, source};
  return ir_visitor_.Visit(ir_context, root_node);
}
