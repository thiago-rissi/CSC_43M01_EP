#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

double sumdist(const vector<double> &prefix, const vector<double> &prefix_square, int l, int r) {
    double sum = prefix[r] - prefix[l - 1];
    double sum_square = prefix_square[r] - prefix_square[l - 1];
    double len = r - l + 1;
    return sum_square - (sum * sum) / len;
}

int main() {
    int k, n;
    cin >> k >> n;

    int used_clusters = min(k, n);

    vector<double> points(n, 0);

    for (int i = 0; i < n; i++) {
        cin >> points[i];
    }

    sort(points.begin(), points.end());

    vector<double> prefix(n + 1, 0.0), prefix_square(n + 1, 0.0);
    for (int i = 1; i <= n; i++) {
        prefix[i] = prefix[i - 1] + points[i - 1];
        prefix_square[i] = prefix_square[i - 1] + points[i - 1] * points[i - 1];
    }

    vector<vector<double>> DP(n + 1, vector<double>(used_clusters + 1, 0.0));
    vector<vector<int>> indexes(n + 1, vector<int>(used_clusters + 1, 0));

    for (int i = 1; i <= n; i++) {
        DP[i][0] = numeric_limits<double>::infinity();
    }

    DP[0][0] = 0.0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= min(used_clusters, i); j++) {
            double value;
            int index = -1;
            double OPT = numeric_limits<double>::infinity();
            for (int m = j; m <= i; m++) {
                value = DP[m - 1][j - 1] + sumdist(prefix, prefix_square, m, i);
                if (value < OPT) {
                    OPT = value;
                    index = m - 1;
                }
            }

            indexes[i][j] = index;
            DP[i][j] = OPT;
        }
    }

    // cout << fixed << setprecision(6) << DP[n][k] << endl;

    vector<int> starts(used_clusters, 0);

    int cur_i = n;
    for (int j = used_clusters; j >= 1; j--) {
        starts[j - 1] = indexes[cur_i][j];
        cur_i = indexes[cur_i][j];
    }

    cout << used_clusters;
    for (int start : starts) {
        cout << ' ' << start;
    }

    return 0;
}
