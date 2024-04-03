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

# Check clang command
if ! command -v clang &> /dev/null; then
    echo "clang could not be found"
    exit 1
else
    echo "clang found at $(command -v clang)"
fi

# Change directory to <workspace>/third_party/packcc-1.8.0/build/clang
cd "$workspace/third_party/packcc-1.8.0/build/clang"

# Call make clean
make clean

# Call make
make

# Ensure $HOME/.local/bin exists
if [ ! -d "$HOME/.local/bin" ]; then
    mkdir -p "$HOME/.local/bin"
fi

# Copy packcc to $HOME/.local/bin
cp "$workspace/third_party/packcc-1.8.0/build/clang/debug/bin/packcc" "$HOME/.local/bin"

# Print installation message
echo "packcc installed to $HOME/.local/bin"
echo "ensure $HOME/.local/bin is in your PATH"
