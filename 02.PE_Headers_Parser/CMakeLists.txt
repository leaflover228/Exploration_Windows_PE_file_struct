add_executable(pe_parser
    src/main.cpp
    src/dos_rw.cpp
)

target_include_directories(pe_parser PRIVATE include)