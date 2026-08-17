#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int u, v;
    int w;
};

const long long INF = 4e18;

bool bellman_ford(
    int n,
    const vector<Edge>& edges,
    int source
) {
    vector<long long> dist(n, INF);

    dist[source] = 0;

    for (int i = 0; i < n - 1; i++) {
        bool changed = false;

        for (const Edge& e : edges) {
            if (dist[e.u] == INF) continue;

            if (dist[e.u] + e.w < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.w;
                changed = true;
            }
        }

        if (!changed) break;
    }

    bool has_negative_cycle = false;

    for (const Edge& e : edges) {
        if (dist[e.u] == INF) continue;

        if (dist[e.u] + e.w < dist[e.v]) {
            has_negative_cycle = true;
            break;
        }
    }

    return has_negative_cycle;
}

bool has_cycle(int n, const std::vector<int>& a, const std::vector<int>& b) {
    vector<Edge> edges;
    int source = -1;
    for(int i = 0; i < n; i++){
        int low = i - a[i];
        int high = i + b[i];

        if (low >= 0){
            Edge e;
            e.u = i;
            e.v = low;
            e.w = -a[i];
            edges.push_back(e);
        }

        if (high < n){
            Edge e;
            e.u = i;
            e.v = high;
            e.w = -b[i];
            edges.push_back(e);
        }
        if (high != i || low != i)
            source = i;

    }

    if (source == -1){
        return false;
    }

    bool has_cycle = bellman_ford(n, edges, source);
    
    return has_cycle;
}


int main() {
    int n;
    std::cin >> n;

    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i] >> b[i];
    }

    std::cout << (has_cycle(n, a, b) ? "YES" : "NO") << std::endl;
    return 0;
}
