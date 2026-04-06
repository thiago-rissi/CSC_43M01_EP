#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iostream>

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
 * @brief Finds the largest x+y among all nonnegative solutions of a*x+b*y=c
 *        using the extended Euclidean algorithm.
 *
 * @param a Positive coefficient of x.
 * @param b Positive coefficient of y.
 * @param c Positive right-hand side of the equation.
 * @return The maximum value of x+y, or -1 if no nonnegative solution exists.
 */
int64_t maximize_extended_gcd(int64_t a, int64_t b, int64_t c) {
    int64_t x0, y0, g;

    if (!find_a_sol(a, b, c, x0, y0, g)) {
        return -1;
    }

    if ((a == b) && (x0 >= 0) && (y0 >= 0)) {
        return x0 + y0;
    }

    const int64_t step_x = b / g;
    const int64_t step_y = a / g;

    const int64_t k_from_x = ceil_div(-x0, step_x);
    const int64_t k_from_y = floor_div(y0, step_y);

    if (k_from_x > k_from_y) {
        return -1;
    }

    const int64_t k = (b > a) ? k_from_y : k_from_x;
    const int64_t x = x0 + k * step_x;
    const int64_t y = y0 - k * step_y;

    return (x >= 0 && y >= 0) ? (x + y) : -1;
}

// ─── Brute-force approach ─────────────────────────────────────────────────────

/**
 * @brief Finds the largest x+y among all nonnegative solutions of a*x+b*y=c
 *        via brute-force search.
 *
 * @param a Positive coefficient of x.
 * @param b Positive coefficient of y.
 * @param c Positive right-hand side of the equation.
 * @return The maximum value of x+y, or -1 if no nonnegative solution exists.
 */
int64_t maximize_brute_force(int64_t a, int64_t b, int64_t c) {
    int64_t best = -1;

    if (a < b) {
        for (int64_t x = c / a; x >= 0; --x) {
            if ((c - a * x) % b == 0) {
                return x + (c - a * x) / b;
            }
        }
    } else {
        for (int64_t y = c / b; y >= 0; --y) {
            if ((c - b * y) % a == 0) {
                return y + (c - b * y) / a;
            }
        }
    }

    return -1;
}

int main() {
    int64_t a, b, c;
    std::cin >> a >> b >> c;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    int64_t res_bf = maximize_brute_force(a, b, c);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Bruteforce search. Result: " << res_bf << ". Runtime: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()
              << " microsec" << std::endl;

    begin = std::chrono::steady_clock::now();
    int64_t res_egcd = maximize_extended_gcd(a, b, c);
    end = std::chrono::steady_clock::now();

    std::cout << "EGCD solution. Result: " << res_egcd << ". Runtime: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()
              << " microsec" << std::endl;

    return 0;
}
