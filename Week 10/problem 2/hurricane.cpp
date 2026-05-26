#include <bits/stdc++.h>
using namespace std;

struct point {
    long long x = 0;
    long long y = 0;
};

struct city {
    point p;
    string name;
};

void solve_case(point &ph1, point &ph2, vector<city> cities) {
    long long min_dist = numeric_limits<long long>::max();

    vector<string> min_names;

    double m = (ph1.y - ph2.y);
    double b = (ph1.x - ph2.x);
    double a = -m;
    double c = m * ph2.x - ph2.y * (ph1.x - ph2.x);

    for (city cp : cities) {
        long long dist = abs(a * cp.p.x + b * cp.p.y + c);

        // / sqrt(pow(a, 2) + pow(b, 2));

        if (dist < min_dist) {
            min_names.clear();
            min_names.push_back(cp.name);
            min_dist = dist;
        } else if (dist == min_dist) {
            min_names.push_back(cp.name);
        }
    }

    for (string name : min_names) {
        cout << name << " ";
    }

    cout << "\n";
}

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        point ph1, ph2;
        cin >> ph1.x >> ph1.y >> ph2.x >> ph2.y;
        int m;
        cin >> m;

        vector<city> cities;
        for (int j = 0; j < m; j++) {
            city c;
            cin >> c.name >> c.p.x >> c.p.y;
            cities.push_back(c);
        }

        solve_case(ph1, ph2, cities);
    }

    return 0;
}