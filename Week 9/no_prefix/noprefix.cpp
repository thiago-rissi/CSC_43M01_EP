#include <bits/stdc++.h>

using namespace std;

struct Node {
    int nxt[26];
    int best1, best2;

    Node() {
        fill(nxt, nxt + 26, -1);
        best1 = best2 = INT_MAX;
    }
};

void add_index(Node &node, int idx) {
    if (idx < node.best1) {
        node.best2 = node.best1;
        node.best1 = idx;
    } else if (idx != node.best1 && idx < node.best2) {
        node.best2 = idx;
    }
}

int main() {
    int N;
    cin >> N;

    vector<string> strings(N + 1);
    vector<int> terminal(N + 1);
    vector<Node> trie(1);

    for (int i = 1; i <= N; i++) {
        cin >> strings[i];

        int node = 0;
        add_index(trie[node], i);

        for (char c : strings[i]) {
            int x = c - 'a';
            if (trie[node].nxt[x] == -1) {
                trie[node].nxt[x] = trie.size();
                trie.push_back(Node());
            }

            node = trie[node].nxt[x];
            add_index(trie[node], i);
        }

        terminal[i] = node;
    }

    for (int i = 1; i <= N; i++) {
        Node node = trie[terminal[i]];
        int j = node.best1 == i ? node.best2 : node.best1;

        if (j != INT_MAX) {
            cout << i << " " << j;
            return 0;
        }
    }

    cout << "NO";
    return 0;
}
