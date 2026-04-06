#include <cstdint>
#include <iostream>

uint64_t multiply_modulo(uint64_t a, uint64_t b, uint64_t m) {
    uint64_t result = 0;
    a %= m;

    while (b > 0) {
        uint64_t digit = b & 7;
        for (uint64_t i = 0; i < digit; i++) {
            result = (result + a) % m;
        }

        b >>= 3;
        for (int i = 0; i < 3; i++) {
            a = (a + a) % m;
        }
    }

    return result;
}

uint64_t exponentiate_modulo(uint64_t a, uint64_t e, uint64_t m) {
    uint64_t result = 1;
    a %= m;
    while (e > 0) {
        if (e & 1)
            result = multiply_modulo(result, a, m);
        a = multiply_modulo(a, a, m);
        e >>= 1;
    }
    return result;
}

int main() {
    uint64_t a, e, m;
    std::cin >> a >> e >> m;
    std::cout << exponentiate_modulo(a, e, m) << std::endl;
}
