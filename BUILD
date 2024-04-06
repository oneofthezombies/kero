cc_library(
    name = "kero_grammar",
    srcs = [
        "src/grammar/parser.cc",
    ] + glob(["third_party/PEGTL-3.2.7/include/**/*.hpp"]),
    hdrs = [
        "src/grammar/parser.h",
    ],
    copts = [
        "-std=c++20",
    ],
    includes = [
        "src",
        "third_party/PEGTL-3.2.7/include",
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
