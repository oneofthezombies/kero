/* A packrat parser generated by PackCC 1.8.0 */

#ifndef PCC_INCLUDED_PARSERGENERATED_H
#define PCC_INCLUDED_PARSERGENERATED_H

#include "ParserAuxil.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct KGParser_context_tag KGParser_context_t;

KGParser_context_t *KGParser_create(KGParserAuxil *auxil);
int KGParser_parse(KGParser_context_t *ctx, KGNodeId *ret);
void KGParser_destroy(KGParser_context_t *ctx);

#ifdef __cplusplus
}
#endif

#endif /* !PCC_INCLUDED_PARSERGENERATED_H */