#include <iostream>
#include <chrono>
#include <cassert>

// The modulus: Mersenne prime 2^31 - 1
static const uint64_t MOD = 2147483647ULL;

/**
 * @brief  Compute the n-th Fibonacci number modulo MOD using a linear scan.
 *         O(n) time, O(1) space.
 * @param  n  Index of the Fibonacci number (F(0)=0, F(1)=1).
 * @return F(n) mod (2^31 - 1).
 */
uint64_t fib_linear(uint64_t n) {
    if (n == 0) return 0;
    uint64_t a = 0, b = 1;
    for (uint64_t i = 2; i <= n; ++i) {
        uint64_t c = (a + b) % MOD;
        a = b;
        b = c;
    }
    return b;
}

void multiply(uint64_t A[2][2], uint64_t B[2][2]){
    uint64_t C[2][2];
    
    C[0][0] = (A[0][0] * B[0][0] + A[0][1] * B[1][0]) % MOD;
    C[0][1] = (A[0][0] * B[0][1] + A[0][1] * B[1][1]) % MOD;
    C[1][0] = (A[1][0] * B[0][0] + A[1][1] * B[1][0]) % MOD;
    C[1][1] = (A[1][0] * B[0][1] + A[1][1] * B[1][1]) % MOD;

    A[0][0] = C[0][0];
    A[0][1] = C[0][1];
    A[1][0] = C[1][0];
    A[1][1] = C[1][1];
}

void power(uint64_t M[2][2], uint64_t ans[2][2], int exp){
    ans[0][0] = 1; ans[0][1] = 0;
    ans[1][0] = 0; ans[1][1] = 1;

    while (exp) {
        if (exp & 1)
            multiply(ans, M);
        multiply(M, M);
        exp >>= 1;
    }
}

/**
 * @brief  Compute the n-th Fibonacci number modulo MOD using matrix
 *         exponentiation.  O(log n) time, O(1) space.
 *
 *         Uses the identity:
 *           [ 1 1 ]^n   [ F(n+1)  F(n)  ]
 *           [ 1 0 ]   = [ F(n)    F(n-1) ]
 *
 * @param  n  Index of the Fibonacci number (F(0)=0, F(1)=1).
 * @return F(n) mod (2^31 - 1).
 */
uint64_t fib_matrix(uint64_t n) {
    if (n == 0 || n == 1) return 0;
    uint64_t M[2][2] = {{1, 1}, {1, 0}};
    uint64_t F[2][2] = {{1, 0}, {0, 0}};

    power(M, F, n - 1);
    uint64_t res = F[0][0];

    return res;
}

int main() {
    uint64_t n;
    std::cin >> n;

    auto start = std::chrono::steady_clock::now();
    uint64_t res_matrix = fib_matrix(n);
    auto end = std::chrono::steady_clock::now();
    int matrix_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "Matrix result: " << res_matrix << " in time " << matrix_time << " ns" << std::endl;

    start = std::chrono::steady_clock::now();
    uint64_t res_linear = fib_linear(n);
    end = std::chrono::steady_clock::now();
    int linear_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "Linear result: " << res_linear << " in time " << linear_time << " ns" << std::endl;


    return 0;
}
