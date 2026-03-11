#include <iostream>
#include <cstdint>

bool verify_limit(const uint64_t* duration, int n, int k, int lim){
    int numDays = 1;
    int dailyDuration = 0;
    for (int i=0; i < n; i++){
        if (duration[i] > lim) return false;
        else{
            if (dailyDuration + duration[i] > lim){
                numDays++;
                dailyDuration = duration[i];
            }
            else{
                dailyDuration += duration[i]; 
            }
        }
    }

    return numDays <= k;
}

uint64_t min_daily_limit(const uint64_t* duration, int n, int k) {
    int L = 0;
    int *arr = new int[n];

    for (int i = 0; i < n; i++){
        L += duration[i];
    } 

    int l = 0;
    int r = L;
    int ans = r;

    while (l <= r){
        int mid = l + (r - l) / 2;
        if (verify_limit(duration, n, k, mid)){
            ans = mid;
            r = mid - 1;
        }
        else{
            l = mid + 1;
        }
    }

    return ans;
}

int main() {
    int n, k;
    std::cin >> n >> k;
    uint64_t* duration = new uint64_t[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> duration[i];
    }
    
    uint64_t result = min_daily_limit(duration, n, k);
    std::cout << result << std::endl;

    return 0;
}
