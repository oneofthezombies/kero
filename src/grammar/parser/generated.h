/* A packrat parser generated by PackCC 1.8.0 */

#ifndef PCC_INCLUDED_GENERATED_H
#define PCC_INCLUDED_GENERATED_H

#include "core.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct KeroGrammarParser_context_tag KeroGrammarParser_context_t;

KeroGrammarParser_context_t *KeroGrammarParser_create(struct KeroGrammarParserAuxil *auxil);
int KeroGrammarParser_parse(KeroGrammarParser_context_t *ctx, struct KeroObject **ret);
void KeroGrammarParser_destroy(KeroGrammarParser_context_t *ctx);

#ifdef __cplusplus
}
#endif

#endif /* !PCC_INCLUDED_GENERATED_H */