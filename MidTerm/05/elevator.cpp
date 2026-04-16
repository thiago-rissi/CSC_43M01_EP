#include <chrono>
#include <iostream>
#include <vector>

using namespace std;

int min_elevator_rides(const std::vector<int> &a, const std::vector<int> &b) {
    int N = a.size();

    vector<int> dp(N, 0);
    vector<int> indexes;

    indexes.push_back(0);
    int min, index;
    for (int i = 1; i < N; i++) {
        min = N + 1;
        index = N + 1;
        for (int j : indexes) {
            if (a[j] == i - j || b[j] == i - j) {
                if (1 + dp[j] < min) {
                    min = 1 + dp[j];
                    index = i;
                }
            }
        }

        dp[i] = min;
        if (index != N + 1)
            indexes.push_back(index);
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

    // std::cout << "Runtime = "
    //           << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()
    //           << "[ms]" << std::endl;
    return 0;
}
