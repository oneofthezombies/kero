#ifndef KERO_COMPILER_PARSER_H
#define KERO_COMPILER_PARSER_H

#include <optional>
#include <string_view>

#include "cpp_tree_sitter/api.h"

namespace kero::compiler {

// Parser
// --------

class Parser {
public:
  class Builder {
  public:
    Builder() noexcept = default;
    Builder(const Builder &) = delete;
    Builder(Builder &&) noexcept = delete;
    ~Builder() noexcept = default;

    auto operator=(const Builder &) -> Builder & = delete;
    auto operator=(Builder &&) noexcept -> Builder & = delete;

    auto build() const noexcept -> std::optional<Parser>;
  };

  Parser(const Parser &) = delete;
  Parser(Parser &&) noexcept = default;
  ~Parser() noexcept = default;

  auto operator=(const Parser &) -> Parser & = delete;
  auto operator=(Parser &&) noexcept -> Parser & = default;

  auto parse(const std::string_view source) const noexcept
      -> std::optional<kero::ts::Tree>;

private:
  Parser(kero::ts::Parser &&parser) noexcept;

  kero::ts::Parser parser_;
};

} // namespace kero::compiler

#endif // KERO_COMPILER_PARSER_H
