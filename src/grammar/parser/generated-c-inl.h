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

inline KeroObject *KeroObject_create(KeroObjectKind Kind, void *Data,
                                     KeroObject_Destructor Destructor) {
  assert(Data != NULL && "Data must not be NULL.");
  assert(Destructor != NULL && "Destructor must not be NULL.");

  KeroObject *Owner = (KeroObject *)malloc(sizeof(KeroObject));
  if (Owner == NULL) {
    return NULL;
  }

  Owner->Kind = Kind;
  Owner->Ownership = KeroObjectOwnership_Owned;
  Owner->Data = Data;
  Owner->Destructor = Destructor;
  return Owner;
}

inline void KeroObject_destroy(KeroObject *Object) {
  if (Object == NULL) {
    return;
  }

  if (Object->Destructor != NULL) {
    assert(Object->Ownership == KeroObjectOwnership_Owned &&
           "Object must be owned.");
    assert(Object->Data != NULL && "Data must not be NULL.");
    Object->Destructor(Object->Data);
  } else {
    assert(Object->Ownership == KeroObjectOwnership_Borrowed &&
           "Object must be borrowed.");
  }

  free(Object);
}

inline KeroObject *KeroObject_createBorrower(KeroObject *Object) {
  assert(Object != NULL && "Object must not be NULL.");

  KeroObject *Borowser = (KeroObject *)malloc(sizeof(KeroObject));
  if (Borowser == NULL) {
    return NULL;
  }

  Borowser->Kind = Object->Kind;
  Borowser->Ownership = KeroObjectOwnership_Borrowed;
  Borowser->Data = Object->Data;
  Borowser->Destructor = NULL;
  return Borowser;
}
