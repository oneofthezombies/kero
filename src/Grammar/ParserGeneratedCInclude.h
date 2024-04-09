/**
 * This file is included by generated parser implementation file
 * "parser_generated.c".
 */

#define PCC_ERROR(Auxil) KGParserAuxil_pccError(Auxil)
#define PCC_GETCHAR(Auxil) KGParserAuxil_pccGetChar(Auxil)
#define PCC_MALLOC(Auxil, Size) KGParserAuxil_pccMalloc(Auxil, Size)
#define PCC_REALLOC(Auxil, Ptr, Size) KGParserAuxil_pccRealloc(Auxil, Ptr, Size)
#define PCC_FREE(Auxil, Ptr) KGParserAuxil_pccFree(Auxil, Ptr)
#define PCC_DEBUG(Auxil, Event, Rule, Level, Pos, Buffer, Length)              \
  KGParserAuxil_pccDebug(Auxil, Event, Rule, Level, Pos, Buffer, Length)

// TODO: Change this to DEBUG when debugging
#undef PCC_DEBUG

#define KGNODE_NONTERMINAL0(Kind)                                              \
  KGParserAuxil_createNonTerminal0(auxil, _0s, _0e, Kind)
#define KGNODE_NONTERMINAL1(Kind, Child0)                                      \
  KGParserAuxil_createNonTerminal1(auxil, _0s, _0e, Kind, Child0)
#define KGNODE_NONTERMINAL2(Kind, Child0, Child1)                              \
  KGParserAuxil_createNonTerminal2(auxil, _0s, _0e, Kind, Child0, Child1)
#define KGNODE_NONTERMINAL3(Kind, Child0, Child1, Child2)                      \
  KGParserAuxil_createNonTerminal3(auxil, _0s, _0e, Kind, Child0, Child1,      \
                                   Child2)
#define KGNODE_NONTERMINAL4(Kind, Child0, Child1, Child2, Child3)              \
  KGParserAuxil_createNonTerminal4(auxil, _0s, _0e, Kind, Child0, Child1,      \
                                   Child2, Child3)
#define KGNODE_NONTERMINAL5(Kind, Child0, Child1, Child2, Child3, Child4)      \
  KGParserAuxil_createNonTerminal5(auxil, _0s, _0e, Kind, Child0, Child1,      \
                                   Child2, Child3, Child4)
#define KGNODE_NONTERMINAL6(Kind, Child0, Child1, Child2, Child3, Child4,      \
                            Child5)                                            \
  KGParserAuxil_createNonTerminal6(auxil, _0s, _0e, Kind, Child0, Child1,      \
                                   Child2, Child3, Child4, Child5)

#define KGNODE_TERMINAL0(Kind)                                                 \
  KGParserAuxil_createTerminal0(auxil, _0s, _0e, Kind)
#define KGNODE_TERMINAL1(Kind, Value)                                          \
  KGParserAuxil_createTerminal1(auxil, _0s, _0e, Kind, Value)
