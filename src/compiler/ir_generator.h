#ifndef KERO_COMPILER_IR_GENERATOR_H
#define KERO_COMPILER_IR_GENERATOR_H

#include "cpp_tree_sitter/api.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

#include "compiler/ir_visitor.h"

namespace kero::compiler {

struct IrContext {
  const IrVisitor &ir_visitor;
  ts::Parser parser;
  std::unique_ptr<llvm::LLVMContext> llvm_context;
  std::unique_ptr<llvm::Module> module;
  std::unique_ptr<llvm::IRBuilder<>> builder;

  explicit IrContext(const IrVisitor &ir_visitor, ts::Parser &&parser) noexcept;
  IrContext(const IrContext &) = delete;
  IrContext(IrContext &&) = delete;
  ~IrContext() noexcept = default;

  auto operator=(const IrContext &) -> IrContext & = delete;
  auto operator=(IrContext &&) -> IrContext & = delete;
};

class IrGenerator {
public:
  explicit IrGenerator(const IrVisitor &ir_visitor,
                       ts::Parser &&parser) noexcept;
  IrGenerator(const IrGenerator &) = delete;
  IrGenerator(IrGenerator &&) = delete;
  ~IrGenerator() noexcept = default;

  auto operator=(const IrGenerator &) -> IrGenerator & = delete;
  auto operator=(IrGenerator &&) -> IrGenerator & = delete;

  auto Generate() noexcept -> void;

private:
  IrContext ir_context_;
};

} // namespace kero::compiler

#endif // KERO_COMPILER_IR_GENERATOR_H
