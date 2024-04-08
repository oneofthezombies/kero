#ifndef KERO_GRAMMAR_PARSER_H
#define KERO_GRAMMAR_PARSER_H

#include <cstddef>

namespace kero {
namespace grammar {

class Parser {
public:
  int pccGetChar() noexcept;
  void pccError() noexcept;
  void pccDebug(int event, const char *rule, size_t level, size_t pos,
                const char *buffer, size_t length) noexcept;
};

} // namespace grammar
} // namespace kero

#endif // KERO_GRAMMAR_PARSER_H
