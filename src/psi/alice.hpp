#pragma once

#include "../utils.cpp"
#include <utility>
#include <vector>
using std::vector;

namespace ALICE {

// length of a Oblivious Pseudorandom Seed set.
// for each element in A set,
// alice will generate L OPR seed.
// i.e. K_{0}, K_{1}, .., K_{L - 1}
const int L = 30;

inline vector<int> gen_OPR_seed() {
    int val1 = gen_bit_string();
    int val2 = gen_bit_string();
    return vector<int>{val1, val2};
}
inline vector<vector<int>> gen_OPR_set() {
    vector<vector<int>> OPR_set;
    for (int j = 0; j < L; ++j)
        OPR_set.emplace_back(gen_OPR_seed());
    return OPR_set;
}
inline int OPRF(int elem, const vector<vector<int>> &OPR_set) {
    int val = 0;
    for (int j = 0; j < static_cast<int>(OPR_set.size()); ++j) {
        int idx = (elem >> j) & 1;
        val ^= OPR_set[j][idx];
    }
    return val;
}

class Alice_Base {
    virtual void gen_OPR_set_group() = 0;
    virtual void calc_a_set() = 0;
};

class Naive_Alice : Alice_Base {
private:
    // Obvilious Pseudorandom Seed.
    // size = n * L * 2.
    vector<vector<vector<int>>> K;

    // number of OPR set.
    // in navie Alice edtion,
    // n = a.size()
    int n;

    // Alice's plaintext set.
    vector<int> a;

    // Alice's hashed set.
    vector<int> a_set;

public:
    // TODO: these functions will cause copy assignment of big object
    // To optimize: a(std::move(_a)).
    // then the a outside Alice will be eliminated.
    Naive_Alice(const vector<int> &_a) : a(_a) {
        n = static_cast<int>(a.size());
        K.resize(n);
    }
    void gen_OPR_set_group() {
        for (int i = 0; i < n; ++i)
            K[i] = gen_OPR_set();
    }
    void calc_a_set() {
        // traverse each elem in a.
        // complete OT operation with each OPR
        for (auto &elem : a) {
            for (int i = 0; i < static_cast<int>(K.size()); ++i)
                a_set.emplace_back(OPRF(elem, K[i]));
        }
    }
    // TODO: these functions will cause copy assignment of big object
    // which is a big overhead to our system which can not be ignored
    vector<int> get_a_set() {
        return a_set;
    }
    vector<vector<vector<int>>> get_OPR_set_group() {
        return K;
    }
};

inline int hash1_ = 1, hash2_ = 2;
inline int bucket_size = 2;

inline int hash(int hash_param, int key) {
    return std::hash<int>()(key) / hash_param % (bucket_size / 2);
}
inline int hash1(int key) {
    return hash(hash1_, key);
}
inline int hash2(int key) {
    return hash(hash2_, key) + (bucket_size / 2);
}

class Smart_Alice : public Alice_Base {
private:
    vector<vector<vector<int>>> K;
    int n;
    vector<int> a;
    vector<int> a_set;

public:
    Smart_Alice(const vector<int> &_a, int _n) : a(_a), n(_n) {
        K.resize(n);
    }
    void gen_OPR_set_group() {
        for (int i = 0; i < n; ++i)
            K[i] = gen_OPR_set();
    }
    void calc_a_set() {
        for (auto &elem : a) {
            // naive algo: for each elem in a, for each OPR_seed K[i] in K, do OPRF(a, K[i]).
            // smart algo: for each elem in a, do OPRF(elem, K[hash1(elem)]) and OPRF(elem, K[hash2(elem)]).
            a_set.emplace_back(OPRF(elem, K[hash1(elem)]));
            a_set.emplace_back(OPRF(elem, K[hash2(elem)]));
        }
    }
    vector<int> get_a_set() {
        return a_set;
    }
    vector<vector<vector<int>>> get_OPR_set_group() {
        return K;
    }
};
} // namespace ALICE