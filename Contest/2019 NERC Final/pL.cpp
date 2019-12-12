#include <bits/stdc++.h>
using namespace std;
const int kN = 1e3 + 10;
string ans[kN];
int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int n, l, k;
	string s;
	cin >> n >> l >> k;
	cin >> s;
	sort(s.begin(), s.end());
	int cur = 0;
	int now = 1;
	while(now != k && int(ans[k].size()) < l) {
		for(int i = now; i <= k; i++) ans[i] += s[cur++];
		while(ans[now].back() != ans[k].back()) now++;
	}
	int sz = int(ans[k].size());
	for(int j = 0; j < l - sz; j++) ans[k] += s[cur++];
	for(int i = 1; i <= n; i++) if(i != k) {
		int sz = int(ans[i].size());
		for(int j = 0; j < l - sz; j++) ans[i] += s[cur++];
	}
	for(int i = 1; i <= n; i++) cout << ans[i] << '\n';
}
