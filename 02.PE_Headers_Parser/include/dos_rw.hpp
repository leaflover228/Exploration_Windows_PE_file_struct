#ifndef DOS_RW_HPP
#define DOS_RW_HPP

#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <windows.h>
#include <string>

struct PEFileContext {
    HANDLE file = nullptr;
    HANDLE mapfile = nullptr;
    LPVOID ptr_mapfile = nullptr;
    PIMAGE_DOS_HEADER magic_addr = nullptr;
    PIMAGE_NT_HEADERS start_nt_addr = nullptr;
};

using pe = PEFileContext;
extern pe PES;

namespace pe_parser {
    void get_file(char *argv, HANDLE &hfile, HANDLE &hfile_mapping, LPVOID &view_map);
    void anal_file(LPVOID ptr_file);

    // void read_dos_stub(const PEFileContext& ctx);
    // void read_dos_header(const PEFileContext& ctx);
    // void read_nt_headers(const PEFileContext& ctx);

    // void read_data_dirs(const PEFileContext& ctx);

    void read_number_sections(const PEFileContext& ctx);
    void close_file_mapping(const PEFileContext& ctx);

    // void read_secticon_headers(const PEFileContext& ctx);
    // void read_section_text(const PEFileContext& ctx);
    // void read_section_data(const PEFileContext& ctx);
    // void read_section_rdata(const PEFileContext& ctx);
    // void read_section_rsrc(const PEFileContext& ctx);
}

#endif