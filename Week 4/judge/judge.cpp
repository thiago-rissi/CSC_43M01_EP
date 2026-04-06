#include <algorithm>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <queue>

using namespace std;

int main() {
    uint32_t N;
    std::cin >> N;

    priority_queue<uint64_t, vector<uint64_t>, greater<uint64_t>> pq;

    for (size_t i = 0; i < N; ++i) {
        uint64_t page;
        std::cin >> page;
        pq.push(page);
    }

    uint64_t sum = 0;
    while (pq.size() > 1) {
        uint64_t a = pq.top();
        pq.pop();
        uint64_t b = pq.top();
        pq.pop();
        sum += a + b;
        pq.push(a + b);
    }

    if (N > 0) {
        sum += pq.top();
    }

    cout << sum << '\n';
}