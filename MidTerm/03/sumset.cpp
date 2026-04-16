#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>

using namespace std;

bool subset_sum_backtrack(const std::vector<int64_t> &num_list, int64_t current_index,
                          int64_t target_k, std::vector<int64_t> &chosen_elements) {

    if (target_k == 0) {
        return true;
    }

    if (current_index > (num_list.size()) || target_k < 0) {
        return false;
    }

    if (num_list[current_index] == target_k) {
        chosen_elements.push_back(num_list[current_index]);
        return true;
    }

    if (num_list[current_index] < target_k) {
        chosen_elements.push_back(num_list[current_index]);
        if (subset_sum_backtrack(num_list, current_index + 2, target_k - num_list[current_index],
                                 chosen_elements)) {
            return true;
        }
        chosen_elements.pop_back();
    }

    int64_t next_index = current_index + 1;

    return subset_sum_backtrack(num_list, next_index, target_k, chosen_elements);
}

std::vector<int64_t> find_subset(std::vector<int64_t> num_list, int64_t target_k,
                                 int64_t start_index) {

    if (target_k <= 0) {
        return {};
    }

    std::vector<int64_t> chosen_elements;
    if (subset_sum_backtrack(num_list, start_index, target_k, chosen_elements)) {
        return chosen_elements;
    }

    return std::vector<int64_t>{};
}

/**
 * For an array of length n and a target K, finds the minimum
 * cardinality of a subset summing to K with no two elements at consecutive
 * indices. Returns -1 if no such subset exists.
 *
 * @param arr Array of positive int64_tegers (length <= 30).
 * @param K   Target sum (up to 10^8).
 * @return Minimum cardinality of a valid subset, or -1.
 */
int64_t solve_no_consecutive_subset(const std::vector<int64_t> &arr, int64_t K) {
    vector<int64_t> sub0 = find_subset(arr, K, 0);
    vector<int64_t> sub1 = find_subset(arr, K, 1);

    int64_t res;
    int num0 = sub0.size();
    int num1 = sub1.size();
    if (num0 > 0 && num1 > 0) {
        res = min(num0, num1);
    }

    else if (num0 == 0 && num1 != 0) {
        res = num1;
    } else if (num1 == 0 && num0 != 0) {
        res = num0;
    } else {
        res = -1;
    }

    return res;
}

int main() {
    int64_t n;
    int64_t K;
    std::cin >> n >> K;

    std::vector<int64_t> arr(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    int64_t res;
    chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    res = solve_no_consecutive_subset(arr, K);
    chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << res << std::endl;
    // std::cout << "Runtime = "
    //           << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()
    //           << "[ms]" << std::endl;
    return 0;
}
