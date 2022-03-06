#include <functional>
#include <iostream>
#include <vector>
using std::cout;
using std::vector;

template <typename T> bool check(const vector<T> &in, const vector<T> &out) {
    if (static_cast<int>(in.size()) != static_cast<int>(out.size()))
        return false;
    for (int i = 0; i < static_cast<int>(in.size()); ++i) {
        if (in[i] != out[i])
            return false;
    }
    return true;
}

template <typename T> void TEST(const vector<T> &out, const vector<T> &std_out, bool flag) {
    bool ret = (out == std_out);
    if (ret == flag)
        cout << "pass!\n";
    else
        cout << "fail!\n";
}