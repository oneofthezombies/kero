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
        "src/compiler/parser.h",
    ],
    hdrs = [
    ],
    copts = [
        "-std=c++20",
        "-fno-rtti",
    ],
    includes = [
        "src",
    ],
    deps = [
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
