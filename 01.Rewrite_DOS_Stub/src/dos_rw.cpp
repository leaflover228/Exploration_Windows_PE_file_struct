#include "dos_rw.hpp"

void write_key_in_dos_stub(const char* key) {
    char* base_addr = reinterpret_cast<char*>(GetModuleHandle(nullptr));
    DWORD old_ptr;

    VirtualProtect(base_addr + 0x40, 32, PAGE_READWRITE, &old_ptr);
    memset(base_addr + 0x40, 0, 32);
    std::memmove(base_addr + 0x40, key, strlen(key));
    VirtualProtect(base_addr + 0x40, 32, PAGE_READONLY, &old_ptr);
}

void clear_key(char* base_addr) {
    DWORD old_ptr;
    VirtualProtect(base_addr + 0x40, 32, PAGE_READWRITE, &old_ptr);
    memset(base_addr + 0x40, 0, 32);
    VirtualProtect(base_addr + 0x40, 32, PAGE_READONLY, &old_ptr);
}