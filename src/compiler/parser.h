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

    auto SetConsoleLogger(const bool set = true) noexcept -> Builder &;
    auto SetPrintDotGraphsToStdout(const bool set = true) noexcept -> Builder &;

    auto Build() const noexcept -> std::optional<Parser>;

  private:
    bool set_console_logger_{false};
    bool set_print_dot_graphs_to_stdout_{false};
  };

  Parser(const Parser &) = delete;
  Parser(Parser &&) noexcept = default;
  ~Parser() noexcept = default;

  auto operator=(const Parser &) -> Parser & = delete;
  auto operator=(Parser &&) noexcept -> Parser & = default;

  auto Parse(const std::string_view source) const noexcept
      -> std::optional<ts::Tree>;
  auto Symbol(const std::string_view type, const bool named) const noexcept
      -> ts::Symbol;

private:
  Parser(ts::Parser &&ts_parser) noexcept;

  ts::Parser ts_parser_;
};

} // namespace kero::compiler

#endif // KERO_COMPILER_PARSER_H
