#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

struct Rectangle {
    uint32_t w;
    uint32_t h;
    uint32_t x;
    uint32_t y;

    uint32_t area() const { return this->w * this->h; }
};

std::istream &operator>>(std::istream &is, Rectangle &s) {
    is >> s.w;
    is >> s.h;
    is >> s.x;
    is >> s.y;
    return is;
}

bool overlap(const Rectangle &s1, const Rectangle &s2) {
    int x1_l = s1.x;
    int x1_r = s1.x + s1.w;
    int y1_d = s1.y;
    int y1_u = s1.y + s1.h;

    int x2_l = s2.x;
    int x2_r = s2.x + s2.w;
    int y2_d = s2.y;
    int y2_u = s2.y + s2.h;

    bool avoid_x_overlap = (x1_l >= x2_r) || (x1_r <= x2_l);
    bool avoid_y_overlap = (y1_u <= y2_d) || (y1_d >= y2_u);

    if ((!avoid_x_overlap) && (!avoid_y_overlap)) {
        return true;
    }
    return false;
}

bool overlap_vector(Rectangle v1, std::vector<Rectangle> v2) {
    for (Rectangle r : v2) {
        if (overlap(v1, r))
            return true;
    }

    return false;
}
int find_area(std::vector<Rectangle> &num_list, std::vector<Rectangle> &chosen_elements,
              int current_index) {

    for (int i = current_index; i < num_list.size(), i++) {
        if (!overlap_vector)
    }
}
int find_subset(std::vector<Rectangle> &num_list) {
    int area = 0;
    std::vector<Rectangle> chosen_elements = {};

    for (int i = 0; i < num_list.size(); i--) {
        if (!overlap_vector(num_list[i], chosen_elements)) {
            chosen_elements.push_back(num_list[i]);
            area += num_list[i].area();
        }
    }

    std::cout << chosen_elements.size() << std::endl;

    return area;
}

bool comp(const Rectangle &r1, const Rectangle &r2) { return (r1.area() > r2.area()); }

int main() {
    int n;
    std::cin >> n;
    std::vector<Rectangle> v(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> v[i];
    }

    int max_area = find_subset(v);

    std::cout << max_area << std::endl;

    // Rectangle r;
    // std::cin >> r;
    // std::cout << "The area of the rectangle is " << r.area() << std::endl;
}
