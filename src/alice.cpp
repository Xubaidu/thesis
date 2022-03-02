#pragma once

#include "utils.cpp"
#include <utility>
#include <vector>

namespace ALICE {
const int L = 30;

class Alice {
private:
    vector<vector<vector<int>>> K; // size = n * l * 2
    vector<int> a;
    vector<int> a_set;

public:
    // TODO: these functions will cause copy assignment of big object
    Alice(const vector<int> &_a) : a(_a) {
        K.resize(static_cast<int>(a.size()));
    }
    void gen_bit_string() {
        int n = static_cast<int>(a.size());
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < L; ++j) {
                int val1 = gen_n_bit_string(n);
                int val2 = gen_n_bit_string(n);
                K[i].push_back(vector<int>{val1, val2});
            }
        }
    }
    void calc_a_set() {
        // traverse each elem in a
        for (auto &elem : a) {
            // complete OT operation with each OPRF
            for (int i = 0; i < static_cast<int>(K.size()); ++i) {
                int temp_val = 0;
                // calc the Kth bit and choose corresponding bit string
                for (int j = 0; j < L; ++j) {
                    int idx = (elem >> j) & 1;
                    temp_val ^= K[i][j][idx];
                }
                a_set.push_back(temp_val);
            }
        }
    }
    // TODO: these functions will cause copy assignment of big object
    // which is a big overhead to our system which can not be ignored
    vector<int> get_a_set() {
        return a_set;
    }
    vector<vector<vector<int>>> get_K() {
        return K;
    }
};
} // namespace ALICE