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
  auto operator()(KGParserAuxil *Auxil) const noexcept -> void;
};

class KGParserDeleter {
public:
  auto operator()(KGParser_context_t *Context) const noexcept -> void;
};

class Parser {
public:
  explicit Parser(const std::string_view Source) noexcept;

  auto pccError() noexcept -> void;
  auto pccGetChar() noexcept -> int;
  auto pccMalloc(const size_t Size) noexcept -> void *;
  auto pccRealloc(void *Ptr, const size_t Size) noexcept -> void *;
  auto pccFree(void *Ptr) noexcept -> void;
  auto pccDebug(const int Event, const char *const Rule, const size_t Level,
                const size_t Pos, const char *const Buffer,
                const size_t Length) noexcept -> void;

  auto createNode(const KGNodeKind Kind, const size_t Start,
                  const size_t End) noexcept -> KGNode *;

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
