#include "si.hpp"
#include "../common/test.cpp"

const int test_time = 10;

int main()
{
    for (int i = 0; i < test_time; ++i) {
        auto IN_1 = gen_unique_vector_int(50);
        auto IN_2 = gen_unique_vector_int(100);
        auto ans1 = SI::display(IN_1, IN_2, 1); // merge
        auto ans2 = SI::display(IN_1, IN_2, 0); // hash
        TEST(ans1, ans2, true);
    }
    return 0;
}