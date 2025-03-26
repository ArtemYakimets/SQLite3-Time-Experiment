#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../generate_string/generate_string.h"

void write_strings_to_file(const std::string& filename, const std::vector<std::string>& strings_vector);