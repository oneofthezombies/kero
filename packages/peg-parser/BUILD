cc_library(
    name = "peg-parser",
    srcs = ["peg-parser.cc"],
    hdrs = ["peg-parser.h"],
)

cc_binary(
    name = "peg-parser-cli",
    srcs = ["peg-parser-cli.cc"],
    deps = [
        ":peg-parser",
    ],
)
