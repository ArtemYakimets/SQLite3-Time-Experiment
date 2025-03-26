#include "generate_string.h"

std::string generate_random_string(size_t length) {
    static std::random_device rd;
    static std::mt19937 rng(rd());
    static std::uniform_int_distribution<int> char_dist(0, CHARSET.size() - 1);
    
    std::string result;
    result.reserve(length);
    for (size_t i = 0; i < length; ++i) {
        result += CHARSET[char_dist(rng)];
    }
    return result;
}