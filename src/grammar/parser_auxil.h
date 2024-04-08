#ifndef KERO_GRAMMAR_PARSER_AUXIL_H
#define KERO_GRAMMAR_PARSER_AUXIL_H

#include <stddef.h>

#ifdef __cplusplus
namespace kero {
namespace grammar {

extern "C" {
#endif

typedef struct ParserAuxil ParserAuxil;

int ParserAuxil_pccGetChar(ParserAuxil *auxil);
void ParserAuxil_pccError(ParserAuxil *auxil);
void ParserAuxil_pccDebug(ParserAuxil *auxil, int event, const char *rule,
                          size_t level, size_t pos, const char *buffer,
                          size_t length);

#ifdef __cplusplus
}

} // namespace grammar
} // namespace kero
#endif

#endif // KERO_GRAMMAR_PARSER_AUXIL_H
