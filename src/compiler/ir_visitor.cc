#include "ir_visitor.h"

#include <sstream>

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

auto kero::compiler::IrVisitor::Builder::Build() noexcept
    -> Result<IrVisitor, Error> {
  if (auto result = RegisterAllHandler(); result.IsErr()) {
    return Result<IrVisitor, Error>::Err(result.TakeErr());
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

auto kero::compiler::IrVisitor::Visit(const IrContext &ir_context,
                                      const ts::Node &node) const noexcept
    -> IrVisitResult {
  if (node.IsNull()) {
    std::stringstream ss;
    ss << node;
    return IrVisitResult::Err(Error{ErrorCode::kNodeIsNull, ss.str()});
  }

  const auto symbol = node.Symbol();
  const auto handler = handlers_.find(symbol);
  if (handler == handlers_.end()) {
    std::stringstream ss;
    ss << node;
    return IrVisitResult::Err(
        Error{ErrorCode::kVisitHandlerNotFound, ss.str()});
  }

  return handler->second(ir_context, node);
}
