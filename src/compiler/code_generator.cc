#include "code_generator.h"

#include <memory>

#include "compiler/utils.h"

#include "compiler/code_gen_visitors.cc"

using namespace kero::compiler;

// CodeGenContext
// --------------

kero::compiler::CodeGenContext::CodeGenContext(
    const CodeGenVisitorFacade &visitor, const LlvmContext &llvm_context,
    const LlvmModule &module, const LlvmIrBuilder &builder,
    const std::string_view source) noexcept
    : visitor{visitor}, llvm_context{llvm_context}, module{module},
      builder{builder}, source{source} {}

// CodeGenVisitor
// --------------

kero::compiler::CodeGenVisitor::CodeGenVisitor(CodeGenKind &&kind) noexcept
    : kind_{std::move(kind)} {}

auto kero::compiler::CodeGenVisitor::Kind() const noexcept -> CodeGenKind {
  return kind_;
}

// CodeGenVisitorFacadeBuilder
// ---------------------------

auto kero::compiler::CodeGenVisitorFacadeBuilder::Build() noexcept
    -> CodeGenVisitorFacade {
  RegisterAllVisitor();
  return CodeGenVisitorFacade{std::move(visitors_)};
}

auto kero::compiler::CodeGenVisitorFacadeBuilder::RegisterAllVisitor() noexcept
    -> void {
  RegisterVisitor(std::make_unique<TrueVisitor>());
  RegisterVisitor(std::make_unique<FalseVisitor>());
  RegisterVisitor(std::make_unique<BinaryExpressionVisitor>());
  RegisterVisitor(std::make_unique<ModuleVisitor>());
  RegisterVisitor(std::make_unique<NumberVisitor>());
}

auto kero::compiler::CodeGenVisitorFacadeBuilder::RegisterVisitor(
    std::unique_ptr<CodeGenVisitor> &&visitor) noexcept -> void {
  assert(visitor != nullptr && "Visitor must not be null");

  const auto [type, named] = visitor->Kind();
  const auto symbol = Language().SymbolForName(type, named);
  assert(symbol != ts::Language::kSymbolNotFound && "Symbol must be found");
  assert(visitors_.find(symbol) == visitors_.end() &&
         "Visitor must not be registered");

  visitors_.emplace(symbol, std::move(visitor));
}

// CodeGenVisitorFacade
// --------------------

kero::compiler::CodeGenVisitorFacade::CodeGenVisitorFacade(
    CodeGenVisitors &&visitors) noexcept
    : visitors_{std::move(visitors)} {}

auto kero::compiler::CodeGenVisitorFacade::Visit(
    const CodeGenContext &context, const ts::Node &node) const noexcept
    -> CodeGenResult {
  if (node.IsNull()) {
    return CodeGenResult::Err(
        Error{ErrorCode::kNodeIsNull, NodeToString(node)});
  }

  const auto symbol = node.Symbol();
  const auto visitor = visitors_.find(symbol);
  if (visitor == visitors_.end()) {
    return CodeGenResult::Err(
        Error{ErrorCode::kVisitorNotFound, NodeToString(node)});
  }

  return visitor->second->Visit(context, node);
}

// CodeGenerator
// -------------

kero::compiler::CodeGenerator::CodeGenerator(
    const CodeGenVisitorFacade &visitor) noexcept
    : visitor_{visitor}, llvm_context_{std::make_unique<llvm::LLVMContext>()},
      module_{std::make_unique<llvm::Module>("kero", *llvm_context_)},
      builder_{std::make_unique<llvm::IRBuilder<>>(*llvm_context_)} {}

auto kero::compiler::CodeGenerator::Generate(const std::string_view source,
                                             ts::Tree &&tree) noexcept
    -> CodeGenResult {
  const auto root_node = tree.RootNode();
  const auto context =
      CodeGenContext{visitor_, llvm_context_, module_, builder_, source};
  return visitor_.Visit(context, root_node);
}
