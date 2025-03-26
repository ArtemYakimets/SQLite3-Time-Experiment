#include <chrono>
#include <vector>

#include "file_insert/file_insert.h"
#include "sqlite3_insert/sqlite3_insert.h"
#include "generate_string/generate_string.h"

int main() {

    std::vector<std::string> strings_vector = generate_strings(3000, 800000);
    
    std::cout << "Start working with database" << std::endl;
    auto start_db = std::chrono::high_resolution_clock::now();
    write_strings_to_db("strings.db", strings_vector);
    auto end_db = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_db = end_db - start_db;
    std::cout << "Database time: " << duration_db.count() << " seconds" << std::endl;

    std::cout << "Start working with file" << std::endl;
    auto start_file = std::chrono::high_resolution_clock::now();
    write_strings_to_file("strings.txt", strings_vector);
    auto end_file = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_file = end_file - start_file;
    std::cout << "File time: " << duration_file.count() << " seconds" << std::endl;
    
    return 0;
}