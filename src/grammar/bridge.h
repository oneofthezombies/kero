#ifndef KERO_GRAMMAR_PARSER_CORE_BRIDGE_H
#define KERO_GRAMMAR_PARSER_CORE_BRIDGE_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

int KeroGrammarParser_GetChar(void* auxil);
void KeroGrammarParser_Error(void* auxil);

#define PCC_GETCHAR(auxil) KeroGrammarParser_GetChar(auxil)
#define PCC_ERROR(auxil) KeroGrammarParser_Error(auxil)

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // KERO_GRAMMAR_PARSER_CORE_BRIDGE_H
