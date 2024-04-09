#ifndef KERO_GRAMMAR_PARSER_AUXIL_H
#define KERO_GRAMMAR_PARSER_AUXIL_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct KGParserAuxilTag KGParserAuxil;

void KGParserAuxil_pccError(const KGParserAuxil *const Auxil);
int KGParserAuxil_pccGetChar(const KGParserAuxil *const Auxil);
void *KGParserAuxil_pccMalloc(const KGParserAuxil *const Auxil,
                              const size_t Size);
void *KGParserAuxil_pccRealloc(const KGParserAuxil *const Auxil, void *Ptr,
                               const size_t Size);
void KGParserAuxil_pccFree(const KGParserAuxil *const Auxil, void *Ptr);
void KGParserAuxil_pccDebug(const KGParserAuxil *const Auxil, const int Event,
                            const char *const Rule, const size_t Level,
                            const size_t Pos, const char *const Buffer,
                            const size_t Length);

typedef enum KGNodeKindTag {
  KGNodeKind_Module = 0,
  KGNodeKind_ModuleItemList,
  KGNodeKind_StatementList,
  KGNodeKind_IfStatement_IfElse,
  KGNodeKind_IfStatement_If,
  KGNodeKind_ArrayLiteral_Empty, // Terminal
  KGNodeKind_ArrayLiteral_List,
  KGNodeKind_SpreadElement,
  KGNodeKind_ObjectLiteral_Empty, // Terminal
  KGNodeKind_ObjectLiteral,
  KGNodeKind_PropertyDefinitionList,
  KGNodeKind_PropertyDefinition,
  KGNodeKind_CoverInitializedName,
  KGNodeKind_MemberExpression,
  KGNodeKind_NewExpression,
  KGNodeKind_CallExpression,
  KGNodeKind_Arguments_Empty, // Terminal
  KGNodeKind_Arguments_Ellipsis,
  KGNodeKind_Arguments_List,
  KGNodeKind_Arguments_List_Ellipsis,
  KGNodeKind_PostfixExpression_PlusPlus,
  KGNodeKind_PostfixExpression_MinusMinus,
  KGNodeKind_UnaryExpression_PlusPlus,
  KGNodeKind_UnaryExpression_MinusMinus,
  KGNodeKind_UnaryExpression_Plus,
  KGNodeKind_UnaryExpression_Minus,
  KGNodeKind_UnaryExpression_Tilde,
  KGNodeKind_UnaryExpression_Bang,
  KGNodeKind_MultiplicativeExpression,
  KGNodeKind_MultiplicativeOperator_Asterisk, // Terminal
  KGNodeKind_MultiplicativeOperator_Div,      // Terminal
  KGNodeKind_MultiplicativeOperator_Percent,  // Terminal
  KGNodeKind_AdditiveExpression_Plus,
  KGNodeKind_AdditiveExpression_Minus,
  KGNodeKind_ShiftExpression_LeftShift,
  KGNodeKind_ShiftExpression_RightShift,
  KGNodeKind_RelationalExpression_LessThan,
  KGNodeKind_RelationalExpression_GreaterThan,
  KGNodeKind_RelationalExpression_LessThanOrEqual,
  KGNodeKind_RelationalExpression_GreaterThanOrEqual,
  KGNodeKind_EqualityExpression_Equal,
  KGNodeKind_EqualityExpression_NotEqual,
  KGNodeKind_BitwiseANDExpression,
  KGNodeKind_BitwiseXORExpression,
  KGNodeKind_BitwiseORExpression,
  KGNodeKind_LogicalANDExpression,
  KGNodeKind_LogicalORExpression,
  KGNodeKind_ConditionalExpression,
  KGNodeKind_Expression,
  KGNodeKind_KW_Break,      // Terminal
  KGNodeKind_KW_Case,       // Terminal
  KGNodeKind_KW_Catch,      // Terminal
  KGNodeKind_KW_Class,      // Terminal
  KGNodeKind_KW_Const,      // Terminal
  KGNodeKind_KW_Continue,   // Terminal
  KGNodeKind_KW_Debugger,   // Terminal
  KGNodeKind_KW_Default,    // Terminal
  KGNodeKind_KW_Delete,     // Terminal
  KGNodeKind_KW_Do,         // Terminal
  KGNodeKind_KW_Else,       // Terminal
  KGNodeKind_KW_Export,     // Terminal
  KGNodeKind_KW_Extends,    // Terminal
  KGNodeKind_KW_Finally,    // Terminal
  KGNodeKind_KW_For,        // Terminal
  KGNodeKind_KW_Function,   // Terminal
  KGNodeKind_KW_If,         // Terminal
  KGNodeKind_KW_Import,     // Terminal
  KGNodeKind_KW_In,         // Terminal
  KGNodeKind_KW_Instanceof, // Terminal
  KGNodeKind_KW_New,        // Terminal
  KGNodeKind_KW_Return,     // Terminal
  KGNodeKind_KW_Super,      // Terminal
  KGNodeKind_KW_Switch,     // Terminal
  KGNodeKind_KW_This,       // Terminal
  KGNodeKind_KW_Throw,      // Terminal
  KGNodeKind_KW_Try,        // Terminal
  KGNodeKind_KW_Typeof,     // Terminal
  KGNodeKind_KW_Var,        // Terminal
  KGNodeKind_KW_Void,       // Terminal
  KGNodeKind_KW_While,      // Terminal
  KGNodeKind_KW_With,       // Terminal
  KGNodeKind_KW_Yield,      // Terminal
  KGNodeKind_KW_Enum,       // Terminal
  KGNodeKind_KW_Await,      // Terminal
  KGNodeKind_KW_Implements, // Terminal
  KGNodeKind_KW_Interface,  // Terminal
  KGNodeKind_KW_Package,    // Terminal
  KGNodeKind_KW_Private,    // Terminal
  KGNodeKind_KW_Protected,  // Terminal
  KGNodeKind_KW_Public,     // Terminal
} KGNodeKind;

