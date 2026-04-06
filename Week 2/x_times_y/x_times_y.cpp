#include <iostream>
#include <algorithm>
#include <chrono>
#include <cstdint>

/**
 * @brief Finds the largest x*y among all nonnegative integer solutions of
 *        a*x+b*y=c using the extended Euclidean algorithm.
 *
 * @param a Positive coefficient of x.
 * @param b Positive coefficient of y.
 * @param c Positive right-hand side of the equation.
 * @return The maximum value of x*y, or -1 if no nonnegative solution exists.
 */
int64_t maximize_product(int64_t a, int64_t b, int64_t c) {
    return 0;
}

int main() {
    int64_t a, b, c;
    std::cin >> a >> b >> c;
    std::cout <<  maximize_product(a, b, c) << std::endl;

    return 0;
}
