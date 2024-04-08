#include "parser_auxil.h"
#include "parser.h"

#include <cassert>

using namespace kero::grammar;

struct kero::grammar::ParserAuxil {
  Parser *parser;
};

int kero::grammar::ParserAuxil_pccGetChar(ParserAuxil *auxil) {
  assert(auxil != nullptr && "auxil must not be nullptr.");
  assert(auxil->parser != nullptr && "parser must not be nullptr.");
  return auxil->parser->pccGetChar();
}

void kero::grammar::ParserAuxil_pccError(ParserAuxil *auxil) {
  assert(auxil != nullptr && "auxil must not be nullptr.");
  assert(auxil->parser != nullptr && "parser must not be nullptr.");
  auxil->parser->pccError();
}

void kero::grammar::ParserAuxil_pccDebug(ParserAuxil *auxil, int event,
                                         const char *rule, size_t level,
                                         size_t pos, const char *buffer,
                                         size_t length) {
  assert(auxil != nullptr && "auxil must not be nullptr.");
  assert(auxil->parser != nullptr && "parser must not be nullptr.");
  auxil->parser->pccDebug(event, rule, level, pos, buffer, length);
}
