package(default_visibility = ["//visibility:public"])

cc_library(
    name = "peg_parser",
    srcs = [
        "log.cc",
        "peg_parser.cc",
    ],
    hdrs = [
        "log.h",
        "peg_parser.h",
    ],
)

cc_test(
    name = "peg_parser_test",
    size = "small",
    srcs = ["peg_parser_test.cc"],
    deps = [
        ":peg_parser",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_binary(
    name = "peg_parser_cli",
    srcs = ["peg_parser_cli.cc"],
    toolchains = ["//toolchain:llvm_local"],
    deps = [":peg_parser"],
)
