#ifndef KERO_GRAMMAR_PARSER_H
#define KERO_GRAMMAR_PARSER_H

namespace kero {
namespace grammar {

class Parser {
public:
  explicit Parser() noexcept = default;
  ~Parser() noexcept = default;

  auto analyze(const bool verbose = true) -> bool;
  auto parse() -> bool;
};

} // namespace grammar
} // namespace kero

#endif // KERO_GRAMMAR_PARSER_H
