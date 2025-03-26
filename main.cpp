#include <chrono>

#include "file_insert/file_insert.h"
#include "sqlite3_insert/sqlite3_insert.h"

int main() {
    size_t total_size = 500 * 1024 * 1024; // 500 MB
    size_t max_length = 100;

    std::cout << "Start working with file" << std::endl;
    auto start_db = std::chrono::high_resolution_clock::now();
    write_random_strings_to_db("strings.db", total_size, max_length);
    auto end_db = std::chrono::high_resolution_clock::now();

    std::cout << "Start working with database" << std::endl;
    auto start_file = std::chrono::high_resolution_clock::now();
    write_random_strings_to_file("strings.txt", total_size, max_length);
    auto end_file = std::chrono::high_resolution_clock::now();

    return 0;
}