#include "parser.h"

#include <cassert>
#include <iostream>

using namespace kero::grammar;

struct KGParserAuxilTag {
  ::Parser *Parser{nullptr};
};

void checkParserAuxil(const KGParserAuxilTag *const Auxil) {
  assert(Auxil != nullptr && "auxil must not be nullptr.");
  assert(Auxil->Parser != nullptr && "parser must not be nullptr.");
}

void KGParserAuxil_pccError(const KGParserAuxilTag *const Auxil) {
  checkParserAuxil(Auxil);
  Auxil->Parser->pccError();
}

int KGParserAuxil_pccGetChar(const KGParserAuxilTag *const Auxil) {
  checkParserAuxil(Auxil);
  return Auxil->Parser->pccGetChar();
}

void *KGParserAuxil_pccMalloc(const KGParserAuxilTag *const Auxil,
                              const size_t Size) {
  checkParserAuxil(Auxil);
  return Auxil->Parser->pccMalloc(Size);
}

void *KGParserAuxil_pccRealloc(const KGParserAuxilTag *const Auxil, void *Ptr,
                               const size_t Size) {
  checkParserAuxil(Auxil);
  return Auxil->Parser->pccRealloc(Ptr, Size);
}

void KGParserAuxil_pccFree(const KGParserAuxilTag *const Auxil, void *Ptr) {
  checkParserAuxil(Auxil);
  Auxil->Parser->pccFree(Ptr);
}

void KGParserAuxil_pccDebug(const KGParserAuxilTag *const Auxil,
                            const int Event, const char *const Rule,
                            const size_t Level, const size_t Pos,
                            const char *const Buffer, const size_t Length) {
  checkParserAuxil(Auxil);
  Auxil->Parser->pccDebug(Event, Rule, Level, Pos, Buffer, Length);
}

KGNodeId KGParserAuxil_createNonTerminal0(const KGParserAuxilTag *const Auxil,
                                          const size_t Start, const size_t End,
                                          const KGNodeKind Kind) {
  checkParserAuxil(Auxil);
  return Auxil->Parser->createNonTerminalNode(Start, End, Kind, {});
}

KGNodeId KGParserAuxil_createNonTerminal1(const KGParserAuxilTag *const Auxil,
                                          const size_t Start, const size_t End,
                                          const KGNodeKind Kind,
                                          const KGNodeId Child0) {
  checkParserAuxil(Auxil);
  return Auxil->Parser->createNonTerminalNode(Start, End, Kind, {Child0});
}

KGNodeId KGParserAuxil_createNonTerminal2(const KGParserAuxilTag *const Auxil,
                                          const size_t Start, const size_t End,
                                          const KGNodeKind Kind,
                                          const KGNodeId Child0,
                                          const KGNodeId Child1) {
  checkParserAuxil(Auxil);
  return Auxil->Parser->createNonTerminalNode(Start, End, Kind,
                                              {Child0, Child1});
}

KGNodeId KGParserAuxil_createNonTerminal3(const KGParserAuxilTag *const Auxil,
                                          const size_t Start, const size_t End,
                                          const KGNodeKind Kind,
                                          const KGNodeId Child0,
                                          const KGNodeId Child1,
                                          const KGNodeId Child2) {
  checkParserAuxil(Auxil);
  return Auxil->Parser->createNonTerminalNode(Start, End, Kind,
                                              {Child0, Child1, Child2});
}

KGNodeId KGParserAuxil_createNonTerminal4(
    const KGParserAuxilTag *const Auxil, const size_t Start, const size_t End,
    const KGNodeKind Kind, const KGNodeId Child0, const KGNodeId Child1,
    const KGNodeId Child2, const KGNodeId Child3) {
  checkParserAuxil(Auxil);
  return Auxil->Parser->createNonTerminalNode(Start, End, Kind,
                                              {Child0, Child1, Child2, Child3});
}

KGNodeId KGParserAuxil_createNonTerminal5(
    const KGParserAuxilTag *const Auxil, const size_t Start, const size_t End,
    const KGNodeKind Kind, const KGNodeId Child0, const KGNodeId Child1,
    const KGNodeId Child2, const KGNodeId Child3, const KGNodeId Child4) {
  checkParserAuxil(Auxil);
  return Auxil->Parser->createNonTerminalNode(
      Start, End, Kind, {Child0, Child1, Child2, Child3, Child4});
}

KGNodeId KGParserAuxil_createNonTerminal6(
    const KGParserAuxilTag *const Auxil, const size_t Start, const size_t End,
    const KGNodeKind Kind, const KGNodeId Child0, const KGNodeId Child1,
    const KGNodeId Child2, const KGNodeId Child3, const KGNodeId Child4,
    const KGNodeId Child5) {
  checkParserAuxil(Auxil);
  return Auxil->Parser->createNonTerminalNode(
      Start, End, Kind, {Child0, Child1, Child2, Child3, Child4, Child5});
}

KGNodeId KGParserAuxil_createTerminal0(const KGParserAuxilTag *const Auxil,
                                       const size_t Start, const size_t End,
                                       const KGNodeKind Kind) {
  checkParserAuxil(Auxil);
  return Auxil->Parser->createTerminalNode(Start, End, Kind, {});
}

KGNodeId KGParserAuxil_createTerminal1(const KGParserAuxilTag *const Auxil,
                                       const size_t Start, const size_t End,
                                       const KGNodeKind Kind,
                                       const char *const Value) {
  checkParserAuxil(Auxil);
  return Auxil->Parser->createTerminalNode(Start, End, Kind, Value);
}

