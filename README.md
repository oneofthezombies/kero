# Kero

Kero is a programming language written in C++.
It is a simple and intuitive system programming language with the philosophy “Less is better than more.”

![mascot](/resources/mascot.webp)

# How to Build

## Install LLVM

```sh
LLVM_VERSION=18.1.4
LLVM_INSTALL_PATH="$HOME/.local"
curl -LO https://github.com/llvm/llvm-project/archive/refs/tags/llvmorg-$LLVM_VERSION.zip
unzip llvmorg-$LLVM_VERSION.zip
rm -f llvmorg-$LLVM_VERSION.zip
cd llvm-project-llvmorg-$LLVM_VERSION

# choose ninja or make
# build using ninja
cmake -S llvm -B build -G Ninja \
    -DLLVM_ENABLE_PROJECTS="" \
    -DCMAKE_INSTALL_PREFIX="$LLVM_INSTALL_PATH" \
    -DCMAKE_BUILD_TYPE=Debug \
    -DLLVM_ENABLE_ASSERTIONS=ON \
    -DLLVM_USE_LINKER=lld
cmake --build build

# build using make
cmake -S llvm -B build -G "Unix Makefiles" \
    -DLLVM_ENABLE_PROJECTS="" \
    -DCMAKE_INSTALL_PREFIX="$LLVM_INSTALL_PATH" \
    -DCMAKE_BUILD_TYPE=Debug \
    -DLLVM_ENABLE_ASSERTIONS=ON \
    -DLLVM_USE_LINKER=lld
cd build
make -j
```

## Install C++ Tree-sitter

```sh
CPP_TREE_SITTER_VERSION=0.2.0
CPP_TREE_SITTER_INSTALL_PATH="$HOME/.local"
curl -LO https://github.com/oneofthezombies/cpp-tree-sitter/archive/refs/tags/v$CPP_TREE_SITTER_VERSION.zip
unzip v$CPP_TREE_SITTER_VERSION.zip
rm -f v$CPP_TREE_SITTER_VERSION.zip
cd cpp-tree-sitter-$CPP_TREE_SITTER_VERSION
cmake -B build -G Ninja -DCMAKE_INSTALL_PREFIX="$CPP_TREE_SITTER_INSTALL_PATH"
cmake --build build
sudo cmake --install build
```

## Kero

```sh
mkdir build && cd build
cmake .. -G Ninja -DCMAKE_PREFIX_PATH="$LLVM_INSTALL_PATH;$CPP_TREE_SITTER_INSTALL_PATH"
cmake --build .
```
