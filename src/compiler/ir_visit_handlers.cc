/*
 * This file is included in `ir_visitor.cc` to define the visit handlers.
 */

#include "cpp_tree_sitter/api.h"

#include "llvm/ADT/APFloat.h"

#include "compiler/ir_visitor.h"
#include "compiler/utils.h"

using namespace kero::compiler;

auto True(const IrVisitorContext &context, const ts::Node &node) noexcept
    -> IrVisitResult {
  assert(node.Type() == "true" && "node type must be 'true'");
  return IrVisitResult::Ok(context.ir_builder->getTrue());
}

auto False(const IrVisitorContext &context, const ts::Node &node) noexcept
    -> IrVisitResult {
  assert(node.Type() == "false" && "node type must be 'false'");
  return IrVisitResult::Ok(context.ir_builder->getFalse());
}

auto BinaryExpression(const IrVisitorContext &context,
                      const ts::Node &node) noexcept -> IrVisitResult {
  assert(node.Type() == "binary_expression" &&
         "node type must be 'binary_expression'");
  if (node.ChildCount() != 3) {
    return IrVisitResult::Err(Error{
        ErrorCode::kBinaryExpressionChildCountIsNotThree, NodeToString(node)});
  }

  auto left_result = context.ir_visitor.Visit(context, node.Child(0));
  if (left_result.IsErr()) {
    return left_result;
  }
  const auto left = std::move(left_result.Ok());

  const auto operator_ = node.Child(1);
  if (operator_.IsNull()) {
    return IrVisitResult::Err(Error{ErrorCode::kNodeIsNull, "operator"});
  }

  auto right_result = context.ir_visitor.Visit(context, node.Child(2));
  if (right_result.IsErr()) {
    return right_result;
  }
  const auto right = std::move(right_result.Ok());

  if (operator_.Type() == "*") {
    return IrVisitResult::Ok(
        context.ir_builder->CreateMul(left, right, "multmp"));
  }

  if (operator_.Type() == "/") {
    return IrVisitResult::Ok(
        context.ir_builder->CreateSDiv(left, right, "divtmp"));
  }

  if (operator_.Type() == "%") {
    return IrVisitResult::Ok(
        context.ir_builder->CreateSRem(left, right, "modtmp"));
  }

  if (operator_.Type() == "+") {
    return IrVisitResult::Ok(
        context.ir_builder->CreateAdd(left, right, "addtmp"));
  }

  if (operator_.Type() == "-") {
    return IrVisitResult::Ok(
        context.ir_builder->CreateSub(left, right, "subtmp"));
  }

  if (operator_.Type() == "==") {
    return IrVisitResult::Ok(
        context.ir_builder->CreateICmpEQ(left, right, "eqtmp"));
  }

  if (operator_.Type() == "!=") {
    return IrVisitResult::Ok(
        context.ir_builder->CreateICmpNE(left, right, "netmp"));
  }

  if (operator_.Type() == "&&") {
    return IrVisitResult::Ok(
        context.ir_builder->CreateAnd(left, right, "andtmp"));
  }

  if (operator_.Type() == "||") {
    return IrVisitResult::Ok(
        context.ir_builder->CreateOr(left, right, "ortmp"));
  }

  return IrVisitResult::Err(
      Error{ErrorCode::kBinaryExpressionOperatorIsNotValid,
            std::string{operator_.Type()}});
}

auto Module(const IrVisitorContext &context, const ts::Node &node) noexcept
    -> IrVisitResult {
  assert(node.Type() == "module" && "node type must be 'module'");
  const auto child_count = node.ChildCount();
  for (size_t i = 0; i < child_count; ++i) {
    auto result = context.ir_visitor.Visit(context, node.Child(i));
    if (result.IsErr()) {
      return result;
    }
  }

  return IrVisitResult::Err(Error{ErrorCode::kNotImplemented, "module"});
}

auto Number(const IrVisitorContext &context, const ts::Node &node)
    -> IrVisitResult {
  assert(node.Type() == "number" && "node type must be 'number'");

  const auto start = node.StartByte();
  assert(start >= 0 && "start byte must be greater than or equal to 0");
  assert(start < context.source.size() &&
         "start byte must be less than source size");

  const auto end = node.EndByte();
  assert(end >= 0 && "end byte must be greater than or equal to 0");
  assert(end <= context.source.size() &&
         "end byte must be less than or equal to source size");

  const auto length = end - start;
  assert(length >= 0 && "length must be greater than or equal to 0");
  assert(length <= context.source.size() &&
         "length must be less than or equal to source size");

  const auto number_string = context.source.substr(start, length);
  const auto number = std::strtod(number_string.data(), nullptr);
  return IrVisitResult::Ok(
      llvm::ConstantFP::get(*context.llvm_context, llvm::APFloat(number)));
}
