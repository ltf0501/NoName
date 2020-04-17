#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
map<ll, int> mp;
vector<pair<int, int>> ans;
int cnt;
void solve(ll n) {
	if(mp.count(n)) return;
	if(n == 1) {
		mp[n] = cnt++;
		ans.emplace_back(-1, -1);
		return;
	}
	solve(n / 2);
	solve((n + 1) / 2);
	int x = mp[n / 2], y = mp[(n + 1) / 2];
	mp[n] = cnt++;
	ans.emplace_back(y, x); 
}
int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int T; cin >> T;
	while(T--) {
		ll n; cin >> n;
		mp.clear(); cnt = 0;
		ans.clear();
		solve(n);
		cout << cnt << '\n';
		for(auto p : ans) cout << p.first << ' ' << p.second << '\n';
		cout << cnt - 1 << '\n';
	} 
	return 0;
}
