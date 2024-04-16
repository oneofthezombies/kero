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
        "src/compiler/parser.cc",
    ],
    hdrs = [
        "src/compiler/parser.h",
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
        "src/compiler/parser_test.cc",
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

genrule(
    name = "llvm_config_flags",
    outs = ["llvm_config_flags.txt"],
    cmd = "./.build/llvm/bin/llvm-config --cxxflags --ldflags --system-libs --libs core > $@",
    tools = [".build/llvm/bin/llvm-config"],
)

cc_library(
    name = "llvm",
    hdrs = glob([
        ".build/llvm/include/**/*",
        ".build/llvm/lib/**/*.*",
        "third_party/llvm-project-llvmorg-18.1.3/llvm/include/**/*",
        "third_party/llvm-project-llvmorg-18.1.3/llvm/lib/**/*",
    ]),
    copts = [":llvm_config_flags"],
    includes = [
        ".build/llvm/include",
        "third_party/llvm-project-llvmorg-18.1.3/llvm/include",
    ],
    deps = [
        ":llvm_config_flags",
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
