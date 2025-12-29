cmake_minimum_required(VERSION 3.10)

project(scrabble C)
set(CMAKE_C_STANDARD 99)

include_directories(.)
file(GLOB SOURCES "*.c")
file(GLOB HEADERS "*.h")


set(COMMON_COMPILE_OPTIONS -O2 -DNDEBUG -s -flto -Wall -Wextra -std=c99 -fno-strict-aliasing)
set(COMMON_LIBS m raylib GL pthread dl rt)

add_executable(scrabble ${SOURCES} ${HEADERS})

target_compile_options(scrabble PRIVATE ${COMMON_COMPILE_OPTIONS})

target_link_libraries(scrabble ${COMMON_LIBS})

