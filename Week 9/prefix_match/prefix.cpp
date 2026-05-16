#include <bits/stdc++.h>

using namespace std;

int lpm(const string &S, const string &P) {
    int n = S.size();

    int max_counter = 0;

    for (int j = 0; j < n; j++) {
        if (P[0] == S[j]) {
            int i = 0;
            int counter = 0;
            while (S[j + i] == P[i]) {
                counter++;
                i++;
            }
            if (counter > max_counter) {
                max_counter = counter;
            }
        }
    }

    return max_counter;
}

vector<int> compute_pi(const string &P) {
    int m = P.size();
    vector<int> pi(m, 0);
    for (int i = 1; i < m; i++) {
        int j = pi[i - 1];
        while (j > 0 && P[i] != P[j])
            j = pi[j - 1];
        if (P[i] == P[j])
            j++;
        pi[i] = j;
    }

    return pi;
}

int fast_lpm(const string &S, const string &P) {
    int n = S.size(), m = P.size();
    if (m == 0)
        return 0;
    vector<int> pi = compute_pi(P);

    int max_counter = 0;
    for (int i = 0, j = 0; i < n;) {
        if (S[i] == P[j]) {
            i++;
            j++;
            if (j > max_counter)
                max_counter = j;
            if (j == m) {
                return m;
            }
        } else if (j > 0) {
            j = pi[j - 1];
        } else
            i++;
    }
    return max_counter;
}

int main() {
    string S;
    string P;
    cin >> S >> P;

    cout << fast_lpm(S, P);
}