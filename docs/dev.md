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
mkdir -p third_party

cd third_party
git clone --depth=1 https://github.com/llvm/llvm-project.git

cd llvm-project
git fetch --tags origin llvmorg-17.0.6
git checkout llvmorg-17.0.6

# ensure third_party/llvm-project directory.
cmake -S llvm -B build -G Ninja -DLLVM_ENABLE_PROJECTS="clang;lld" -DCMAKE_BUILD_TYPE=Release
ninja -C build

# ensure <kero_project_dir> directory.
export PATH="$(pwd)/third_party/llvm-project/build/bin:${PATH}"
```

## Bazel

1. ensure commands `bazelisk` and `bazel`.

    _version >= 7.0.2_

    please see [Official Documents](https://github.com/bazelbuild/bazelisk).

    ```sh
    bazelisk --version
    # bazel 7.0.2

    bazel --version
    # bazel 7.0.2
    ```

2. ensure command `buildifier`.

    _version >= 6.4.0_

    please see [Official Documents](https://github.com/bazelbuild/buildtools).

    ```sh
    buildifier --version
    # buildifier version: 6.4.0 
    # buildifier scm revision: 433ea8554e82832e4fa4bdd530ca471564071511
    ```
