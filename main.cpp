#include <chrono>

#include "file_insert/file_insert.h"
#include "sqlite3_insert/sqlite3_insert.h"
#include "file_read/file_read.h"
#include "sqlite3_read/sqlite3_read.h"
#include "file_select/file_select.h"
#include "sqlite3_select/sqlite3_select.h"
#include "generate_string/generate_string.h"

void flush_cache() {
    constexpr size_t cache_size = 32 * 1024 * 1024; // 32 GB
    static std::vector<char> dummy(cache_size, 0);

    for (volatile char &c : dummy) {
        c += 1; 
    }
}

int main() {

    for (int k = 100000; k <= 1000000; k += 100000) {

        std::cout << "k = " << k << std::endl;

        std::vector<std::string> strings_vector = generate_strings(3000, k);
        
        flush_cache();
        std::cout << "Start insertion in database" << std::endl;
        auto start_insertion_db = std::chrono::high_resolution_clock::now();
        write_strings_to_db("strings.db", strings_vector);
        auto end_insertion_db = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration_insertion_db = end_insertion_db - start_insertion_db;
        std::cout << "Database insertion time: " << duration_insertion_db.count() << " seconds" << std::endl;

        flush_cache();
        std::cout << "Start insertion in file" << std::endl;
        auto start_insertion_file = std::chrono::high_resolution_clock::now();
        write_strings_to_file("strings.txt", strings_vector);
        auto end_insertion_file = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration_insertion_file = end_insertion_file - start_insertion_file;
        std::cout << "File insertion time: " << duration_insertion_file.count() << " seconds" << std::endl;

        flush_cache();
        std::cout << "Start reading from database" << std::endl;
        auto start_reading_db = std::chrono::high_resolution_clock::now();
        std::vector<std::string> strings_db = read_strings_from_db("strings.db");
        auto end_reading_db = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration_reading_db = end_reading_db - start_reading_db;
        std::cout << "Database reading time: " << duration_reading_db.count() << " seconds" << std::endl;

        flush_cache();
        std::cout << "Start reading from file" << std::endl;
        auto start_reading_file = std::chrono::high_resolution_clock::now();
        std::vector<std::string> strings_file = read_strings_from_file("strings.txt");
        auto end_reading_file = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration_reading_file = end_reading_file - start_reading_file;
        std::cout << "File reading time: " << duration_reading_file.count() << " seconds" << std::endl;

        std::string search_substring = "abc"; 

        flush_cache();
        std::cout << "Start selection from database" << std::endl;
        auto start_selection_db = std::chrono::high_resolution_clock::now();
        std::vector<std::string> filtered_strings_db = read_filtered_strings_from_db("strings.db", search_substring);
        auto end_selection_db = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration_selection_db = end_selection_db - start_selection_db;
        std::cout << "Database selection time: " << duration_selection_db.count() << " seconds" << std::endl;
        
        flush_cache();
        std::cout << "Start selection from file" << std::endl;
        auto start_selection_file = std::chrono::high_resolution_clock::now();
        std::vector<std::string> filtered_strings_file = read_filtered_strings_from_file("strings.db", search_substring);
        auto end_selection_file = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration_selection_file = end_selection_file - start_selection_file;
        std::cout << "File selection time: " << duration_selection_file.count() << " seconds" << std::endl;

        strings_vector.clear();
        strings_db.clear();
        strings_file.clear();
        filtered_strings_db.clear();
        filtered_strings_file.clear();

        if (std::remove("strings.txt") == 0) {
            std::cout << "Deleted strings.txt" << std::endl;
        } else {
            std::cerr << "Failed to delete strings.txt" << std::endl;
        }

        if (std::remove("strings.db") == 0) {
            std::cout << "Deleted strings.db" << std::endl;
        } else {
            std::cerr << "Failed to delete strings.db" << std::endl;
        }

        std::cout << "Test iteration completed.\n" << std::endl;
    }
    
    return 0;
}