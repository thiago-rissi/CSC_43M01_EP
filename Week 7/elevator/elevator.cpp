#include <bits/stdc++.h>

using namespace std;
using i64 = int64_t;
using u64 = uint64_t;

i64 minrides(const vector<pair<i64, i64>> &data) {
    deque<i64> q;
    i64 N = data.size();
    vector<i64> dist(N, -1);

    dist[0] = 0;
    q.push_back(0);

    while (!q.empty()) {
        i64 i = q.front();
        q.pop_front();

        if (i == N - 1)
            return dist[i];

        for (i64 j : {i - data[i].first, i + data[i].second}) {
            if (j >= 0 && j < N && dist[j] < 0) {
                q.push_back(j);
                dist[j] = dist[i] + 1;
            }
        }
    }

    return dist[N - 1];
}

int main() {
    i64 N;
    cin >> N;
    vector<pair<i64, i64>> data;

    while (N-- > 0) {
        i64 a, b;
        cin >> a >> b;
        data.push_back({a, b});
    }

    cout << minrides(data);
    return 0;
}