#pragma once
#include <cstdlib>
#include <random>
#include <vector>
#include "../common/utils.cpp"
using std::string;

namespace CRYPT {
const std::vector<int> base = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

inline int qpow(int a, int b, int mod) {
    int ans = 1;
    while (b) {
        if (b & 1) ans = 1LL * ans * a % mod;
        a = 1LL * a * a % mod;
        b >>= 1;
    }
    return ans;
}

int exgcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int r = exgcd(b, a % b, y, x);
    y = y - (a / b) * x;
    return r;
}

int get_inv(int &a, int &m) {
    int x = 0, y = 0;
    int r = exgcd(a, m, x, y);
    if (r != 1) return -1;
    while(x < 0) x += m;
    return x % m;
}

// https://zhuanlan.zhihu.com/p/220203643
// 原理：要么全是 1，要么先出现 -1 然后全是 1
// 本质上是在费马检测的基础上加入了二次探测
// 时间复杂度 O(klogP)
inline bool miller_rabin(int p) {
    int t = p - 1;
    int s = 0;
    while (!(t & 1)) {
        s++;
        t >>= 1;
    }
    for (auto &a : base) {
        int val = qpow(a, t, p);

        // val = 0 意味着 p | a
        // val = 1 or val = -1，意味着之后都是 1，可以提前退出
        if (val <= 1 || val == p - 1)
            continue;

        for (int j = 0; j < s; ++j) {
            val = 1LL * val * val % p;

            // 计算出 -1，意味着接下来都是 1，可以提前退出
            if (val == p - 1 && j != s - 1) {
                val = 1;
                break;
            }

            // 之前
            if (val == 1)
                return false;
        }

        // 费马检测
        if (val != 1)
            return false;
    }
    return true;
}

inline bool isprime(int p) {
    if (!(p & 1)) return false; // 特判偶数
    if (p < 3) return p == 2;   // 特判小于 3 的数
    return miller_rabin(p);
}

inline bool isprime_brute(int p) {
    if (!(p & 1)) return false; // 特判偶数
    if (p < 3) return p == 2;   // 特判小于 3 的数
    for (int i = 2; i * i <= p; ++i) {
        if (p % i == 0) return false;
    }
    return true;
}

int bits2int(const string& bits) {
    int ans = 0;
    for (auto &i: bits) ans *= 2, ans += i - '0';
    return ans;
}

// 生成长度为 L 的大素数
inline int gen_big_prime(int L) {
    while (1) {
        string prime("1");
        for (int i = 1; i < L - 1; ++i) {
            prime += u(e) % 2 + '0';
        }
        prime += 1;
        int val = bits2int(prime);
        if (isprime(val)) return static_cast<int>(val);
    }
}

int add(int a, int b, int mod) {
    return (a + b) % mod;
}
int sub(int a, int b, int mod) {
    return (a - b % mod + mod) % mod;
}
int mul(int a, int b, int mod) {
    return 1LL * a * b % mod;
}
} // namespace CRYPT