#include "sqlite3_read.h"

std::vector<std::string> read_strings_from_db(const std::string& db_name) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    std::vector<std::string> strings;

    if (sqlite3_open(db_name.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Error: cannot open the database: " << sqlite3_errmsg(db) << std::endl;
        return {};
    }

    const char* select_sql = "SELECT length, value FROM Strings;";
    if (sqlite3_prepare_v2(db, select_sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error: cannot prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return {};
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int length = sqlite3_column_int(stmt, 0);
        const char* value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        strings.push_back(std::to_string(length) + ":" + std::string(value));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return strings;
}