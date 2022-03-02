#pragma once

#include <iostream>
#include <memory>
#include <random>
#include <unordered_map>
using std::vector;
using std::unordered_map;
using std::cout;
using std::make_pair;

int gen_n_bit_string(int n) {
    int val = 0;
    for (int j = 0; j < n; ++j) {
        val *= 2, val += random() % 2;
    }
    return val;
}

template <typename T> class SetIntersection {
private:
    vector<T> IN_1, IN_2;
    vector<T> OUT;
    vector<int> OUT_Index;

public:
    SetIntersection(const vector<T> &_IN_1, const vector<T> &_IN_2) : IN_1(_IN_1), IN_2(_IN_2) {}
    void Intersect() {
        unordered_map<T, bool> mp;
        for (int i = 0; i < static_cast<int>(IN_1.size()); ++i) {
            auto pair = make_pair(IN_1[i], true);
            mp.insert(pair);
        }
        for (int i = 0; i < static_cast<int>(IN_2.size()); ++i) {
            if (mp.find(IN_2[i]) != mp.end()) {
                OUT.push_back(IN_2[i]);
                OUT_Index.push_back(i);
            }
        }
    }
    void Show() {
        int n = static_cast<int>(OUT.size());
        cout << '[';
        for (int i = 0; i < n; ++i) {
            if (i != n - 1)
                cout << OUT[i] << ", ";
            else
                cout << OUT[i] << "]\n";
        }
    }
    vector<int> Get_OUT_Index() {
        return OUT_Index;
    }
};