#include <iostream>
#include <vector>
#include <cassert>
#include <cstdint>

constexpr char DIM = 4;

uint16_t read_configuration() {
    std::string buf;
    uint16_t c = 0;
    for (size_t j = 0; j < DIM; ++j) {
        std::cin >> buf;
        for (size_t k = 0; k < DIM; ++k) {
            if (buf[k] == '*') {
                c += (1 << (k + DIM * j));
            }
        }
    }
    return c;
}

int main() {
    uint16_t source = read_configuration();
    uint16_t target = read_configuration();
}
