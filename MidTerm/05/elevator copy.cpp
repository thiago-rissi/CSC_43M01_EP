#include <chrono>
#include <iostream>
#include <vector>

using namespace std;

/**
 * @param a Offset a for each floor.
 * @param b Offset b for each floor.
 * @return Minimum number of rides to reach floor N (1-indexed), or -1 if
 *         impossible.
 */
int min_elevator_rides(const std::vector<int> &a, const std::vector<int> &b) {
    int N = a.size();

    vector<int> dp(N, 0);

    for (int i = 1; i < N; i++) {
        int min = N + 1;
        for (int j = i - 1; j >= 0; j--) {
            if (a[j] == i - j || b[j] == i - j) {
                if (1 + dp[j] < min)
                    min = 1 + dp[j];
            }
        }
        dp[i] = min;
    }

    int res = dp[N - 1] < N + 1 ? dp[N - 1] : -1;
    return res;
}

int main() {
    int N;
    std::cin >> N;

    std::vector<int> a(N), b(N);
    for (size_t i = 0; i < N; ++i) {
        std::cin >> a[i] >> b[i];
    }

    int64_t res;
    chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    res = min_elevator_rides(a, b);
    chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << res << std::endl;

    std::cout << "Runtime = "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()
              << "[ms]" << std::endl;
    return 0;
}
