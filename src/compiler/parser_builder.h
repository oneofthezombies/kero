#ifndef KERO_COMPILER_PARSER_BUILDER_H
#define KERO_COMPILER_PARSER_BUILDER_H

#include "cpp_tree_sitter/api.h"

#include "compiler/core.h"

namespace kero::compiler {

class ParserBuilder final : private NonCopyable, NonMovable {
public:
  using Result = kero::compiler::Result<ts::Parser, Error>;

  auto SetConsoleLogger(const bool is_set = true) noexcept -> ParserBuilder &;
  auto SetPrintDotGraphsToStdout(const bool is_set = true) noexcept
      -> ParserBuilder &;

  auto Build() const noexcept -> Result;

private:
  bool set_console_logger_{false};
  bool set_print_dot_graphs_to_stdout_{false};
};

} // namespace kero::compiler

#endif // KERO_COMPILER_PARSER_BUILDER_H