typedef size_t KGNodeId;

KGNodeId KGParserAuxil_createNonTerminal0(const KGParserAuxil *const Auxil,
                                          const size_t Start, const size_t End,
                                          const KGNodeKind Kind);
KGNodeId KGParserAuxil_createNonTerminal1(const KGParserAuxil *const Auxil,
                                          const size_t Start, const size_t End,
                                          const KGNodeKind Kind,
                                          const KGNodeId Child0);
KGNodeId KGParserAuxil_createNonTerminal2(const KGParserAuxil *const Auxil,
                                          const size_t Start, const size_t End,
                                          const KGNodeKind Kind,
                                          const KGNodeId Child0,
                                          const KGNodeId Child1);
KGNodeId KGParserAuxil_createNonTerminal3(const KGParserAuxil *const Auxil,
                                          const size_t Start, const size_t End,
                                          const KGNodeKind Kind,
                                          const KGNodeId Child0,
                                          const KGNodeId Child1,
                                          const KGNodeId Child2);
KGNodeId KGParserAuxil_createNonTerminal4(
    const KGParserAuxil *const Auxil, const size_t Start, const size_t End,
    const KGNodeKind Kind, const KGNodeId Child0, const KGNodeId Child1,
    const KGNodeId Child2, const KGNodeId Child3);
KGNodeId KGParserAuxil_createNonTerminal5(
    const KGParserAuxil *const Auxil, const size_t Start, const size_t End,
    const KGNodeKind Kind, const KGNodeId Child0, const KGNodeId Child1,
    const KGNodeId Child2, const KGNodeId Child3, const KGNodeId Child4);
KGNodeId KGParserAuxil_createNonTerminal6(
    const KGParserAuxil *const Auxil, const size_t Start, const size_t End,
    const KGNodeKind Kind, const KGNodeId Child0, const KGNodeId Child1,
    const KGNodeId Child2, const KGNodeId Child3, const KGNodeId Child4,
    const KGNodeId Child5);
KGNodeId KGParserAuxil_createTerminal0(const KGParserAuxil *const Auxil,
                                       const size_t Start, const size_t End,
                                       const KGNodeKind Kind);
KGNodeId KGParserAuxil_createTerminal1(const KGParserAuxil *const Auxil,
                                       const size_t Start, const size_t End,
                                       const KGNodeKind Kind,
                                       const char *const Value);

#ifdef __cplusplus
}
#endif

#endif // KERO_GRAMMAR_PARSER_AUXIL_H
