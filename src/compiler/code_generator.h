#ifndef KERO_COMPILER_CODE_GENERATOR_H
#define KERO_COMPILER_CODE_GENERATOR_H

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

namespace kero::compiler {

class CodeGenerator {
public:
  explicit CodeGenerator() noexcept;
  ~CodeGenerator() noexcept = default;

private:
  std::unique_ptr<llvm::LLVMContext> context_;
  std::unique_ptr<llvm::Module> module_;
  std::unique_ptr<llvm::IRBuilder<>> builder_;
};

} // namespace kero::compiler

#endif // KERO_COMPILER_CODE_GENERATOR_H
