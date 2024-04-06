#ifndef KERO_GRAMMAR_PARSER_CORE_H
#define KERO_GRAMMAR_PARSER_CORE_H

#include <stddef.h>

typedef int (*KeroParserAuxil_PccGetChar)(struct KeroParserAuxilTag *Auxil);
typedef void (*KeroParserAuxil_PccError)(struct KeroParserAuxilTag *Auxil);
typedef void (*KeroParserAuxil_PccDebug)(struct KeroParserAuxilTag *Auxil,
                                         int Event, const char *Rule,
                                         size_t Level, size_t Pos,
                                         const char *Buffer, size_t Length);

typedef struct KeroParserAuxilTag {
  KeroParserAuxil_PccGetChar PccGetChar;
  KeroParserAuxil_PccError PccError;
  KeroParserAuxil_PccDebug PccDebug;
} KeroParserAuxil;

typedef enum KeroObjectKindTag {
  KeroObjectKind_Borrower = 0,
} KeroObjectKind;

typedef enum KeroObjectOwnershipTag {
  KeroObjectOwnership_Owned = 0,
  KeroObjectOwnership_Borrowed,
} KeroObjectOwnership;

typedef void (*KeroObject_Destructor)(void *Data);

typedef struct KeroObjectTag {
  KeroObjectKind Kind;
  KeroObjectOwnership Ownership;
  void *Data;
  KeroObject_Destructor Destructor;
} KeroObject;

KeroObject *KeroObject_create(KeroObjectKind Kind, void *Data,
                              KeroObject_Destructor Destructor);
void KeroObject_destroy(KeroObject *Object);

KeroObject *KeroObject_createBorrower(KeroObject *Object);

#endif // KERO_GRAMMAR_PARSER_CORE_H
