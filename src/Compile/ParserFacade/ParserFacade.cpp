#include "ParserFacade.h"

#include "Compile/Parser/Core.h"
#include "Compile/Parser/ParserGenerated.h"

#include <cassert>
#include <iostream>

using namespace kero::compile;

kero::compile::Span::Span(const size_t Start, const size_t End) noexcept
    : Start{Start}, End{End} {}

auto kero::compile::Span::operator==(const Span &Other) const noexcept -> bool {
  return Start == Other.Start && End == Other.End;
}

auto kero::compile::operator<<(std::ostream &Out, const Span &S)
    -> std::ostream & {
  Out << "Span{Start: " << S.Start << ", End: " << S.End << "}";
  return Out;
}

kero::compile::Node::Node(Span &&Location, const NodeKind Kind,
                          const std::string_view Value) noexcept
    : Value{Value}, Location{Location}, Kind{Kind}, IsTerminal{true} {}

kero::compile::Node::Node(Span &&Location, const NodeKind Kind,
                          std::vector<NodeId> &&Children) noexcept
    : Children{std::move(Children)}, Location{Location}, Kind{Kind},
      IsTerminal{false} {}

auto kero::compile::operator<<(std::ostream &Out, const Node &N)
    -> std::ostream & {
  Out << "Node{";
  Out << "Kind: " << N.Kind;
  Out << ", ";
  if (N.IsTerminal) {
    if (!N.Value) {
      Out << "Value: empty";
    } else {
      Out << "Value: '" << *N.Value << "'";
    }
  } else {
    Out << "Children: [";
    for (size_t i = 0; i < N.Children.size(); ++i) {
      Out << N.Children[i];
      if (i + 1 < N.Children.size()) {
        Out << ", ";
      }
    }
    Out << "]";
  }
  Out << "}";
  return Out;
}

auto kero::compile::ParserAuxilDeleter::operator()(
    ParserAuxil *Auxil) const noexcept -> void {
  if (Auxil == nullptr) {
    return;
  }
  delete Auxil;
}

auto kero::compile::ParserContextDeleter::operator()(
    ParserContext *Context) const noexcept -> void {
  if (Context == nullptr) {
    return;
  }
  KCParser_destroy(Context);
}

kero::compile::ParserImpl::ParserImpl(std::string &&Source) noexcept
    : Source{std::move(Source)} {
  initAuxil();
  Context.reset(KCParser_create(Auxil.get()));
}

auto kero::compile::ParserImpl::parse() noexcept -> bool {
  std::cout << "ParserImpl{";
  std::cout << "Source: '" << Source << "'";
  std::cout << "}\n";

  NodeId Ret{0};
  while (true) {
    if (KCParser_parse(Context.get(), &Ret) == 0) {
      break;
    }

    if (ErrorOccurred) {
      break;
    }
  }

  if (ErrorOccurred) {
    std::cout << "Error occurred" << '\n';
  }

  dumpRec(std::cout, Ret, 0);
  return !ErrorOccurred;
}

auto kero::compile::ParserImpl::initAuxil() noexcept -> void {
  assert(!Auxil && "Auxil already set up");
  Auxil.reset(new ParserAuxil{this});
  Auxil->Error = [](const ParserAuxil *const Auxil) {
    ParserImpl::fromAuxil(Auxil).error();
  };
  Auxil->GetChar = [](const ParserAuxil *const Auxil) {
    return ParserImpl::fromAuxil(Auxil).getChar();
  };
  Auxil->Malloc = [](const ParserAuxil *const Auxil, const size_t Size) {
    return ParserImpl::fromAuxil(Auxil).malloc(Size);
  };
  Auxil->Realloc = [](const ParserAuxil *const Auxil, void *const Ptr,
                      const size_t Size) {
    return ParserImpl::fromAuxil(Auxil).realloc(Ptr, Size);
  };
  Auxil->Free = [](const ParserAuxil *const Auxil, void *const Ptr) {
    ParserImpl::fromAuxil(Auxil).free(Ptr);
  };
  Auxil->Debug = [](const ParserAuxil *const Auxil, const int Event,
                    const char *const Rule, const size_t Level,
                    const size_t Pos, const char *const Buffer,
                    const size_t Length) {
    ParserImpl::fromAuxil(Auxil).debug(Event, Rule, Level, Pos, Buffer, Length);
  };
  Auxil->CreateNonTerminal0 = [](const ParserAuxil *const Auxil,
                                 const size_t Start, const size_t End,
                                 const NodeKind Kind) {
    return ParserImpl::fromAuxil(Auxil).createNonTerminalNode(Start, End, Kind,
                                                              {});
  };
  Auxil->CreateNonTerminal1 = [](const ParserAuxil *const Auxil,
                                 const size_t Start, const size_t End,
                                 const NodeKind Kind, const NodeId Child0) {
    return ParserImpl::fromAuxil(Auxil).createNonTerminalNode(Start, End, Kind,
                                                              {Child0});
  };
  Auxil->CreateNonTerminal2 = [](const ParserAuxil *const Auxil,
                                 const size_t Start, const size_t End,
                                 const NodeKind Kind, const NodeId Child0,
                                 const NodeId Child1) {
    return ParserImpl::fromAuxil(Auxil).createNonTerminalNode(Start, End, Kind,
                                                              {Child0, Child1});
  };
  Auxil->CreateNonTerminal3 = [](const ParserAuxil *const Auxil,
                                 const size_t Start, const size_t End,
                                 const NodeKind Kind, const NodeId Child0,
                                 const NodeId Child1, const NodeId Child2) {
    return ParserImpl::fromAuxil(Auxil).createNonTerminalNode(
        Start, End, Kind, {Child0, Child1, Child2});
  };
  Auxil->CreateTerminal0 = [](const ParserAuxil *const Auxil,
                              const size_t Start, const size_t End,
                              const NodeKind Kind) {
    return ParserImpl::fromAuxil(Auxil).createTerminalNode(Start, End, Kind,
                                                           {});
  };
  Auxil->CreateTerminal1 = [](const ParserAuxil *const Auxil,
                              const size_t Start, const size_t End,
                              const NodeKind Kind, const char *const Value) {
    return ParserImpl::fromAuxil(Auxil).createTerminalNode(Start, End, Kind,
                                                           Value);
  };
}

