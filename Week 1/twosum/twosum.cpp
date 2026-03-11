#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

// ─── Search functions ────────────────────────────────────────────────────────

/**
 * @brief  Find an index i such that there exists j >= i with
 *         arr[i] + arr[j] == target, using a naive quadratic scan.
 * @param  arr     Pointer to a C-style array sorted in strictly ascending order.
 * @param  n       Number of elements in arr; must be >= 0.
 * @param  target  The desired sum.
 * @return An index i for which a valid j exists, or -1 if no such pair exists.
 */
int two_sum_quadratic(const int* arr, int n, int target) {
    for (int i = 0; i < n; ++i)
        for (int j = i; j < n; ++j) {
            if (arr[i] + arr[j] == target) return i;
            if (arr[i] + arr[j] >  target) break;
        }
    return -1;
}

/**
 * @brief  Find an index i such that there exists j >= i with
 *         arr[i] + arr[j] == target, with complexity O(n log n).
 *
 * @param  arr     Pointer to a C-style array sorted in strictly ascending order.
 * @param  n       Number of elements in arr; must be >= 0.
 * @param  target  The desired sum.
 * @return An index i for which a valid j exists, or -1 if no such pair exists.
 */
int two_sum_loglinear(const int* arr, int n, int target) {
    int temp_target;
    for (int i = 0; i < n; i++){
        temp_target = target - arr[i];
        // std::cout << temp_target << std::endl;
        // if (temp_target < 0) break;
        auto it = std::lower_bound(arr, arr + n, temp_target);
        if (it != arr + n) return i;
    }
    return -1;
}

/**
 * @brief  Find an index i such that there exists j >= i with
 *         arr[i] + arr[j] == target, in linear time.
 *
 * @param  arr     Pointer to a C-style array sorted in strictly ascending order.
 * @param  n       Number of elements in arr; must be >= 0.
 * @param  target  The desired sum.
 * @return An index i for which a valid j exists, or -1 if no such pair exists.
 */
int two_sum_linear(const int* arr, int n, int target) {
    int l = 0;
    int r = n - 1;
    int sum = 0;

    while (r >= l){
        sum = arr[r] + arr[l];
        if (sum < target){
            l++;
        }
        else if (sum > target) {
            r--;
        }
        else {
            return l;
        }
    }
    return -1;
}

int main() {
    int n, target;
    std::cin >> n >> target;
    int* arr = new int[n];

    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    int res = two_sum_linear(arr, n, target);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Answer is " << res << std::endl;
    std::cout << "Runtime = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[microsec]" << std::endl;


    delete[] arr;
}
