#include <bits/stdc++.h>
using namespace std;

using Graph = vector<vector<pair<int, double>>>;

const double INF = 1e100;

double prim(const Graph &graph) {
    int n = graph.size();
    vector<bool> in_mst(n, false);
    vector<double> min_edge(n, INF);
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;

    min_edge[0] = 0;
    pq.push({0, 0});

    double total_weight = 0;
    int vertices_used = 0;

    while (!pq.empty()) {
        auto [weight, u] = pq.top();
        pq.pop();

        if (in_mst[u])
            continue;

        in_mst[u] = true;
        total_weight += weight;
        vertices_used++;
        for (auto [v, w] : graph[u]) {
            if (!in_mst[v] && w < min_edge[v]) {
                min_edge[v] = w;
                pq.push({w, v});
            }
        }
    }
    if (vertices_used != n) {
        throw runtime_error(" Graph is not connected ");
    }
    return total_weight;
}

int main() {
    int N;
    cin >> N;

    vector<pair<double, double>> islands(N);
    for (int i = 0; i < N; i++) {
        cin >> islands[i].first >> islands[i].second;
    }

    Graph graph(N);
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            double dx = islands[i].first - islands[j].first;
            double dy = islands[i].second - islands[j].second;
            double distance = sqrt(dx * dx + dy * dy);
            graph[i].push_back({j, distance});
            graph[j].push_back({i, distance});
        }
    }

    cout << fixed << setprecision(4) << prim(graph) << '\n';

    return 0;
}
