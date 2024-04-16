#include "ir_visitor.h"

#include "ir_visit_handlers.cc"

using namespace kero::compiler;

using Type = std::string_view;
using Named = bool;

static const std::vector<std::pair<std::pair<Type, Named>, IrVisitHandler>>
    kIrVisitHandlers = {
        {{"true", true}, True},
        {{"false", true}, False},
        {{"binary_expression", true}, BinaryExpression},
        {{"module", true}, Module},
        {{"number", true}, Number},

        // This comment prevents pair's `}` and vector's `}` from
        // being attached in the form `}}` by `clang-format`.
};

kero::compiler::IrVisitorContext::IrVisitorContext(
    const IrVisitor &ir_visitor, const LlvmContext &llvm_context,
    const LlvmModule &module, const LlvmIrBuilder &ir_builder,
    const std::string_view source) noexcept
    : ir_visitor{ir_visitor}, llvm_context{llvm_context}, module{module},
      ir_builder{ir_builder}, source{source} {}

auto kero::compiler::IrVisitor::Builder::Build() noexcept
    -> Result<IrVisitor, Error> {
  if (auto result = RegisterAllHandler(); result.IsErr()) {
    return Result<IrVisitor, Error>::Err(std::move(result.Err()));
  }

  return Result<IrVisitor, Error>::Ok(IrVisitor{std::move(handlers_)});
}

auto kero::compiler::IrVisitor::Builder::RegisterAllHandler() noexcept
    -> VoidResult {
  for (const auto &[key, visitor] : kIrVisitHandlers) {
    const auto &[type, named] = key;
    if (auto result = RegisterHandler(type, named, visitor); result.IsErr()) {
      return result;
    }
  }

  return VoidResult::Ok(Void{});
}

auto kero::compiler::IrVisitor::Builder::RegisterHandler(
    const std::string_view type, const bool named,
    const IrVisitHandler &handler) noexcept -> Result<Void, Error> {
  const auto symbol = Language().SymbolForName(type, named);
  if (symbol == ts::Language::kSymbolNotFound) {
    return VoidResult::Err(Error{ErrorCode::kSymbolNotFound});
  }

  if (handlers_.find(symbol) != handlers_.end()) {
    return VoidResult::Err(Error{ErrorCode::kVisitHandlerAlreadyRegistered});
  }

  handlers_.emplace(symbol, handler);
  return VoidResult::Ok(Void{});
}

kero::compiler::IrVisitor::IrVisitor(IrVisitHandlers &&handlers) noexcept
    : handlers_{std::move(handlers)} {}

auto kero::compiler::IrVisitor::Visit(const IrVisitorContext &context,
                                      const ts::Node &node) const noexcept
    -> IrVisitResult {
  if (node.IsNull()) {
    return IrVisitResult::Err(
        Error{ErrorCode::kNodeIsNull, NodeToString(node)});
  }

  const auto symbol = node.Symbol();
  const auto handler = handlers_.find(symbol);
  if (handler == handlers_.end()) {
    return IrVisitResult::Err(
        Error{ErrorCode::kVisitHandlerNotFound, NodeToString(node)});
  }

  return handler->second(context, node);
}
