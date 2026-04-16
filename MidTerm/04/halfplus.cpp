#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief Finds the size of the smallest subset of the array whose sum
 *        strictly exceeds the sum of all remaining elements.
 *
 * A subset S satisfies the condition iff sum(S) > total - sum(S),
 * i.e. sum(S) > total / 2.
 *
 * @param arr The input array of non-negative integers.
 * @return The minimum number of elements whose sum exceeds half the total.
 */
int smallest_majority_subset(std::vector<uint32_t> &arr) {
    uint64_t total = 0;
    for (uint32_t value : arr)
        total += value;

    sort(arr.begin(), arr.end());

    int counter = 0;
    uint64_t cum_sum = 0;
    for (auto it = arr.rbegin(); it != arr.rend(); it++) {
        cum_sum += (*it);
        counter++;
        if (cum_sum > total - cum_sum)
            break;
    }

    return counter;
}

int main() {
    int n;
    std::cin >> n;

    std::vector<uint32_t> arr(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    int res;
    chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    res = smallest_majority_subset(arr);
    chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << res << std::endl;
    // std::cout << "Runtime = " << std::chrono::duration_cast<std::chrono::milliseconds>(end -
    // begin).count() << "[ms]" << std::endl;

    return 0;
}
