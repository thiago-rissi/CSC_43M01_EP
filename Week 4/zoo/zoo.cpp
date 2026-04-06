#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

uint32_t calculate_num_rides(vector<uint32_t> temperaments, uint32_t S, uint32_t C, uint32_t K) {
    sort(temperaments.begin(), temperaments.end());
    int n = temperaments.size();
    uint32_t counter = 0;
    int i = 0;
    int j = 0;
    // cout << "C=" << C << endl;

    while (i < n) {
        j = i + 1;
        uint32_t onboard = 1;
        while (j < n && temperaments.at(j) - temperaments.at(i) <= K && onboard < C) {
            // cout << "i=" << i << ", j=" << j;
            // cout << ", a(i)" << temperaments.at(i) << ", a(j)=" << temperaments.at(j) << endl
            //      << endl;
            onboard++;
            j++;
        }
        counter++;
        i = j;
    }

    return counter;
}

int main() {
    uint32_t S, C, K;
    std::cin >> S >> C >> K;
    std::vector<uint32_t> temperaments(S, 0);

    for (size_t i = 0; i < S; ++i) {
        std::cin >> temperaments[i];
    }

    cout << calculate_num_rides(temperaments, S, C, K) << endl;
}