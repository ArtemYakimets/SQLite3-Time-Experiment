#pragma once

#include <iostream>
#include <sqlite3.h>
#include <string>

#include "../generate_string/generate_string.h"

void write_random_strings_to_db(const std::string& db_name, size_t total_size_bytes, size_t max_string_length);