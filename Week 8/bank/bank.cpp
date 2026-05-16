#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

struct Exchange {
    int from, to;
    double rate;
};

double best_exchange_rate(int n, const std::vector<Exchange> &services) {
    const double neg_inf = -std::numeric_limits<double>::infinity();
    const double eps = 1e-12;

    std::vector<std::vector<int>> reverse_graph(n);
    for (const auto &svc : services) {
        reverse_graph[svc.to].push_back(svc.from);
    }

    std::vector<bool> can_reach_target(n, false);
    std::queue<int> q;
    can_reach_target[n - 1] = true;
    q.push(n - 1);

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        for (int prev : reverse_graph[cur]) {
            if (!can_reach_target[prev]) {
                can_reach_target[prev] = true;
                q.push(prev);
            }
        }
    }

    std::vector<double> best(n, neg_inf);
    best[0] = 0.0;

    for (int step = 0; step < n - 1; ++step) {
        bool changed = false;

        for (const auto &svc : services) {
            if (best[svc.from] == neg_inf) {
                continue;
            }

            double candidate = best[svc.from] + std::log(svc.rate);
            if (candidate > best[svc.to] + eps) {
                best[svc.to] = candidate;
                changed = true;
            }
        }

        if (!changed) {
            break;
        }
    }

    for (const auto &svc : services) {
        if (best[svc.from] == neg_inf) {
            continue;
        }

        double candidate = best[svc.from] + std::log(svc.rate);
        if (candidate > best[svc.to] + eps && can_reach_target[svc.to]) {
            return std::numeric_limits<double>::max();
        }
    }

    if (best[n - 1] == neg_inf) {
        return 0.0;
    }

    return std::exp(best[n - 1]);
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<Exchange> services(m);
    for (auto &svc : services) {
        std::cin >> svc.from >> svc.to >> svc.rate;
    }

    double result = best_exchange_rate(n, services);

    if (result == 0.0) {
        std::cout << "Not possible" << std::endl;
    } else if (result == std::numeric_limits<double>::max()) {
        std::cout << "Youhou!" << std::endl;
    } else {
        std::cout << std::fixed << std::setprecision(4) << result << std::endl;
    }

    return 0;
}
