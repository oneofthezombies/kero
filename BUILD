cc_library(
    name = "kero_grammar_parser",
    srcs = [
        "src/grammar/parser.cc",
        "src/grammar/parser_auxil.h",
        "src/grammar/parser_generated.c",
        "src/grammar/parser_generated.h",
        "src/grammar/parser_generated_c_include.h",
    ],
    hdrs = [
        "src/grammar/parser.h",
    ],
    copts = [
        "-std=c17",
    ],
    includes = [
        "src",
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
