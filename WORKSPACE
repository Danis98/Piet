
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "org_libpng_libpng",
    build_file = "//bazel:libpng.BUILD",
    sha256 = "7f415186d38ca71c23058386d7cf5135c8beda821ee1beecdc2a7a26c0356615",
    strip_prefix = "libpng-1.2.57",
    urls = [
        "https://mirror.bazel.build/github.com/glennrp/libpng/archive/v1.2.57.tar.gz",
        "https://github.com/glennrp/libpng/archive/v1.2.57.tar.gz",
    ],
)

http_archive(
    name = "net_zlib_zlib",
    sha256 = "6d4d6640ca3121620995ee255945161821218752b551a1a180f4215f7d124d45",
    build_file = "//bazel:zlib.BUILD",
    strip_prefix = "zlib-cacf7f1d4e3d44d871b605da3b647f07d718623f",
    urls = [
        "https://mirror.bazel.build/github.com/madler/zlib/archive/cacf7f1d4e3d44d871b605da3b647f07d718623f.tar.gz",
        "https://github.com/madler/zlib/archive/cacf7f1d4e3d44d871b605da3b647f07d718623f.tar.gz",
    ],
)