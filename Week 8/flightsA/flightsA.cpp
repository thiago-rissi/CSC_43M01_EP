#include <bits/stdc++.h>
using namespace std;

using Graph = vector<vector<pair<int, long long>>>;

const long long INF = 4e18;

vector<long long> dijkstra(const Graph &graph, int source) {
    int n = graph.size();

    vector<long long> dist(n, INF);

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
    vector<long long> distances = dijkstra(graph, s);

    if (distances[d] == INF) {
        cout << -1;
    } else {
        cout << distances[d];
    }

    return 0;
}
