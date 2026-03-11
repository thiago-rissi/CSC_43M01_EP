#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cassert>
#include <chrono>

/**
 * @brief  Linear scan to find the peak of a unimodal array.  O(n).
 * @param  arr  Pointer to a C-style array of integers that is strictly
 *              increasing and then strictly decreasing (unimodal).
 * @param  n    Number of elements in arr; must be > 0.
 * @return Index of the maximum element.
 */
int peak_linear(const int* arr, int n) {
    assert(n > 0);
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1])
            return i;
    }
    return n - 1;   // peak is the last element
}

/**
 * @brief  Binary search to find the peak of a unimodal array.  O(log n).
 * @param  arr  Pointer to a C-style array of integers that is strictly
 *              increasing and then strictly decreasing (unimodal).
 * @param  n    Number of elements in arr; must be > 0.
 * @return Index of the maximum element.
 */
int peak_binary(const int* arr, int n) {
    assert(n > 0);
    int l = 0;
    int r = n-1;
    int mid;

    while (l < r) {
        mid = l + (r - l) / 2;

        if (arr[mid] < arr[mid + 1]) {
            l = mid + 1;
        }
        else {
            r = mid;
        }
    }

    return l;
}

/**
 * @brief  Fill a pre-allocated buffer with a random unimodal sequence.
 * @param  arr  Caller-allocated output buffer of at least n ints.  On return,
 *              arr[0..n-1] is strictly increasing up to the peak index and
 *              strictly decreasing afterwards.
 * @param  n    Number of elements to write; must be > 0.  The peak index is
 *              chosen uniformly at random from [0, n-1].
 */
void generate_unimodal(int* arr, int n) {
    assert(n > 0);
    int peak = rand() % n;
    int counter = 0;

    for (int i = 0; i < peak; ++i) {
        arr[i] = counter++; 
    }
    for (int i = peak; i < n; ++i) {
        arr[i] = counter--; 
    }

    return;
}

// Assumes that generate_unimodal is implemented
void test_correctness() {
    constexpr int N = 15;
    int data[N];

    for (int trial = 0; trial < 100; ++trial) {
        generate_unimodal(data, N);

        int res_linear = peak_linear(data, N);
        int res_binary = peak_binary(data, N);

        // std::cout << res_linear << std::endl;
        // std::cout << res_binary << std::endl;

        assert(res_linear == res_binary && "Wrong answer");
    }
    std::cout << "All correctness tests passed.\n\n";
}

void test_bigdata() {
    constexpr int NN = 500000;
    int bigdata[NN];
    for (int i = 0; i < NN / 2 - 1; ++i) {
        bigdata[i] = i; 
    }
    for (int i = NN / 2 - 1; i < NN; ++i) {
        bigdata[i] = NN - i;
    }

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    int res = peak_linear(bigdata, NN);
    // int res = peak_binary(bigdata, NN);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Runtime = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "[ns]" << std::endl;
    std::cout << "Result = " << res << std::endl;
}

void run_on_external_input() {
    int n;
    std::cin >> n;
    assert(n > 0);

    int* data = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> data[i];
    }

    std::cout << peak_binary(data, n) << std::endl;

    delete[] data;
}

int main() {
    test_correctness();
    // test_bigdata();
    // run_on_external_input();

    return 0;
}
