#ifndef KERO_COMPILER_CODE_GENERATOR_H
#define KERO_COMPILER_CODE_GENERATOR_H

#include <string_view>
#include <unordered_map>

#include "cpp_tree_sitter/api.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

#include "compiler/core.h"
#include "compiler/parser.h"

namespace kero::compiler {

struct Context;

struct Context {
  Visitor visitor;
  Parser parser;
  std::unique_ptr<llvm::LLVMContext> llvm_context;
  std::unique_ptr<llvm::Module> module;
  std::unique_ptr<llvm::IRBuilder<>> builder;

  Context(kero::compiler::Parser &&parser) noexcept;
  Context(const Context &) = delete;
  Context(Context &&) noexcept = default;
  ~Context() noexcept = default;

  auto operator=(const Context &) -> Context & = delete;
  auto operator=(Context &&) noexcept -> Context & = default;
};

class CodeGenerator {
public:
  class Builder {
  public:
    Builder(Parser &&parser) noexcept;
    Builder(const Builder &) = delete;
    Builder(Builder &&) noexcept = delete;
    ~Builder() noexcept = default;

    auto operator=(const Builder &) -> Builder & = delete;
    auto operator=(Builder &&) noexcept -> Builder & = delete;

    auto Build() noexcept -> Result<CodeGenerator>;

  private:
    Parser parser_;
  };

  explicit CodeGenerator(Parser &&parser) noexcept;
  CodeGenerator(const CodeGenerator &) = delete;
  CodeGenerator(CodeGenerator &&) noexcept = default;
  ~CodeGenerator() noexcept = default;

  auto operator=(const CodeGenerator &) -> CodeGenerator & = delete;
  auto operator=(CodeGenerator &&) noexcept -> CodeGenerator & = default;

  auto Generate() noexcept -> void;

private:
  Context context_;
};

} // namespace kero::compiler

#endif // KERO_COMPILER_CODE_GENERATOR_H
