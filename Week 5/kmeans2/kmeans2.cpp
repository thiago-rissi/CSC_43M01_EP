#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

double sumdist(const vector<double> &points, int j, int n) {

    double mean;
    double sum = 0.0;
    for (int i = n - 1; i >= j - 1; i--) {
        sum += points[i];
    }
    mean = sum / (n - j + 1);

    double dist = 0.0;
    for (int i = n - 1; i >= j - 1; i--) {
        dist += (mean - points[i]) * (mean - points[i]);
    }

    return dist;
}

double recurrence(const vector<double> &points, int n, int k,
                  vector<vector<double>> &memo) {
    if (n == 0)
        return 0.0;

    else if (n != 0 && k == 0)
        return numeric_limits<double>::infinity();

    else if (memo[n][k] >= 0.0)
        return memo[n][k];

    else {
        double value;
        double OPT = numeric_limits<double>::infinity();
        for (int j = 1; j <= n; j++) {
            value = recurrence(points, j - 1, k - 1, memo) + sumdist(points, j, n);
            if (value < OPT)
                OPT = value;
        }
        memo[n][k] = OPT;
        return OPT;
    }
}

int main() {
    int k, n;
    cin >> k >> n;

    vector<double> points(n, 0);

    for (size_t i = 0; i < n; i++) {
        cin >> points[i];
    }

    sort(points.begin(), points.end());

    vector<vector<double>> memo(n + 1, vector<double>(k + 1, -1.0));

    double res = recurrence(points, n, k, memo);
    if (res < 5e-13) {
        res = 0.0;
    }

    cout << fixed << setprecision(6) << res << endl;

    return 0;
}
