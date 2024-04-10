#ifndef KERO_COMPILE_PARSER_FACADE_PARSER_FACADE_H
#define KERO_COMPILE_PARSER_FACADE_PARSER_FACADE_H

#include "Compile/Parser/ParserGenerated.h"

#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace kero::compile {

using ParserAuxil = KCParserAuxil;
using ParserContext = KCParser_context_t;
using ParserEvent = KCParserEvent;
using NodeKind = KCNodeKind;
using NodeId = KCNodeId;

struct Span {
  size_t Start; // Inclusive
  size_t End;   // Exclusive

  explicit Span(const size_t Start, const size_t End) noexcept;

  auto operator==(const Span &Other) const noexcept -> bool;
};

auto operator<<(std::ostream &Out, const Span &S) -> std::ostream &;

struct Node {
  std::vector<NodeId> Children;
  std::optional<std::string_view> Value;
  Span Location;
  NodeKind Kind;
  bool IsTerminal;

  explicit Node(Span &&Location, const NodeKind Kind,
                const std::string_view Value) noexcept;
  explicit Node(Span &&Location, const NodeKind Kind,
                std::vector<NodeId> &&Children) noexcept;
};

auto operator<<(std::ostream &Out, const Node &N) -> std::ostream &;

constexpr NodeId NullNodeId{0};

class ParserAuxilDeleter {
public:
  auto operator()(ParserAuxil *Auxil) const noexcept -> void;
};

class ParserContextDeleter {
public:
  auto operator()(ParserContext *Context) const noexcept -> void;
};

class ParserImpl {
public:
  explicit ParserImpl(std::string &&Source) noexcept;
  ~ParserImpl() noexcept = default;

  auto parse() noexcept -> bool;

private:
  auto initAuxil() noexcept -> void;
  auto error() noexcept -> void;
  auto getChar() noexcept -> int;
  auto malloc(const size_t Size) noexcept -> void *;
  auto realloc(void *Ptr, const size_t Size) noexcept -> void *;
  auto free(void *Ptr) noexcept -> void;
  auto debug(const int Event, const char *const Rule, const size_t Level,
             const size_t Pos, const char *const Buffer,
             const size_t Length) noexcept -> void;

  auto createNonTerminalNode(const size_t Start, const size_t End,
                             const NodeKind Kind,
                             std::vector<NodeId> &&Children) noexcept -> NodeId;
  auto createTerminalNode(const size_t Start, const size_t End,
                          const NodeKind Kind,
                          const std::string_view Value) noexcept -> NodeId;

  auto createNodeId() noexcept -> NodeId;
  auto dumpRec(std::ostream &OS, const NodeId Id,
               const size_t level) const noexcept -> void;

  static auto fromAuxil(const ParserAuxil *const Auxil) noexcept
      -> ParserImpl &;

  std::unordered_map<NodeId, Node> NodeMap;
  size_t NextNodeId{1};
  std::string Source;
  size_t SourcePos{0};
  std::unique_ptr<ParserAuxil, ParserAuxilDeleter> Auxil;
  std::unique_ptr<ParserContext, ParserContextDeleter> Context;
  bool ErrorOccurred{false};
};

class ParserFacade {
public:
  explicit ParserFacade(std::string &&Source) noexcept;

  auto parse() noexcept -> bool;

private:
  std::unique_ptr<ParserImpl> Impl;
};

} // namespace kero::compile

#endif // KERO_COMPILE_PARSER_FACADE_PARSER_FACADE_H
