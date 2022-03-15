#pragma once
#include "../si/si.hpp"
#include "../cuckoo/cuckoo_hash.hpp"
#include <vector>

namespace BOB {

inline int OPRF(int elem, const vector<vector<int>> &OPR_set) {
    int val = 0;
    for (int j = 0; j < static_cast<int>(OPR_set.size()); ++j) {
        int idx = (elem >> j) & 1;
        val ^= OPR_set[j][idx];
    }
    return val;
}
class Bob_Base {
    virtual void calc_b_set(const vector<vector<vector<int>>> &K) = 0;
    virtual vector<int> get_intersection(const vector<int> &a_set) = 0;
};
class Naive_Bob : Bob_Base {
private:
    vector<int> b;
    vector<int> b_set;

public:
    Naive_Bob(const vector<int> &_b) :
        b(_b) {
    }
    void calc_b_set(const vector<vector<vector<int>>> &K) {
        for (int i = 0; i < static_cast<int>(b.size()); ++i)
            b_set.emplace_back(OPRF(b[i], K[i]));
    }
    vector<int> get_intersection(const vector<int> &a_set) {
        auto Set_Intersection = SI::display<int>(a_set, b_set);
        vector<int> ans;
        for (auto i : Set_Intersection) {
            ans.push_back(b[i]);
        }
        return ans;
    }
};

class Smart_Bob : public Bob_Base {
private:
    vector<int> b;
    vector<int> b_set;
    CUCKOO_HASH::CuckooHash<int, int> CH;

public:
    Smart_Bob(const vector<int> &_b) :
        b(_b) {
    }
    void pre_work() {
        for (auto &i : b)
            CH.put(i, 1);
    }
    int get_hash_table_size() {
        return CH.size();
    }
    int get_hash_param1() {
        return CH.get_hash_param1();
    }
    int get_hash_param2() {
        return CH.get_hash_param2();
    }
    void calc_b_set(const vector<vector<vector<int>>> &K) {
        for (auto &elem : b) {
            auto hash_val = CH.get_actual_hash_val(elem);
            b_set.emplace_back(OPRF(elem, K[hash_val]));
        }
    }
    vector<int> get_intersection(const vector<int> &a_set) {
        auto Set_Intersection = SI::display<int>(a_set, b_set);
        vector<int> ans;
        for (auto i : Set_Intersection) {
            ans.push_back(b[i]);
        }
        return ans;
    }
};
} // namespace BOB