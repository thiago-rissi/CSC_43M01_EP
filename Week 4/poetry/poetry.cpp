#include <algorithm>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <queue>

using namespace std;

static string to_string_u128(unsigned __int128 x) {
    if (x == 0) {
        return "0";
    }
    string s;
    while (x > 0) {
        int digit = static_cast<int>(x % 10);
        s.push_back(static_cast<char>('0' + digit));
        x /= 10;
    }
    reverse(s.begin(), s.end());
    return s;
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<uint64_t> poems(N, 0);

    for (size_t i = 0; i < N; i++) {
        cin >> poems[i];
    }

    sort(poems.begin(), poems.end());

    vector<pair<uint64_t, uint64_t>> journals;

    for (size_t j = 0; j < M; j++) {
        pair<uint64_t, uint64_t> p;
        cin >> p.first >> p.second;
        journals.push_back(p);
    }

    sort(journals.begin(), journals.end(),
         [](pair<uint64_t, uint64_t> &a, pair<uint64_t, uint64_t> &b) {
             return a.second < b.second;
         });

    unsigned __int128 res = 0;
    while (!poems.empty() && !journals.empty()) {
        pair<uint64_t, uint64_t> p = journals.back();
        journals.pop_back();

        while (!poems.empty() && (p.first > 0)) {
            uint64_t num_lines = poems.back();
            poems.pop_back();

            res += static_cast<unsigned __int128>(p.second) * num_lines;
            p.first -= 1;
        }
    }

    cout << to_string_u128(res) << endl;
}