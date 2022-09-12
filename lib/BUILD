package(default_visibility = ["//visibility:public"])

cc_library(
    name="piet-lib",
    srcs=[
        "codel.cpp",
        "color.cpp",
        "image_read.cpp"
    ],
    hdrs=[
        "codel.h",
        "color.h",
        "image.h",
        "state.h"
    ],
    deps=[
        "@org_libpng_libpng//:libpng",
    ],
    copts=[
        "/std:c++20",
    ],
)