add_executable(rewrite_dos_stub
    src/main.cpp
    src/dos_rw.cpp
)

target_include_directories(rewrite_dos_stub PRIVATE include)