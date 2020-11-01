#include <bits/stdc++.h>
using namespace std;

uint32_t ToInt(string s) {
    uint32_t n = 0;
    for (char c : s) {
        if (isdigit(c)) n = n * 16 + (c - '0');
        else n = n * 16 + (c - 'A' + 10);
    }
    return n;
}

uint32_t Rotate(uint32_t x, int i) {
    if (!i) return x;
    return (x >> i) | (x << (32 - i));
}

int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    int cases = 0;
    while (t--) {
        string s1, s2; cin >> s1 >> s2;
        uint32_t i1 = ToInt(s1), i2 = ToInt(s2);
        int mn = 32, mx = 0;
        for (int i = 0; i < 32; i++) {
            if (Rotate(i1, i) == i2) {
                mn = min(mn, i);
                mx = max(mx, i);
                //cerr << "!" << i << '\n';
            }
        }
        cout << "Case #" << ++cases << ": ";
        if (min(mn, 32 - mx) == 32) {
            cout << "Not possible";
        } else {
            cout << min(mn, 32 - mx) << ' ';
            if (mn == 0 || mn == 32 - mx) cout << "Any";
            else if (mn > 32 - mx) cout << "Left";
            else cout << "Right";
        }
        cout << '\n';
    }
}
