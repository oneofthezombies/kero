# Kero

Kero is a programming language written in C++.
It is a simple and intuitive system programming language with the philosophy “Less is better than more.”

![mascot](/resources/mascot.webp)

# How to Build

## Install LLVM

```sh
LLVM_VERSION=18.1.4
curl -LO https://github.com/llvm/llvm-project/archive/refs/tags/llvmorg-${LLVM_VERSION}.zip
unzip llvmorg-${LLVM_VERSION}.zip
rm -f llvmorg-${LLVM_VERSION}.zip
cd llvm-project-llvmorg-${LLVM_VERSION}
cmake -S llvm -B build -G Ninja \
    -DLLVM_ENABLE_PROJECTS="" \
    -DCMAKE_INSTALL_PREFIX=$HOME/.local \
    -DCMAKE_BUILD_TYPE=Debug \
    -DLLVM_ENABLE_ASSERTIONS=ON \
    -DLLVM_USE_LINKER=lld
cmake --build build
```

## Kero

```sh
mkdir build && cd build
cmake .. -G Ninja -DCMAKE_PREFIX_PATH="$HOME/.local"
cmake --build .
```
