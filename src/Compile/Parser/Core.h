#ifndef KERO_COMPILE_PARSER_CORE_H
#define KERO_COMPILE_PARSER_CORE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "NodeKindGenerated.h"

#include <stddef.h>

typedef struct KCParserAuxilTag KCParserAuxil;

void KCParserAuxilPccError(const KCParserAuxil *const Auxil);
int KCParserAuxilPccGetChar(const KCParserAuxil *const Auxil);
void *KCParserAuxilPccMalloc(const KCParserAuxil *const Auxil,
                             const size_t Size);
void *KCParserAuxilPccRealloc(const KCParserAuxil *const Auxil, void *Ptr,
                              const size_t Size);
void KCParserAuxilPccFree(const KCParserAuxil *const Auxil, void *Ptr);
void KCParserAuxilPccDebug(const KCParserAuxil *const Auxil, const int Event,
                           const char *const Rule, const size_t Level,
                           const size_t Pos, const char *const Buffer,
                           const size_t Length);

typedef size_t KCNodeId;

KCNodeId KCParserAuxilCeateNonTerminal0(const KCParserAuxil *const Auxil,
                                        const size_t Start, const size_t End,
                                        const KCNodeKind Kind);
KCNodeId KCParserAuxilCreateNonTerminal1(const KCParserAuxil *const Auxil,
                                         const size_t Start, const size_t End,
                                         const KCNodeKind Kind,
                                         const KCNodeId Child0);
KCNodeId KCParserAuxilCreateNonTerminal2(const KCParserAuxil *const Auxil,
                                         const size_t Start, const size_t End,
                                         const KCNodeKind Kind,
                                         const KCNodeId Child0,
                                         const KCNodeId Child1);
KCNodeId KCParserAuxilCreateNonTerminal3(const KCParserAuxil *const Auxil,
                                         const size_t Start, const size_t End,
                                         const KCNodeKind Kind,
                                         const KCNodeId Child0,
                                         const KCNodeId Child1,
                                         const KCNodeId Child2);
KCNodeId KCParserAuxilCreateNonTerminal4(
    const KCParserAuxil *const Auxil, const size_t Start, const size_t End,
    const KCNodeKind Kind, const KCNodeId Child0, const KCNodeId Child1,
    const KCNodeId Child2, const KCNodeId Child3);
KCNodeId KCParserAuxilCreateNonTerminal5(
    const KCParserAuxil *const Auxil, const size_t Start, const size_t End,
    const KCNodeKind Kind, const KCNodeId Child0, const KCNodeId Child1,
    const KCNodeId Child2, const KCNodeId Child3, const KCNodeId Child4);
KCNodeId KCParserAuxilCreateNonTerminal6(
    const KCParserAuxil *const Auxil, const size_t Start, const size_t End,
    const KCNodeKind Kind, const KCNodeId Child0, const KCNodeId Child1,
    const KCNodeId Child2, const KCNodeId Child3, const KCNodeId Child4,
    const KCNodeId Child5);

KCNodeId KCParserAuxilCreateTerminal0(const KCParserAuxil *const Auxil,
                                      const size_t Start, const size_t End,
                                      const KCNodeKind Kind);
KCNodeId KCParserAuxilCreateTerminal1(const KCParserAuxil *const Auxil,
                                      const size_t Start, const size_t End,
                                      const KCNodeKind Kind,
                                      const char *const Value);

#ifdef __cplusplus
}
#endif

#endif // KERO_COMPILE_PARSER_CORE_H
