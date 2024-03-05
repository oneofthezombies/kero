cc_library(
    name = "peg_parser",
    srcs = ["peg_parser.cc", "log.cc"],
    hdrs = ["peg_parser.h", "log.h"],
)

cc_test(
    name = "peg_parser_test",
    size = "small",
    srcs = ["peg_parser_test.cc"],
    deps = ["@com_google_googletest//:gtest_main", ":peg_parser"],
)

cc_binary(
    name = "peg_parser_main",
    srcs = ["peg_parser_main.cc"],
    toolchains = ["//toolchain:llvm_local"],
    deps = [":peg_parser"],
)
