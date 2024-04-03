#include "./bridge.h"

#include <cassert>

#include "./parser.h"

auto AsParser(void* auxil) -> kero::grammar::Parser* {
  assert(auxil != nullptr);
  return static_cast<kero::grammar::Parser*>(auxil);
}

int KeroGrammarParser_OnGetChar(void* auxil) {
  return AsParser(auxil)->OnGetChar();
}

void KeroGrammarParser_OnError(void* auxil) { AsParser(auxil)->OnError(); }

void KeroGrammarParser_OnDebug(void* auxil, int event, const char* rule,
                               size_t level, size_t pos, const char* buffer,
                               size_t length) {
  AsParser(auxil)->OnDebug(event, rule, level, pos, buffer, length);
}

void* KeroGrammarParser_OnCreateNode(void* auxil) {
  return AsParser(auxil)->OnCreateNode();
}
