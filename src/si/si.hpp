#pragma once

#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>
using std::cout;
using std::make_pair;
using std::shared_ptr;
using std::unordered_map;
using std::vector;
using std::string;
namespace SI {

template <typename T>
class SetIntersection {
private:
    vector<T> IN_1, IN_2;
    vector<T> OUT;
    vector<int> OUT_Index;

public:
    SetIntersection(const vector<T> &_IN_1, const vector<T> &_IN_2) :
        IN_1(_IN_1), IN_2(_IN_2) {
    }
    void hash_intersect() {
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
    void merge_intersect() {
        sort(IN_1.begin(), IN_1.end());
        sort(IN_2.begin(), IN_2.end());
        int L1 = static_cast<int>(IN_1.size());
        int L2 = static_cast<int>(IN_2.size());
        int i = 0, j = 0;
        while (i < L1 && j < L2) {
            if (IN_1[i] > IN_2[j]) {
                j++;
            } else if (IN_1[i] < IN_2[j]) {
                i++;
            } else {
                OUT.emplace_back(IN_2[j]);
                OUT_Index.emplace_back(j);
                i++, j++;
            }
        }
    }
    void show() {
        int n = static_cast<int>(OUT.size());
        cout << '[';
        for (int i = 0; i < n; ++i) {
            if (i != n - 1)
                cout << OUT[i] << ", ";
            else
                cout << OUT[i] << "]\n";
        }
    }
    vector<int> get_out_index() const {
        return OUT_Index;
    }
    vector<int> get_out() const {
        return OUT;
    }
};

// method = 0 => hash_intersect
// method = 1 => merge_intersect
template <typename T>
vector<int> display(const vector<T> &IN_1, const vector<T> &IN_2, int method) {
    // using shared_ptr to implement RAII (Resources Acquisition Is Initialization)
    shared_ptr<SetIntersection<T>> SI(new SetIntersection<T>(IN_1, IN_2));
    if (method == 0) SI->hash_intersect();
    else SI->merge_intersect();
    return SI->get_out_index();
}
} // namespace SI