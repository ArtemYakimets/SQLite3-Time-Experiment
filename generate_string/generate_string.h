#pragma once

#include <iostream>
#include <random>
#include <string>

const std::string CHARSET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

std::string generate_random_string(size_t length);
