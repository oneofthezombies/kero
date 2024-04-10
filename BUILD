cc_library(
    name = "KeroCompileParser",
    srcs = [
        "src/Compile/Parser/Core.c",
        "src/Compile/Parser/Core.h",
        "src/Compile/Parser/NodeKindGenerated.c",
        "src/Compile/Parser/NodeKindGenerated.h",
        "src/Compile/Parser/ParserGenerated.c",
        "src/Compile/Parser/ParserGenerated.h",
        "src/Compile/Parser/ParserGeneratedCInclude.h",
    ],
    hdrs = [
        "src/Compile/Parser/Core.h",
    ],
    copts = [
        "-std=c17",
    ],
    includes = [
        "src",
    ],
)

cc_library(
    name = "KeroCompileParserFacade",
    srcs = [
        "src/Compile/ParserFacade/ParserFacade.cpp",
    ],
    hdrs = [
        "src/Compile/ParserFacade/ParserFacade.h",
    ],
    copts = [
        "-std=c++20",
        "-fno-rtti",
    ],
    includes = [
        "src",
    ],
    deps = [
        ":KeroCompileParser",
    ],
)

cc_test(
    name = "KeroCompileParserFacade_test",
    srcs = [
        "src/Compile/ParserFacade/ParserFacadeTest.cpp",
    ],
    copts = [
        "-std=c++20",
        "-fno-rtti",
    ],
    deps = [
        ":KeroCompileParserFacade",
        "@googletest//:gtest_main",
    ],
)
