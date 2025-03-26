#include "sqlite3_insert.h"

void write_strings_to_db(const std::string& db_name, const std::vector<std::string>& strings_vector) {
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

    sqlite3_stmt* stmt;
    const char* insert_sql = "INSERT INTO Strings (length, value) VALUES (?, ?);";
    sqlite3_prepare_v2(db, insert_sql, -1, &stmt, nullptr);

    for (const auto& str : strings_vector) {
        size_t length = str.size();

        sqlite3_bind_int(stmt, 1, static_cast<int>(length)); 
        sqlite3_bind_text(stmt, 2, str.c_str(), -1, SQLITE_STATIC); 

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Error: cannot insert the data: " << sqlite3_errmsg(db) << std::endl;
        }

        sqlite3_reset(stmt); 
    }

    sqlite3_finalize(stmt); 
    sqlite3_close(db); 

    std::cout << "Database " << db_name << " is completed." << std::endl;
}