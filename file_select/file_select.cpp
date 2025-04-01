#include "file_select.h"

std::vector<std::string> read_filtered_strings_from_file(const std::string& filename, const std::string& substring) {
    std::ifstream file(filename, std::ios::in);
    if (!file) {
        std::cerr << "Error: cannot open the file" << std::endl;
        return {};
    }

    std::vector<std::string> filtered_strings;
    std::string line;
    
    while (std::getline(file, line)) {

        size_t colon_pos = line.find(':');
        std::string length_str = line.substr(0, colon_pos);
        std::string value = line.substr(colon_pos + 1);

        char* endptr;
        size_t length = std::strtoul(length_str.c_str(), &endptr, 10);

        if (value.find(substring) != std::string::npos) {
            filtered_strings.push_back(std::to_string(length) + ":" + value);
        }
    }

    file.close();

    return filtered_strings;
}

