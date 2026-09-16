#include "dos_rw.hpp"

int32_t main(int argc, char** argv) {
    HANDLE file = nullptr;
    HANDLE mapfile = nullptr;
    LPVOID ptr_mapfile = nullptr;

    if (argc > 2) {
        std::cout << "fuck u, so many shit\n";
        std::exit(EXIT_FAILURE);
    }
    else if (argc < 2) {
        std::cout << "Usage: pe_parser <path_to_file>\n";
    }

    try {
        get_file(argv[1], file, mapfile, ptr_mapfile);
        anal_file(file, mapfile, ptr_mapfile);
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return 0;
}