#ifndef KERO_COMPILER_RESULT_H
#define KERO_COMPILER_RESULT_H

#include <cstdint>
#include <variant>

namespace kero::compiler {

enum class ResultCode : int32_t {
  kSuccess = 0,

  // CodeGenerator
  // --------
  kSymbolNotFound = 100,
  kVisitorAlreadyRegistered,

  // Visitor
  // --------
  kBinaryExpressionLeftIsNull = 200,
  kBinaryExpressionOperatorIsNull,
  kBinaryExpressionRightIsNull,
};

template <typename T> using Result = std::variant<T, ResultCode>;

using ValueRef = llvm::Value *;

} // namespace kero::compiler

#endif // KERO_COMPILER_RESULT_H
