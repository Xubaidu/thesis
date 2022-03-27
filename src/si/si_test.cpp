#include "si.hpp"
#include "../common/utils.cpp"
#include "../common/test.cpp"
#include <vector>

using TEST::Correctness_TEST;

const vector<int> a = {100, 1000, 10000, 100000, 1000000};

const int test_time = 10;
void test(int n) {
    cout << "data size = " << n << "\n";
    auto IN_1 = gen_unique_vector_int(n);
    vector<int> IN_2;
    for (auto &i: IN_1) {
        int idx = u(e) % 2;
        if (idx) IN_2.push_back(i);
    }
    auto ans1 = SI::display(IN_1, IN_2, 0); // hash
    auto ans2 = SI::display(IN_1, IN_2, 1); // merge
    cout << "ans1.size = " << ans1.size() << ", ans2.size = " << ans2.size() << "\n";
    Correctness_TEST(ans1, ans2, true);
}

int main()
{
    cout << "SI TEST\n";
    for (int i = 0; i < static_cast<int>(a.size()); ++i) {
        cout << "case# " << i << ":\n";
        test(a[i]);
    }
    return 0;
}