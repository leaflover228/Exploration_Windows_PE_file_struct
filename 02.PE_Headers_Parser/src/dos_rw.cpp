#include "dos_rw.hpp"

void get_file(int count_arg, char *argv[], HANDLE &file, HANDLE &hfile_mapping, LPVOID &view_map) {
    std::string FILENAME;

    for (size_t id_x = 1; id_x < count_arg; id_x++) {
        FILENAME = argv[id_x];
        LPCSTR ptr_file = FILENAME.c_str();
        
        HANDLE hfile = CreateFileA(ptr_file, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
        
        if (hfile == INVALID_HANDLE_VALUE) {
            std::cerr << "Please kick yourself faggot, I hate you and your parents!\n" << GetLastError() << "\n";
            exit(EXIT_FAILURE);
        }

        file = hfile;
        hfile_mapping = CreateFileMappingA(file, nullptr, PAGE_READONLY, 0, 0, nullptr);

        if (hfile_mapping == nullptr) {
            std::cerr << "I wanna rape your ass\n" << GetLastError() << "\n";
            exit(EXIT_FAILURE);
        }

        view_map = MapViewOfFile(hfile_mapping, FILE_MAP_READ, 0, 0, 0);

        if (view_map == nullptr) {
            std::cerr << GetLastError() << "\n";
            exit(EXIT_FAILURE);
        }
    }
    std::cout << "File handle: " << file << "\n";
}

void anal_file(HANDLE file, HANDLE mapfile, LPVOID ptr_file) {
    PIMAGE_DOS_HEADER magic_addr = reinterpret_cast<PIMAGE_DOS_HEADER>(ptr_file);
    PIMAGE_NT_HEADERS start_nt_addr = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<char*>(ptr_file) + (*magic_addr).e_lfanew);

    if ((*magic_addr).e_magic == IMAGE_DOS_SIGNATURE) {
        std::cout << "MZ was found\n";
        if((*start_nt_addr).Signature == IMAGE_NT_SIGNATURE) {
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