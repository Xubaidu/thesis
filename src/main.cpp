#include "alice.cpp"
#include "bob.cpp"
#include <memory>
using std::shared_ptr;

int main() {
    /*
    vector<int> v1 = {1, 2, 5, 7, 8, 9, 100, 101};
    vector<int> v2 = {2, 3, 6, 100, 101, 200, 500, 1000};
    */

    vector<int> v1 = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    vector<int> v2 = {1, 2, 3, 4, 5, 6, 7, 11};

    // alice's round
    shared_ptr<ALICE::Alice> alice(new ALICE::Alice(v1));
    alice->gen_bit_string();
    alice->calc_a_set();
    int L = ALICE::L;
    auto K = alice->get_K();
    auto a_set = alice->get_a_set();

    // bob's round
    shared_ptr<BOB::Bob> bob(new BOB::Bob(v2));
    bob->calc_b_set(L, K);
    auto ans = bob->get_intersection(a_set);

    for (auto &i : ans)
        cout << i << "\n";
    return 0;
}