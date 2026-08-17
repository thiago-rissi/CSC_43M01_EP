#include <bits/stdc++.h>
using namespace std;

const long long INF = 4e18;

using Graph = vector<vector<pair<int, long long>>>;

struct Edge{
    int u, v;
};

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

int dfs(const vector<vector<int>>& graph, int source, const vector<bool> marks) {
    int n = graph.size();

    long long min_dist = n+1;

    bool has_marked = false;

    vector<bool> visited(n, false);
    vector<int> order;

    stack<int> st;
    st.push(source);

    long long dist = 0;
    while (!st.empty()) {
        int u = st.top();
        st.pop();
        
        if(marks[u]){
            has_marked = true;
        }
        
        if (u == n-1){
            if(has_marked){
                if(dist < min_dist){
                    min_dist = dist;
                }
                dist = 0;
                has_marked = false;
            }
        }

        if(graph[u].empty()){
            dist = 0;
            has_marked = false;
        }else{
            for (int v : graph[u]) {
                st.push(v);
            }
            dist++;
        }
    }

    return min_dist;
}

int main() {
    int N, E, M;
    cin >> N >> E >> M;

    vector<bool> marks(M+1, false);
    vector<Edge> edges;

    for(int i = 0; i < M; i++){
        int m;
        cin >> m;
        marks[M]=true;
    }

    for(int i = 0; i < E; i++){
        Edge e;
        cin >> e.u >> e.v;
        edges.push_back(e);
    }

    
    vector<vector<int>> graph(N+1);

    for(Edge e : edges){
        graph[e.u].push_back(e.v);
    }

    
    cout << dfs(graph, 1, marks) << "\n";
   
    return 0;
}