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

using TEST::Correctness_TEST;

const int test_time = 5;

void test_isprime() {
    cout << "PRIME GENERATION TEST\n";
    for (int i = 0; i < test_time; ++i) {
        cout << "case# " << i << ":\n";
        auto val = CRYPT::gen_big_prime(30);
        cout << "val = " << val << "\n";
        bool out_1 = isprime(val);
        bool out_2 = isprime_brute(val);
        Correctness_TEST(out_1, out_2, true);
    }
    puts("---");
}

void test_rsa() {
    cout << "RSA TEST\n";
    for (int i = 0; i < test_time; ++i) {
        cout << "case# " << i << ":\n";
        shared_ptr<RSA_server> rsa_server(new RSA_server());
        auto pbk = rsa_server->get_pbk();
        auto prk = rsa_server->get_prk();
        cout << "pbk: " << pbk << "\n";
        cout << "prk: " << prk << "\n";
        shared_ptr<RSA_client> rsa_client(new RSA_client(pbk));
        int m = gen_int() % pbk.n;
        cout << "m = " << m << "\n";
        int std_m = rsa_server->INV_RSA(rsa_client->RSA(m));
        cout << "c = " << std_m << "\n";
        Correctness_TEST(m, std_m, true);
    }
    puts("---");
}

void test_ot() {
    cout << "OT TEST\n";
    for (int i = 0; i < test_time; ++i) {
        cout << "case# " << i << ":\n";
        int choose_bit = gen_int() % 2;
        cout << "choose_bit = " << choose_bit << "\n";
        shared_ptr<OT_server> ot_server(new OT_server());
        PBK pbk = ot_server->get_pbk();
        auto x_pair = ot_server->get_x_pair();
        shared_ptr<OT_client> ot_client(new OT_client(choose_bit, pbk));
        int v = ot_client->first_choose_bit(x_pair.first, x_pair.second);
        auto new_b_pair = ot_server->transfer_bit(v);
        int actual_choose_bit = ot_client->second_choose_bit(new_b_pair.first, new_b_pair.second);
        cout << "actual_choose_bit = " << actual_choose_bit << "\n";
        Correctness_TEST(choose_bit, actual_choose_bit, true);
    }
    puts("---");
}
int main() {
    // test_isprime();
    // test_rsa();
    test_ot();
    return 0;
}
/*
pbk: 410881 1373
prk: 46837
m = 401223
c = 339046
correctness test fail!
*/