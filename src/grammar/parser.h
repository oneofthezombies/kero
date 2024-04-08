#ifndef KERO_GRAMMAR_PARSER_H
#define KERO_GRAMMAR_PARSER_H

#include "parser_auxil.h"
#include "parser_generated.h"

#include <cstddef>
#include <memory>
#include <string_view>

namespace kero {
namespace grammar {

class KGParserAuxilDeleter {
public:
  auto operator()(KGParserAuxil *auxil) const noexcept -> void;
};

class KGParserDeleter {
public:
  auto operator()(KGParser_context_t *context) const noexcept -> void;
};

class Parser {
public:
  explicit Parser(const std::string_view source) noexcept;

  auto pccError() noexcept -> void;
  auto pccGetChar() noexcept -> int;
  auto pccMalloc(size_t size) noexcept -> void *;
  auto pccRealloc(void *ptr, size_t size) noexcept -> void *;
  auto pccFree(void *ptr) noexcept -> void;
  auto pccDebug(int event, const char *rule, size_t level, size_t pos,
                const char *buffer, size_t length) noexcept -> void;

  auto parse() noexcept -> bool;

private:
  std::string_view Source;
  size_t SourcePos{0};
  std::unique_ptr<KGParserAuxil, KGParserAuxilDeleter> Auxil;
  std::unique_ptr<KGParser_context_t, KGParserDeleter> Context;
  bool ErrorOccurred{false};
};

} // namespace grammar
} // namespace kero

#endif // KERO_GRAMMAR_PARSER_H
