cmake_minimum_required(VERSION 3.16)
project(PE_Headers CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (MSVC) 
    add_compile_options(/W4 /EHsc)
endif()

add_subdirectory(01.Rewrite_DOS_Stub)
add_subdirectory(02.PE_Headers_Parser)