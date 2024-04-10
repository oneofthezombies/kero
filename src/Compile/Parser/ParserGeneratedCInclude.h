/**
 * This file is included by generated parser implementation file
 * "parser_generated.c".
 */

#define PCC_ERROR(Auxil) Auxil->Error(Auxil)
#define PCC_GETCHAR(Auxil) Auxil->GetChar(Auxil)
#define PCC_MALLOC(Auxil, Size) Auxil->Malloc(Auxil, Size)
#define PCC_REALLOC(Auxil, Ptr, Size) Auxil->Realloc(Auxil, Ptr, Size)
#define PCC_FREE(Auxil, Ptr) Auxil->Free(Auxil, Ptr)
#define PCC_DEBUG(Auxil, Event, Rule, Level, Pos, Buffer, Length)              \
  Auxil->Debug(Auxil, Event, Rule, Level, Pos, Buffer, Length)

// TODO: Change this to DEBUG when debugging
// #undef PCC_DEBUG

#define KGNODE_NONTERMINAL0(Kind)                                              \
  Auxil->CreateNonTerminal0(auxil, _0s, _0e, Kind)
#define KGNODE_NONTERMINAL1(Kind, Child0)                                      \
  Auxil->CreateNonTerminal1(auxil, _0s, _0e, Kind, Child0)
#define KGNODE_NONTERMINAL2(Kind, Child0, Child1)                              \
  Auxil->CreateNonTerminal2(auxil, _0s, _0e, Kind, Child0, Child1)
#define KGNODE_NONTERMINAL3(Kind, Child0, Child1, Child2)                      \
  Auxil->CreateNonTerminal3(auxil, _0s, _0e, Kind, Child0, Child1, Child2)

#define KGNODE_TERMINAL0(Kind) Auxil->CreateTerminal0(auxil, _0s, _0e, Kind)
#define KGNODE_TERMINAL1(Kind, Value)                                          \
  Auxil->CreateTerminal1(auxil, _0s, _0e, Kind, Value)
