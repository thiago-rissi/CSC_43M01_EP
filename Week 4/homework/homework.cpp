#include <algorithm>
#include <cstdint>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

// string create_final_string(vector<string> v) {
//     string final_str = "";
//     for (string chunk : v) {
//         final_str = chunk + " ";
//     }
//     final_str.pop_back();
//     return final_str;
// }

void format_buffer(uint32_t *buffer) {
    string str_buffer = "";
    uint32_t diff = buffer[1] - buffer[0];
    if (buffer[1] == 0) {
        str_buffer = to_string(buffer[0]) + " ";
    } else if (diff == 1) {
        str_buffer = to_string(buffer[0]) + " " + to_string(buffer[1]) + " ";
    } else {
        str_buffer = to_string(buffer[0]) + "-" + to_string(buffer[1]) + " ";
    }

    cout << str_buffer;
    return;
}

void optimise_string(vector<uint32_t> arr) {

    int i = 0;
    int n = arr.size();

    while (i < n) {
        int j = i;
        uint32_t buffer[] = {arr[j], 0};

        while (j + 1 < n && arr[j + 1] == (arr[j] + 1)) {
            buffer[1] = arr[j + 1];
            j++;
        }

        i = j + 1;
        format_buffer(buffer);
    }
}

// void convertStringToArray(char str[], int arr[]) {
//     int i = 0, j = 0, num = 0;
//     int len = strlen(str);

//     for (i = 0; i <= len; i++) {
//         if (str[i] >= '0' && str[i] <= '9') {
//             num = num * 10 + (str[i] - '0');
//         } else if (str[i] == ' ' || str[i] == '\0') {
//             arr[j] = num;
//             j++;
//             num = 0;
//         }
//     }
// }

int main() {
    // int n = 7;
    // char str[] = "100 88 30 31 90 89 1";

    // int arr[n];
    size_t N;
    std::cin >> N;
    std::vector<uint32_t> arr(N, 0);

    for (size_t i = 0; i < N; ++i) {
        std::cin >> arr[i];
    }

    // convertStringToArray(str, arr);
    sort(arr.begin(), arr.end());
    optimise_string(arr);
    // string final_str = optimise_string(arr, n);
    // cout << final_str << "\n";
}