#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <vector>

namespace CUCKOO_HASH {

using PII = std::pair<int, int>;
using std::vector;
const PII EMPTY = {-1, -1};

class CuckooHash {

public:
    void put(int key, int value) {
        auto hash_val_1 = hash1(key), hash_val_2 = hash2(key);
        if (bucket[hash_val_1].first == key)  
            bucket[hash_val_1].second = value;
        else if (bucket[hash_val_2].first == key)     
            bucket[hash_val_2].second = value;
        else
            put_new_val(key, value);
    }

    PII get(int key) {
        auto hash_val_1 = hash1(key), hash_val_2 = hash2(key);
        if (bucket[hash_val_1].first == key) {
            return bucket[hash_val_1];
        }
        if (bucket[hash_val_2].first == key) {
            return bucket[hash_val_2];
        }
        return EMPTY;
    }
    
    void del(int key) {
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

private:
    // bucket to store the k-v elements.
    // suppose size = bucket_size,
    // the bucket is splited into [0, size / 2), [size / 2, size).
    vector<PII> bucket = vector<PII>(2, EMPTY);

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
    int hash(int hash_param, int key) {
        return std::hash<int>()(key) / hash_param % (static_cast<int>(bucket.size()) / 2);
    }
    int hash1(int key) {
        return hash(hash1_, key);
    }
    int hash2(int key) {
        return hash(hash2_, key) + (static_cast<int>(bucket.size()) / 2);
    }

    // dynamically adjust the size of bucket.
    void resize() {
        bucket.resize(static_cast<int>(bucket.size()) * 2, EMPTY);
        retry_threshold = 10 * static_cast<int>(log2(static_cast<int>(bucket.size())));
        rehash();
    }

    // put new val into bucket
    void put_new_val(int key, int value) {

        // add new element into hash table
        ++count_;

        // set load balance between [0, 0.25].
        // why the bound is 0.25?
        // this maybe a magic number from the paper.
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
            if (bucket[i] == EMPTY) continue;
            auto old = bucket[i];
            bucket[i] = EMPTY;
            put_new_val(old.first, old.second);
        
        }
    }
};

} // namespace CUCKOO_HASH