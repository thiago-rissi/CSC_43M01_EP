#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int m, N;
    cin >> m >> N;

    vector<int> costs(m, 0);
    vector<int> DP(N + 1, N + 1);
    vector<vector<int>> coins(N + 1, vector<int>(m, 0));

    for (size_t i = 0; i < m; i++) {
        cin >> costs[i];
    }
    // sort(costs.begin(), costs.end());

    DP[0] = 0;

    for (int i = 1; i <= N; i++) {
        int min = DP[i];
        int cost_id = 0;

        for (int j = 0; j < m; j++) {
            int cost = costs[j];
            if (i - cost < 0)
                continue;

            else if (DP[i - cost] < min) {
                min = DP[i - cost];
                cost_id = j;
            }
        }

        if (min < N + 1) {
            DP[i] = 1 + min;
            vector<int> v = coins[i - costs[cost_id]];
            coins[i].assign(v.begin(), v.end());
            coins[i][cost_id] += 1;
        }
    }

    if (DP[N] == N + 1) {
        cout << "Impossible" << endl;
    } else {
        vector<int> res = coins[N];
        for (int num : res) {
            cout << num << " ";
        }
    }

    return 0;
}