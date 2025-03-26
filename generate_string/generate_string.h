#pragma once

#include <iostream>
#include <random>
#include <string>
#include <vector>

const std::string CHARSET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

std::string generate_random_string(size_t max_length);
std::vector<std::string> generate_strings(size_t array_size, size_t max_string_length);
