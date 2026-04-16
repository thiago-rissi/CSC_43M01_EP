#include <iostream>
#include <algorithm>
#include <cstdint>

using namespace std;

int64_t egcd(int64_t a, int64_t b, int64_t &x, int64_t &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    } else {
        int64_t d = egcd(b, a % b, x, y);
        x -= a / b * y;
        std::swap(x, y);
        return d;
    }
}

int64_t floor_div(int64_t p, int64_t q) {
    int64_t d = p / q;
    int64_t r = p % q;
    if (r != 0 && ((r > 0) != (q > 0))) {
        d--;
    }
    return d;
}

int64_t ceil_div(int64_t p, int64_t q) {
    int64_t d = p / q;
    int64_t r = p % q;
    if (r != 0 && ((r > 0) == (q > 0))) {
        d++;
    }
    return d;
}

bool find_a_sol(int64_t a, int64_t b, int64_t c, int64_t &x0, int64_t &y0, int64_t &g) {
    g = egcd(std::abs(a), std::abs(b), x0, y0);
    if (c % g) {
        return false;
    }
    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) {
        x0 = -x0;
    }
    if (b < 0) {
        y0 = -y0;
    }
    return true;
}

/**
 * @brief Counts integer solutions (x, y) to ax + by = c with x, y in [-N, N].
 *
 * @param a Coefficient of x (positive).
 * @param b Coefficient of y (positive).
 * @param c Right-hand side (positive).
 * @param N Half-width of the allowed interval for x and y.
 * @return Number of valid integer solutions.
 */
int64_t count_solutions(int64_t a, int64_t b, int64_t c, int64_t N) {
    int64_t x0, y0, g, x, y;
    if(!find_a_sol(a, b, c, x0, y0, g)) return 0;
    const int64_t step_x = b / g;
    const int64_t step_y = a / g;

    int k;
    x = x0;
    y = y0;
    k = 1;
    int counter = 0;
    while (x <= N && y >= -N) {
        x = x0 + k*step_x;
        y = y0 - k*step_y;
        if (max(abs(x), abs(y)) <= N){
            counter++;
        }
        k++;
    }
   
    x = x0;
    y = y0;
    k = -1;
    while (x >= -N && y <= N) {
        x = x0 + k*step_x;
        y = y0 - k*step_y;
        if (max(abs(x), abs(y)) <= N){
            counter++;
        }
        k--;
    }

    if (max(abs(x0), abs(y0)) <= N){
            counter++;
    }

    return counter;
}

int main() {

    int64_t a, b, c, N;
    std::cin >> a >> b >> c >> N;

    std::cout << count_solutions(a, b, c, N) << std::endl;
    return 0;
}
