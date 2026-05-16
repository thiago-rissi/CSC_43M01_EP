#include <bits/stdc++.h>

using namespace std;

float euclidean_dist(pair<float, float> v, pair<float, float> q) {
    return sqrt(pow(v.first - q.first, 2) + pow(v.second - q.second, 2));
}

int minair(vector<pair<float, float>> &towns, int D) {
    int N = towns.size();
    vector<bool> visited(N, false);
    int components = 0;

    for (int start = 0; start < N; start++) {
        if (visited[start])
            continue;

        components++;
        queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v = 0; v < N; v++) {
                if (!visited[v] && euclidean_dist(towns[u], towns[v]) <= D) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }

    return components - 1;
}

int main() {
    int N, D;
    cin >> N >> D;
    vector<pair<float, float>> towns;

    for (int i = 0; i < N; i++) {
        pair<float, float> v;
        cin >> v.first >> v.second;
        towns.push_back(v);
    }

    cout << minair(towns, D);
}