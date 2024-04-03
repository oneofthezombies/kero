#ifndef KERO_GRAMMAR_PARSER_H
#define KERO_GRAMMAR_PARSER_H

#include <string_view>

struct KeroGrammarCore_context_tag;

namespace kero {
namespace grammar {

class Parser {
public:
  Parser(const std::string_view source) noexcept;
  ~Parser() noexcept;

  auto OnGetChar() noexcept -> int;
  auto OnError() noexcept -> void;

  auto Parse() noexcept -> void;

private:
  std::string_view source_;
  size_t source_index_{0};
  ::KeroGrammarCore_context_tag* core_context_{nullptr};
  bool error_occurred_{false};
};

} // namespace grammar
} // namespace kero

#endif // KERO_GRAMMAR_PARSER_H
