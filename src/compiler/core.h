#ifndef KERO_COMPILER_RESULT_H
#define KERO_COMPILER_RESULT_H

#include <cstdint>
#include <string>
#include <variant>

namespace ts {

class Language;

} // namespace ts

namespace kero::compiler {

struct CopyAndMovable {
  CopyAndMovable() noexcept = default;
  CopyAndMovable(const CopyAndMovable &) noexcept = default;
  CopyAndMovable(CopyAndMovable &&) noexcept = default;
  ~CopyAndMovable() noexcept = default;

  auto operator=(const CopyAndMovable &) noexcept -> CopyAndMovable & = default;
  auto operator=(CopyAndMovable &&) noexcept -> CopyAndMovable & = default;
};

struct NonCopyAndMovable {
  NonCopyAndMovable() noexcept = default;
  NonCopyAndMovable(const NonCopyAndMovable &) = delete;
  NonCopyAndMovable(NonCopyAndMovable &&) noexcept = default;
  ~NonCopyAndMovable() noexcept = default;

  auto operator=(const NonCopyAndMovable &) -> NonCopyAndMovable & = delete;
  auto operator=(NonCopyAndMovable &&) noexcept
      -> NonCopyAndMovable & = default;
};

struct CopyAndNonMovable {
  CopyAndNonMovable() noexcept = default;
  CopyAndNonMovable(const CopyAndNonMovable &) noexcept = default;
  CopyAndNonMovable(CopyAndNonMovable &&) = delete;
  ~CopyAndNonMovable() noexcept = default;

  auto operator=(const CopyAndNonMovable &) noexcept
      -> CopyAndNonMovable & = default;
  auto operator=(CopyAndNonMovable &&) -> CopyAndNonMovable & = delete;
};

struct NonCopyAndNonMovable {
  NonCopyAndNonMovable() = default;
  NonCopyAndNonMovable(const NonCopyAndNonMovable &) = delete;
  NonCopyAndNonMovable(NonCopyAndNonMovable &&) = delete;
  ~NonCopyAndNonMovable() noexcept = default;

  auto operator=(const NonCopyAndNonMovable &)
      -> NonCopyAndNonMovable & = delete;
  auto operator=(NonCopyAndNonMovable &&) -> NonCopyAndNonMovable & = delete;
};

template <typename T, typename E> class Result : public NonCopyAndMovable {
public:
  using Self = Result<T, E>;

  Result() = delete;

  auto IsOk() const noexcept -> bool {
    return std::holds_alternative<T>(data_);
  }

  auto IsErr() const noexcept -> bool {
    return std::holds_alternative<E>(data_);
  }

  auto Ok() noexcept -> T & {
    assert(IsOk() && "Result must be in Ok state");
    return std::get<T>(data_);
  }

  auto Err() noexcept -> E & {
    assert(IsErr() && "Result must be in Err state");
    return std::get<E>(data_);
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

struct Void : public CopyAndMovable {};

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

struct Error : public NonCopyAndMovable {
  ErrorCode code;
  std::string message;

  explicit Error(const ErrorCode code) noexcept;
  explicit Error(const ErrorCode code, std::string &&message) noexcept;
};

auto operator<<(std::ostream &os, const Error &error) -> std::ostream &;

using VoidResult = Result<Void, Error>;

auto Language() -> ts::Language;

} // namespace kero::compiler

#endif // KERO_COMPILER_RESULT_H
