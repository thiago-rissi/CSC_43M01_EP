#include <algorithm>
#include <iostream>
#include <vector>

bool subset_sum_backtrack(const std::vector<int> &num_list, const std::vector<int> &suffix_sum,
                          int current_index, int target_k, std::vector<int> &chosen_elements) {
    if (target_k == 0) {
        return true;
    }

    if (current_index == (num_list.size()) || target_k < 0) {
        return false;
    }

    if (suffix_sum[current_index] < target_k) {
        return false;
    }

    if (num_list[current_index] == target_k) {
        chosen_elements.push_back(num_list[current_index]);
        return true;
    }

    if (num_list[current_index] < target_k) {
        chosen_elements.push_back(num_list[current_index]);
        if (subset_sum_backtrack(num_list, suffix_sum, current_index + 1,
                                 target_k - num_list[current_index], chosen_elements)) {
            return true;
        }
        chosen_elements.pop_back();
    }

    int next_index = current_index + 1;
    while (next_index < (num_list.size()) && num_list[next_index] == num_list[current_index]) {
        ++next_index;
    }

    return subset_sum_backtrack(num_list, suffix_sum, next_index, target_k, chosen_elements);
}

std::vector<int> find_subset(std::vector<int> num_list, int target_k) {
    std::sort(num_list.rbegin(), num_list.rend());

    if (target_k <= 0) {
        return {};
    }

    std::vector<int> suffix_sum(num_list.size() + 1, 0);
    for (int i = num_list.size() - 1; i >= 0; --i) {
        suffix_sum[i] = suffix_sum[i + 1] + num_list[i];
    }

    std::vector<int> chosen_elements;
    if (subset_sum_backtrack(num_list, suffix_sum, 0, target_k, chosen_elements)) {
        return chosen_elements;
    }

    return std::vector<int>{};
}

int main() {
    int n;
    int K;
    std::cin >> n;
    std::cin >> K;
    std::vector<int> v(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> v[i];
    }
    std::vector<int> res = find_subset(v, K);
    std::sort(res.begin(), res.end());
    if (res.size() == 0) {
        std::cout << "None" << std::endl;
    } else {
        for (auto it = res.begin(); it != res.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
