/**
 * This file is included by generated parser implementation file
 * "parser_generated.c".
 */

#define PCC_GETCHAR(auxil) KGParserAuxil_pccGetChar(auxil)
#define PCC_ERROR(auxil) KGParserAuxil_pccError(auxil)
#define PCC_DEBUG(auxil, event, rule, level, pos, buffer, length)              \
  KGParserAuxil_pccDebug(auxil, event, rule, level, pos, buffer, length)
