#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "../generate_string/generate_string.h"

void write_random_strings_to_file(const std::string& filename, size_t total_size_bytes, size_t max_string_length);