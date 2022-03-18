#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
#include <random>
#include <set>
using std::default_random_engine;
using std::uniform_int_distribution;
using std::cout;
using std::vector;
using std::set;

const int MAX_INT = 100;
const int MIN_INT = 0;

template <typename T>
bool check(const vector<T> &in, const vector<T> &out) {
    if (static_cast<int>(in.size()) != static_cast<int>(out.size()))
        return false;
    for (int i = 0; i < static_cast<int>(in.size()); ++i) {
        if (in[i] != out[i])
            return false;
    }
    return true;
}

template <typename T>
void TEST(const vector<T> &out, const vector<T> &std_out, bool flag) {
    bool ret = check(out, std_out);
    if (ret == flag)
        cout << "pass!\n";
    else
        cout << "fail!\n";
}

vector<int> gen_unique_vector_int(int n) {
    vector<int> vec;
    set<int> st;
    default_random_engine e;
    uniform_int_distribution<int> u(MIN_INT, MAX_INT);
    for (int i = 0; i < n; ++i) {
        st.insert(u(e));
    }
    for (auto &i: st) vec.emplace_back(i);
    return vec;
}