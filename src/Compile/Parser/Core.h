#ifndef KERO_COMPILE_PARSER_CORE_H
#define KERO_COMPILE_PARSER_CORE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "NodeKindGenerated.h"

#include <stddef.h>

typedef size_t KCNodeId;

typedef struct KCParserAuxilTag {
  void *UserData;

  void (*Error)(const struct KCParserAuxilTag *const Auxil);
  int (*GetChar)(const struct KCParserAuxilTag *const Auxil);
  void *(*Malloc)(const struct KCParserAuxilTag *const Auxil,
                  const size_t Size);
  void *(*Realloc)(const struct KCParserAuxilTag *const Auxil, void *Ptr,
                   const size_t Size);
  void (*Free)(const struct KCParserAuxilTag *const Auxil, void *Ptr);
  void (*Debug)(const struct KCParserAuxilTag *const Auxil, const int Event,
                const char *const Rule, const size_t Level, const size_t Pos,
                const char *const Buffer, const size_t Length);

  KCNodeId (*CreateNonTerminal0)(const struct KCParserAuxilTag *const Auxil,
                                 const size_t Start, const size_t End,
                                 const KCNodeKind Kind);
  KCNodeId (*CreateNonTerminal1)(const struct KCParserAuxilTag *const Auxil,
                                 const size_t Start, const size_t End,
                                 const KCNodeKind Kind, const KCNodeId Child0);
  KCNodeId (*CreateNonTerminal2)(const struct KCParserAuxilTag *const Auxil,
                                 const size_t Start, const size_t End,
                                 const KCNodeKind Kind, const KCNodeId Child0,
                                 const KCNodeId Child1);
  KCNodeId (*CreateNonTerminal3)(const struct KCParserAuxilTag *const Auxil,
                                 const size_t Start, const size_t End,
                                 const KCNodeKind Kind, const KCNodeId Child0,
                                 const KCNodeId Child1, const KCNodeId Child2);

  KCNodeId (*CreateTerminal0)(const struct KCParserAuxilTag *const Auxil,
                              const size_t Start, const size_t End,
                              const KCNodeKind Kind);
  KCNodeId (*CreateTerminal1)(const struct KCParserAuxilTag *const Auxil,
                              const size_t Start, const size_t End,
                              const KCNodeKind Kind, const char *const Value);
} KCParserAuxil;

typedef enum KCParserEventTag {
  KCParserEvent_Evaluate = 0,
  KCParserEvent_Match,
  KCParserEvent_NoMatch,
} KCParserEvent;

const char *KCParserEventToString(const KCParserEvent Event);

#ifdef __cplusplus
}
#endif

#endif // KERO_COMPILE_PARSER_CORE_H
