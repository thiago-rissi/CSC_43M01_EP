#include <chrono>
#include <iostream>
#include <iterator>
#include <list>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
using i64 = int64_t;
using u64 = uint64_t;

template <typename T> class Graph {
    typename std::unordered_map<T, std::list<T>> adj;

  public:
    Graph() {};

    void add_vertex(const T &v);

    int num_vertices() const { return this->adj.size(); }

    void add_edge(const T &from, const T &to);

    typename std::unordered_map<T, std::list<T>>::const_iterator cbegin() const {
        return adj.cbegin();
    }

    typename std::unordered_map<T, std::list<T>>::const_iterator cend() const { return adj.cend(); }

    typename std::list<T>::const_iterator edges_begin(const T &v) const {
        return adj.at(v).cbegin();
    }

    typename std::list<T>::const_iterator edges_end(const T &v) const { return adj.at(v).cend(); }
};

// -----------------------------------------------------------

template <typename T> void Graph<T>::add_vertex(const T &v) {
    if (this->adj.find(v) != this->adj.end()) {
        return;
    }
    adj.insert({v, std::list<T>()});
}

template <typename T> void Graph<T>::add_edge(const T &from, const T &to) {
    auto from_iter = this->adj.find(from);
    auto to_iter = this->adj.find(to);
    if (from_iter == this->adj.end() || to_iter == this->adj.end()) {
        throw std::invalid_argument("One of the vertices is not in the graph");
    }
    from_iter->second.push_back(to);
}

// -----------------------------------------------------------

namespace std {
template <> struct hash<std::pair<int, int>> {
    size_t operator()(const std::pair<int, int> &p) const { return 1000 * p.first + p.second; }
};
} // namespace std

int minrides(const Graph<pair<int, int>> &g, int n, int m) {
    deque<pair<int, int>> q;
    unordered_map<pair<int, int>, int> dist;

    dist[{0, 0}] = 0;
    q.push_back({0, 0});
    pair<int, int> target = {n - 1, m - 1};

    while (!q.empty()) {
        pair<int, int> i = q.front();
        q.pop_front();

        if (i == target) {
            return dist[i];
        }

        for (auto it = g.edges_begin(i); it != g.edges_end(i); it++) {
            if (dist.find(*it) == dist.end()) {
                dist[*it] = dist[i] + 1;
                q.push_back(*it);
            }
        }
    }

    if (dist.find(target) == dist.end())
        return -1;

    return dist[target];
}

int main() {
    int n, m, ks, k;
    Graph<pair<int, int>> g;

    cin >> n >> m;

    vector<vector<int>> grid(n, vector<int>(m, 0));

    for (int i = 0; i < n; i++) {
        string line;
        cin >> line;

        int j = 0;
        for (char c : line) {
            int k = c - '0';
            grid[i][j] = k;
            j++;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            pair<int, int> v = {i, j};
            g.add_vertex(v);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int k = grid[i][j];

            pair<int, int> v = {i, j};

            if (j + k < m) {
                pair<int, int> v_right = {i, j + k};
                g.add_edge(v, v_right);
            }

            if (j - k >= 0) {
                pair<int, int> v_left = {i, j - k};
                g.add_edge(v, v_left);
            }

            if (i + k < n) {
                pair<int, int> v_down = {i + k, j};
                g.add_edge(v, v_down);
            }

            if (i - k >= 0) {
                pair<int, int> v_up = {i - k, j};
                g.add_edge(v, v_up);
            }
        }
    }

    cout << minrides(g, n, m);

    return 0;
}