#include <bits/stdc++.h>
using namespace std;

using Graph = vector<vector<pair<int, long long>>>;

const long long INF = 4e18;

vector<long long> dijkstra(const Graph &graph, int source, vector<int> &parent) {
    int n = graph.size();

    vector<long long> dist(n, INF);
    parent.assign(n, -1);

    dist[source] = 0;

    priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                   greater<pair<long long, int>>>
        pq;

    pq.push({0, source});
    while (!pq.empty()) {
        auto [du, u] = pq.top();
        pq.pop();
        if (du != dist[u])
            continue;
        for (auto [v, w] : graph[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}
struct flight {
    int s, d;
    int duration;
};

int main() {
    int N, M, s, d;
    cin >> N >> M >> s >> d;

    vector<int> changing_times(N, 0);

    for (int i = 0; i < N; i++) {
        cin >> changing_times[i];
    }

    vector<flight> flights(M);

    for (int i = 0; i < M; i++) {
        cin >> flights[i].s >> flights[i].d >> flights[i].duration;
    }

    Graph graph(N);
    for (flight f : flights) {
        long long change_at_d = (f.d == d ? 0 : changing_times[f.d]);
        long long change_at_s = (f.s == d ? 0 : changing_times[f.s]);

        graph[f.s].push_back({f.d, f.duration + change_at_d});
        graph[f.d].push_back({f.s, f.duration + change_at_s});
    }
    vector<int> parent;
    vector<long long> distances = dijkstra(graph, s, parent);

    if (distances[d] == INF) {
        cout << -1 << '\n' << '\n';
    } else {
        cout << distances[d] << '\n';

        vector<int> path;
        for (int cur = d; cur != -1; cur = parent[cur]) {
            path.push_back(cur);
        }
        reverse(path.begin(), path.end());

        for (int i = 0; i < (int)path.size(); i++) {
            if (i > 0)
                cout << ' ';
            cout << path[i];
        }
        cout << '\n';
    }

    return 0;
}
