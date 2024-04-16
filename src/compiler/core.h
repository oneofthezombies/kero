#ifndef KERO_COMPILER_RESULT_H
#define KERO_COMPILER_RESULT_H

#include <cstdint>
#include <string>
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
  kNodeIsNull,
  kBinaryExpressionChildCountIsNotThree,
  kBinaryExpressionOperatorIsNotValid,
};

template <typename T, typename E> class Result {
public:
  using Self = Result<T, E>;

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
    return std::holds_alternative<E>(data_);
  }

  [[nodiscard]] auto TakeOk() noexcept -> T {
    assert(IsOk() && "Result must be in Ok state");
    return std::move(std::get<T>(data_));
  }

  [[nodiscard]] auto TakeErr() const noexcept -> E {
    assert(IsErr() && "Result must be in Err state");
    return std::move(std::get<E>(data_));
  }

  [[nodiscard]] static auto Ok(T &&value) noexcept -> Self {
    return Self{std::move(value)};
  }

  [[nodiscard]] static auto Err(E &&error) noexcept -> Self {
    return Self{std::move(error)};
  }

private:
  explicit Result(T &&value) noexcept : data_{std::move(value)} {}
  explicit Result(E &&error) noexcept : data_{std::move(error)} {}

  std::variant<std::monostate, T, E> data_;
};

struct Void {};

struct Error {
  ErrorCode code;
  std::string message;

  explicit Error(const ErrorCode code) noexcept;
  explicit Error(const ErrorCode code, std::string &&message) noexcept;
  ~Error() noexcept = default;

  static auto FromStringView(const ErrorCode code,
                             std::string_view &&message) noexcept -> Error;
};

auto operator<<(std::ostream &os, const Error &error) -> std::ostream &;

using VoidResult = Result<Void, Error>;

auto Language() -> ts::Language;

} // namespace kero::compiler

#endif // KERO_COMPILER_RESULT_H
