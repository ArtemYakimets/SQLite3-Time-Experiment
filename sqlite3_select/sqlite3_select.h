#include <iostream>
#include <sqlite3.h>
#include <vector>
#include <string>

std::vector<std::string> read_filtered_strings_from_db(const std::string& db_name, const std::string& substring);
