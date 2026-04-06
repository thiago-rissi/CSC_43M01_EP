#include <iostream>
#include <vector>
#include <cstdint>

struct Rectangle {
    uint32_t w;
    uint32_t h;
    uint32_t x;
    uint32_t y;

    uint32_t area() const {
        return this->w * this->h;
    }
};

std::istream& operator >> (std::istream& is, Rectangle& s) {
    is >> s.w;
    is >> s.h;
    is >> s.x;
    is >> s.y;
    return is;
}

bool overlap(const Rectangle& s1, const Rectangle& s2) {
    return false;
}

int main() {
    Rectangle r;
    std::cin >> r;
    std::cout << "The area of the rectangle is " << r.area() << std::endl;
}
