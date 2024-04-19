# Kero

Kero is a programming language written in C++.
It is a simple and intuitive system programming language with the philosophy “Less is better than more.”

![mascot](/resources/mascot.webp)

# How to Build

## Install LLVM

```sh
LLVM_VERSION=18.1.4
curl -LO https://github.com/llvm/llvm-project/archive/refs/tags/llvmorg-$LLVM_VERSION.zip
unzip llvmorg-$LLVM_VERSION.zip
rm -f llvmorg-$LLVM_VERSION.zip
cd llvm-project-llvmorg-$LLVM_VERSION

# choose ninja or make build system
# build using ninja
cmake -S llvm -B build -G Ninja \
    -DCMAKE_INSTALL_PREFIX="$HOME/.local" \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_C_COMPILER=clang \
    -DCMAKE_CXX_COMPILER=clang++ \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    -DLLVM_ENABLE_PROJECTS="clang;lld;lldb" \
    -DLLVM_ENABLE_ASSERTIONS=ON \
    -DLLVM_USE_LINKER=lld
cd build
cmake --build .

# build using make
cmake -S llvm -B build -G "Unix Makefiles" \
    -DCMAKE_INSTALL_PREFIX="$HOME/.local" \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_C_COMPILER=clang \
    -DCMAKE_CXX_COMPILER=clang++ \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    -DLLVM_ENABLE_PROJECTS="clang;lld;lldb" \
    -DLLVM_ENABLE_ASSERTIONS=ON \
    -DLLVM_USE_LINKER=lld
cd build
make -j

# install
sudo cmake --install .

# copy compile_commands.json
mkdir -p $HOME/.local/share/compile_commands/llvm && \
    cp -f ./compile_commands.json $HOME/.local/share/compile_commands/llvm/
```

## Install C++ Tree-sitter

```sh
CPP_TREE_SITTER_VERSION=0.2.0
curl -LO https://github.com/oneofthezombies/cpp-tree-sitter/archive/refs/tags/v$CPP_TREE_SITTER_VERSION.zip
unzip v$CPP_TREE_SITTER_VERSION.zip
rm -f v$CPP_TREE_SITTER_VERSION.zip
cd cpp-tree-sitter-$CPP_TREE_SITTER_VERSION
mkdir -p build && cd build
cmake .. -G Ninja \
    -DCMAKE_INSTALL_PREFIX="$HOME/.local" \
    -DCMAKE_C_COMPILER=clang \
    -DCMAKE_CXX_COMPILER=clang++ \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build .
sudo cmake --install .

# copy compile_commands.json
mkdir -p $HOME/.local/share/compile_commands/cpp-tree-sitter && \
    cp -f ./compile_commands.json $HOME/.local/share/compile_commands/cpp-tree-sitter/
```

## Install Google Test

```sh
GOOGLE_TEST_VERSION=1.14.0
curl -LO https://github.com/google/googletest/archive/refs/tags/v$GOOGLE_TEST_VERSION.zip
unzip v$GOOGLE_TEST_VERSION.zip
rm -f v$GOOGLE_TEST_VERSION.zip
cd googletest-$GOOGLE_TEST_VERSION
mkdir -p build && cd build
cmake .. -G Ninja \
    -DCMAKE_INSTALL_PREFIX="$HOME/.local" \
    -DCMAKE_C_COMPILER=clang \
    -DCMAKE_CXX_COMPILER=clang++ \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build .
sudo cmake --install .

# copy compile_commands.json
mkdir -p $HOME/.local/share/compile_commands/googletest && \
    cp -f ./compile_commands.json $HOME/.local/share/compile_commands/googletest/
```

## Kero

```sh
mkdir -p build && cd build
cmake .. -G Ninja -DCMAKE_PREFIX_PATH="$HOME/.local"
cmake --build .
```
