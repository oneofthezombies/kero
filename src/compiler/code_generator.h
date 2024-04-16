#ifndef KERO_COMPILER_CODE_GENERATOR_H
#define KERO_COMPILER_CODE_GENERATOR_H

#include <string_view>

#include "cpp_tree_sitter/api.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

#include "compiler/parser.h"

namespace kero::compiler {

using Visitor = std::function<llvm::Value *(const ts::Node &)>;

class CodeGenerator {
public:
  explicit CodeGenerator(kero::compiler::Parser &&parser) noexcept;
  ~CodeGenerator() noexcept = default;

  auto Generate() noexcept -> void;

private:
  auto Register(const std::string_view type, const bool named,
                Visitor &&visitor) noexcept -> bool;

  std::unordered_map<ts::Symbol, Visitor> visitors_;
  kero::compiler::Parser parser_;
  std::unique_ptr<llvm::LLVMContext> context_;
  std::unique_ptr<llvm::Module> module_;
  std::unique_ptr<llvm::IRBuilder<>> builder_;
};

} // namespace kero::compiler

#endif // KERO_COMPILER_CODE_GENERATOR_H
