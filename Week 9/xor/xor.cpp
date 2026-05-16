#include <bits/stdc++.h>
using namespace std;

struct Node {
    int child[2];
    int cnt;

    Node() {
        child[0] = child[1] = -1;
        cnt = 0;
    }
};

void insert_number(vector<Node> &trie, int x) {
    int cur = 0;
    trie[cur].cnt++;

    for (int b = 30; b >= 0; b--) {
        int bit = (x >> b) & 1;

        if (trie[cur].child[bit] == -1) {
            trie[cur].child[bit] = trie.size();
            trie.push_back(Node());
        }

        cur = trie[cur].child[bit];
        trie[cur].cnt++;
    }
}

long long count_xor_leq_k(const vector<Node> &trie, int x, int k) {
    int cur = 0;
    long long ans = 0;

    for (int b = 30; b >= 0; b--) {
        if (cur == -1)
            break;

        int xbit = (x >> b) & 1;
        int kbit = (k >> b) & 1;

        if (kbit == 0) {
            cur = trie[cur].child[xbit];
        } else {
            int smaller_child = trie[cur].child[xbit];
            if (smaller_child != -1) {
                ans += trie[smaller_child].cnt;
            }

            cur = trie[cur].child[1 - xbit];
        }
    }

    if (cur != -1) {
        ans += trie[cur].cnt;
    }

    return ans;
}

int main() {

    int N, K;
    cin >> N >> K;

    vector<Node> trie;
    trie.push_back(Node());

    long long answer = 0;

    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;

        answer += count_xor_leq_k(trie, x, K);
        insert_number(trie, x);
    }

    cout << answer;

    return 0;
}
