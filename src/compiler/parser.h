#ifndef KERO_COMPILER_PARSER_H
#define KERO_COMPILER_PARSER_H

#include <string_view>

namespace kero::compiler {

class Parser {
public:
  explicit Parser(const std::string_view source) noexcept;

private:
  std::string_view source_;
};

} // namespace kero::compiler

#endif // KERO_COMPILER_PARSER_H
