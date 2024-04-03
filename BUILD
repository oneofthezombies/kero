cc_library(
    name = "kero_grammar",
    srcs = [
        "src/grammar/bridge.cc",
        "src/grammar/bridge.h",
        "src/grammar/core.c",
        "src/grammar/core.h",
        "src/grammar/parser.cc",
        "src/grammar/parser.h",
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
