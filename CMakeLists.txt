cmake_minimum_required(VERSION 3.22)
project(Apc_binary_files_exc)

set(CMAKE_CXX_STANDARD 20)

add_executable(Apc_binary_files_exc main.cpp
        student.h
        person.h
        person.cpp
        TextFileSerializer.h)
target_compile_options(Apc_binary_files_exc PRIVATE
        $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -pedantic>
        $<$<CXX_COMPILER_ID:MSVC>: /W4>
        $<$<CXX_COMPILER_ID:GNU,Clang>:$<$<CONFIG:Debug>:-Og -g>>
)
