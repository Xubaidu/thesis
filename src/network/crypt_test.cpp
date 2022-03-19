#include "../common/utils.cpp"
#include "../common/test.cpp"
#include "crypt.cpp"
#include "rsa.hpp"
#include "ot.hpp"

using std::shared_ptr;
using CRYPT::isprime;
using CRYPT::isprime_brute;
using CRYPT::RSA_server;
using CRYPT::RSA_client;
using CRYPT::OT_server;
using CRYPT::OT_client;
using CRYPT::PBK;

const int test_time = 20;

void test_isprime() {
    for (int i = 0; i < test_time; ++i) {
        auto vec = gen_unique_vector_int(100);
        vector<bool> out_1, out_2;
        for (auto &i : vec) {
            LL val = static_cast<long long>(i);
            out_1.emplace_back(isprime(val));
            out_2.emplace_back(isprime_brute(val));
        }
        TEST(out_1, out_2, true);
    }
}

void test_rsa() {
    for (int i = 0; i < test_time; ++i) {
        shared_ptr<RSA_server> rsa_server(new RSA_server());
        shared_ptr<RSA_client> rsa_client(new RSA_client(rsa_server->get_pbk()));
        int m = gen_int() % rsa_server->get_pbk().n;
        int std_m = rsa_server->INV_RSA(rsa_client->RSA(m));
        TEST(m, std_m, true);
    }
}

void test_ot() {
    for (int i = 0; i < test_time; ++i) {
        int choose_bit = gen_int() % 2;
        shared_ptr<OT_server> ot_server(new OT_server());
        PBK pbk = ot_server->get_pbk();
        auto x_pair = ot_server->get_x_pair();
        shared_ptr<OT_client> ot_client(new OT_client(choose_bit, pbk));
        int v = ot_client->first_choose_bit(x_pair.first, x_pair.second);
        auto new_b_pair = ot_server->transfer_bit(v);
        int actual_choose_bit = ot_client->second_choose_bit(new_b_pair.first, new_b_pair.second);
        TEST(choose_bit, actual_choose_bit, true);
    }
}
int main() {
    test_ot();
    return 0;
}