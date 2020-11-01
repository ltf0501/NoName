#include <bits/stdc++.h>
using namespace std;
const int kN = 1e5 + 10;
typedef long long ll;

int n;
int bit[kN];
void add(int x, int d) {
    for(int i = x; i <= n; i += i & -i) bit[i] += d;
}
int query(int x) {
    int res = 0;
    for(int i = x; i; i -= i & -i) res += bit[i];
    return res;
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    while(cin >> n && n) {
        for(int i = 1; i <= n; i++) bit[i] = 0;
        map<string, int> mp;
        int cnt = 0;
        for(int i = 1; i <= n; i++) {
            string s; cin >> s;
            mp[s] = ++cnt;
        }

        vector<int> v(n + 1);
        for(int i = 1; i <= n; i++) {
            string s; cin >> s;
            v[i] = mp[s];
        }

        ll ans = 0;
        for(int i = 1; i <= n; i++) {
            ans += query(n) - query(v[i]);
            add(v[i], 1);
        }
        cout << ans << '\n';
    }
    return 0;
}
