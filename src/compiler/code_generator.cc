#include "code_generator.h"

#include <tuple>
#include <vector>

using namespace kero::compiler;

static const std::vector<std::tuple<std::string_view, bool, Visitor>>
    kVisitors = {
        {
            "true",
            true,
            [](Context &context, const ts::Node &node) -> Result<ValueRef> {
              return context.builder->getTrue();
            },
        },
        {
            "false",
            true,
            [](Context &context, const ts::Node &node) -> Result<ValueRef> {
              return context.builder->getFalse();
            },
        },
        {
            "binary_expression",
            true,
            [](Context &context, const ts::Node &node) -> Result<ValueRef> {
              const auto left = node.Child(0);
              if (left.IsNull()) {
                return ResultCode::kBinaryExpressionLeftIsNull;
              }

              const auto operator_ = node.Child(1);
              if (operator_.IsNull()) {
                return ResultCode::kBinaryExpressionOperatorIsNull;
              }

              const auto right = node.Child(2);
              if (right.IsNull()) {
                return ResultCode::kBinaryExpressionRightIsNull;
              }

              if (auto visitor = context.visitors.find(left.Symbol());
                  visitor != context.visitors.end()) {
                const auto left_value = visitor->second(context, left);
                if (std::holds_alternative<ResultCode>(left_value)) {
                  return std::get<ResultCode>(left_value);
                }
              }
            },
        },

        // This comment prevents tuple's `}` and vector's `}` from
        // being attached in the form `}}` by `clang-format`.
};

kero::compiler::Context::Context(kero::compiler::Parser &&parser) noexcept
    : parser{std::move(parser)},
      llvm_context{std::make_unique<llvm::LLVMContext>()},
      module{std::make_unique<llvm::Module>("kero", *llvm_context)},
      builder{std::make_unique<llvm::IRBuilder<>>(*llvm_context)} {}

kero::compiler::CodeGenerator::Builder::Builder(
    kero::compiler::Parser &&parser) noexcept
    : parser_{std::move(parser)} {}

auto kero::compiler::CodeGenerator::Builder::Build() noexcept
    -> Result<CodeGenerator> {
  auto code_generator = CodeGenerator{std::move(parser_)};
  const auto result = code_generator.RegisterAllVisitor();
  if (result != ResultCode::kSuccess) {
    return result;
  }
  return code_generator;
}

kero::compiler::CodeGenerator::CodeGenerator(
    kero::compiler::Parser &&parser) noexcept
    : context_{std::move(parser)} {}

auto kero::compiler::CodeGenerator::Generate() noexcept -> void {}

auto kero::compiler::CodeGenerator::RegisterAllVisitor() noexcept
    -> ResultCode {
  for (const auto &[type, named, visitor] : kVisitors) {
    const auto result = RegisterVisitor(type, named, visitor);
    if (result != ResultCode::kSuccess) {
      return result;
    }
  }
  return ResultCode::kSuccess;
}

auto kero::compiler::CodeGenerator::RegisterVisitor(
    const std::string_view type, const bool named,
    const Visitor &visitor) noexcept -> ResultCode {
  const auto symbol = context_.parser.Symbol(type, named);
  if (symbol == ts::Language::kSymbolNotFound) {
    return ResultCode::kSymbolNotFound;
  }

  if (context_.visitors.find(symbol) != context_.visitors.end()) {
    return ResultCode::kVisitorAlreadyRegistered;
  }

  context_.visitors.emplace(symbol, visitor);
  return ResultCode::kSuccess;
}
