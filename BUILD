cc_library(
    name = "KeroCompileParser",
    srcs = [
        "src/Compile/Parser/Core.c",
        "src/Compile/Parser/Core.h",
        "src/Compile/Parser/NodeKindGenerated.c",
        "src/Compile/Parser/NodeKindGenerated.h",
        "src/Compile/Parser/ParserGenerated.c",
        "src/Compile/Parser/ParserGenerated.h",
        "src/Compile/Parser/ParserGeneratedCInclude.h",
    ],
    hdrs = [
        "src/Compile/Parser/Core.h",
    ],
    copts = [
        "-std=c17",
    ],
    includes = [
        "src",
    ],
)

cc_library(
    name = "tree_sitter_kero",
    srcs = [
        "third_party/tree-sitter-kero/src/parser.c",
        "third_party/tree-sitter-kero/src/tree_sitter/alloc.h",
        "third_party/tree-sitter-kero/src/tree_sitter/array.h",
        "third_party/tree-sitter-kero/src/tree_sitter/parser.h",
    ],
    hdrs = [
        "third_party/tree-sitter-kero/bindings/c/tree-sitter-kero.h",
    ],
    copts = [
        "-std=c17",
    ],
    includes = [
        "third_party/tree-sitter-kero/bindings/c",
        "third_party/tree-sitter-kero/src",
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
    ],
)

cc_library(
    name = "KeroCompileParserFacade",
    srcs = [
        "src/Compile/ParserFacade/ParserFacade.cpp",
    ],
    hdrs = [
        "src/Compile/ParserFacade/ParserFacade.h",
    ],
    copts = [
        "-std=c++20",
        "-fno-rtti",
    ],
    includes = [
        "src",
    ],
    deps = [
        ":KeroCompileParser",
    ],
)

cc_test(
    name = "KeroCompileParserFacade_test",
    srcs = [
        "src/Compile/ParserFacade/ParserFacadeTest.cpp",
    ],
    copts = [
        "-std=c++20",
        "-fno-rtti",
    ],
    deps = [
        ":KeroCompileParserFacade",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "tree_sitter_kero_test",
    srcs = [
        "src/Compile/Parser2/tree_sitter_kero_test.cc",
    ],
    copts = [
        "-std=c++20",
        "-fno-rtti",
    ],
    deps = [
        ":tree_sitter_kero",
        "@googletest//:gtest_main",
    ],
)
