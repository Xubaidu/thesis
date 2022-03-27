#include "alice.hpp"
#include "bob.hpp"
#include "../si/si.hpp"
#include "../common/test.cpp"
#include "../common/utils.cpp"
#include <functional>
#include <memory>

using std::shared_ptr;
using TEST::Correctness_TEST;
using SI::SetIntersection;

inline vector<int> test_PSI_impl(const vector<int>& IN_1, const vector<int>& IN_2) {

    // alice's round
    shared_ptr<ALICE::Naive_Alice> alice(new ALICE::Naive_Alice(IN_1));
    alice->gen_OPR_set_group();
    alice->calc_a_set();
    auto K = alice->get_OPR_set_group();
    auto a_set = alice->get_a_set();
    cout << "|a| = " << IN_1.size() << ", |a_set| = " << a_set.size() << "\n";

    // bob's round
    shared_ptr<BOB::Naive_Bob> bob(new BOB::Naive_Bob(IN_2));
    bob->calc_b_set(K);
    auto ans = bob->get_intersection(a_set, 0);
    return ans;
}

inline vector<int> test_smart_PSI_impl(const vector<int>& IN_1, const vector<int>& IN_2) {
    // bob's round
    shared_ptr<BOB::Smart_Bob> bob(new BOB::Smart_Bob(IN_2));
    bob->pre_work();
    ALICE::hash1_ = bob->get_hash_param1();
    ALICE::hash2_ = bob->get_hash_param2();
    ALICE::bucket_size = bob->get_hash_table_size();

    // alice's round
    shared_ptr<ALICE::Smart_Alice> alice(new ALICE::Smart_Alice(IN_1, ALICE::bucket_size));
    alice->gen_OPR_set_group();
    alice->calc_a_set();
    auto K = alice->get_OPR_set_group();
    auto a_set = alice->get_a_set();
    cout << "|a| = " << IN_1.size() << ", |a_set| = " << a_set.size() << "\n";

    // bob's round;
    bob->calc_b_set(K);
    auto ans = bob->get_intersection(a_set, 0);
    return ans;
}

inline void test_PSI(int n, bool is_smart) {
    auto IN_1 = gen_unique_vector_int(n);
    vector<int> IN_2;
    for (auto &i: IN_1) {
        int idx = u(e) % 2;
        if (idx) IN_2.push_back(i);
    }

    // psi
    auto ans = is_smart ? test_smart_PSI_impl(IN_1, IN_2) : test_PSI_impl(IN_1, IN_2);

    // si
    shared_ptr<SetIntersection<int>> SI(new SetIntersection<int>(IN_1, IN_2));
    SI->hash_intersect();
    auto std_ans = SI->get_out();

    Correctness_TEST(ans, std_ans, true);
}