# Development

# Prequirements

## Python

version >= 3.12.2

## CMake

version >= 3.28.3

## Ninja

version >= 1.11.1

## LLVM

version >= 17.0.6

### Macos

```sh
curl -LO https://github.com/llvm/llvm-project/releases/download/llvmorg-17.0.6/clang+llvm-17.0.6-arm64-apple-darwin22.0.tar.xz && \
    tar zxvf clang+llvm-17.0.6-arm64-apple-darwin22.0.tar.xz && \
    mkdir -p third_party && \
    mv clang+llvm-17.0.6-arm64-apple-darwin22.0 third_party/llvm && \
    rm clang+llvm-17.0.6-arm64-apple-darwin22.0.tar.xz
```
