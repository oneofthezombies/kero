# Development

# Prequirements

## Python

version >= 3.12.2

### Install Libraries

```sh
python -m pip install -r requirements.txt
```

## CMake

version >= 3.28.3

## Ninja

version >= 1.11.1

## LLVM

tag == llvmorg-17.0.6

```sh
mkdir -p third_party && \
    cd third_party && \
    git clone --depth=1 https://github.com/llvm/llvm-project.git && \
    cd llvm-project && \
    git fetch --tags origin llvmorg-17.0.6 && \
    git checkout llvmorg-17.0.6
```
