cc_library(
    name = "KeroGrammarParser",
    srcs = [
        "src/Grammar/NodeKindGenerated.h",
        "src/Grammar/NodeKindUtilGenerated.cpp",
        "src/Grammar/NodeKindUtilGenerated.h",
        "src/Grammar/Parser.cpp",
        "src/Grammar/ParserAuxil.h",
        "src/Grammar/ParserGenerated.c",
        "src/Grammar/ParserGenerated.h",
        "src/Grammar/ParserGeneratedCInclude.h",
    ],
    hdrs = [
        "src/Grammar/Parser.h",
    ],
    copts = [
        "-std=c17",
    ],
    includes = [
        "src",
    ],
)

cc_test(
    name = "KeroGrammarTest",
    srcs = [
        "src/Grammar/ParserTest.cpp",
    ],
    deps = [
        ":KeroGrammarParser",
        "@googletest//:gtest_main",
    ],
)
