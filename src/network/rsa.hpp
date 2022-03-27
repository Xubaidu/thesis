#pragma once
#include "crypt.cpp"
#include <ostream>

using std::ostream;

namespace CRYPT {

struct PBK {
    int n, e;
    PBK() {
    }
    PBK(int _n, int _e) :
        n(_n), e(_e) {
    }
    friend ostream &operator<<(ostream &cout, const PBK &pbk) {
        cout << "n = " << pbk.n << ", e = " << pbk.e;
        return cout;
    }
};

struct PRK {
    int d;
    PRK() {
    }
    PRK(int _d) :
        d(_d) {
    }
    friend ostream &operator<<(ostream &cout, const PRK &prk) {
        cout << "d = " << prk.d;
        return cout;
    }
};

class RSA_server {
private:
    PBK pbk;
    PRK prk;

public:
    RSA_server() {
        int p, q;
        p = gen_big_prime(10);
        do {
            q = gen_big_prime(10);
        } while (q == p);
        int n = p * q;
        int phi_n = (p - 1) * (q - 1);
        int e = gen_big_prime(11);
        int d = get_inv(e, phi_n);
        pbk = PBK(n, e);
        prk = PRK(d);
    }
    int INV_RSA(int c) {
        return qpow(c, prk.d, pbk.n);
    }
    PBK get_pbk() const {
        return pbk;
    }
    PRK get_prk() const {
        return prk;
    }
};

class RSA_client {
private:
    PBK pbk;

public:
    RSA_client(const PBK &_pbk) :
        pbk(_pbk) {
    }
    int RSA(int m) {
        return qpow(m, pbk.e, pbk.n);
    }
    PBK get_pbk() {
        return pbk;
    }
};

} // namespace CRYPT