#include <bits/stdint-uintn.h>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ios>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>
#include <stdint.h>
#include <stdlib.h>

int main (int argc, const char** argv) {
    if (argc < 5) {
        std::cerr << "Not enough args. [start] [end] [code] [file-to-apply-to]\n";
        return 1;
    }
    std::cout << std::hex;
    std::cerr << std::hex;

    // Ugh, I can't find a good function to convert a char* to a number
    // that supports hex. Seriously?
    // Also, it should auto detect... ugh. May write my own utility sometime.
    const std::string start_addr_text = argv[1];
    const std::string end_addr_text = argv[2];
    const uint32_t start_addr = std::stoul(start_addr_text, nullptr, 16);
    const uint32_t end_addr = std::stoul(end_addr_text, nullptr, 16);

    if (start_addr >= end_addr) {
        std::cerr << "Incorrect range. Start was bigger/equivalent to the end address.\n";
        return 2;
    }

    // if (start_addr >= 0x00400000 || end_addr >= 0x00400000) {
    //     std::cerr << "You gave an address that was greater than 0x00400000. Did you mean to subtract that from the address to get the correct file address?\n";
    //     return 3;
    // }

    const uint32_t size = end_addr - start_addr;
    const char* filename = argv[3];
    const char* output_filename = argv[4];

    // std::cout << std::hex << start_addr << "-" << end_addr << " (" << size << ") with " << filename << "\n";

    // std::cout << "Installing patch on program..\n";

    std::filesystem::path path{filename};
    auto code_size = std::filesystem::file_size(path);
    // std::cout << "\t: " << code_size << "\n";
    if (code_size > size) {
        std::cerr << "Code size was too large! " << code_size << "/" << size << "\n";
        return 4;
    }

    auto executable_size = std::filesystem::file_size(output_filename);
    if (start_addr >= executable_size || end_addr > executable_size) {
        std::cerr << "Address was outside of file, failure.\n";
        return 9;
    }

    char* env_log_size = getenv("LOG_SIZE");
    if (env_log_size != nullptr && env_log_size[0] == '1') {
        std::cout << "Code Size: " << code_size << "/" << size << "\n";
    }

    // I love that the fstream is considered to be over a char
    // but if you try making it use a uint8_t (you know, the sensible type to represent a
    // byte with) then it combusts.
    // and so i have to rely on the implicit cast in the vector constructor
    std::fstream code_file(filename, std::ios::in | std::ios::binary);
    std::vector<uint8_t> code((std::istreambuf_iterator<char>(code_file)), std::istreambuf_iterator<char>());
    if (code.size() > size) {
        std::cerr << "Code size was too large (" << code.size() << "/" << size << "), and we only noticed this after loading the file!\n";
        return 5;
    }

    // std::cout << "Writing to executable\n";
    std::fstream executable(output_filename, std::ios::binary | std::ios::in | std::ios::out);
    executable.seekp(start_addr);
    if (executable.fail()) {
        std::cerr << "Failed to seek\n";
        return 6;
    }
    executable.write(reinterpret_cast<const char*>(code.data()), code.size());
    if (executable.fail() || executable.bad()) {
        std::cerr << "Failed to write data\n";
        return 7;
    }
    executable.flush();
    if (executable.fail() || executable.bad()) {
        std::cerr << "Failed to flush data\n";
        return 8;
    }
    return 0;
}