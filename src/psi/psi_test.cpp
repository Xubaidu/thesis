#include "alice.hpp"
#include "bob.hpp"
#include "../common/test.cpp"
#include <functional>
#include <memory>
using std::shared_ptr;

vector<int> v1 = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
vector<int> v2 = {1, 2, 3, 4, 5, 6, 7, 11};
vector<int> std_out = {2, 3, 4, 5, 6, 7, 11};

vector<int> test_PSI() {
    // alice's round
    shared_ptr<ALICE::Naive_Alice> alice(new ALICE::Naive_Alice(v1));
    alice->gen_OPR_set_group();
    alice->calc_a_set();
    auto K = alice->get_OPR_set_group();
    auto a_set = alice->get_a_set();

    // bob's round
    shared_ptr<BOB::Naive_Bob> bob(new BOB::Naive_Bob(v2));
    bob->calc_b_set(K);
    auto ans = bob->get_intersection(a_set);

    return ans;
}

vector<int> test_smart_PSI() {
    // bob's round
    shared_ptr<BOB::Smart_Bob> bob(new BOB::Smart_Bob(v2));
    bob->pre_work();
    ALICE::hash1_ = bob->get_hash_param1();
    ALICE::hash2_ = bob->get_hash_param2();
    ALICE::bucket_size = bob->get_hash_table_size();

    // alice's round
    shared_ptr<ALICE::Smart_Alice> alice(new ALICE::Smart_Alice(v1, ALICE::bucket_size));
    alice->gen_OPR_set_group();
    alice->calc_a_set();
    auto K = alice->get_OPR_set_group();
    auto a_set = alice->get_a_set();

    // bob's round;
    bob->calc_b_set(K);
    auto ans = bob->get_intersection(a_set);

    return ans;
}

int main() {
    TEST(test_PSI(), std_out, true);
    TEST(test_smart_PSI(), std_out, true);
    return 0;
}