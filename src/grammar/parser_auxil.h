#ifndef KERO_GRAMMAR_PARSER_AUXIL_H
#define KERO_GRAMMAR_PARSER_AUXIL_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct KGObject KGObject;

typedef struct KGParserAuxil KGParserAuxil;

int KGParserAuxil_pccGetChar(KGParserAuxil *auxil);
void KGParserAuxil_pccError(KGParserAuxil *auxil);
void KGParserAuxil_pccDebug(KGParserAuxil *auxil, int event, const char *rule,
                            size_t level, size_t pos, const char *buffer,
                            size_t length);

#ifdef __cplusplus
}
#endif

#endif // KERO_GRAMMAR_PARSER_AUXIL_H
