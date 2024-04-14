cc_library(
    name = "tree_sitter",
    srcs = [
        "third_party/tree-sitter-0.22.2/lib/src/lib.c",
    ],
    hdrs = [
        "third_party/tree-sitter-0.22.2/lib/include/tree_sitter/api.h",
    ] + glob(
        [
            "third_party/tree-sitter-0.22.2/lib/src/**/*.c",
            "third_party/tree-sitter-0.22.2/lib/src/**/*.h",
        ],
        ["third_party/tree-sitter-0.22.2/lib/src/lib.c"],
    ),
    copts = [
        "-std=c17",
    ],
    includes = [
        "third_party/tree-sitter-0.22.2/lib/include",
        "third_party/tree-sitter-0.22.2/lib/src",
    ],
)

cc_library(
    name = "tree_sitter_kero",
    srcs = ["third_party/tree-sitter-kero/src/parser.c"],
    hdrs = [
        "third_party/tree-sitter-kero/bindings/c/tree-sitter-kero.h",
    ] + glob(["third_party/tree-sitter-kero/src/tree_sitter/*.h"]),
    copts = [
        "-std=c17",
    ],
    includes = [
        "third_party/tree-sitter-kero/bindings/c",
        "third_party/tree-sitter-kero/src",
    ],
)

cc_library(
    name = "kero_cpp_tree_sitter",
    srcs = ["src/cpp_tree_sitter/api.cc"],
    hdrs = [
        "src/cpp_tree_sitter/api.h",
    ],
    copts = [
        "-std=c++20",
        "-fno-rtti",
    ],
    includes = [
        "src",
    ],
    deps = [
        ":tree_sitter",
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
        ":kero_cpp_tree_sitter",
        ":tree_sitter_kero",
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
