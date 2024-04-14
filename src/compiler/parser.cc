#include "compiler/parser.h"

#include "cpp_tree_sitter/api.h"
#include "tree-sitter-kero.h"

using namespace kero::compiler;

// Parser::Builder
// --------

auto Parser::Builder::set_console_logger() noexcept -> Builder & {
  set_console_logger_ = true;
  return *this;
}

auto Parser::Builder::set_print_dot_graphs_to_stdout() noexcept -> Builder & {
  set_print_dot_graphs_to_stdout_ = true;
  return *this;
}

auto Parser::Builder::build() const noexcept -> std::optional<Parser> {
  auto ts_parser = ts::Parser{};
  if (!ts_parser.SetLanguage(ts::Language{tree_sitter_kero()})) {
    return std::nullopt;
  }
  if (set_console_logger_) {
    ts_parser.SetLogger(std::make_unique<ts::ConsoleLogger>());
  }
  if (set_print_dot_graphs_to_stdout_) {
    auto stdout_fd = dup(1);
    ts_parser.PrintDotGraphs(stdout_fd);
  }
  return Parser{std::move(ts_parser)};
}

// Parser
// --------

Parser::Parser(ts::Parser &&ts_parser) noexcept
    : ts_parser_{std::move(ts_parser)} {}

auto Parser::parse(const std::string_view source) const noexcept
    -> std::optional<ts::Tree> {
  return ts_parser_.ParseString(ts::Tree::Null(), source);
}
