"""
import fs from "fs";

const enumName = "KGNodeKind";
const values = [
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
];

const enumValues = values
  .map((value, index) =>
    index === 0 ? `  KGNodeKind_${value} = 0,` : `  KGNodeKind_${value},`
  )
  .join("\n");

const headerContent = `#ifndef KERO_GRAMMAR_NODE_KIND_GENERATED_H
#define KERO_GRAMMAR_NODE_KIND_GENERATED_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum KGNodeKindTag {
${enumValues}
} KGNodeKind;

#ifdef __cplusplus
}
#endif

#endif // KERO_GRAMMAR_NODE_KIND_GENERATED_H
`;

const utilHeaderContent = `#ifndef KERO_GRAMMAR_NODE_KIND_UTIL_GENERATED_H
#define KERO_GRAMMAR_NODE_KIND_UTIL_GENERATED_H

#include "NodeKindGenerated.h"

#include <ostream>

namespace kero::grammar {

auto operator<<(std::ostream &OS, KGNodeKind Kind) -> std::ostream &;

} // namespace kero::grammar

#endif // KERO_GRAMMAR_NODE_KIND_UTIL_GENERATED_H
`;

const enumStringValues = values
  .map(
    (value) => `  case KGNodeKind_${value}:
    OS << "${value}";
    break;`
  )
  .join("\n");

const utilSourceContent = `#include "NodeKindUtilGenerated.h"

using namespace kero::grammar;

auto kero::grammar::operator<<(std::ostream &OS, KGNodeKind Kind) -> std::ostream & {
  switch (Kind) {
${enumStringValues}
  }
  return OS;
}
`;

fs.writeFileSync("src/Grammar/NodeKindGenerated.h", headerContent);
fs.writeFileSync("src/Grammar/NodeKindUtilGenerated.h", utilHeaderContent);
fs.writeFileSync("src/Grammar/NodeKindUtilGenerated.cpp", utilSourceContent);

"""

"""
#!/usr/bin/env bash

# --verbose flag to enable debug output
for arg in "$@"; do
  if [ "$arg" = "--verbose" ]; then
    set -x
  fi
done

set -e
set -o pipefail

# Check if WORKSPACE file exists in the root directory or one level down
if [ -f "WORKSPACE" ]; then
    workspace=$(pwd)
elif [ -f "../WORKSPACE" ]; then
    workspace=$(cd .. && pwd)
else
    echo "WORKSPACE file not found."
    exit 1
fi

# Change directory to <workspace>
cd "$workspace"

# Check packcc command
if ! command -v packcc &> /dev/null; then
    echo "packcc could not be found"
    exit 1
else
    echo "packcc found at $(command -v packcc)"
fi

cd "$workspace/src/Grammar"

packcc -o ParserGenerated grammar.peg

echo "ParserGenerated.h and ParserGenerated.c generated in $workspace/src/Grammar"

"""
