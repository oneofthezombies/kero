#ifndef KERO_GRAMMAR_PARSER_INLINE_H
#define KERO_GRAMMAR_PARSER_INLINE_H

#define PCC_GETCHAR(auxil) auxil->pcc_get_char(auxil)
#define PCC_ERROR(auxil) auxil->pcc_error(auxil)
#define PCC_DEBUG(auxil, event, rule, level, pos, buffer, length)              \
  auxil->pcc_debug(auxil, event, rule, level, pos, buffer, length)

#endif // KERO_GRAMMAR_PARSER_INLINE_H
