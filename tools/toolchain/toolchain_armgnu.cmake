set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

# Append current directory to CMAKE_MODULE_PATH for making device specific cmake modules visible
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

# Target definition
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

# ---------------------------------------------------------------------------------------
# Set toolchain paths
# ---------------------------------------------------------------------------------------
set(TOOLCHAIN arm-none-eabi)

if(NOT DEFINED TOOLCHAIN_PREFIX)
    if(CMAKE_HOST_SYSTEM_NAME STREQUAL Linux)
        set(TOOLCHAIN_PREFIX "/opt/gcc-arm-none-eabi")
    elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL Darwin)
        set(TOOLCHAIN_PREFIX "/arm-toolchain/arm-gnu-toolchain-12.2.rel1-x86_64-arm-none-eabi")
    elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL Windows)
        set(TOOLCHAIN_PREFIX "C:/arm-toolchain/arm-gnu-toolchain-12.2.rel1-mingw-w64-i686-arm-none-eabi")
    else()
        set(TOOLCHAIN_PREFIX "/usr")
        message(STATUS "No TOOLCHAIN_PREFIX specified, using default: " ${TOOLCHAIN_PREFIX})
    endif()
endif()

set(TOOLCHAIN_BIN_DIR ${TOOLCHAIN_PREFIX}/bin)
set(TOOLCHAIN_INC_DIR ${TOOLCHAIN_PREFIX}/${TOOLCHAIN}/include)

# set(TOOLCHAIN_INC_NEWLIB${TOOLCHAIN_PREFIX}/${TOOLCHAIN}/include/newlib-nano)
set(TOOLCHAIN_LIB_DIR ${TOOLCHAIN_PREFIX}/${TOOLCHAIN}/lib)

# Set system depended extensions
if(WIN32)
    set(TOOLCHAIN_EXT ".exe")
else()
    set(TOOLCHAIN_EXT "")
endif()

# Perform compiler test with static library
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# ---------------------------------------------------------------------------------------
# Set compiler flags
# ---------------------------------------------------------------------------------------

# Object build options
# -O0                   No optimizations, reduce compilation time and make debugging produce the expected results.
# -mthumb               Generat thumb instructions.
# -fno-builtin          Do not use built-in functions provided by GCC.
# -Wall                 Print only standard warnings, for all use Wextra
# -ffunction-sections   Place each function item into its own section in the output file.
# -fdata-sections       Place each data item into its own section in the output file.
# -fomit-frame-pointer  Omit the frame pointer in functions that don't need one.
# -mabi=aapcs           Defines enums to be a variable sized type.
# -Og                   Enables optimizations that do not interfere with debugging.
# -g                    Produce debugging information in the operating system's native format.
# -Os                   Optimize for size. -Os enables all -O2 optimizations, O3 is O2 plus some.
# -D                    Define that can be used in the code
# NOTE 1: if using C++ instead of C, the variable name becomes CMAKE_CXX_FLAGS and so on
# NOTE 2: Use NEW_LIB and NEW_LIB_NANO instead of RED_LIB since RED_LIB is a MCU Expresso specific library

# flags common to both debug and release compilation
set(CMAKE_C_FLAGS "-mcpu=cortex-m7 -mthumb -mfpu=fpv5-sp-d16 -fno-common -fmerge-constants -mfloat-abi=hard -g3 -fno-builtin -Wall -ffunction-sections -fdata-sections -fomit-frame-pointer -D__NEWLIB__ -std=gnu17 " CACHE INTERNAL "C Compiler options")

# flags specific to debug compilation
set(CMAKE_C_FLAGS_DEBUG "-Og -g -DNDEBUG" CACHE INTERNAL "C Compiler options for debug build type")

# flags specific to release compilation
set(CMAKE_C_FLAGS_RELEASE "-O3 -flto -ffat-lto-objects -DDEBUG" CACHE INTERNAL "C Compiler options for release build type")

# ---------------------------------------------------------------------------------------
# Set linker flags
# ---------------------------------------------------------------------------------------

# location of linker script
set(LINKER_FILE "${CMAKE_SOURCE_DIR}/tools/build/${PROJECT_NAME}.ld")

# Linker build options
# -Wl,--gc-sections     Perform the dead code elimination.
# --specs=nano.specs    Link with newlib-nano.
# --specs=nosys.specs   No syscalls, provide empty implementations for the POSIX system calls.
# -flto                 Runs the standard link-time optimizer. 
# -ffat-lto-objects     Pairs with this and is necessary but not fully understood.
# NOTE: make sure you use "-T${LINKER_FILE}" and "-Map=${PROJECT_NAME}.map" instead of the default one provided by MCU Expresso

# flags common to both debug and release linker
set(CMAKE_EXE_LINKER_FLAGS "-T${LINKER_FILE} -mthumb -nostdlib -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -specs=nano.specs -specs=nosys.specs -lc -lm -Wl,-Map=${PROJECT_NAME}.map,--cref -Wl,--gc-sections,--sort-section=alignment -Xlinker -print-memory-usage -Xlinker" CACHE INTERNAL "Linker options")

# flags specific to debug linker
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "" CACHE INTERNAL "Linker options for debug build type")

# flags specific to release linker
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-flto -ffat-lto-objects" CACHE INTERNAL "Linker options for release build type")

# ---------------------------------------------------------------------------------------
# Set compilers
# ---------------------------------------------------------------------------------------
set(CMAKE_C_COMPILER ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-gcc${TOOLCHAIN_EXT} CACHE INTERNAL "C Compiler")
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-g++${TOOLCHAIN_EXT} CACHE INTERNAL "C++ Compiler")
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-gcc${TOOLCHAIN_EXT} CACHE INTERNAL "ASM Compiler")

set(CMAKE_FIND_ROOT_PATH ${TOOLCHAIN_PREFIX}/${${TOOLCHAIN}} ${CMAKE_PREFIX_PATH})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)