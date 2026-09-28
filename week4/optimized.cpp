
#include <iostream>
#include <iomanip>
#include <vector>
#include <climits>
#include <chrono>
#include <cstdint>

static const uint64_t LCG_A = 1664525ULL;
static const uint64_t LCG_C = 1013904223ULL;
static const uint64_t LCG_M = 1ULL << 32;

inline uint64_t lcg_next(uint64_t &value) {
    value = (LCG_A * value + LCG_C) % LCG_M;
    return value;
}

long long max_subarray_sum(int n, uint64_t seed, int min_val, int max_val) {
    uint64_t state = seed;
    int range = max_val - min_val + 1;
    
    std::vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        nums[i] = (int)(lcg_next(state) % (uint64_t)range) + min_val;
    }
    
    // O(n^2) as in original Python
    long long max_sum = LLONG_MIN;
    for (int i = 0; i < n; i++) {
        long long current_sum = 0;
        for (int j = i; j < n; j++) {
            current_sum += nums[j];
            if (current_sum > max_sum)
                max_sum = current_sum;
        }
    }
    return max_sum;
}

long long total_max_subarray_sum(int n, uint64_t initial_seed, int min_val, int max_val) {
    long long total_sum = 0;
    uint64_t state = initial_seed;
    for (int i = 0; i < 20; i++) {
        uint64_t seed = lcg_next(state);
        total_sum += max_subarray_sum(n, seed, min_val, max_val);
    }
    return total_sum;
}

int main() {
    int n = 10000;
    uint64_t initial_seed = 42;
    int min_val = -10;
    int max_val = 10;

    auto start = std::chrono::high_resolution_clock::now();
    long long result = total_max_subarray_sum(n, initial_seed, min_val, max_val);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Total Maximum Subarray Sum (20 runs): " << result << std::endl;
    std::cout << "Execution Time: " << std::fixed << std::setprecision(6) << elapsed.count() << " seconds" << std::endl;

    return 0;
}
