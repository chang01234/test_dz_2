file(GLOB _HDRS "*.h*")
file(GLOB _SRCS "*.c*")

add_library(app_lib OBJECT "${_SRCS}" "${_HDRS}")

target_link_libraries(app_lib PRIVATE
    std_lib
    services_lib
    hal_sources_lib
    hal_ports_mcu_lib
    hal_ports_common_lib
    hal_ports_devices_lib
    nmea_common_lib
    nmea_lib
)

target_include_directories(app_lib PRIVATE
    "../lib/std/sources"
    "../lib/hal/ports/kv5x"
    "../lib/hal/ports/devices"
    "../lib/hal/ports/common"
    "../lib/hal/sources"
    "../lib/services/sources"
    "../lib/nmea/sources/common"
    "../lib/nmea/sources/v2"
)
