#ifndef KERO_GRAMMAR_PARSER_CORE_H
#define KERO_GRAMMAR_PARSER_CORE_H

#include <stddef.h>

enum KeroObjectKind {
  kKeroObjectKind_Parser = 0,
};

enum KeroObjectOwnership {
  kKeroObjectOwnership_Own = 0,
  kKeroObjectOwnership_Borrow,
};

struct KeroObject {
  enum KeroObjectKind kind;
  enum KeroObjectOwnership ownership;
  void* data;
};

struct KeroGrammarParserAuxil {
  int (*pcc_get_char)(struct KeroGrammarParserAuxil* auxil);
  void (*pcc_error)(struct KeroGrammarParserAuxil* auxil);
  void (*pcc_debug)(struct KeroGrammarParserAuxil* auxil, int event,
                    const char* rule, size_t level, size_t pos,
                    const char* buffer, size_t length);
};

#endif // KERO_GRAMMAR_PARSER_CORE_H
