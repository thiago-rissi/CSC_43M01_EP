#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

typedef std::vector<uint32_t>::iterator Iter;

uint32_t count_max_jobs(Iter sessions_start, Iter sessions_end, Iter jobs_start, Iter jobs_end) {
    std::sort(jobs_start, jobs_end);
    std::sort(sessions_start, sessions_end);
    uint32_t counter = 0;
    Iter j = sessions_start;

    for (Iter i = jobs_start; i < jobs_end && j < sessions_end; i++) {
        while (j < sessions_end && *i > *j) {
            j++;
        }
        if (j < sessions_end) {
            counter++;
            j++;
        }
    }

    return counter;
}

int main() {
    size_t num_jobs, num_times;
    std::cin >> num_jobs >> num_times;
    std::vector<uint32_t> jobs(num_jobs, 0);
    std::vector<uint32_t> times(num_times, 0);
    for (size_t i = 0; i < num_jobs; ++i) {
        std::cin >> jobs[i];
    }
    for (size_t i = 0; i < num_times; ++i) {
        std::cin >> times[i];
    }
    std::cout << count_max_jobs(times.begin(), times.end(), jobs.begin(), jobs.end()) << std::endl;
}
