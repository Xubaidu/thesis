#pragma once
#include "../utils.cpp"
#include <vector>
using std::shared_ptr;

namespace BOB {
template <typename T> vector<int> display(const vector<T> &IN_1, const vector<T> &IN_2) {
    // using shared_ptr to implement RAII (Resources Acquisition Is Initialization)
    shared_ptr<SetIntersection<T>> SI(new SetIntersection<T>(IN_1, IN_2));
    SI->Intersect();
    return SI->Get_OUT_Index();
}

class Bob {
private:
    vector<int> b;
    vector<int> b_set;

public:
    Bob(const vector<int> &_b) : b(_b) {}
    void calc_b_set(int l, const vector<vector<vector<int>>> &K) {
        for (int i = 0; i < static_cast<int>(b.size()); ++i) {
            int temp_val = 0;
            for (int j = 0; j < l; ++j) {
                int idx = (b[i] >> j) & 1;
                temp_val ^= K[i][j][idx];
            }
            b_set.push_back(temp_val);
        }
    }
    vector<int> get_intersection(const vector<int> &a_set) {
        auto Set_Intersection = display<int>(a_set, b_set);
        vector<int> ans;
        for (auto i : Set_Intersection) {
            ans.push_back(b[i]);
        }
        return ans;
    }
};
} // namespace Bob