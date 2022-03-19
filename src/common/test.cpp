#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
#include <random>
#include <set>
using std::cout;

template <typename T>
void TEST(const T &out, const T &std_out, bool flag) {
    bool ret = (out == std_out);
    if (ret == flag)
        cout << "pass!\n";
    else
        cout << "fail!\n";
}