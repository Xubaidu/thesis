#pragma once

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <vector>
using std::vector;

namespace CUCKOO_HASH {
using PII = std::pair<int, int>;
const PII EMPTY = {-1, -1};

template<typename K, typename V>
class CuckooHash {
using PKV = std::pair<K, V>;
private:
    // bucket to store the k-v elements.
    // suppose size = bucket_size,
    // the bucket is splited into [0, size / 2), [size / 2, size).
    vector<PKV> bucket = vector<PKV>(2, EMPTY);

    // actual number of elements in the bucket.
    int count_ = 0;

    // max elements stored in bucket.
    // when the count of cuckoo hash loop goes beyond retry_threshold,
    // cuckoo hash table needs to do a rehash.
    int retry_threshold = 10;

    // hash parameters.
    // used to generate new hash function.
    int hash1_ = 1, hash2_ = 2;

    // calculate hash value.
    // when the hash_param is changed, a new hash function is generated.
    int hash(int hash_param, K key) {
        return std::hash<K>()(key) / hash_param % (static_cast<int>(bucket.size()) / 2);
    }
    int hash1(K key) {
        return hash(hash1_, key);
    }
    int hash2(K key) {
        return hash(hash2_, key) + (static_cast<int>(bucket.size()) / 2);
    }

    // dynamically adjust the size of bucket.
    void resize() {
        bucket.resize(static_cast<int>(bucket.size()) * 2, EMPTY);
        retry_threshold = 10 * static_cast<int>(log2(static_cast<int>(bucket.size())));
        rehash();
    }

    // put new val into bucket
    void put_new_val(K key, V value) {
        // add new element into hash table
        ++count_;

        // set load factor alpha between [0, 0.25].
        // why the bound is 0.25?
        // this maybe a magic number from the paper.
        // update: alpha = 1 is also ok!
        if (4 * count_ >= static_cast<int>(bucket.size()))
            resize();

        bool switcher = true;
        for (int loop_cnt = 0; loop_cnt < retry_threshold; ++loop_cnt) {
            auto hash_val_1 = hash1(key), hash_val_2 = hash2(key);

            // if there is a empty slot.
            // we can put the k-v into it.
            if (bucket[hash_val_1] == EMPTY) {
                bucket[hash_val_1] = {key, value};
                break;
            }
            if (bucket[hash_val_2] == EMPTY) {
                bucket[hash_val_2] = {key, value};
                break;
            }

            // otherwise, we will keep kicking out the existing element.
            auto hash_val = switcher ? hash_val_1 : hash_val_2;
            std::swap(key, bucket[hash_val].first);
            std::swap(value, bucket[hash_val].second);
            switcher = !switcher;

            // loop_cnt meets the bound, so we need to rehash.
            if (loop_cnt + 1 == retry_threshold) {
                rehash();
                loop_cnt = static_cast<int>(-1);
            }
        }
    }

    void rehash() {
        // choose new hash function.
        // with multiple testing experiments,
        // here counts a lot to the efficiency of our data structure.
        hash1_ = 1;
        hash2_ = rand() % retry_threshold + 1;

        // do a in-place rehash
        for (int i = 0; i < static_cast<int>(bucket.size()); ++i) {
            if (bucket[i] == EMPTY)
                continue;
            auto old = bucket[i];
            bucket[i] = EMPTY;
            put_new_val(old.first, old.second);
        }
    }

public:
    void put(K key, V value) {
        auto hash_val_1 = hash1(key), hash_val_2 = hash2(key);
        if (bucket[hash_val_1].first == key)
            bucket[hash_val_1].second = value;
        else if (bucket[hash_val_2].first == key)
            bucket[hash_val_2].second = value;
        else
            put_new_val(key, value);
    }

    PKV get(K key) {
        auto hash_val_1 = hash1(key), hash_val_2 = hash2(key);
        if (bucket[hash_val_1].first == key) {
            return bucket[hash_val_1];
        }
        if (bucket[hash_val_2].first == key) {
            return bucket[hash_val_2];
        }
        return EMPTY;
    }

    void del(V key) {
        auto hash_val_1 = hash1(key), hash_val_2 = hash2(key);
        if (bucket[hash_val_1].first == key) {
            bucket[hash_val_1] = EMPTY;
            --count_;
        }
        if (bucket[hash_val_2].first == key) {
            bucket[hash_val_2] = EMPTY;
            --count_;
        }
    }

    int size() {
        return static_cast<int>(bucket.size());
    }

    int get_hash_param1() {
        return hash1_;
    }

    int get_hash_param2() {
        return hash2_;
    }

    int get_actual_hash_val(K key) {
        auto hash_val_1 = hash1(key), hash_val_2 = hash2(key);
        if (bucket[hash_val_1].first == key) {
            return hash_val_1;
        }
        if (bucket[hash_val_2].first == key) {
            return hash_val_2;
        }
        return -1;
    }
};

} // namespace CUCKOO_HASH