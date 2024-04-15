#include "compiler/parser.h"

#include "cpp_tree_sitter/api.h"
#include "tree-sitter-kero.h"

using namespace kero::compiler;

// Parser::Builder
// --------

auto Parser::Builder::SetConsoleLogger(const bool set) noexcept -> Builder & {
  set_console_logger_ = set;
  return *this;
}

auto Parser::Builder::SetPrintDotGraphsToStdout(const bool set) noexcept
    -> Builder & {
  set_print_dot_graphs_to_stdout_ = set;
  return *this;
}

auto Parser::Builder::Build() const noexcept -> std::optional<Parser> {
  auto ts_parser = ts::Parser{};
  if (!ts_parser.SetLanguage(ts::Language::FromRaw(tree_sitter_kero()))) {
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

auto Parser::Parse(const std::string_view source) const noexcept
    -> std::optional<ts::Tree> {
  return ts_parser_.ParseString(ts::Tree::Null(), source);
}
