#include "./bridge.h"

#include <cassert>

#include "parser.h"

auto AsParser(void* auxil) -> kero::grammar::Parser* {
  assert(auxil != nullptr);
  return static_cast<kero::grammar::Parser*>(auxil);
}

int KeroGrammarParser_GetChar(void* auxil) {
  return AsParser(auxil)->GetChar();
}

void KeroGrammarParser_Error(void* auxil) { AsParser(auxil)->Error(); }
