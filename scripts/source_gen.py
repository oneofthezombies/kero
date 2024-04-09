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
]

enum_values = "\n".join([f"  KGNodeKind_{value} = 0," if i == 0 else f"  KGNodeKind_{value}," for i, value in enumerate(node_kinds)])
header_content = f"""#ifndef KERO_GRAMMAR_NODE_KIND_GENERATED_H
#define KERO_GRAMMAR_NODE_KIND_GENERATED_H

#ifdef __cplusplus
extern "C" {{
#endif

typedef enum KGNodeKindTag {{
{enum_values}
}} KGNodeKind;

#ifdef __cplusplus
}}
#endif

#endif // KERO_GRAMMAR_NODE_KIND_GENERATED_H
"""

util_header_content = """#ifndef KERO_GRAMMAR_NODE_KIND_UTIL_GENERATED_H
#define KERO_GRAMMAR_NODE_KIND_UTIL_GENERATED_H

#include "NodeKindGenerated.h"

#include <ostream>

namespace kero::grammar {

auto operator<<(std::ostream &OS, KGNodeKind Kind) -> std::ostream &;

} // namespace kero::grammar

#endif // KERO_GRAMMAR_NODE_KIND_UTIL_GENERATED_H
"""

enum_string_values = "\n".join([f"""  case KGNodeKind_{value}:
    OS << "{value}";
    break;""" for value in node_kinds])
util_source_content = f"""#include "NodeKindUtilGenerated.h"

using namespace kero::grammar;

auto kero::grammar::operator<<(std::ostream &OS, KGNodeKind Kind) -> std::ostream & {{
  switch (Kind) {{
{enum_string_values}
  }}
  return OS;
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

print("Generating NodeKindGenerated.h and NodeKindUtilGenerated.h/cpp")
with open("src/Grammar/NodeKindGenerated.h", "w") as f:
  f.write(header_content)
with open("src/Grammar/NodeKindUtilGenerated.h", "w") as f:
  f.write(util_header_content)
with open("src/Grammar/NodeKindUtilGenerated.cpp", "w") as f:
  f.write(util_source_content)
print("NodeKindGenerated.h, NodeKindUtilGenerated.h/cpp generated in src/Grammar")

print("Changing directory to src/Grammar")
os.chdir("src/Grammar")

print("Generating ParserGenerated.h/c")
if os.system("packcc -o ParserGenerated Grammar.peg") != 0:
  print("packcc failed to generate parser")
  exit(1)
print("ParserGenerated.h/c generated in src/Grammar")
