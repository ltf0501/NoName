#include <bits/stdc++.h>
using namespace std;

constexpr int kN = int(1E2 + 10);

int cnt[26];
int curtp[kN], cur[kN];

void solve() {
	int n, k, c, ans = 0, now = 0;
	string s;
	cin >> n >> k;
	for (int i = 0; i < 26; i++) cnt[i] = 0;
	for (int i = 0; i < k; i++) curtp[i] = cur[i] = 0;
	for (int i = 1; i <= n; i++) {
		cin >> s >> c;
		if (cnt[curtp[i % k]] == 5) now--;
		cnt[curtp[i % k]] -= cur[i % k];
		if (cnt[curtp[i % k]] == 5) now++;
		curtp[i % k] = s[0] - 'A';
		cur[i % k] = c;
		if (cnt[curtp[i % k]] == 5) now--;
		cnt[curtp[i % k]] += cur[i % k];
		if (cnt[curtp[i % k]] == 5) now++;
		ans += now;
	}
	cout << ans << endl;
	return ;
}


int main() {
	int t;
	cin >> t;
	while (t--) solve();
} 
