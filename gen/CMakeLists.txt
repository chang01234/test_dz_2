file(GLOB _HDRS "*.h*")
file(GLOB _SRCS "*.c*")

add_library(gen_lib OBJECT "${_SRCS}" "${_HDRS}")

target_link_libraries(gen_lib PRIVATE
    std_lib
    services_lib
    nmea_common_lib
    nmea_lib
)

target_include_directories(gen_lib PRIVATE
    "../lib/std/sources"
    "../lib/services/sources"
    "../lib/nmea/sources/common"
    "../lib/nmea/sources/v2"
)