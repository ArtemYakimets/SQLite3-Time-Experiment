#include "file_insert.h"

void write_random_strings_to_file(const std::string& filename, size_t total_size_bytes, size_t max_string_length) {
    std::ofstream file(filename, std::ios::out | std::ios::binary);
    if (!file) {
        std::cerr << "Error: cannot open the file" << std::endl;
        return;
    }
    
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_int_distribution<size_t> length_dist(0, max_string_length);
    
    size_t current_size = 0;
    while (current_size < total_size_bytes) {
        if (current_size % (10 * 1024 * 1024) == 0) {
            std::cout << "Current size: " << current_size * 1024 * 1024 << " MB" << std::endl;
        }
        size_t length = length_dist(rng);
        std::string random_string = generate_random_string(length);
        file << length << "\n" << random_string << "\n";
        current_size += std::to_string(length).size() + 1 + random_string.size() + 1; 
    }
    file.close();
    std::cout << "File " << filename << " generated" << std::endl;
}