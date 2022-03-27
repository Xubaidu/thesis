#include "cuckoo_hash.hpp"
#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <sys/_types/_clock_t.h>
#include <unordered_map>
#include <vector>
#include <chrono>
#include "../common/test.cpp"

using std::shared_ptr;
using std::string;
using std::vector;
using std::unordered_map;

using CUCKOO_HASH::CuckooHash;
using CUCKOO_HASH::EMPTY;

using TEST::Correctness_TEST;
using TEST::Performance_TEST;

vector<string> command;
vector<int> val;
vector<string> out1, out2;

void gen_data(int n) {
    command.clear(), val.clear();
    vector<string> command_pool = {"contains", "add", "add", "add", "add", "add", "remove"};
    std::shuffle(command.begin(), command.end(), e);
    for (int i = 0; i < n; ++i) {
        int idx = gen_int() % 4;
        command.push_back(command_pool[idx]);
        val.push_back(gen_int() % 100);
    }
}

void test_cuckoo_hash() {
    auto CH = shared_ptr<CuckooHash<int, int>>(new CuckooHash<int, int>());
    vector<string> ans;
    for (int i = 0; i < static_cast<int>(command.size()); ++i) {
        if (command[i] == "contains") {
            if (CH->get(val[i]) != EMPTY)
                ans.emplace_back("true");
            else
                ans.emplace_back("false");
        } else if (command[i] == "remove") {
            CH->del(val[i]);
            ans.emplace_back("null");
        } else {
            CH->put(val[i], 1);
            ans.emplace_back("null");
        }
    }
    cout << "load factor = " << CH->get_load_factor() << " ";
    out1 = ans;
}

void test_benchmark() {
    unordered_map<int, int> mp;
    vector<string> ans;
    for (int i = 0; i < static_cast<int>(command.size()); ++i) {
        if (command[i] == "contains") {
            if (mp.find(val[i]) != mp.end())
                ans.emplace_back("true");
            else
                ans.emplace_back("false");
        } else if (command[i] == "remove") {
            mp.erase(val[i]);
            ans.emplace_back("null");
        } else {
            mp.insert({val[i], 1});
            ans.emplace_back("null");
        }
    }
    cout << "load factor = " << mp.load_factor() << " ";
    out2 = ans;
}

void test(int n) {
    cout << "data size: " << n << "\n";
    gen_data(n);
    auto func1 = test_cuckoo_hash;
    auto func2 = test_benchmark;
    cout << "cuckoo_hash: ";
    Performance_TEST(func1);
    cout << "std::unordered_map: ";
    Performance_TEST(func2);
    Correctness_TEST(out1, out2, true);
    puts("---");
}

int main() {
    cout << "CUCKOO TEST\n";
    const vector<int> n = {100, 1000, 10000, 100000, 1000000, 10000000};
    for (int i = 0; i < static_cast<int>(n.size()); ++i) {
        cout << "case# " << i << ":\n";
        test(n[i]);
    }
    return 0;
}