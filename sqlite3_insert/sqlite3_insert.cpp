#include "sqlite3_insert.h"

void write_random_strings_to_db(const std::string& db_name, size_t total_size_bytes, size_t max_string_length) {
    sqlite3* db;
    char* err_msg = nullptr;
    
    if (sqlite3_open(db_name.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Error: cannot open the database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    
    const char* create_table_sql = "CREATE TABLE IF NOT EXISTS Strings (id INTEGER PRIMARY KEY AUTOINCREMENT, length INTEGER, value TEXT);";
    if (sqlite3_exec(db, create_table_sql, nullptr, nullptr, &err_msg) != SQLITE_OK) {
        std::cerr << "Error: cannot create the table: " << err_msg << std::endl;
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return;
    }
    
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_int_distribution<size_t> length_dist(0, max_string_length);
    
    size_t current_size = 0;
    sqlite3_stmt* stmt;
    const char* insert_sql = "INSERT INTO Strings (length, value) VALUES (?, ?);";
    sqlite3_prepare_v2(db, insert_sql, -1, &stmt, nullptr);
    
    while (current_size < total_size_bytes) {
        if (current_size % (10 * 1024 * 1024) == 0) {
            std::cout << "Current size: " << current_size * 1024 * 1024 << " MB" << std::endl;
        }
        size_t length = length_dist(rng);
        std::string random_string = generate_random_string(length);
        
        sqlite3_bind_int(stmt, 1, length);
        sqlite3_bind_text(stmt, 2, random_string.c_str(), -1, SQLITE_STATIC);
        
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Error: cannot insert the data: " << sqlite3_errmsg(db) << std::endl;
        }
        sqlite3_reset(stmt);
        
        current_size += sizeof(int) + random_string.size();
    }
    
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    std::cout << "Database " << db_name << " is completed." << std::endl;
}