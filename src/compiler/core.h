#ifndef KERO_COMPILER_RESULT_H
#define KERO_COMPILER_RESULT_H

#include <cstdint>
#include <string>
#include <variant>

namespace ts {

class Language;

} // namespace ts

namespace kero::compiler {

class Copyable {
public:
  Copyable() noexcept = default;
  Copyable(const Copyable &) noexcept = default;
  Copyable(Copyable &&) noexcept = default;
  ~Copyable() noexcept = default;

  auto operator=(const Copyable &) noexcept -> Copyable & = default;
  auto operator=(Copyable &&) noexcept -> Copyable & = default;
};

class NonCopyable {
public:
  NonCopyable() noexcept = default;
  NonCopyable(const NonCopyable &) = delete;
  NonCopyable(NonCopyable &&) noexcept = default;
  ~NonCopyable() noexcept = default;

  auto operator=(const NonCopyable &) -> NonCopyable & = delete;
  auto operator=(NonCopyable &&) noexcept -> NonCopyable & = default;
};

class Movable {
public:
  Movable() noexcept = default;
  Movable(const Movable &) noexcept = default;
  Movable(Movable &&) noexcept = default;
  ~Movable() noexcept = default;

  auto operator=(const Movable &) noexcept -> Movable & = default;
  auto operator=(Movable &&) noexcept -> Movable & = default;
};

class NonMovable {
public:
  NonMovable() noexcept = default;
  NonMovable(const NonMovable &) noexcept = default;
  NonMovable(NonMovable &&) = delete;
  ~NonMovable() noexcept = default;

  auto operator=(const NonMovable &) noexcept -> NonMovable & = default;
  auto operator=(NonMovable &&) -> NonMovable & = delete;
};

template <typename T, typename E>
  requires std::movable<T> && std::movable<E>
class Result final : private NonCopyable, Movable {
public:
  using Self = Result<T, E>;

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
    return std::move(Self{std::move(value)});
  }

  [[nodiscard]] static auto Err(E &&error) noexcept -> Self {
    return std::move(Self{std::move(error)});
  }

private:
  explicit Result(T &&value) noexcept : data_{std::move(value)} {}
  explicit Result(E &&error) noexcept : data_{std::move(error)} {}

  std::variant<std::monostate, T, E> data_;
};

struct Void final : private Copyable, Movable {};

enum class ErrorCode : int32_t {
  kNotImplemented = 0,

  // ParserBuilder
  // -------------
  kParserSetLanguageFailed,

  // CodeGenerator
  // -------------
  kVisitorNotFound,
  kNodeIsNull,
  kBinaryExpressionChildCountIsNotThree,
  kBinaryExpressionOperatorIsNotValid,
};

struct Error final : private NonCopyable, Movable {
  ErrorCode code;
  std::string message;

  explicit Error(const ErrorCode code) noexcept;
  explicit Error(const ErrorCode code, std::string &&message) noexcept;
};

auto operator<<(std::ostream &os, const Error &error) -> std::ostream &;

using VoidResult = Result<Void, Error>;

} // namespace kero::compiler

#endif // KERO_COMPILER_RESULT_H
