#ifndef KERO_GRAMMAR_PARSER_H
#define KERO_GRAMMAR_PARSER_H

#include <memory>

struct KeroGrammarParserAuxilTag;
struct KeroGrammarParser_context_tag;

namespace kero {
namespace grammar {

class Parser {
public:
  Parser() noexcept;
  ~Parser() noexcept;

  auto parse() noexcept -> void;

private:
  std::unique_ptr<KeroGrammarParserAuxilTag> auxil_;
  KeroGrammarParser_context_tag* context_{nullptr};
};

} // namespace grammar
} // namespace kero

#endif // KERO_GRAMMAR_PARSER_H
