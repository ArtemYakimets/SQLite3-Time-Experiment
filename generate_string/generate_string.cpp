#include "generate_string.h"

std::string generate_random_string(size_t max_length) {
    static std::random_device rd;
    static std::mt19937 rng(rd());
    static std::uniform_int_distribution<int> char_dist(0, CHARSET.size() - 1);
    static std::uniform_int_distribution<size_t> length_dist(0, max_length);

    size_t length = length_dist(rng);
    std::string result;
    result.reserve(length + 10);  

    result += std::to_string(length) + ":"; 

    for (size_t i = 0; i < length; ++i) {
        result += CHARSET[char_dist(rng)];
    }

    return result;
}

std::vector<std::string> generate_strings(size_t array_size, size_t max_string_length) {
    std::vector<std::string> vec;
    vec.reserve(array_size);  

    for (size_t i = 0; i < array_size; ++i) {
        vec.push_back(generate_random_string(max_string_length));
    }

    return vec;
}