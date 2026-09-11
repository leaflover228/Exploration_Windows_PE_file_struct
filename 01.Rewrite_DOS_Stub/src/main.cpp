#include "dos_rw.hpp"

int32_t main() {
    char *base_addr = reinterpret_cast<char*>(GetModuleHandle(nullptr));
    const char* embedded_key = base_addr + 0x40;
    std::string key_guess = {};
    bool key_is_true;

    std::cout << "Enter key guess: ";
    std::cin >> key_guess;

    write_key_in_dos_stub("something");
    key_is_true = (key_guess.compare(embedded_key) == 0) ? true : false;
    std::cout << (key_is_true ? "YES\n" : "NO\n");
    clear_key(base_addr);
    std::cout << "Key was cleared from RAM\n";
    return 0;
}