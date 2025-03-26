#include "file_insert.h"

void write_strings_to_file(const std::string& filename, const std::vector<std::string>& strings_vector) {
    std::ofstream file(filename, std::ios::out | std::ios::binary);
    if (!file) {
        std::cerr << "Error: cannot open the file" << std::endl;
        return;
    }

    for (const auto& str : strings_vector) {
        file << str << "\n";  
    }

    file.close();
    std::cout << "File " << filename << " generated" << std::endl;
}