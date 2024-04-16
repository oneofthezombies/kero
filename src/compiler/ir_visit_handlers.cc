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
