import os

node_kinds = [
  "AdditiveExpression_Minus",
  "AdditiveExpression_Plus",
  "Arguments_Ellipsis",
  "Arguments_Empty",
  "Arguments_List",
  "Arguments_List_Ellipsis",
  "ArrayLiteral_Empty",
  "ArrayLiteral_List",
  "BitwiseANDExpression",
  "BitwiseORExpression",
  "BitwiseXORExpression",
  "Block",
  "BooleanLiteral_False",
  "BooleanLiteral_True",
  "CallExpression",
  "ConditionalExpression",
  "CoverInitializedName",
  "DecimalDigit",
  "DecimalDigits",
  "DecimalIntegerLiteral",
  "DecimalIntegerLiteral_Zero",
  "DecimalLiteral_Integer",
  "DecimalLiteral_Integer_Period",
  "DecimalLiteral_Period",
  "EqualityExpression_Equal",
  "EqualityExpression_NotEqual",
  "ExponentIndicator",
  "ExponentPart",
  "Expression",
  "IdentifierName",
  "IdentifierPart",
  "IfStatement_If",
  "IfStatement_IfElse",
  "KW_Await",
  "KW_Break",
  "KW_Case",
  "KW_Catch",
  "KW_Class",
  "KW_Const",
  "KW_Continue",
  "KW_Debugger",
  "KW_Default",
  "KW_Delete",
  "KW_Do",
  "KW_Else",
  "KW_Enum",
  "KW_Export",
  "KW_Extends",
  "KW_Finally",
  "KW_For",
  "KW_Function",
  "KW_If",
  "KW_Implements",
  "KW_Import",
  "KW_In",
  "KW_Instanceof",
  "KW_Interface",
  "KW_New",
  "KW_Package",
  "KW_Private",
  "KW_Protected",
  "KW_Public",
  "KW_Return",
  "KW_Super",
  "KW_Switch",
  "KW_This",
  "KW_Throw",
  "KW_Try",
  "KW_Typeof",
  "KW_Var",
  "KW_Void",
  "KW_While",
  "KW_With",
  "KW_Yield",
  "LogicalANDExpression",
  "LogicalORExpression",
  "MemberExpression",
  "Module",
  "ModuleItemList",
  "MultiplicativeExpression",
  "MultiplicativeOperator_Asterisk",
  "MultiplicativeOperator_Div",
  "MultiplicativeOperator_Percent",
  "NewExpression",
  "NonZeroDigit",
  "NullLiteral",
  "ObjectLiteral",
  "ObjectLiteral_Empty",
  "PostfixExpression_MinusMinus",
  "PostfixExpression_PlusPlus",
  "PropertyDefinition",
  "PropertyDefinitionList",
  "PT_ArrowFunction",
  "PT_Assign",
  "PT_Asterisk",
  "PT_AsteriskAssign",
  "PT_Backslash",
  "PT_Bang",
  "PT_BitwiseAND",
  "PT_BitwiseANDAssign",
  "PT_BitwiseOR",
  "PT_BitwiseORAssign",
  "PT_BitwiseXOR",
  "PT_BitwiseXORAssign",
  "PT_Colon",
  "PT_Comma",
  "PT_Div",
  "PT_DivAssign",
  "PT_Dollar",
  "PT_Ellipsis",
  "PT_Equal",
  "PT_GreaterThan",
  "PT_GreaterThanOrEqual",
  "PT_LeftBrace",
  "PT_LeftBracket",
  "PT_LeftParenthesis",
  "PT_LeftShift",
  "PT_LeftShiftAssign",
  "PT_LessThan",
  "PT_LessThanOrEqual",
  "PT_LogicalAND",
  "PT_LogicalOR",
  "PT_Minus",
  "PT_MinusAssign",
  "PT_MinusMinus",
  "PT_NotEqual",
  "PT_NotStrictEqual",
  "PT_Percent",
  "PT_PercentAssign",
  "PT_Period",
  "PT_Plus",
  "PT_PlusAssign",
  "PT_PlusPlus",
  "PT_Question",
  "PT_RightBrace",
  "PT_RightBracket",
  "PT_RightParenthesis",
  "PT_RightShift",
  "PT_RightShiftAssign",
  "PT_Semicolon",
  "PT_StrictEqual",
  "PT_Tilde",
  "PT_Underscore",
  "PT_UnsignedRightShift",
  "PT_UnsignedRightShiftAssign",
  "RelationalExpression_GreaterThan",
  "RelationalExpression_GreaterThanOrEqual",
  "RelationalExpression_LessThan",
  "RelationalExpression_LessThanOrEqual",
  "ShiftExpression_LeftShift",
  "ShiftExpression_RightShift",
  "SignedInteger_Minus",
  "SignedInteger_Plus",
  "SpreadElement",
  "StatementList",
  "UnaryExpression_Bang",
  "UnaryExpression_Minus",
  "UnaryExpression_MinusMinus",
  "UnaryExpression_Plus",
  "UnaryExpression_PlusPlus",
  "UnaryExpression_Tilde",
  "UnicodeIDContinue",
  "UnicodeIDStart"
]

enum_values = "\n".join(
    [
        f"  KCNodeKind_{value} = 0," if i == 0 else f"  KCNodeKind_{value},"
        for i, value in enumerate(node_kinds)
    ]
)
header_content = f"""#ifndef KERO_COMPILE_PARSER_NODE_KIND_GENERATED_H
#define KERO_COMPILE_PARSER_NODE_KIND_GENERATED_H

#ifdef __cplusplus
extern "C" {{
#endif

typedef enum KCNodeKindTag {{
{enum_values}
}} KCNodeKind;

const char *KCNodeKindToString(KCNodeKind Kind);

#ifdef __cplusplus
}}
#endif

#endif // KERO_COMPILE_PARSER_NODE_KIND_GENERATED_H
"""

source_content = f"""#include "NodeKindGenerated.h"

const char *KCNodeKindToString(KCNodeKind Kind) {{
  switch (Kind) {{
{"".join([f"  case KCNodeKind_{value}:\n    return \"{value}\";\n" for value in node_kinds])}
  default:
    return "Unknown";
  }}
}}
"""


print("Checking WORKSPACE file")
if os.path.exists("WORKSPACE"):
    workspace = os.getcwd()
elif os.path.exists("../WORKSPACE"):
    workspace = os.path.abspath(os.path.join(os.getcwd(), ".."))
else:
    print("WORKSPACE file not found.")
    exit(1)

print(f"Changing directory to {workspace}")
os.chdir(workspace)

print("Checking if packcc is installed")
if os.system("packcc --version") != 0:
    print("packcc is not installed")
    exit(1)
else:
    print("packcc is installed")

print("Generating NodeKindGenerated.h/cpp")
with open("src/Compile/Parser/NodeKindGenerated.h", "w") as f:
    f.write(header_content)
with open("src/Compile/Parser/NodeKindGenerated.c", "w") as f:
    f.write(source_content)
print("NodeKindGenerated.h/cpp generated in src/Compile/Parser")

print("Changing directory to src/Compile/Parser")
os.chdir("src/Compile/Parser")

print("Generating ParserGenerated.h/c")
if os.system("packcc -o ParserGenerated Grammar.peg") != 0:
    print("packcc failed to generate parser")
    exit(1)
print("ParserGenerated.h/c generated in src/Compile/Parser")
