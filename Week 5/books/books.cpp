#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

int knapsackBottomUp(vector<int> &weight, vector<int> &value, int W) {
    int N = weight.size();

    vector<vector<int>> dp(N + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= N; ++i) {
        for (int w = 1; w <= W; ++w) {
            if (weight[i - 1] <= w) {
                // Max value by including the current item
                // or excluding it
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - weight[i - 1]] + value[i - 1]);
            } else {
                // If current item's weight is more than the
                // current capacity, exclude it
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Return the maximum value that can be obtained with
    // the given capacity W
    return dp[N][W];
}

int main() {
    int N;
    cin >> N;

    vector<int> pages(N, 0);

    for (size_t i = 0; i < N; i++) {
        cin >> pages[i];
    }

    sort(pages.begin(), pages.end());

    int best_value = knapsackBottomUp(pages, pages, 1000);

    int slack = 1000 - best_value;

    for (int i = 1; i <= slack; i++) {
        int value = knapsackBottomUp(pages, pages, 1000 + i);
        if (value > best_value) {
            best_value = value;
        }
    }

    cout << best_value << endl;

    return 0;
}