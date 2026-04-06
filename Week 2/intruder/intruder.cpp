#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <vector>

/**
 * @brief Finds the unique element in a vector where all others appear exactly twice,
 *        using sorting.
 *
 * @param nums Vector of integers where every element appears twice except one.
 * @return The unique element.
 */
int find_unique_sort(std::vector<int> nums) {
    std::sort(nums.begin(), nums.end());
    for (int i = 0; i + 1 < (int)nums.size(); i += 2) {
        if (nums[i] != nums[i + 1]) {
            return nums[i];
        }
    }
    return nums.back(); // unique element is the last one
}

/**
 * @brief Finds the unique element in a vector where all others appear exactly twice,
 *        using XOR.
 *
 * @param nums Vector of integers where every element appears twice except one.
 * @return The unique element.
 */
int find_unique_xor(const std::vector<int> &nums) {
    int result = 0;

    for (int num : nums) {
        result ^= num;
    }

    return result;
}

/**
 * @brief Finds the smallest of the two unique elements in a vector where all
 *        others appear exactly twice, using sorting.
 *
 * @param nums Vector of integers where every element appears twice except two.
 * @return The smallest of the two unique elements.
 */
int find_smallest_unique_sort(std::vector<int> nums) {
    std::sort(nums.begin(), nums.end());
    for (int i = 0; i + 1 < nums.size(); i += 2) {
        if (nums[i] != nums[i + 1]) {
            return nums[i];
        }
    }
    return nums.back();
}

/**
 * @brief Finds the smallest of the two unique elements in a vector where all
 *        others appear exactly twice, using XOR.
 *
 * @param nums Vector of integers where every element appears twice except two.
 * @return The smallest of the two unique elements.
 */
int find_smallest_unique_xor(const std::vector<int> &nums) {
    int xor_uniques, xor_uniques_copy, xor_mask, slice_id, mask_id = 0;

    for (int num : nums) {
        xor_uniques ^= num;
    }

    int mask = 1;
    while (xor_uniques > 0) {
        if (xor_uniques & 1) {
            mask += 1;
            break;
        }

        xor_uniques >>= 1;
        mask *= 2;
    }

    std::vector<int> first_slice;
    std::vector<int> second_slice;

    for (int num : nums) {
        int mask_and = num && mask;

        if (mask_and == 0) {
            first_slice.push_back(num);
        } else {
            second_slice.push_back(num);
        }
    }

    std::vector<int> first_slice(slice_id + 1);
    std::vector<int> second_slice(nums.size() - slice_id - 1);
    std::copy(nums.begin(), nums.begin() + slice_id + 1, first_slice.begin());
    std::copy(nums.begin() + slice_id + 1, nums.end(), second_slice.begin());

    int x1 = find_unique_xor(first_slice);
    int x2 = find_unique_xor(second_slice);

    return std::min(x1, x2);
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> data(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> data[i];
    }

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    int res_sort = find_smallest_unique_sort(data);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Sorting-based solution. Result: " << res_sort << ". Runtime: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()
              << " microsec" << std::endl;

    begin = std::chrono::steady_clock::now();
    int res_xor = find_smallest_unique_xor(data);
    end = std::chrono::steady_clock::now();

    std::cout << "Linear solution. Result: " << res_xor << ". Runtime: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()
              << " microsec" << std::endl;

    return 0;
}
