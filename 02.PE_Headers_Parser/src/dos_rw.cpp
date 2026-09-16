#include "dos_rw.hpp"

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
    std::cout << "File handle: " << hfile << "\n";
}

void anal_file(HANDLE file, HANDLE mapfile, LPVOID ptr_file) {
    auto* magic_addr = reinterpret_cast<PIMAGE_DOS_HEADER>(ptr_file);
    auto* start_nt_addr = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<char*>(ptr_file) + (*magic_addr).e_lfanew);

    if (magic_addr->e_magic == IMAGE_DOS_SIGNATURE) {
        std::cout << "MZ was found\n";
        if(start_nt_addr->Signature == IMAGE_NT_SIGNATURE) {
            std::cout << "PE Signature was found\n";
        }
        else {
            std::cout << "Not found\n";
        }
    }
    else {
        std::cout << "Kill yourself\n";
    }

    UnmapViewOfFile(ptr_file);
    CloseHandle(mapfile);
    CloseHandle(file);
}