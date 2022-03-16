#pragma once

#include <random>

// length of a Oblivious Pseudorandom Seed
const int bit_length = 20;

// generate n-bit string
int gen_bit_string() {
    int val = 0;
    for (int j = 0; j < bit_length; ++j) {
        val <<= 1, val += random() % 2;
    }
    return val;
}

template <typename T>
std::string vector_to_string(const std::vector<T> &vec) {
    std::string ans("[");
    int len = static_cast<int>(vec.size());
    for (int i = 0; i < len; ++i) {
        ans += std::to_string(vec[i]) + (i + 1 == len ? "]" : ", ");
    }
    return ans;
}
