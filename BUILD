cc_library(
    name = "kero_grammar_parser",
    srcs = [
        "src/grammar/parser/generated.c",
        "src/grammar/parser/generated.h",
        "src/grammar/parser/generated-c-inl.h",
    ] + glob(["third_party/PEGTL-3.2.7/include/**/*.hpp"]),
    hdrs = [
        "src/grammar/parser/core.h",
    ],
    copts = ["-std=c17"],
    includes = [
        "src",
        "third_party/PEGTL-3.2.7/include",
    ],
)

cc_library(
    name = "kero_grammar",
    srcs = [
        "src/grammar/parser_facade.cc",
        "src/grammar/parser_facade.h",
    ],
    hdrs = [
    ],
    copts = ["-std=c++20"],
    includes = ["src"],
    deps = [
        ":kero_grammar_parser",
    ],
)

cc_test(
    name = "kero_grammar_test",
    srcs = [
        "src/grammar/parser_test.cc",
    ],
    deps = [
        ":kero_grammar",
        "@googletest//:gtest_main",
    ],
)
