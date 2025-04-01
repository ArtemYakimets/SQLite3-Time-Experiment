#include "file_read.h"

std::vector<std::string> read_strings_from_file(const std::string& filename) {
    std::ifstream file(filename, std::ios::in);
    if (!file) {
        std::cerr << "Error: cannot open the file" << std::endl;
        return {};
    }

    std::vector<std::string> strings;
    std::string line;
    while (std::getline(file, line)) {
        size_t length = std::stoul(line);
        std::string value;
        if (std::getline(file, value)) {
            strings.push_back(std::to_string(length) + ":" + value);
        }
    }

    file.close();
    return strings;
}