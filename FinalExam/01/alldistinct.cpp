#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

bool all_distinct(const std::string& s) {
    
    vector<bool> letters(25, false);

    for (char c: s){
        int l = (c - 'a');

        if (letters[l] == true)
            return false;

        letters[l] = true;
    }

    for(bool l : letters){
        if (l == false)
            return false;
    }
    return true;
}

int main() {
    std::string s;
    std::cin >> s;
    if (all_distinct(s)) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }
}

  