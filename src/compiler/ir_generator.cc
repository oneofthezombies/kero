#include "ir_generator.h"

using namespace kero::compiler;

kero::compiler::IrContext::IrContext(const IrVisitor &ir_visitor,
                                     ts::Parser &&parser) noexcept
    : ir_visitor{std::move(ir_visitor)}, parser{std::move(parser)},
      llvm_context{std::make_unique<llvm::LLVMContext>()},
      module{std::make_unique<llvm::Module>("kero", *llvm_context)},
      builder{std::make_unique<llvm::IRBuilder<>>(*llvm_context)} {}

kero::compiler::IrGenerator::IrGenerator(const IrVisitor &ir_visitor,
                                         ts::Parser &&parser) noexcept
    : ir_context_{ir_visitor, std::move(parser)} {}

auto kero::compiler::IrGenerator::Generate() noexcept -> void {}
