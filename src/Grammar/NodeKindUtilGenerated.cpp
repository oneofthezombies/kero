#include "NodeKindUtilGenerated.h"

using namespace kero::grammar;

auto kero::grammar::operator<<(std::ostream &OS, KGNodeKind Kind) -> std::ostream & {
  switch (Kind) {
  case KGNodeKind_Module:
    OS << "Module";
    break;
  case KGNodeKind_ModuleItemList:
    OS << "ModuleItemList";
    break;
  case KGNodeKind_StatementList:
    OS << "StatementList";
    break;
  case KGNodeKind_IfStatement_IfElse:
    OS << "IfStatement_IfElse";
    break;
  case KGNodeKind_IfStatement_If:
    OS << "IfStatement_If";
    break;
  case KGNodeKind_ArrayLiteral_Empty:
    OS << "ArrayLiteral_Empty";
    break;
  case KGNodeKind_ArrayLiteral_List:
    OS << "ArrayLiteral_List";
    break;
  case KGNodeKind_SpreadElement:
    OS << "SpreadElement";
    break;
  case KGNodeKind_ObjectLiteral_Empty:
    OS << "ObjectLiteral_Empty";
    break;
  case KGNodeKind_ObjectLiteral:
    OS << "ObjectLiteral";
    break;
  case KGNodeKind_PropertyDefinitionList:
    OS << "PropertyDefinitionList";
    break;
  case KGNodeKind_PropertyDefinition:
    OS << "PropertyDefinition";
    break;
  case KGNodeKind_CoverInitializedName:
    OS << "CoverInitializedName";
    break;
  case KGNodeKind_MemberExpression:
    OS << "MemberExpression";
    break;
  case KGNodeKind_NewExpression:
    OS << "NewExpression";
    break;
  case KGNodeKind_CallExpression:
    OS << "CallExpression";
    break;
  case KGNodeKind_Arguments_Empty:
    OS << "Arguments_Empty";
    break;
  case KGNodeKind_Arguments_Ellipsis:
    OS << "Arguments_Ellipsis";
    break;
  case KGNodeKind_Arguments_List:
    OS << "Arguments_List";
    break;
  case KGNodeKind_Arguments_List_Ellipsis:
    OS << "Arguments_List_Ellipsis";
    break;
  case KGNodeKind_PostfixExpression_PlusPlus:
    OS << "PostfixExpression_PlusPlus";
    break;
  case KGNodeKind_PostfixExpression_MinusMinus:
    OS << "PostfixExpression_MinusMinus";
    break;
  case KGNodeKind_UnaryExpression_PlusPlus:
    OS << "UnaryExpression_PlusPlus";
    break;
  case KGNodeKind_UnaryExpression_MinusMinus:
    OS << "UnaryExpression_MinusMinus";
    break;
  case KGNodeKind_UnaryExpression_Plus:
    OS << "UnaryExpression_Plus";
    break;
  case KGNodeKind_UnaryExpression_Minus:
    OS << "UnaryExpression_Minus";
    break;
  case KGNodeKind_UnaryExpression_Tilde:
    OS << "UnaryExpression_Tilde";
    break;
  case KGNodeKind_UnaryExpression_Bang:
    OS << "UnaryExpression_Bang";
    break;
  case KGNodeKind_MultiplicativeExpression:
    OS << "MultiplicativeExpression";
    break;
  case KGNodeKind_MultiplicativeOperator_Asterisk:
    OS << "MultiplicativeOperator_Asterisk";
    break;
  case KGNodeKind_MultiplicativeOperator_Div:
    OS << "MultiplicativeOperator_Div";
    break;
  case KGNodeKind_MultiplicativeOperator_Percent:
    OS << "MultiplicativeOperator_Percent";
    break;
  case KGNodeKind_AdditiveExpression_Plus:
    OS << "AdditiveExpression_Plus";
    break;
  case KGNodeKind_AdditiveExpression_Minus:
    OS << "AdditiveExpression_Minus";
    break;
  case KGNodeKind_ShiftExpression_LeftShift:
    OS << "ShiftExpression_LeftShift";
    break;
  case KGNodeKind_ShiftExpression_RightShift:
    OS << "ShiftExpression_RightShift";
    break;
  case KGNodeKind_RelationalExpression_LessThan:
    OS << "RelationalExpression_LessThan";
    break;
  case KGNodeKind_RelationalExpression_GreaterThan:
    OS << "RelationalExpression_GreaterThan";
    break;
  case KGNodeKind_RelationalExpression_LessThanOrEqual:
    OS << "RelationalExpression_LessThanOrEqual";
    break;
  case KGNodeKind_RelationalExpression_GreaterThanOrEqual:
    OS << "RelationalExpression_GreaterThanOrEqual";
    break;
  case KGNodeKind_EqualityExpression_Equal:
    OS << "EqualityExpression_Equal";
    break;
  case KGNodeKind_EqualityExpression_NotEqual:
    OS << "EqualityExpression_NotEqual";
    break;
  case KGNodeKind_BitwiseANDExpression:
    OS << "BitwiseANDExpression";
    break;
  case KGNodeKind_BitwiseXORExpression:
    OS << "BitwiseXORExpression";
    break;
  case KGNodeKind_BitwiseORExpression:
    OS << "BitwiseORExpression";
    break;
  case KGNodeKind_LogicalANDExpression:
    OS << "LogicalANDExpression";
    break;
  case KGNodeKind_LogicalORExpression:
    OS << "LogicalORExpression";
    break;
  case KGNodeKind_ConditionalExpression:
    OS << "ConditionalExpression";
    break;
  case KGNodeKind_Expression:
    OS << "Expression";
    break;
  case KGNodeKind_KW_Break:
    OS << "KW_Break";
    break;
  case KGNodeKind_KW_Case:
    OS << "KW_Case";
    break;
  case KGNodeKind_KW_Catch:
    OS << "KW_Catch";
    break;
  case KGNodeKind_KW_Class:
    OS << "KW_Class";
    break;
  case KGNodeKind_KW_Const:
    OS << "KW_Const";
    break;
  case KGNodeKind_KW_Continue:
    OS << "KW_Continue";
    break;
  case KGNodeKind_KW_Debugger:
    OS << "KW_Debugger";
    break;
  case KGNodeKind_KW_Default:
    OS << "KW_Default";
    break;
  case KGNodeKind_KW_Delete:
    OS << "KW_Delete";
    break;
  case KGNodeKind_KW_Do:
    OS << "KW_Do";
    break;
  case KGNodeKind_KW_Else:
    OS << "KW_Else";
    break;
  case KGNodeKind_KW_Export:
    OS << "KW_Export";
    break;
  case KGNodeKind_KW_Extends:
    OS << "KW_Extends";
    break;
  case KGNodeKind_KW_Finally:
    OS << "KW_Finally";
    break;
  case KGNodeKind_KW_For:
    OS << "KW_For";
    break;
  case KGNodeKind_KW_Function:
    OS << "KW_Function";
    break;
  case KGNodeKind_KW_If:
    OS << "KW_If";
    break;
  case KGNodeKind_KW_Import:
    OS << "KW_Import";
    break;
  case KGNodeKind_KW_In:
    OS << "KW_In";
    break;
  case KGNodeKind_KW_Instanceof:
    OS << "KW_Instanceof";
    break;
  case KGNodeKind_KW_New:
    OS << "KW_New";
    break;
  case KGNodeKind_KW_Return:
    OS << "KW_Return";
    break;
  case KGNodeKind_KW_Super:
    OS << "KW_Super";
    break;
  case KGNodeKind_KW_Switch:
    OS << "KW_Switch";
    break;
  case KGNodeKind_KW_This:
    OS << "KW_This";
    break;
  case KGNodeKind_KW_Throw:
    OS << "KW_Throw";
    break;
  case KGNodeKind_KW_Try:
    OS << "KW_Try";
    break;
  case KGNodeKind_KW_Typeof:
    OS << "KW_Typeof";
    break;
  case KGNodeKind_KW_Var:
    OS << "KW_Var";
    break;
  case KGNodeKind_KW_Void:
    OS << "KW_Void";
    break;
  case KGNodeKind_KW_While:
    OS << "KW_While";
    break;
  case KGNodeKind_KW_With:
    OS << "KW_With";
    break;
  case KGNodeKind_KW_Yield:
    OS << "KW_Yield";
    break;
  case KGNodeKind_KW_Enum:
    OS << "KW_Enum";
    break;
  case KGNodeKind_KW_Await:
    OS << "KW_Await";
    break;
  case KGNodeKind_KW_Implements:
    OS << "KW_Implements";
    break;
  case KGNodeKind_KW_Interface:
    OS << "KW_Interface";
    break;
  case KGNodeKind_KW_Package:
    OS << "KW_Package";
    break;
  case KGNodeKind_KW_Private:
    OS << "KW_Private";
    break;
  case KGNodeKind_KW_Protected:
    OS << "KW_Protected";
    break;
  case KGNodeKind_KW_Public:
    OS << "KW_Public";
    break;
  }
  return OS;
}
