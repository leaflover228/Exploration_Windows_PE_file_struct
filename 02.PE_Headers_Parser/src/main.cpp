#include "dos_rw.hpp"

int32_t main(int argc, char** argv) {
    HANDLE file = nullptr;
    HANDLE mapfile = nullptr;
    LPVOID ptr_mapfile = nullptr;

    if (argc > 2) {
        std::cout << "fuck u, so many shit\n";
        std::exit(EXIT_FAILURE);
    }

    get_file(argc, argv, file, mapfile, ptr_mapfile);
    anal_file(file, mapfile, ptr_mapfile);
    return 0;
}