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
namespace SI {

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

template <typename T> vector<int> display(const vector<T> &IN_1, const vector<T> &IN_2) {
    // using shared_ptr to implement RAII (Resources Acquisition Is Initialization)
    shared_ptr<SetIntersection<T>> SI(new SetIntersection<T>(IN_1, IN_2));
    SI->Intersect();
    return SI->Get_OUT_Index();
}
} // namespace SI