auto kero::compile::ParserImpl::error() noexcept -> void {
  ErrorOccurred = true;
}

auto kero::compile::ParserImpl::getChar() noexcept -> int {
  if (SourcePos >= Source.size()) {
    return -1;
  }
  return Source[SourcePos++];
}

auto kero::compile::ParserImpl::malloc(const size_t Size) noexcept -> void * {
  void *P = std::malloc(Size);
  if (P == nullptr) {
    std::cerr << "ParserImpl::malloc() failed to allocate memory" << '\n'
              << std::flush;
    std::exit(EXIT_FAILURE);
  }
  return P;
}

auto kero::compile::ParserImpl::realloc(void *Ptr, const size_t Size) noexcept
    -> void * {
  void *P = std::realloc(Ptr, Size);
  if (P == nullptr) {
    std::cerr << "ParserImpl::realloc() failed to reallocate memory" << '\n'
              << std::flush;
    std::exit(EXIT_FAILURE);
  }
  return P;
}

auto kero::compile::ParserImpl::free(void *Ptr) noexcept -> void {
  if (Ptr == nullptr) {
    return;
  }
  std::free(Ptr);
}

auto kero::compile::ParserImpl::debug(const int Event, const char *const Rule,
                                      const size_t Level, const size_t Pos,
                                      const char *const Buffer,
                                      const size_t Length) noexcept -> void {
  assert(Rule != nullptr && "Rule must not be null");
  std::cout << "Debug{";
  std::cout << "Event: "
            << KCParserEventToString(static_cast<ParserEvent>(Event));
  std::cout << ", ";
  std::cout << "Rule: " << Rule;
  std::cout << ", ";
  std::cout << "Level: " << Level;
  std::cout << ", ";
  std::cout << "Pos: " << Pos;
  std::cout << ", ";
  std::cout << "Buffer: '" << std::string_view{Buffer, Length} << "'";
  std::cout << "}\n";
}

auto kero::compile::ParserImpl::createNonTerminalNode(
    const size_t Start, const size_t End, const NodeKind Kind,
    std::vector<NodeId> &&Children) noexcept -> NodeId {
  // Remove null children
  Children.erase(
      std::remove_if(Children.begin(), Children.end(),
                     [](const NodeId &Child) { return Child == NullNodeId; }),
      Children.end());

  const NodeId Id{createNodeId()};
  NodeMap.emplace(Id, Node{Span{Start, End}, Kind, std::move(Children)});
  return Id;
}

auto kero::compile::ParserImpl::createTerminalNode(
    const size_t Start, const size_t End, const NodeKind Kind,
    const std::string_view Value) noexcept -> NodeId {
  const NodeId Id{createNodeId()};
  NodeMap.emplace(Id, Node{Span{Start, End}, Kind, Value});
  return Id;
}

auto kero::compile::ParserImpl::createNodeId() noexcept -> NodeId {
  const NodeId Id{NextNodeId++};
  return Id;
}

auto kero::compile::ParserImpl::dumpRec(std::ostream &OS, const NodeId Id,
                                        const size_t level) const noexcept
    -> void {
  const auto Found = NodeMap.find(Id);
  if (Found == NodeMap.end()) {
    OS << "Node Id: " << Id << " not found" << '\n';
    return;
  }

  const Node &N = Found->second;
  for (size_t i = 0; i < level; ++i) {
    OS << "  ";
  }
  OS << N << '\n';
  for (const NodeId ChildId : N.Children) {
    dumpRec(OS, ChildId, level + 1);
  }
}

auto kero::compile::ParserImpl::fromAuxil(
    const ParserAuxil *const Auxil) noexcept -> ParserImpl & {
  assert(Auxil != nullptr && "Auxil must not be null");
  assert(Auxil->UserData != nullptr && "UserData must not be null");
  return *static_cast<ParserImpl *>(Auxil->UserData);
}

kero::compile::ParserFacade::ParserFacade(std::string &&Source) noexcept
    : Impl{std::make_unique<ParserImpl>(std::move(Source))} {}

auto kero::compile::ParserFacade::parse() noexcept -> bool {
  return Impl->parse();
}

template <> struct std::hash<kero::compile::Span> {
  auto operator()(const kero::compile::Span &Span) const noexcept -> size_t {
    return std::hash<size_t>{}(Span.Start) ^ std::hash<size_t>{}(Span.End);
  }
};
