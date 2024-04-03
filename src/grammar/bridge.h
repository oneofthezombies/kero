#ifndef KERO_GRAMMAR_BRIDGE_H
#define KERO_GRAMMAR_BRIDGE_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

int KeroGrammarParser_OnGetChar(void* auxil);
#define PCC_GETCHAR(auxil) KeroGrammarParser_OnGetChar(auxil)

void KeroGrammarParser_OnError(void* auxil);
#define PCC_ERROR(auxil) KeroGrammarParser_OnError(auxil)

void KeroGrammarParser_OnDebug(void* auxil, int event, const char* rule,
                               size_t level, size_t pos, const char* buffer,
                               size_t length);

// TODO: if KERO_DEBUG is defined, then enable PCC_DEBUG
// #ifdef KERO_DEBUG
#define PCC_DEBUG(auxil, event, rule, level, pos, buffer, length)              \
  KeroGrammarParser_OnDebug(auxil, event, rule, level, pos, buffer, length)
// #endif // KERO_DEBUG

void* KeroGrammarParser_OnCreateNode(void* auxil);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // KERO_GRAMMAR_BRIDGE_H
