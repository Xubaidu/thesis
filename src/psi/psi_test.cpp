#include "psi_test.hpp"
using TEST::Performance_TEST;

const vector<int> a = {100, 1000, 10000, 100000};

void test_naive_psi(int n) {
    test_PSI(n, 0);
}

void test_smart_psi(int n) {
    test_PSI(n, 1);
}

void test() {
    cout << "PSI TEST\n";
    for (int i = 0; i < static_cast<int>(a.size()); ++i) {
        cout << "data size = " << a[i] << "\n";
        auto func1 = test_naive_psi;
        auto func2 = test_smart_psi;
        if (i < 2) {
            cout << "naive psi (data size <= 1000): ";
            Performance_TEST<int>(func1, a[i]);
        }
        cout << "smart psi: ";
        Performance_TEST<int>(func2, a[i]);
        puts("---");
    }
}

int main() {
    test();
    return 0;
}
