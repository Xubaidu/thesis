#include "alice.hpp"
#include "bob.hpp"
#include <functional>
#include <memory>
using std::shared_ptr;

vector<int> v1 = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
vector<int> v2 = {1, 2, 3, 4, 5, 6, 7, 11};

void test_PSI() {

    // alice's round
    shared_ptr<ALICE::Naive_Alice> alice(new ALICE::Naive_Alice(v1));
    alice->gen_OPR_set_group();
    alice->calc_a_set();
    int L = ALICE::L;
    auto K = alice->get_OPR_set_group();
    auto a_set = alice->get_a_set();

    // bob's round
    shared_ptr<BOB::Naive_Bob> bob(new BOB::Naive_Bob(v2));
    bob->calc_b_set(K);
    auto ans = bob->get_intersection(a_set);

    for (auto &i : ans)
        cout << i << "\n";
}

int main() {
    test_PSI();
    return 0;
}