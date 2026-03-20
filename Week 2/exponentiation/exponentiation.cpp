#include <cmath>
#include <cstdint>
#include <iostream>

uint64_t exponentiate_modulo(uint64_t a, uint64_t e, uint64_t m) {
    uint64_t b1 = a / 8;
    uint64_t b2 = a % 8;

    for (uint64_t i = 0; i < e; i++) {
        b1 = (b1 * b1) % m;
        b2 = (b2 * b2) % m;
    }

    return (b1 * 8 + b2) % m;
}

int main() {
    uint64_t a, e, m;
    std::cin >> a >> e >> m;
    std::cout << exponentiate_modulo(a, e, m) << std::endl;
}
