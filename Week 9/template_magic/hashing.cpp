#include <iostream>

// fixed power and base
constexpr int p = 7877;
constexpr int base = 42;

template <int N> int compute_hash(const char *str) {
    return (compute_hash<N - 1>(str) * base + str[N - 1] - 'a') % p;
}

template <> int compute_hash<0>(const char *str) { return 0; };

template <int N> void initialize_powers(int *arr) {
    initialize_powers<N - 1>(arr);
    arr[N] = arr[N - 1] * base % p;
}

template <> void initialize_powers<0>(int *arr) { arr[0] = 1; }

int main() {
    const char *str = "abracadabra";
    std::cout << "Should print 68901" << std::endl;
    std::cout << "Result: " << compute_hash<11>(str) << std::endl;

    constexpr int N = 20;
    int powers[N];
    initialize_powers<N>(powers);
    std::cout << "Should print" << std::endl
              << "1 42 1764 3195 281 3925 7310 7694 191 145 6090 3716 6409 1360 1981 4432 4973 "
                 "4064 5271 826"
              << std::endl;
    for (int i = 0; i < N; ++i) {
        std::cout << powers[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
