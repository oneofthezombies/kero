#ifndef KERO_COMPILER_CODE_GENERATOR_H
#define KERO_COMPILER_CODE_GENERATOR_H

#include "cpp_tree_sitter/api.h"
#include "llvm/IR/IRBuilder.h"

#include "compiler/core.h"

namespace kero::compiler {

class CodeGenVisitorFacade;

using LlvmContext = std::unique_ptr<llvm::LLVMContext>;
using LlvmModule = std::unique_ptr<llvm::Module>;
using LlvmIrBuilder = std::unique_ptr<llvm::IRBuilder<>>;

struct CodeGenContext final : private NonCopyable, NonMovable {
  const CodeGenVisitorFacade &visitor;
  const LlvmContext &llvm_context;
  const LlvmModule &module;
  const LlvmIrBuilder &builder;
  const std::string_view source;

  explicit CodeGenContext(const CodeGenVisitorFacade &visitor,
                          const LlvmContext &llvm_context,
                          const LlvmModule &module,
                          const LlvmIrBuilder &builder,
                          const std::string_view source) noexcept;
};

using CodeGenResult = Result<llvm::Value *, Error>;

using CodeGenType = std::string_view;
using CodeGenNamed = bool;
using CodeGenKind = std::pair<CodeGenType, CodeGenNamed>;

class CodeGenVisitor : private NonCopyable, Movable {
public:
  CodeGenVisitor(CodeGenKind &&kind) noexcept;
  virtual ~CodeGenVisitor() noexcept = default;

  [[nodiscard]] auto Kind() const noexcept -> CodeGenKind;

  virtual auto Visit(const CodeGenContext &context,
                     const ts::Node &node) const noexcept -> CodeGenResult = 0;

private:
  const CodeGenKind kind_;
};

using CodeGenVisitors =
    std::unordered_map<ts::Symbol, std::unique_ptr<CodeGenVisitor>>;

class CodeGenVisitorFacade final : private NonCopyable, Movable {
public:
  friend class CodeGenVisitorFacadeBuilder;

  auto Visit(const CodeGenContext &context, const ts::Node &node) const noexcept
      -> CodeGenResult;

private:
  explicit CodeGenVisitorFacade(CodeGenVisitors &&visitors) noexcept;

  CodeGenVisitors visitors_;
};

class CodeGenVisitorFacadeBuilder final : private NonCopyable, NonMovable {
public:
  auto Build() noexcept -> CodeGenVisitorFacade;

private:
  auto RegisterAllVisitor() noexcept -> void;
  auto RegisterVisitor(std::unique_ptr<CodeGenVisitor> &&visitor) noexcept
      -> void;

  CodeGenVisitors visitors_;
};

class CodeGenerator final : private NonCopyable, Movable {
public:
  explicit CodeGenerator(const CodeGenVisitorFacade &visitor) noexcept;

  auto Generate(const std::string_view source, ts::Tree &&tree) noexcept
      -> CodeGenResult;

private:
  const CodeGenVisitorFacade &visitor_;
  const LlvmContext llvm_context_;
  const LlvmModule module_;
  const LlvmIrBuilder builder_;
};

} // namespace kero::compiler

#endif // KERO_COMPILER_CODE_GENERATOR_H
