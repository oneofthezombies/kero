#include "./bridge.h"

#include <cassert>

#include "parser.h"

auto AsParser(void* auxil) -> kero::grammar::Parser* {
  assert(auxil != nullptr);
  return static_cast<kero::grammar::Parser*>(auxil);
}

int KeroGrammarParser_OnGetChar(void* auxil) {
  return AsParser(auxil)->OnGetChar();
}

void KeroGrammarParser_OnError(void* auxil) { AsParser(auxil)->OnError(); }
