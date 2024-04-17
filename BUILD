load("@hedron_compile_commands//:refresh_compile_commands.bzl", "refresh_compile_commands")

refresh_compile_commands(
    name = "refresh_compile_commands",
    targets = [
        ":tree_sitter_kero",
        ":kero_compiler",
        ":kero_compiler_test",
        ":llvm_compile_commands_test",
        "@googletest//:gtest_main",
        "@cpp_tree_sitter",
    ],
)

cc_library(
    name = "tree_sitter_kero",
    srcs = ["src/tree-sitter-kero/src/parser.c"],
    hdrs = [
        "src/tree-sitter-kero/bindings/c/tree-sitter-kero.h",
    ] + glob(["src/tree-sitter-kero/src/tree_sitter/*.h"]),
    copts = [
        "-std=c17",
    ],
    includes = [
        "src/tree-sitter-kero/bindings/c",
        "src/tree-sitter-kero/src",
    ],
)

cc_library(
    name = "kero_compiler",
    srcs = [
        "src/compiler/code_generator.cc",
        "src/compiler/core.cc",
        "src/compiler/parser_builder.cc",
        "src/compiler/utils.cc",
    ],
    hdrs = [
        "src/compiler/code_gen_visitors.cc",
        "src/compiler/code_generator.h",
        "src/compiler/core.h",
        "src/compiler/parser_builder.h",
        "src/compiler/utils.h",
    ],
    copts = [
        "-std=c++20",
        "-fno-rtti",
    ],
    includes = [
        "src",
    ],
    deps = [
        ":llvm",
        ":tree_sitter_kero",
        "@cpp_tree_sitter",
    ],
)

cc_test(
    name = "kero_compiler_test",
    srcs = [
        "src/compiler/code_generator_test.cc",
        "src/compiler/parser_builder_test.cc",
    ],
    copts = [
        "-std=c++20",
        "-fno-rtti",
    ],
    includes = [
        "src",
    ],
    deps = [
        ":kero_compiler",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "llvm",
    hdrs = glob([
        ".build/llvm/include/**/*",
        ".build/llvm/lib/**/*.*",
        "third_party/llvm-project-llvmorg-18.1.3/llvm/include/**/*",
        "third_party/llvm-project-llvmorg-18.1.3/llvm/lib/**/*",
    ]),
    includes = [
        ".build/llvm/include",
        "third_party/llvm-project-llvmorg-18.1.3/llvm/include",
    ],
    linkopts = [
        "-L/Users/hunhoekim/repo/kero/.build/llvm/lib",
        "-lLLVMCore",
        "-lLLVMRemarks",
        "-lLLVMBitstreamReader",
        "-lLLVMBinaryFormat",
        "-lLLVMTargetParser",
        "-lLLVMSupport",
        "-lLLVMDemangle",

        # linux specific to select
        # "-lrt",
        # "-ldl",
        # "-lm",
        # "-ltinfo",
        # "-lxml2",

        # macos specific to select
        "-lm",
        "-lz",
        "-lzstd",
        "-lcurses",
        "-lxml2",
    ],
)

# This test is for generating compile_commands.json. It's not really a test.
cc_test(
    name = "llvm_compile_commands_test",
    srcs = ["src/utils/llvm_compile_commands_test.cc"],
    deps = [
        ":llvm",
    ],
)
