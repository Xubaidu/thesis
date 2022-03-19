#pragma once

#include <random>
#include <set>

using std::default_random_engine;
using std::uniform_int_distribution;
using std::vector;
using std::set;
using LL = long long int;

default_random_engine e((unsigned)time(NULL));
uniform_int_distribution<int> u;

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

vector<int> gen_unique_vector_int(int n) {
    vector<int> vec;
    set<int> st;
    for (int i = 0; i < n; ++i) {
        st.insert(u(e));
    }
    for (auto &i : st) vec.emplace_back(i);
    return vec;
}

int gen_int() {
    return u(e);
}


// 序列化 vector
template <typename T>
std::string vector_to_string(const std::vector<T> &vec) {
    std::string ans("[");
    int len = static_cast<int>(vec.size());
    for (int i = 0; i < len; ++i) {
        ans += std::to_string(vec[i]) + (i + 1 == len ? "]" : ", ");
    }
    return ans;
}