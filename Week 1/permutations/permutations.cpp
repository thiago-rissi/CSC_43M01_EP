#include <algorithm>
#include <array>
#include <cstdint>
#include <cstring>
#include <iostream>

uint64_t count_permutations(const std::array<int, 256> &freq, size_t len) {
    uint64_t numerator = 1;
    for (size_t i = 2; i <= len; i++) {
        numerator *= i;
    }

    uint64_t denominator = 1;
    for (int count : freq) {
        for (int i = 2; i <= count; i++) {
            denominator *= i;
        }
    }

    return numerator / denominator;
}

/**
 * @brief Finds the n-th (1-indexed) lexicographic permutation of a C-string.
 *
 * @param s   The input C-string (consisting of upper-case letters).
 * @param n   The 1-based index of the desired permutation.
 * @param out Output buffer for the result (must be at least strlen(s)+1 bytes).
 * @return true on success, false if n is out of range.
 */
bool nth_permutation(const char *s, uint64_t n, char *out) {
    size_t len = std::strlen(s);

    if (len == 0) {
        out[0] = '\0';
        return true;
    }

    std::array<int, 256> freq = {};
    for (size_t i = 0; i < len; ++i) {
        freq[s[i]]++;
    }

    uint64_t total_permutations = count_permutations(freq, len);

    if (n == 0 || n > total_permutations) {
        return false;
    }

    n--;
    for (size_t i = 0; i < len; i++) {
        for (int ch = 0; ch < 256; ch++) {
            if (freq[ch] == 0) {
                continue;
            }

            freq[ch]--;

            uint64_t block_size = count_permutations(freq, len - i - 1);

            if (n >= block_size) {
                n -= block_size;
                freq[ch]++;
                continue;
            }

            out[i] = static_cast<char>(ch);
            break;
        }
    }

    out[len] = '\0';

    return true;
}

/**
 * @brief Computes the 1-based lexicographic rank of a given permutation.
 *
 * @param s The input C-string representing the permutation (upper-case letters).
 * @return  The 1-based rank of the permutation, or -1 if the string is empty.
 */
int64_t permutation_rank(const char *s) {
    size_t len = std::strlen(s);
    if (len == 0) {
        return -1;
    }

    std::array<int, 256> freq = {};
    for (size_t i = 0; i < len; i++) {
        freq[s[i]]++;
    }

    int64_t rank = 1;
    for (size_t i = 0; i < len; i++) {
        char current = s[i];
        for (int ch = 0; ch < current; ch++) {
            if (freq[ch] == 0) {
                continue;
            }

            freq[ch]--;
            rank += count_permutations(freq, len - i - 1);
            freq[ch]++;
        }

        freq[current]--;
    }

    return rank;
}

int main() {
    char s[20];
    uint64_t n;

    std::cin >> s;
    std::cin >> n;

    char result[20];
    if (!nth_permutation(s, n, result)) {
        return 1;
    }
    std::cout << result << std::endl;

    return 0;
}
