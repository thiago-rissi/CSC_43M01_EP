#include <bits/stdc++.h>
using namespace std;

void solve_case(int price, const vector<int> &values) {
    int total = 0;
    for (int value : values) {
        total += value;
    }

    const int INF = numeric_limits<int>::max() / 2;
    vector<int> dp(total + 1, INF);
    dp[0] = 0;

    for (int value : values) {
        for (int sum = total; sum >= value; sum--) {
            dp[sum] = min(dp[sum], dp[sum - value] + 1);
        }
    }

    for (int sum = price; sum <= total; sum++) {
        if (dp[sum] != INF) {
            cout << sum << " " << dp[sum] << "\n";
            return;
        }
    }
}

int main() {
    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        int price, n;
        cin >> price >> n;
        vector<int> values(n);
        for (int j = 0; j < n; j++) {
            cin >> values[j];
        }
        solve_case(price, values);
    }

    return 0;
}
