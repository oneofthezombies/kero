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

#define CREATE_NONTERMINAL0(Kind)                                              \
  auxil->CreateNonTerminal0(auxil, _0s, _0e, Kind)
#define CREATE_NONTERMINAL1(Kind, Child0)                                      \
  auxil->CreateNonTerminal1(auxil, _0s, _0e, Kind, Child0)
#define CREATE_NONTERMINAL2(Kind, Child0, Child1)                              \
  auxil->CreateNonTerminal2(auxil, _0s, _0e, Kind, Child0, Child1)
#define CREATE_NONTERMINAL3(Kind, Child0, Child1, Child2)                      \
  auxil->CreateNonTerminal3(auxil, _0s, _0e, Kind, Child0, Child1, Child2)

#define CREATE_TERMINAL0(Kind) auxil->CreateTerminal0(auxil, _0s, _0e, Kind)
#define CREATE_TERMINAL1(Kind, Value)                                          \
  auxil->CreateTerminal1(auxil, _0s, _0e, Kind, Value)
