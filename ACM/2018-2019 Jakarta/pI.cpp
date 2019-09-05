#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr), ios_base::sync_with_stdio(false);
    int n; cin >> n;
    vector<bool> vec;
    for (int i = 0; i < n; i++) {
        string str; cin >> str;
        vec.push_back(str == "LIE" ? false : true);
    }
    bool res = true;
    while (vec.size()) {
        res ^= !vec.back();
        vec.pop_back();
    }
    cout << (res ? "TRUTH" : "LIE") << '\n';
}
