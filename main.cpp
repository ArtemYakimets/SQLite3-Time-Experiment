#include <chrono>
#include <vector>

#include "file_insert/file_insert.h"
#include "sqlite3_insert/sqlite3_insert.h"
#include "file_read/file_read.h"
#include "sqlite3_read/sqlite3_read.h"
#include "generate_string/generate_string.h"

int main() {

    std::vector<std::string> strings_vector = generate_strings(3000, 800000);
    
    std::cout << "Start insertion in database" << std::endl;
    auto start_insertion_db = std::chrono::high_resolution_clock::now();
    write_strings_to_db("strings.db", strings_vector);
    auto end_insertion_db = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_insertion_db = end_insertion_db - start_insertion_db;
    std::cout << "Database insertion time: " << duration_insertion_db.count() << " seconds" << std::endl;

    std::cout << "Start insertion in file" << std::endl;
    auto start_insertion_file = std::chrono::high_resolution_clock::now();
    write_strings_to_file("strings.txt", strings_vector);
    auto end_insertion_file = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_insertion_file = end_insertion_file - start_insertion_file;
    std::cout << "File insertion time: " << duration_insertion_file.count() << " seconds" << std::endl;

    std::cout << "Start reading from database" << std::endl;
    auto start_reading_db = std::chrono::high_resolution_clock::now();
    std::vector<std::string> strings = read_strings_from_db("strings.db");
    auto end_reading_db = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_reading_db = end_reading_db - start_reading_db;
    std::cout << "Database insertion time: " << duration_reading_db.count() << " seconds" << std::endl;

    std::cout << "Start reading from file" << std::endl;
    auto start_reading_file = std::chrono::high_resolution_clock::now();
    std::vector<std::string> strings = read_strings_from_file("strings.txt");
    auto end_reading_file = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_reading_file = end_reading_file - start_reading_file;
    std::cout << "Database insertion time: " << duration_reading_file.count() << " seconds" << std::endl;
    
    return 0;
}