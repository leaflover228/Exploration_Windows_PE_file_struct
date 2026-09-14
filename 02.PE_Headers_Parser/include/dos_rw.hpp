#pragma once

#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <windows.h>
#include <string>

void get_file(int count_arg, char *argv[], HANDLE &hfile, HANDLE &mapfile, LPVOID &ptr_mapfile);
void anal_file(HANDLE file, HANDLE mapfile, LPVOID ptr_file);

void read_dos_stub();
void read_dos_header();
void read_nt_headers();

void read_data_dirs();

void read_secticon_headers();
void read_section_text();
void read_section_data();
void read_section_rdata();
void read_section_rsrc();