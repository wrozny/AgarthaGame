cmake_minimum_required(VERSION 3.12)
project(AgarthaGame C)

set(CMAKE_C_STANDARD 11)

include(FetchContent)
set(RAYLIB_VERSION 5.5)

FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    FIND_PACKAGE_ARGS ${RAYLIB_VERSION}
)

set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(raylib)

#add_subdirectory(external/raylib)

file(GLOB_RECURSE GAME_SOURCE_FILES src/*.c)
list(REMOVE_ITEM GAME_SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/main.c")

add_executable(AgarthaGame src/main.c ${GAME_SOURCE_FILES})

target_include_directories(AgarthaGame PRIVATE include)
target_link_libraries(AgarthaGame PRIVATE raylib)

if(WIN32 AND (CMAKE_BUILD_TYPE STREQUAL "Debug") AND MSVC)
    target_compile_options(AgarthaGame PRIVATE /fsanitize=address /Zi /MDd)
    target_link_options(AgarthaGame PRIVATE /fsanitize=address)
endif()

if(UNIX AND NOT APPLE)
    target_link_libraries(AgarthaGame PRIVATE m pthread dl)
endif()

if(APPLE)
    target_link_libraries(AgarthaGame "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
endif()