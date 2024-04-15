exports_files(["include/llvm/Config/llvm-config.h.cmake"])

cmake_external(
    name = "llvm_config",
    cache_entries = {
        "LLVM_ENABLE_PROJECTS": "clang;lld",
        "LLVM_TARGETS_TO_BUILD": "X86;ARM;AArch64",
        "LLVM_ENABLE_TERMINFO": "OFF",
        "LLVM_ENABLE_ASSERTIONS": "ON",
        "CMAKE_BUILD_TYPE": "Release",
    },
    cmake_options = [
        "-GNinja",
    ],
    generate_args = [
        "-DLLVM_ENABLE_RUNTIMES=all",
    ],
    lib_source = ":all",
)

filegroup(
    name = "all",
    srcs = glob(["**"]),
)
