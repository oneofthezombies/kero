#ifndef KERO_GRAMMAR_PARSER_FACADE_H
#define KERO_GRAMMAR_PARSER_FACADE_H

#include <memory>
#include <string_view>

namespace kero {

class ParserImpl;

class ParserFacade {
public:
  ParserFacade(const std::string_view source) noexcept;
  ~ParserFacade() noexcept = default;

  auto Parse() noexcept -> bool;

private:
  std::unique_ptr<ParserImpl> impl_;
};

} // namespace kero

#endif // KERO_GRAMMAR_PARSER_FACADE_H
