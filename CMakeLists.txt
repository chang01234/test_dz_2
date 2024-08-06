cmake_minimum_required(VERSION 3.22.1)

message("Target: ${CMAKE_BUILD_TYPE}")

# Select toolchain based on build type (ie "test" uses host compiler) - do before creating project
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/tools/toolchain/toolchain_armgnu.cmake")

# Create the project
project($ENV{PROJECT_NAME}) # the project name comes from the build.toml and setup.sh script

# Set variables required for library to configure correctly
set(DOMETIC_NMEA_VER "v2")
set(DOMETIC_HAL_PORT "kv5x")
# SDK drivers the library hal layer will depend on (see Library/halp/port/kv5x/CMakeList.txt for how it is used)
set(DOMETIC_DRIVER_LIB "drivers_lib;device_lib;CMSIS_lib")
set(DOMETIC_DRIVER_INCLUDES "${CMAKE_SOURCE_DIR}/drivers;${CMAKE_SOURCE_DIR}/CMSIS;${CMAKE_SOURCE_DIR}/device")

# Add all subdirectories (other than "tests")
add_subdirectory(app)
add_subdirectory(gen)
add_subdirectory(Library)

# Add exectutable, from startup file
set(CMAKE_EXECUTABLE_SUFFIX ".elf")
add_executable(${PROJECT_NAME} startup/startup_mkv58f24.cpp)

# Link all object libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    app_lib
    gen_lib
    std_lib
    services_lib
    nmea_common_lib
    nmea_lib
    hal_sources_lib
    hal_ports_mcu_lib
    hal_ports_common_lib
    hal_ports_devices_lib
)
