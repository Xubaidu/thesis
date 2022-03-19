#include "rsa.hpp"
using std::pair;

namespace CRYPT {
class OT_server {
private:
    int x_0, x_1;
    int b_0 = 0;
    int b_1 = 1;
    int mod;
    RSA_server rsa_server; // 组合，wrap 一个 rsa_server
public:
    OT_server() :
        rsa_server(RSA_server()) {
        mod = rsa_server.get_pbk().n;
        x_0 = gen_int() % mod;
        x_1 = gen_int() % mod;
    }
    pair<int, int> transfer_bit(int v) {
        int r_0 = rsa_server.INV_RSA(sub(v, x_0, mod));
        int r_1 = rsa_server.INV_RSA(sub(v, x_1, mod));
        int new_b_0 = add(b_0, r_0, mod);
        int new_b_1 = add(b_1, r_1, mod);
        return {new_b_0, new_b_1};
    }
    pair<int, int> get_x_pair() {
        return {x_0, x_1};
    }
    PBK get_pbk() {
        return rsa_server.get_pbk();
    }
};

class OT_client {
    int r;
    int choose_bit;
    int actual_choose_bit;
    int mod;
    RSA_client rsa_client;

public:
    OT_client(int _choose_bit, const PBK &pbk) :
        choose_bit(_choose_bit),
        rsa_client(pbk) {
        mod = rsa_client.get_pbk().n;
        r = gen_int() % mod;
    }
    int first_choose_bit(const int x_0, const int x_1) {
        int v;
        if (choose_bit == 1) v = (x_1 + rsa_client.RSA(r)) % mod;
        else v = (x_0 + rsa_client.RSA(r)) % mod;
        return v;
    }
    int second_choose_bit(const int b_0, const int b_1) {
        if (choose_bit == 1) actual_choose_bit = sub(b_1, r, mod);
        else actual_choose_bit = sub(b_0, r, mod);
        return actual_choose_bit;
    }
};
} // namespace CRYPT