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

    for (size_t i = 0; i < m; i++) {
        cin >> costs[i];
    }
    sort(costs.begin(), costs.end());

    DP[0] = 0;

    for (int i = 1; i <= N; i++) {
        int min = DP[i];
        for (int cost : costs) {

            if (i - cost < 0)
                break;

            else if (DP[i - cost] < min) {
                min = DP[i - cost];
            }
        }

        DP[i] = 1 + min;
    }

    if (DP[N] >= N + 1) {
        cout << "Impossible" << endl;
    } else {
        cout << DP[N] << endl;
    }

    return 0;
}