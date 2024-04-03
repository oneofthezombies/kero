cc_library(
    name = "kero_grammar",
    srcs = [
        "src/grammar/c/gen/parser.c",
        "src/grammar/c/gen/parser.h",
        "src/grammar/c/parser_auxil.h",
        "src/grammar/parser.cc",
    ],
    hdrs = [
        "src/grammar/parser.h",
    ],
    copts = ["-std=c++20"],
    includes = ["src"],
    deps = [
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
