cmake_minimum_required(VERSION 3.26)

include(pico_sdk_import.cmake)
include(pico_extras_import_optional.cmake)

project(car_sign C CXX ASM)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 17)

# Pico Libs
pico_sdk_init()

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
)
if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wno-maybe-uninitialized)
endif()

# Third Party Libs
add_subdirectory(lib/cofgifs)

## Car sign
add_executable(car_sign src/main.c
        src/device.h
        src/external.s
        src/external.h)
target_link_libraries(car_sign pico_stdlib cofgifs)

pico_add_extra_outputs(car_sign)