#include <bits/stdc++.h>

using namespace std;

vector<int> compute_pi(const string& pattern) {
    int m = pattern.size();

    vector<int> pi(m, 0);

    for (int i = 1; i < m; i++) {
        int j = pi[i - 1];

        while (j > 0 && pattern[i] != pattern[j]) {
            j = pi[j - 1];
        }

        if (pattern[i] == pattern[j]) {
            j++;
        }

        pi[i] = j;
    }

    return pi;
}

vector<int> kmp_match(const string& text, const string& pattern) {
    int n = text.size();
    int m = pattern.size();

    vector<int> occurrences;

    if (m == 0) {
        return occurrences;
    }

    vector<int> pi = compute_pi(pattern);

    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j > 0 && text[i] != pattern[j]) {
            j = pi[j - 1];
        }

        if (text[i] == pattern[j]) {
            j++;
        }

        if (j == m) {
            int id = i - m + 1;
            if(occurrences.empty()){
                occurrences.push_back(id);
            }
            else{
                int last_id = occurrences.back();
                if(id < last_id + m){
                    continue;
                }
            }
            occurrences.push_back(i - m + 1);
        }
    }

    return occurrences;
}
int main(){
    string S,P;
    cin >> S >> P;

    vector<int> occurrences;

    occurrences = kmp_match(S, P);
    int len = occurrences.size();

    if (len == 0){
        cout << 0 << "\n";
        return 0;
    }

    int size_p = P.size();

    int n = 1;
    int max_n = -1;
    int last_ocurrence = occurrences[0];

    for(int i = 1; i < len; i++){
        int occurrence = occurrences[i];

        if(occurrence == last_ocurrence + size_p){
            n++;    
        }
        else{
            if(n > max_n){
                max_n = n;
            }
            n = 1;
        }
        last_ocurrence = occurrence;
    }

    if(n > max_n){
        max_n = n;
    }
    cout << max_n << "\n";

}