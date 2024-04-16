#ifndef KERO_COMPILER_RESULT_H
#define KERO_COMPILER_RESULT_H

#include <cstdint>
#include <variant>

namespace ts {

class Language;

} // namespace ts

namespace kero::compiler {

enum class ErrorCode : int32_t {
  kNotImplemented = 0,

  // ParserBuilder
  // ------------
  kParserSetLanguageFailed,

  // IrVisitor
  // --------
  kSymbolNotFound,
  kVisitHandlerAlreadyRegistered,
  kVisitHandlerNotFound,
  kBinaryExpressionLeftIsNull,
  kBinaryExpressionOperatorIsNull,
  kBinaryExpressionRightIsNull,
};

template <typename T> class Result {
public:
  Result() = delete;
  Result(const Result &) = delete;
  Result(Result &&) noexcept = default;
  ~Result() noexcept = default;

  auto operator=(const Result &) -> Result & = delete;
  auto operator=(Result &&) noexcept -> Result & = default;

  auto IsOk() const noexcept -> bool {
    return std::holds_alternative<T>(data_);
  }

  auto IsErr() const noexcept -> bool {
    return std::holds_alternative<ErrorCode>(data_);
  }

  [[nodiscard]] auto TakeOk() noexcept -> T {
    assert(IsOk() && "Result must be in Ok state");
    return std::move(std::get<T>(data_));
  }

  auto Err() const noexcept -> ErrorCode {
    assert(IsErr() && "Result must be in Err state");
    return std::get<ErrorCode>(data_);
  }

  [[nodiscard]] static auto Ok(T &&value) noexcept -> Result<T> {
    return Result<T>{std::move(value)};
  }

  static auto Err(const ErrorCode code) noexcept -> Result<T> {
    return Result<T>{code};
  }

private:
  explicit Result(T &&value) noexcept : data_{std::move(value)} {}
  explicit Result(const ErrorCode code) noexcept : data_(code) {}

  std::variant<std::monostate, T, ErrorCode> data_;
};

struct Void {};

using VoidResult = Result<Void>;

auto Language() -> ts::Language;

} // namespace kero::compiler

#endif // KERO_COMPILER_RESULT_H
