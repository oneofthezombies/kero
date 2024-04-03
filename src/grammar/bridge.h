#ifndef KERO_GRAMMAR_PARSER_CORE_BRIDGE_H
#define KERO_GRAMMAR_PARSER_CORE_BRIDGE_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

int KeroGrammarParser_OnGetChar(void* auxil);
void KeroGrammarParser_OnError(void* auxil);

#define PCC_GETCHAR(auxil) KeroGrammarParser_OnGetChar(auxil)
#define PCC_ERROR(auxil) KeroGrammarParser_OnError(auxil)

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // KERO_GRAMMAR_PARSER_CORE_BRIDGE_H
