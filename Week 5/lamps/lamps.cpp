#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int main() {
    int N;
    cin >> N;

    string target;
    cin >> target;

    const int INF = 1e9;
    
    int next0 = 0;
    int next1 = INF;

    for (int i = N - 1; i >= 0; i--) {
        const int bit = target[i] - '0';

        int current0 = (bit != 0) + min(next0, 1 + next1);
        int current1 = (bit != 1) + min(next1, 1 + next0);

        next0 = current0;
        next1 = current1;
    }

    cout << min(next0, next1) << endl;

    return 0;
}