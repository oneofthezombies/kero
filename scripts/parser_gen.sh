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

cd "$workspace/src/grammar"

packcc -o parser_generated grammar.peg

echo "parser_generated.h and parser_generated.c generated in $workspace/src/grammar"
