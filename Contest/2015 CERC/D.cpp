#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
constexpr int kMod = int(1E9 + 7);
ll Pow(ll a, ll b) {
	ll ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % kMod;
		a = a * a % kMod;
		b >>= 1;
	}
	return ans;
}

int main() {
	int n, m, now = 0, cnt = 0;
	string s;
	cin >> n >> m >> s;
	for (int i = 0; i < n; i++) {
		now = (now * 10 + s[i] - '0') % m;
		if (now == 0) cnt++;
	}
	if (now != 0) cout << 0 << '\n';
	else cout << Pow(2, cnt - 1) << '\n';
} 
