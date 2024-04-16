#include "compiler/parser_builder.h"

#include <unistd.h>

#include "cpp_tree_sitter/api.h"
#include "tree-sitter-kero.h"

using namespace kero::compiler;

auto kero::compiler::ParserBuilder::SetConsoleLogger(const bool is_set) noexcept
    -> ParserBuilder & {
  set_console_logger_ = is_set;
  return *this;
}

auto kero::compiler::ParserBuilder::SetPrintDotGraphsToStdout(
    const bool is_set) noexcept -> ParserBuilder & {
  set_print_dot_graphs_to_stdout_ = is_set;
  return *this;
}

auto kero::compiler::ParserBuilder::Build() const noexcept -> BuildResult {
  auto parser = ts::Parser{};
  if (!parser.SetLanguage(ts::Language::FromRaw(tree_sitter_kero()))) {
    return BuildResult::Err(Error{ErrorCode::kParserSetLanguageFailed});
  }

  if (set_console_logger_) {
    parser.SetLogger(std::make_unique<ts::ConsoleLogger>());
  }

  if (set_print_dot_graphs_to_stdout_) {
    auto stdout_fd = dup(1);
    parser.PrintDotGraphs(stdout_fd);
  }

  return BuildResult::Ok(std::move(parser));
}
