#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdint>

using namespace std; 

/**
 * @param v Vector of exactly 4 non-negative integers.
 * @return true if some triple forms an arithmetic progression.
 */
bool has_arithmetic_triple(std::vector<uint32_t> v) {
    sort(v.begin(), v.end());
    bool res1 = v[1] - v[0] == v[2] - v[1];
    bool res2 = v[3] - v[2] == v[2] - v[1];
    bool res3 = v[1] - v[0] == v[3] - v[1];

    return res1 || res2 || res3;
}

int main() {

    std::vector<uint32_t> v(4);
    for (size_t i = 0; i < 4; ++i) {
        std::cin >> v[i];
    }

    std::cout << (has_arithmetic_triple(v) ? "Yes" : "No") << std::endl;
    return 0;
}
