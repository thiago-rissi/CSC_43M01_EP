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

// #include <climits>
// #include <iostream>
// #include <queue>
// #include <vector>
// using namespace std;

// vector<int> dijkstra(vector<vector<pair<int, int>>> &adj, int src) {

//     int V = adj.size();

//     // Min-heap (priority queue) storing pairs of (distance, node)
//     priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

//     vector<int> dist(V, INT_MAX);

//     // Distance from source to itself is 0
//     dist[src] = 0;
//     pq.emplace(0, src);

//     // Process the queue until all reachable vertices are finalized
//     while (!pq.empty()) {
//         auto top = pq.top();
//         pq.pop();

//         int d = top.first;
//         int u = top.second;

//         // If this distance not the latest shortest one, skip it
//         if (d > dist[u])
//             continue;

//         // Explore all neighbors of the current vertex
//         for (auto &p : adj[u]) {
//             int v = p.first;
//             int w = p.second;

//             // If we found a shorter path to v through u, update it
//             if (dist[u] + w < dist[v]) {
//                 dist[v] = dist[u] + w;
//                 pq.emplace(dist[v], v);
//             }
//         }
//     }

//     // Return the final shortest distances from the source
//     return dist;
// }

// int main() {
//     int src = 0;

//     vector<vector<pair<int, int>>> adj(5);
//     adj[0] = {{1, 4}, {2, 8}};
//     adj[1] = {{0, 4}, {4, 6}, {2, 3}};
//     adj[2] = {{0, 8}, {3, 2}, {1, 3}};
//     adj[3] = {{2, 2}, {4, 10}};
//     adj[4] = {{1, 6}, {3, 10}};

//     vector<int> result = dijkstra(adj, src);

//     for (int d : result)
//         cout << d << " ";
//     cout << "
//             ";

//         return 0;
// }
