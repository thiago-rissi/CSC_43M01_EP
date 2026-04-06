#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

constexpr char DIM = 4;

uint16_t flip_lamp(uint16_t c, size_t i) {
    c ^= (1 << i);
    size_t row = i / DIM;
    size_t col = i % DIM;

    if (row > 0) {
        c ^= (1 << (i - DIM));
    }
    if (row < DIM - 1) {
        c ^= (1 << (i + DIM));
    }
    if (col > 0) {
        c ^= (1 << (i - 1));
    }
    if (col < DIM - 1) {
        c ^= (1 << (i + 1));
    }
    return c;
}

bool recursive(uint16_t c, uint16_t const &target, int index, int &counter) {
    if (c == target) {
        return true;
    }

    if (index >= DIM * DIM) {
        return false;
    }

    counter++;

    bool unflipped = recursive(c, target, index + 1, counter);
    if (unflipped)
        return true;

    uint16_t c_flipped = flip_lamp(c, index);
    bool flipped = recursive(c_flipped, target, index + 1, counter);

    if (flipped)
        return true;

    return false;
}

int min_flips(uint16_t c, uint16_t const &target, int index) {
    if (index == DIM * DIM) {
        return c == target ? 0 : DIM * DIM + 1;
    }

    int best_without_flip = min_flips(c, target, index + 1);
    int best_with_flip = 1 + min_flips(flip_lamp(c, index), target, index + 1);

    return std::min(best_without_flip, best_with_flip);
}

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

    int result = min_flips(source, target, 0);

    if (result > DIM * DIM)
        std::cout << "n achou :(" << std::endl;
    else
        std::cout << result << std::endl;

    return 0;
}
