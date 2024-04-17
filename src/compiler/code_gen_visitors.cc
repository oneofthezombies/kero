/*
 * This file is included in `code_generator.cc` to define the code generation
 * visitors for the tree-sitter nodes.
 */

#include "cpp_tree_sitter/api.h"
#include "llvm/ADT/APFloat.h"

#include "compiler/code_generator.h"
#include "compiler/utils.h"

using namespace kero::compiler;

class TrueVisitor final : public CodeGenVisitor {
public:
  TrueVisitor() noexcept : CodeGenVisitor{CodeGenKind{"true", true}} {}

  auto Visit(const CodeGenContext &context, const ts::Node &node) const noexcept
      -> CodeGenResult override {
    return CodeGenResult::Ok(context.builder->getTrue());
  }
};

class FalseVisitor final : public CodeGenVisitor {
public:
  FalseVisitor() noexcept : CodeGenVisitor{CodeGenKind{"false", true}} {}

  auto Visit(const CodeGenContext &context, const ts::Node &node) const noexcept
      -> CodeGenResult override {
    return CodeGenResult::Ok(context.builder->getFalse());
  }
};

class BinaryExpressionVisitor final : public CodeGenVisitor {
public:
  BinaryExpressionVisitor() noexcept
      : CodeGenVisitor{CodeGenKind{"binary_expression", true}} {}

  auto Visit(const CodeGenContext &context, const ts::Node &node) const noexcept
      -> CodeGenResult override {
    if (node.ChildCount() != 3) {
      return CodeGenResult::Err(
          Error{ErrorCode::kBinaryExpressionChildCountIsNotThree,
                NodeToString(node)});
    }

    auto left_result = context.visitor.Visit(context, node.Child(0));
    if (left_result.IsErr()) {
      return left_result;
    }
    const auto left = std::move(left_result.Ok());

    const auto operator_ = node.Child(1);
    if (operator_.IsNull()) {
      return CodeGenResult::Err(Error{ErrorCode::kNodeIsNull, "operator"});
    }

    auto right_result = context.visitor.Visit(context, node.Child(2));
    if (right_result.IsErr()) {
      return right_result;
    }
    const auto right = std::move(right_result.Ok());

    if (operator_.Type() == "*") {
      return CodeGenResult::Ok(
          context.builder->CreateMul(left, right, "multmp"));
    }

    if (operator_.Type() == "/") {
      return CodeGenResult::Ok(
          context.builder->CreateSDiv(left, right, "divtmp"));
    }

    if (operator_.Type() == "%") {
      return CodeGenResult::Ok(
          context.builder->CreateSRem(left, right, "modtmp"));
    }

    if (operator_.Type() == "+") {
      return CodeGenResult::Ok(
          context.builder->CreateAdd(left, right, "addtmp"));
    }

    if (operator_.Type() == "-") {
      return CodeGenResult::Ok(
          context.builder->CreateSub(left, right, "subtmp"));
    }

    if (operator_.Type() == "==") {
      return CodeGenResult::Ok(
          context.builder->CreateICmpEQ(left, right, "eqtmp"));
    }

    if (operator_.Type() == "!=") {
      return CodeGenResult::Ok(
          context.builder->CreateICmpNE(left, right, "netmp"));
    }

    if (operator_.Type() == "&&") {
      return CodeGenResult::Ok(
          context.builder->CreateAnd(left, right, "andtmp"));
    }

    if (operator_.Type() == "||") {
      return CodeGenResult::Ok(context.builder->CreateOr(left, right, "ortmp"));
    }

    return CodeGenResult::Err(
        Error{ErrorCode::kBinaryExpressionOperatorIsNotValid,
              std::string{operator_.Type()}});
  }
};

class ModuleVisitor final : public CodeGenVisitor {
public:
  ModuleVisitor() noexcept : CodeGenVisitor{CodeGenKind{"module", true}} {}

  auto Visit(const CodeGenContext &context, const ts::Node &node) const noexcept
      -> CodeGenResult override {
    const auto child_count = node.ChildCount();
    for (size_t i = 0; i < child_count; ++i) {
      auto result = context.visitor.Visit(context, node.Child(i));
      if (result.IsErr()) {
        return result;
      }
    }

    return CodeGenResult::Err(Error{ErrorCode::kNotImplemented, "module"});
  }
};

class NumberVisitor final : public CodeGenVisitor {
public:
  NumberVisitor() noexcept : CodeGenVisitor{CodeGenKind{"number", true}} {}

  auto Visit(const CodeGenContext &context, const ts::Node &node) const noexcept
      -> CodeGenResult override {
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
    return CodeGenResult::Ok(
        llvm::ConstantFP::get(*context.llvm_context, llvm::APFloat(number)));
  }
};
