#ifndef KERO_GRAMMAR_PARSER_AUXIL_H
#define KERO_GRAMMAR_PARSER_AUXIL_H

#include "NodeKindGenerated.h"

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

typedef size_t KGNodeId;

KGNodeId KGParserAuxil_createNonTerminal0(const KGParserAuxil *const Auxil,
                                          const size_t Start, const size_t End,
                                          const KGNodeKind Kind);
KGNodeId KGParserAuxil_createNonTerminal1(const KGParserAuxil *const Auxil,
                                          const size_t Start, const size_t End,
                                          const KGNodeKind Kind,
                                          const KGNodeId Child0);
KGNodeId KGParserAuxil_createNonTerminal2(const KGParserAuxil *const Auxil,
                                          const size_t Start, const size_t End,
                                          const KGNodeKind Kind,
                                          const KGNodeId Child0,
                                          const KGNodeId Child1);
KGNodeId KGParserAuxil_createNonTerminal3(const KGParserAuxil *const Auxil,
                                          const size_t Start, const size_t End,
                                          const KGNodeKind Kind,
                                          const KGNodeId Child0,
                                          const KGNodeId Child1,
                                          const KGNodeId Child2);
KGNodeId KGParserAuxil_createNonTerminal4(
    const KGParserAuxil *const Auxil, const size_t Start, const size_t End,
    const KGNodeKind Kind, const KGNodeId Child0, const KGNodeId Child1,
    const KGNodeId Child2, const KGNodeId Child3);
KGNodeId KGParserAuxil_createNonTerminal5(
    const KGParserAuxil *const Auxil, const size_t Start, const size_t End,
    const KGNodeKind Kind, const KGNodeId Child0, const KGNodeId Child1,
    const KGNodeId Child2, const KGNodeId Child3, const KGNodeId Child4);
KGNodeId KGParserAuxil_createNonTerminal6(
    const KGParserAuxil *const Auxil, const size_t Start, const size_t End,
    const KGNodeKind Kind, const KGNodeId Child0, const KGNodeId Child1,
    const KGNodeId Child2, const KGNodeId Child3, const KGNodeId Child4,
    const KGNodeId Child5);

KGNodeId KGParserAuxil_createTerminal0(const KGParserAuxil *const Auxil,
                                       const size_t Start, const size_t End,
                                       const KGNodeKind Kind);
KGNodeId KGParserAuxil_createTerminal1(const KGParserAuxil *const Auxil,
                                       const size_t Start, const size_t End,
                                       const KGNodeKind Kind,
                                       const char *const Value);

#ifdef __cplusplus
}
#endif

#endif // KERO_GRAMMAR_PARSER_AUXIL_H
