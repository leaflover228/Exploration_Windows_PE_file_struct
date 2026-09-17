#include "dos_rw.hpp"

pe PES;

int32_t main(int argc, char** argv) {
    if (argc > 2) {
        std::cout << "fuck u, so many shit\n";
        std::exit(EXIT_FAILURE);
    }
    else if (argc < 2) {
        std::cout << "Usage: pe_parser <path_to_file>\n";
        std::exit(EXIT_FAILURE);
    }

    try {
        pe_parser::get_file(argv[1], PES.file, PES.mapfile, PES.ptr_mapfile);
        pe_parser::anal_file(PES.ptr_mapfile);
        pe_parser::read_number_sections(PES);
        pe_parser::close_file_mapping(PES);
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return 0;
}