#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <vector>
#include <random>
#include <set>
#include "utils.cpp"

using std::cout;
using std::function;
using std::chrono::system_clock;
using std::chrono::milliseconds;
using std::chrono::microseconds;
using std::chrono::duration_cast;

namespace TEST {

template <typename T>
void Correctness_TEST(const T &out, const T &std_out, bool flag) {
    bool ret = (out == std_out);
    if (ret == flag)
        cout << "\033[32;4mCorrectness TEST Success!\033[0m\n";
    else
        cout << "\033[31;4mCorrectness TEST Fail!\033[0m\n";
}

void Performance_TEST(function<void()> func) {
    auto bg = system_clock::now();
    func();
    auto ed = system_clock::now();
    auto duration = duration_cast<microseconds>(ed - bg);
    cout << "duration = " << duration.count() << " mus\n";
}

template<typename T>
void Performance_TEST(function<void(T)> func, int n) {
    auto bg = system_clock::now();
    func(n);
    auto ed = system_clock::now();
    auto duration = duration_cast<microseconds>(ed - bg);
    cout << "duration = " << duration.count() << " mus\n";
}
}