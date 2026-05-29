#include <bits/stdc++.h>
using namespace std;

struct stone {
    int a, b, h;
    long long cost_cents;

    stone(int aa, int bb, int hh) : a(aa), b(bb), h(hh), cost_cents(1LL * (aa + bb) * hh) {}
};

void solve_case(const vector<stone> &stones, int porch, int gazebo) {
    const int MAX_WIDTH = 1000;
    const long long INF = numeric_limits<long long>::max() / 4;

    vector<vector<pair<int, long long>>> graph(MAX_WIDTH + 1);

    for (const stone &s : stones) {
        graph[s.a].push_back({s.b, s.cost_cents});
        graph[s.b].push_back({s.a, s.cost_cents});
    }

    vector<long long> dist(MAX_WIDTH + 1, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                   greater<pair<long long, int>>>
        pq;

    dist[porch] = 0;
    pq.push({0, porch});

    while (!pq.empty()) {
        auto [current_cost, width] = pq.top();
        pq.pop();

        if (current_cost != dist[width]) {
            continue;
        }
        if (width == gazebo) {
            break;
        }

        for (auto [next_width, stone_cost] : graph[width]) {
            long long next_cost = current_cost + stone_cost;
            if (next_cost < dist[next_width]) {
                dist[next_width] = next_cost;
                pq.push({next_cost, next_width});
            }
        }
    }

    cout << fixed << setprecision(2) << (dist[gazebo] / 100.0) << '\n';
}

int main() {
    int n;
    cin >> n;

    while (n != 0) {
        vector<stone> stones;

        for (int i = 0; i < n; i++) {
            int a, b, h;
            cin >> a >> b >> h;
            stones.push_back(stone(a, b, h));
        }

        int porch, gazebo;
        cin >> porch >> gazebo;

        solve_case(stones, porch, gazebo);

        cin >> n;
    }

    return 0;
}
