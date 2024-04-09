#ifndef KERO_GRAMMAR_PARSER_H
#define KERO_GRAMMAR_PARSER_H

#include "ParserAuxil.h"
#include "ParserGenerated.h"

#include <cstddef>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace kero::grammar {

struct SourceSpan {
  size_t Start; // Inclusive
  size_t End;   // Exclusive

  auto operator==(const SourceSpan &Other) const noexcept -> bool;
};

} // namespace kero::grammar

template <> struct std::hash<kero::grammar::SourceSpan> {
  auto operator()(const kero::grammar::SourceSpan &Span) const noexcept
      -> size_t {
    return std::hash<size_t>{}(Span.Start) ^ std::hash<size_t>{}(Span.End);
  }
};

namespace kero::grammar {

class KGParserAuxilDeleter {
public:
  auto operator()(KGParserAuxil *Auxil) const noexcept -> void;
};

class KGParserDeleter {
public:
  auto operator()(KGParser_context_t *Context) const noexcept -> void;
};

struct Node {
  std::vector<KGNodeId> Children;
  std::string_view Value;
  KGNodeKind Kind;
  bool IsTerminal{false};
};

constexpr KGNodeId NullNodeId{0};

class Parser {
public:
  explicit Parser(std::string &&Source) noexcept;

  auto pccError() noexcept -> void;
  auto pccGetChar() noexcept -> int;
  auto pccMalloc(const size_t Size) noexcept -> void *;
  auto pccRealloc(void *Ptr, const size_t Size) noexcept -> void *;
  auto pccFree(void *Ptr) noexcept -> void;
  auto pccDebug(const int Event, const char *const Rule, const size_t Level,
                const size_t Pos, const char *const Buffer,
                const size_t Length) noexcept -> void;

  auto createNonTerminalNode(const size_t Start, const size_t End,
                             const KGNodeKind Kind,
                             std::vector<KGNodeId> &&Children) noexcept
      -> KGNodeId;
  auto createTerminalNode(const size_t Start, const size_t End,
                          const KGNodeKind Kind,
                          const std::string_view Value) noexcept -> KGNodeId;

  auto parse() noexcept -> bool;

private:
  auto createNodeId() noexcept -> KGNodeId;
  auto printTree(const KGNodeId NodeId, const size_t level) const noexcept
      -> void;

  std::unordered_map<KGNodeId, Node> NodeMap;
  size_t NextNodeId{1};
  std::string Source;
  size_t SourcePos{0};
  std::unique_ptr<KGParserAuxil, KGParserAuxilDeleter> Auxil;
  std::unique_ptr<KGParser_context_t, KGParserDeleter> Context;
  bool ErrorOccurred{false};
};

} // namespace kero::grammar

#endif // KERO_GRAMMAR_PARSER_H
