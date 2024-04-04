cc_library(
    name = "kero_grammar_parser",
    srcs = [
        "src/grammar/parser/generated.c",
        "src/grammar/parser/generated.h",
        "src/grammar/parser/inline.h",
    ],
    hdrs = [
        "src/grammar/parser/core.h",
    ],
    copts = ["-std=c17"],
    includes = ["src"],
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
    copts = [
        "-std=c++20",
    ],
    deps = [
        ":kero_grammar",
        "@googletest//:gtest_main",
    ],
)
