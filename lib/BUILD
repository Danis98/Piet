load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "piet_lib",
    srcs = [
        "codel.cpp",
        "color.cpp",
        "image_read.cpp",
        "state.cpp",
        "util/modular_counter.cpp"
    ],
    hdrs = [
        "codel.h",
        "color.h",
        "image.h",
        "state.h",
        "util/modular_counter.h",
        "util/enum_cast.h"
    ],
    deps = [
        "@libpng//:lib"
    ],
    copts = ["/std:c++20"],
    visibility = ["//visibility:public"]
)