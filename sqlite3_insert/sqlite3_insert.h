#pragma once

#include <iostream>
#include <sqlite3.h>
#include <string>

#include "../generate_string/generate_string.h"

void write_strings_to_db(const std::string& db_name, const std::vector<std::string>& strings_vector);