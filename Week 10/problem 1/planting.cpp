#include <bits/stdc++.h>
using namespace std;

static const long long MOD = 998244353;

long long mod_pow(long long a, long long e) {
    long long res = 1 % MOD;
    a %= MOD;
    while (e > 0) {
        if (e & 1)
            res = (res * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1;
    }
    return res;
}

int main() {
    long long r, c;
    cin >> r >> c;

    long long res = (r % MOD) * mod_pow(r - 1, c - 1) % MOD;

    cout << res;

    return 0;
}