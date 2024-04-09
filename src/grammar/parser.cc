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

struct Span {
  size_t Begin{0}; // inclusive
  size_t End{0};   // exclusive
};

KGNode *KGNode_create(const KGParserAuxilTag *const Auxil,
                      const KGNodeKind Kind, const size_t Start,
                      const size_t End) {
  checkParserAuxil(Auxil);
  return Auxil->Parser->createNode(Kind, Start, End);
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

kero::grammar::Parser::Parser(const std::string_view Source) noexcept
    : Source{Source}, Auxil{new KGParserAuxil{this}},
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

auto kero::grammar::Parser::createNode(const KGNodeKind Kind,
                                       const size_t Start,
                                       const size_t End) noexcept -> KGNode * {
  std::cout << "Parser::createNode() called" << '\n';
  std::cout << "Kind: " << Kind << " Start: " << Start << " End: " << End
            << '\n';
  std::string_view Span{Source.data() + Start, End - Start};
  std::cout << "Span: " << Span << '\n';
  return nullptr;
}

auto kero::grammar::Parser::parse() noexcept -> bool {
  std::cout << "Parser::parse() called" << '\n';
  while (true) {
    KGNode *Ret{nullptr};
    if (KGParser_parse(Context.get(), &Ret) == 0) {
      break;
    }

    if (ErrorOccurred) {
      std::cout << "Parser::parse() has error" << '\n';
      break;
    }
  }

  return !ErrorOccurred;
}
