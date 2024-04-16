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
  const auto left = node.Child(0);
  const auto op = node.Child(1);
  const auto right = node.Child(2);
  // ir_context.builder->CreateICmpEQ();
  return IrVisitResult::Err(ErrorCode::kNotImplemented);
}
