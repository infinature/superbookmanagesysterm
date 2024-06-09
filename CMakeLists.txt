cmake_minimum_required(VERSION 3.10)
project(booksystem)

set(CMAKE_CXX_STANDARD 11)
set(ENV{LANG} en_US.UTF-8)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
include_directories(include)
file(GLOB_RECURSE SRC_LIST "src/*.cpp")

add_executable(booksystem ${SRC_LIST})

set(LIBRARY_PATH "${CMAKE_SOURCE_DIR}/libs")

add_custom_command(TARGET booksystem POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${LIBRARY_PATH}/SDL2_ttf.dll"
    "${LIBRARY_PATH}/SDL2.dll"
    $<TARGET_FILE_DIR:booksystem>)