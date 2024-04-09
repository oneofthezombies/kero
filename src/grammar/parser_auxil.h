#ifndef KERO_GRAMMAR_PARSER_AUXIL_H
#define KERO_GRAMMAR_PARSER_AUXIL_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct KGParserAuxilTag KGParserAuxil;

void KGParserAuxil_pccError(const KGParserAuxil *const Auxil);
int KGParserAuxil_pccGetChar(const KGParserAuxil *const Auxil);
void *KGParserAuxil_pccMalloc(const KGParserAuxil *const Auxil,
                              const size_t Size);
void *KGParserAuxil_pccRealloc(const KGParserAuxil *const Auxil, void *Ptr,
                               const size_t Size);
void KGParserAuxil_pccFree(const KGParserAuxil *const Auxil, void *Ptr);
void KGParserAuxil_pccDebug(const KGParserAuxil *const Auxil, const int Event,
                            const char *const Rule, const size_t Level,
                            const size_t Pos, const char *const Buffer,
                            const size_t Length);

typedef enum KGNodeKindTag {
  KGNodeKind_Module = 0,
} KGNodeKind;

typedef struct KGNodeTag KGNode;

KGNode *KGNode_create(const KGParserAuxil *const Auxil, const KGNodeKind Kind,
                      const size_t Start, const size_t End);

#ifdef __cplusplus
}
#endif

#endif // KERO_GRAMMAR_PARSER_AUXIL_H
