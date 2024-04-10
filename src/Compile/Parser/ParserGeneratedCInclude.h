/**
 * This file is included by generated parser implementation file
 * "parser_generated.c".
 */

#define PCC_ERROR(Auxil) KCParserAuxilPccError(Auxil)
#define PCC_GETCHAR(Auxil) KCParserAuxilPccGetChar(Auxil)
#define PCC_MALLOC(Auxil, Size) KCParserAuxilPccMalloc(Auxil, Size)
#define PCC_REALLOC(Auxil, Ptr, Size) KCParserAuxilPccRealloc(Auxil, Ptr, Size)
#define PCC_FREE(Auxil, Ptr) KCParserAuxilPccFree(Auxil, Ptr)
#define PCC_DEBUG(Auxil, Event, Rule, Level, Pos, Buffer, Length)              \
  KCParserAuxilPccDebug(Auxil, Event, Rule, Level, Pos, Buffer, Length)

// TODO: Change this to DEBUG when debugging
// #undef PCC_DEBUG

#define KGNODE_NONTERMINAL0(Kind)                                              \
  KCParserAuxilCreateNonTerminal0(auxil, _0s, _0e, Kind)
#define KGNODE_NONTERMINAL1(Kind, Child0)                                      \
  KCParserAuxilCreateNonTerminal1(auxil, _0s, _0e, Kind, Child0)
#define KGNODE_NONTERMINAL2(Kind, Child0, Child1)                              \
  KCParserAuxilCreateNonTerminal2(auxil, _0s, _0e, Kind, Child0, Child1)
#define KGNODE_NONTERMINAL3(Kind, Child0, Child1, Child2)                      \
  KCParserAuxilCreateNonTerminal3(auxil, _0s, _0e, Kind, Child0, Child1, Child2)
#define KGNODE_NONTERMINAL4(Kind, Child0, Child1, Child2, Child3)              \
  KCParserAuxilCreateNonTerminal4(auxil, _0s, _0e, Kind, Child0, Child1,       \
                                  Child2, Child3)
#define KGNODE_NONTERMINAL5(Kind, Child0, Child1, Child2, Child3, Child4)      \
  KCParserAuxilCreateNonTerminal5(auxil, _0s, _0e, Kind, Child0, Child1,       \
                                  Child2, Child3, Child4)
#define KGNODE_NONTERMINAL6(Kind, Child0, Child1, Child2, Child3, Child4,      \
                            Child5)                                            \
  KCParserAuxilCreateNonTerminal6(auxil, _0s, _0e, Kind, Child0, Child1,       \
                                  Child2, Child3, Child4, Child5)

#define KGNODE_TERMINAL0(Kind)                                                 \
  KCParserAuxilCreateTerminal0(auxil, _0s, _0e, Kind)
#define KGNODE_TERMINAL1(Kind, Value)                                          \
  KCParserAuxilCreateTerminal1(auxil, _0s, _0e, Kind, Value)
