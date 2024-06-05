cmake_minimum_required(VERSION 3.10)
project(booksystem)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
include_directories(include)
file(GLOB_RECURSE SRC_LIST "src/*.cpp")

add_executable(booksystem ${SRC_LIST})