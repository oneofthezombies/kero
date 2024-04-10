import os

node_kinds = [
    "Module",
    "ModuleItemList",
    "StatementList",
    "IfStatement_IfElse",
    "IfStatement_If",
    "ArrayLiteral_Empty",
    "ArrayLiteral_List",
    "SpreadElement",
    "ObjectLiteral_Empty",
    "ObjectLiteral",
    "PropertyDefinitionList",
    "PropertyDefinition",
    "CoverInitializedName",
    "MemberExpression",
    "NewExpression",
    "CallExpression",
    "Arguments_Empty",
    "Arguments_Ellipsis",
    "Arguments_List",
    "Arguments_List_Ellipsis",
    "PostfixExpression_PlusPlus",
    "PostfixExpression_MinusMinus",
    "UnaryExpression_PlusPlus",
    "UnaryExpression_MinusMinus",
    "UnaryExpression_Plus",
    "UnaryExpression_Minus",
    "UnaryExpression_Tilde",
    "UnaryExpression_Bang",
    "MultiplicativeExpression",
    "MultiplicativeOperator_Asterisk",
    "MultiplicativeOperator_Div",
    "MultiplicativeOperator_Percent",
    "AdditiveExpression_Plus",
    "AdditiveExpression_Minus",
    "ShiftExpression_LeftShift",
    "ShiftExpression_RightShift",
    "RelationalExpression_LessThan",
    "RelationalExpression_GreaterThan",
    "RelationalExpression_LessThanOrEqual",
    "RelationalExpression_GreaterThanOrEqual",
    "EqualityExpression_Equal",
    "EqualityExpression_NotEqual",
    "BitwiseANDExpression",
    "BitwiseXORExpression",
    "BitwiseORExpression",
    "LogicalANDExpression",
    "LogicalORExpression",
    "ConditionalExpression",
    "Expression",
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
    "KW_Export",
    "KW_Extends",
    "KW_Finally",
    "KW_For",
    "KW_Function",
    "KW_If",
    "KW_Import",
    "KW_In",
    "KW_Instanceof",
    "KW_New",
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
    "KW_Enum",
    "KW_Await",
    "KW_Implements",
    "KW_Interface",
    "KW_Package",
    "KW_Private",
    "KW_Protected",
    "KW_Public",
    "Block",
    "BooleanLiteral_True",
    "BooleanLiteral_False",
    "NullLiteral",
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
