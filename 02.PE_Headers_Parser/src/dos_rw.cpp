#include "dos_rw.hpp"

namespace pe_parser {
    void get_file(char *argv, HANDLE &hfile, HANDLE &hfile_mapping, LPVOID &view_map) {
        std::string FILENAME;
        FILENAME = argv;
        LPCSTR ptr_file = FILENAME.c_str();

        hfile = CreateFileA(ptr_file, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (hfile == INVALID_HANDLE_VALUE) {
            throw std::runtime_error("Failed to open file. Error code: " + std::to_string(GetLastError()));
        }

        hfile_mapping = CreateFileMappingA(hfile, nullptr, PAGE_READONLY, 0, 0, nullptr);
        if (hfile_mapping == nullptr) {
            throw std::runtime_error("Failed to create map file. Error code: " + std::to_string(GetLastError()));
        }

        view_map = MapViewOfFile(hfile_mapping, FILE_MAP_READ, 0, 0, 0);
        if (view_map == nullptr) {
            throw std::runtime_error("Failed map view file. Error code: " + std::to_string(GetLastError()));
        }
    }

    void anal_file(LPVOID ptr_file) {
        PES.magic_addr = reinterpret_cast<PIMAGE_DOS_HEADER>(ptr_file);
        PES.start_nt_addr = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<char*>(ptr_file) + PES.magic_addr->e_lfanew);

        if (PES.magic_addr->e_magic == IMAGE_DOS_SIGNATURE) {
            std::cout << "MZ was found\n";
            if(PES.start_nt_addr->Signature == IMAGE_NT_SIGNATURE) {
                std::cout << "PE Signature was found\n";
            }
            else {
                std::cout << "Not found\n";
            }
        }
        else {
            std::cout << "It is not executable WIN32 file\n";
        }
    }

    void read_number_sections(const PEFileContext& ctx) {
        char* base_ptr = reinterpret_cast<char*>(&(ctx.start_nt_addr->OptionalHeader));
        PIMAGE_SECTION_HEADER section_header = reinterpret_cast<PIMAGE_SECTION_HEADER>(base_ptr + ctx.start_nt_addr->FileHeader.SizeOfOptionalHeader);

        for (size_t i = 0; i < ctx.start_nt_addr->FileHeader.NumberOfSections; ++i) {
            std::string sec_name(reinterpret_cast<char*>(section_header[i].Name), 8);
    
            std::cout << "Section [" << i << "]: " << sec_name 
              << " | Virtual Size: " << section_header[i].Misc.VirtualSize 
              << " | Raw Address: " << section_header[i].PointerToRawData << "\n";
        }
    }

    void close_file_mapping(const PEFileContext& ctx) {
        UnmapViewOfFile(ctx.ptr_mapfile);
        CloseHandle(ctx.mapfile);
        CloseHandle(ctx.file);
    }
}