/**
 * This file is included by generated parser implementation file "generated.c".
 */

#include "core.h"

#include <assert.h>
#include <stdlib.h>

#define PCC_GETCHAR(auxil) auxil->PccGetChar(auxil)
#define PCC_ERROR(auxil) auxil->PccError(auxil)
#define PCC_DEBUG(auxil, event, rule, level, pos, buffer, length)              \
  auxil->PccDebug(auxil, event, rule, level, pos, buffer, length)

inline KeroObject *KeroObject_create(KeroObjectKind Kind, void *Data) {
  assert(Data != NULL && "Data must not be NULL.");

  KeroObject *Owner = (KeroObject *)malloc(sizeof(KeroObject));
  if (Owner == NULL) {
    return NULL;
  }

  Owner->Kind = Kind;
  Owner->Data = Data;
  Owner->Ownership = KeroObjectOwnership_Owned;
  return Owner;
}

inline void KeroObject_destroy(KeroObject *KO) {
  if (KO == NULL) {
    return;
  }

  if (KO->Ownership == KeroObjectOwnership_Borrowed) {
    free(KO);
    return;
  }

  assert(KO->Data != NULL && "Data must not be NULL.");
  free(KO);
}

inline KeroObject *KeroObject_createBorrower(KeroObject *Owner) {
  assert(Owner != NULL && "Object must not be NULL.");

  KeroObject *Borowser = (KeroObject *)malloc(sizeof(KeroObject));
  if (Borowser == NULL) {
    return NULL;
  }

  Borowser->Kind = Owner->Kind;
  Borowser->Data = Owner->Data;
  Borowser->Ownership = KeroObjectOwnership_Borrowed;
  return Borowser;
}
