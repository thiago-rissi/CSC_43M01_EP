#include <bits/stdc++.h>

using namespace std;

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

int KPM(const string &S, const string &P) {
    int n = S.size(), m = P.size();
    if (m == 0)
        return 0;
    vector<int> pi = compute_pi(P);

    for (int i = 0, j = 0; i < n;) {
        if (S[i] == P[j]) {
            i++;
            j++;

            if (j == m) {
                return i - m;
            }
        } else if (j > 0) {
            j = pi[j - 1];
        } else
            i++;
    }
    return -1;
}

int main() {
    string S;
    string P;
    cin >> S >> P;

    int n = S.size(), m = P.size();

    if (n != m) {
        cout << "NO";
        return 0;
    }

    string doubleP = P + P;
    int shift = KPM(doubleP, S);

    if (shift == -1 || shift >= n) {
        cout << "NO";
    } else {
        cout << shift;
    }
}
