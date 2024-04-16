/*
 * This file is included in `ir_visitor.cc` to define the visit handlers.
 */

#include "cpp_tree_sitter/api.h"

#include "compiler/ir_generator.h"
#include "compiler/ir_visitor.h"

using namespace kero::compiler;

auto True(IrContext &ir_context, const ts::Node &node) -> IrVisitResult {
  assert(node.Type() == "true" && "node type must be 'true'");
  return IrVisitResult::Ok(ir_context.builder->getTrue());
}

auto False(IrContext &ir_context, const ts::Node &node) -> IrVisitResult {
  assert(node.Type() == "false" && "node type must be 'false'");
  return IrVisitResult::Ok(ir_context.builder->getFalse());
}

auto BinaryExpression(IrContext &ir_context, const ts::Node &node)
    -> IrVisitResult {
  assert(node.Type() == "binary_expression" &&
         "node type must be 'binary_expression'");
  auto left_result = ir_context.ir_visitor.Visit(ir_context, node.Child(0));
  if (left_result.IsErr()) {
    return left_result;
  }
  const auto left = left_result.TakeOk();

  const auto operator_ = node.Child(1);
  if (operator_.IsNull()) {
    return IrVisitResult::Err(Error{ErrorCode::kNodeIsNull, "operator"});
  }

  auto right_result = ir_context.ir_visitor.Visit(ir_context, node.Child(2));
  if (right_result.IsErr()) {
    return right_result;
  }
  const auto right = right_result.TakeOk();

  if (operator_.Type() == "==") {
    return IrVisitResult::Ok(
        ir_context.builder->CreateICmpEQ(left, right, "eqtmp"));
  } else if (operator_.Type() == "!=") {
    return IrVisitResult::Ok(
        ir_context.builder->CreateICmpNE(left, right, "netmp"));
  } else if (operator_.Type() == "&&") {
    return IrVisitResult::Ok(
        ir_context.builder->CreateAnd(left, right, "andtmp"));
  } else if (operator_.Type() == "||") {
    return IrVisitResult::Ok(
        ir_context.builder->CreateOr(left, right, "ortmp"));
  } else {
    return IrVisitResult::Err(
        Error{ErrorCode::kBinaryExpressionOperatorIsNotValid,
              std::string{operator_.Type()}});
  }
}

auto Module(IrContext &ir_context, const ts::Node &node) -> IrVisitResult {
  assert(node.Type() == "module" && "node type must be 'module'");
  return IrVisitResult::Err(Error{ErrorCode::kNotImplemented});
}