namespace {

enum class DebugEvent : int32_t {
  RuleEvaluating = 0,
  RuleMatched = 1,
  RuleNotMatched = 2,
};

auto operator<<(std::ostream &OS, const DebugEvent Event) noexcept
    -> std::ostream & {
  switch (Event) {
  case DebugEvent::RuleEvaluating:
    OS << "RuleEvaluating";
    break;
  case DebugEvent::RuleMatched:
    OS << "RuleMatched";
    break;
  case DebugEvent::RuleNotMatched:
    OS << "RuleNotMatched";
    break;
  }
  return OS;
}

} // namespace

auto kero::grammar::SourceSpan::operator==(
    const SourceSpan &Other) const noexcept -> bool {
  return Start == Other.Start && End == Other.End;
}

auto kero::grammar::KGParserAuxilDeleter::operator()(
    KGParserAuxil *Auxil) const noexcept -> void {
  if (Auxil == nullptr) {
    return;
  }
  delete Auxil;
}

auto kero::grammar::KGParserDeleter::operator()(
    KGParser_context_t *Context) const noexcept -> void {
  KGParser_destroy(Context);
}

kero::grammar::Parser::Parser(std::string &&Source) noexcept
    : Source{std::move(Source)}, Auxil{new KGParserAuxil{this}},
      Context{KGParser_create(Auxil.get())} {}

auto kero::grammar::Parser::pccError() noexcept -> void {
  ErrorOccurred = true;
}

auto kero::grammar::Parser::pccGetChar() noexcept -> int {
  if (SourcePos >= Source.size()) {
    return -1;
  }
  return Source[SourcePos++];
}

auto kero::grammar::Parser::pccMalloc(const size_t Size) noexcept -> void * {
  void *P = std::malloc(Size);
  if (P == nullptr) {
    std::cerr << "Parser::pccMalloc() failed to allocate memory" << '\n'
              << std::flush;
    std::exit(EXIT_FAILURE);
  }
  return P;
}

auto kero::grammar::Parser::pccRealloc(void *Ptr, const size_t Size) noexcept
    -> void * {
  void *P = std::realloc(Ptr, Size);
  if (P == nullptr) {
    std::cerr << "Parser::pccRealloc() failed to reallocate memory" << '\n'
              << std::flush;
    std::exit(EXIT_FAILURE);
  }
  return P;
}

auto kero::grammar::Parser::pccFree(void *Ptr) noexcept -> void {
  if (Ptr != nullptr) {
    std::free(Ptr);
  }
}

auto kero::grammar::Parser::pccDebug(const int Event, const char *const Rule,
                                     const size_t Level, const size_t Pos,
                                     const char *const Buffer,
                                     const size_t Length) noexcept -> void {
  const DebugEvent E{static_cast<DebugEvent>(Event)};
  const std::string_view RV{Rule};
  const std::string_view BV{Buffer, Length};
  std::cout << "Parser::pccDebug() event " << E << " rule " << RV << " level "
            << Level << " pos " << Pos << " buffer " << BV << '\n';
}

auto kero::grammar::Parser::createNonTerminalNode(
    const size_t Start, const size_t End, const KGNodeKind Kind,
    std::vector<KGNodeId> &&Children) noexcept -> KGNodeId {
  const KGNodeId Id{findOrCreateNodeId({Start, End})};

  // Remove null children
  Children.erase(
      std::remove_if(Children.begin(), Children.end(),
                     [](const KGNodeId &Child) { return Child == 0; }),
      Children.end());

  NodeMap[Id] = Node{std::move(Children), {}, Kind, false};
  std::cout << "Parser::createNonTerminalNode() id " << Id << " start " << Start
            << " end " << End << " kind " << static_cast<int>(Kind)
            << " children ";
  for (const auto &Child : NodeMap[Id].Children) {
    std::cout << Child << ' ';
  }
  std::cout << '\n';
  return Id;
}

auto kero::grammar::Parser::createTerminalNode(
    const size_t Start, const size_t End, const KGNodeKind Kind,
    const std::string_view Value) noexcept -> KGNodeId {
  const KGNodeId Id{findOrCreateNodeId({Start, End})};
  NodeMap[Id] = Node{{}, Value, Kind, true};
  std::cout << "Parser::createTerminalNode() id " << Id << " start " << Start
            << " end " << End << " kind " << static_cast<int>(Kind) << " value "
            << Value << '\n';
  return Id;
}

auto kero::grammar::Parser::parse() noexcept -> bool {
  std::cout << "Parser::parse() called" << '\n';
  KGNodeId Ret{0};
  while (true) {
    if (KGParser_parse(Context.get(), &Ret) == 0) {
      break;
    }

    if (ErrorOccurred) {
      std::cout << "Parser::parse() has error" << '\n';
      break;
    }
  }

  std::cout << "Parser::parse() finished" << '\n';
  std::cout << "Parser::parse() return " << Ret << '\n';
  for (const auto &[Id, Node] : NodeMap) {
    std::cout << "Parser::parse() node id " << Id << " kind "
              << static_cast<int>(Node.Kind) << " is terminal "
              << Node.IsTerminal << '\n';
    if (Node.IsTerminal) {
      std::cout << "Parser::parse() node value " << Node.Value << '\n';
    } else {
      std::cout << "Parser::parse() node children ";
      for (const auto &Child : Node.Children) {
        std::cout << Child << ' ';
      }
      std::cout << '\n';
    }
  }

  return !ErrorOccurred;
}

auto kero::grammar::Parser::findOrCreateNodeId(SourceSpan &&Span) noexcept
    -> KGNodeId {
  const auto Found = NodeIdMap.find(Span);
  if (Found != NodeIdMap.end()) {
    return Found->second;
  }

  const KGNodeId Id{NextNodeId++};
  NodeIdMap[Span] = Id;
  return Id;
}
