cmake_minimum_required(VERSION 3.10)
project(booksystem)

set(CMAKE_CXX_STANDARD 11)
set(ENV{LANG} en_US.UTF-8)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
include_directories(include)
file(GLOB_RECURSE SRC_LIST "src/*.cpp")

# 指定 SDL2 和 SDL2_ttf 的路径
set(SDL2_PATH "${CMAKE_SOURCE_DIR}/thirdlib/SDL2-2.30.3/x86_64-w64-mingw32")
set(SDL2_TTF_PATH "${CMAKE_SOURCE_DIR}/thirdlib/SDL2_ttf-2.22.0/x86_64-w64-mingw32")

# 包含 SDL2 和 SDL2_ttf 的头文件路径
include_directories(${SDL2_PATH}/include ${SDL2_PATH}/include/SDL2)
include_directories(${SDL2_TTF_PATH}/include ${SDL2_TTF_PATH}/include/SDL2)
# 链接 SDL2 和 SDL2_ttf 的库文件路径
link_directories(${SDL2_PATH}/lib ${SDL2_TTF_PATH}/lib)

add_executable(booksystem ${SRC_LIST})

# 链接 SDL2 和 SDL2_ttf 库
target_link_libraries(booksystem SDL2 SDL2_ttf)

# 将 DLL 文件复制到目标目录
add_custom_command(TARGET booksystem POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SDL2_PATH}/bin/SDL2.dll
        ${SDL2_TTF_PATH}/bin/SDL2_ttf.dll
        $<TARGET_FILE_DIR:booksystem>
)