#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <vector>
#include <random>
#include <set>
using std::cout;
using std::function;
using std::chrono::system_clock;
using std::chrono::milliseconds;
using std::chrono::microseconds;
using std::chrono::duration_cast;

template <typename T>
void TEST(const T &out, const T &std_out, bool flag) {
    bool ret = (out == std_out);
    if (ret == flag)
        cout << "pass!\n";
    else
        cout << "fail!\n";
}

void Time_TEST(function<void()> func) {
    auto bg = system_clock::now();
    func();
    auto ed = system_clock::now();
    auto duration = duration_cast<microseconds>(ed - bg);
    cout << "duration = " << duration.count() << " mus\n";
    
}