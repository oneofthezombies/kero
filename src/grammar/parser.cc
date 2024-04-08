#include "parser.h"

#include <cassert>
#include <iostream>

using namespace kero::grammar;

struct KGParserAuxilTag {
  Parser *parser{nullptr};
};

void checkParserAuxil(KGParserAuxilTag *auxil) {
  assert(auxil != nullptr && "auxil must not be nullptr.");
  assert(auxil->parser != nullptr && "parser must not be nullptr.");
}

void KGParserAuxil_pccError(KGParserAuxilTag *auxil) {
  checkParserAuxil(auxil);
  auxil->parser->pccError();
}

int KGParserAuxil_pccGetChar(KGParserAuxilTag *auxil) {
  checkParserAuxil(auxil);
  return auxil->parser->pccGetChar();
}

void *KGParserAuxil_pccMalloc(KGParserAuxilTag *auxil, size_t size) {
  checkParserAuxil(auxil);
  return auxil->parser->pccMalloc(size);
}

void *KGParserAuxil_pccRealloc(KGParserAuxilTag *auxil, void *ptr,
                               size_t size) {
  checkParserAuxil(auxil);
  return auxil->parser->pccRealloc(ptr, size);
}

void KGParserAuxil_pccFree(KGParserAuxilTag *auxil, void *ptr) {
  checkParserAuxil(auxil);
  auxil->parser->pccFree(ptr);
}

void KGParserAuxil_pccDebug(KGParserAuxilTag *auxil, int event,
                            const char *rule, size_t level, size_t pos,
                            const char *buffer, size_t length) {
  checkParserAuxil(auxil);
  auxil->parser->pccDebug(event, rule, level, pos, buffer, length);
}

namespace {

enum class DebugEvent : int32_t {
  kRuleEvaluating = 0,
  kRuleMatched = 1,
  kRuleNotMatched = 2,
};

auto operator<<(std::ostream &os, const DebugEvent event) noexcept
    -> std::ostream & {
  switch (event) {
  case DebugEvent::kRuleEvaluating:
    os << "RuleEvaluating";
    break;
  case DebugEvent::kRuleMatched:
    os << "RuleMatched";
    break;
  case DebugEvent::kRuleNotMatched:
    os << "RuleNotMatched";
    break;
  }
  return os;
}

} // namespace

auto kero::grammar::KGParserAuxilDeleter::operator()(
    KGParserAuxil *auxil) const noexcept -> void {
  if (auxil == nullptr) {
    return;
  }
  delete auxil;
}

auto kero::grammar::KGParserDeleter::operator()(
    KGParser_context_t *context) const noexcept -> void {
  KGParser_destroy(context);
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

auto kero::grammar::Parser::pccMalloc(size_t size) noexcept -> void * {
  void *p = std::malloc(size);
  if (p == nullptr) {
    std::cerr << "Parser::pccMalloc() failed to allocate memory" << '\n'
              << std::flush;
    std::exit(EXIT_FAILURE);
  }
  return p;
}

auto kero::grammar::Parser::pccRealloc(void *ptr, size_t size) noexcept
    -> void * {
  void *p = std::realloc(ptr, size);
  if (p == nullptr) {
    std::cerr << "Parser::pccRealloc() failed to reallocate memory" << '\n'
              << std::flush;
    std::exit(EXIT_FAILURE);
  }
  return p;
}

auto kero::grammar::Parser::pccFree(void *ptr) noexcept -> void {
  if (ptr != nullptr) {
    std::free(ptr);
  }
}

auto kero::grammar::Parser::pccDebug(int event, const char *rule, size_t level,
                                     size_t pos, const char *buffer,
                                     size_t length) noexcept -> void {
  const DebugEvent debug_event{static_cast<DebugEvent>(event)};
  const std::string_view rule_view{rule};
  const std::string_view buffer_view{buffer, length};
  std::cout << "Parser::pccDebug() event " << debug_event << " rule "
            << rule_view << " level " << level << " pos " << pos << " buffer "
            << buffer_view << '\n';
}

auto kero::grammar::Parser::parse() noexcept -> bool {
  std::cout << "Parser::parse() called" << std::endl;
  while (true) {
    KGNode *ret{nullptr};
    if (KGParser_parse(Context.get(), &ret) == 0) {
      break;
    }

    if (ErrorOccurred) {
      std::cout << "Parser::parse() has error" << std::endl;
      break;
    }
  }

  return !ErrorOccurred;
}
