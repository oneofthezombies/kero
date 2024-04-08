#include "parser_auxil.h"
#include "parser.h"

#include <cassert>

using namespace kero::grammar;

struct KGParserAuxil {
  Parser *parser;
};

void checkParserAuxil(KGParserAuxil *auxil) {
  assert(auxil != nullptr && "auxil must not be nullptr.");
  assert(auxil->parser != nullptr && "parser must not be nullptr.");
}

int KGParserAuxil_pccGetChar(KGParserAuxil *auxil) {
  checkParserAuxil(auxil);
  return auxil->parser->pccGetChar();
}

void KGParserAuxil_pccError(KGParserAuxil *auxil) {
  checkParserAuxil(auxil);
  auxil->parser->pccError();
}

void KGParserAuxil_pccDebug(KGParserAuxil *auxil, int event, const char *rule,
                            size_t level, size_t pos, const char *buffer,
                            size_t length) {
  checkParserAuxil(auxil);
  auxil->parser->pccDebug(event, rule, level, pos, buffer, length);
}
