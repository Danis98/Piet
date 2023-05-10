cc_library(
   name = "lib",
   srcs = ["lib/libpng16.lib"],
   hdrs = [
       "include/png.h",
       "include/pngconf.h",
       "include/pngdebug.h",
       "include/pnginfo.h",
       "include/pnglibconf.h",
       "include/pngpriv.h",
       "include/pngstruct.h"
   ],
   deps = [
       "@zlib//:lib"
   ],
   visibility = ["//visibility:public"],
)