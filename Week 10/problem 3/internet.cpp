#include <bits/stdc++.h>
using namespace std;

void dfs(int start, const vector<vector<int>> &adj, vector<bool> &visited, int &counter) {
    stack<int> st;
    st.push(start);
    visited[start] = true;

    while (!st.empty()) {
        int u = st.top();
        st.pop();
        counter++;

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                st.push(v);
            }
        }
    }
}

int main() {
    int N, M;

    cin >> N >> M;

    vector<vector<int>> adj(N);
    vector<bool> visited(N, false);

    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int counter = 0;
    dfs(0, adj, visited, counter);

    if (counter == N) {
        cout << "Connected\n";
    } else {
        for (int i = 0; i < N; i++) {
            if (!visited[i]) {
                cout << i + 1 << "\n";
            }
        }
    }
}
