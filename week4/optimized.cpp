
#include <cstdint>
#include <cstdio>
#include <chrono>
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>

static inline uint32_t lcg_next(uint32_t &v) {
    v = 1664525u * v + 1013904223u; // natural wrap mod 2^32
    return v;
}

// Kadane: equivalent to max over all non-empty subarrays (O(n^2) in original)
static int64_t max_subarray_sum(int n, uint32_t seed, int min_val, int max_val) {
    uint32_t v = seed;
    uint32_t range = (uint32_t)(max_val - min_val + 1);
    int64_t best = INT64_MIN;
    int64_t cur = 0;
    bool first = true;
    for (int i = 0; i < n; ++i) {
        int64_t x = (int64_t)(lcg_next(v) % range) + min_val;
        if (first) { cur = x; first = false; }
        else cur = std::max(x, cur + x);
        if (cur > best) best = cur;
    }
    return best;
}

static int64_t total_max_subarray_sum(int n, uint32_t initial_seed, int min_val, int max_val) {
    int64_t total = 0;
    uint32_t g = initial_seed;
    for (int k = 0; k < 20; ++k) {
        uint32_t seed = lcg_next(g);
        total += max_subarray_sum(n, seed, min_val, max_val);
    }
    return total;
}

int main() {
    int n = 10000;
    uint32_t initial_seed = 42;
    int min_val = -10, max_val = 10;

    auto start = std::chrono::high_resolution_clock::now();
    int64_t result = total_max_subarray_sum(n, initial_seed, min_val, max_val);
    auto end = std::chrono::high_resolution_clock::now();
    double elapsed = std::chrono::duration<double>(end - start).count();

    std::cout << "Total Maximum Subarray Sum (20 runs): " << result << "\n";
    std::cout << "Execution Time: " << std::fixed << std::setprecision(6) << elapsed << " seconds\n";
    return 0;
}
