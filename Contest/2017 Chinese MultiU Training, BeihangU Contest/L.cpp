#include <stdio.h>
#include <algorithm>
#include <vector>
#include <tuple>
using namespace std;
typedef long long int ll;
constexpr int kN = int(1E6 + 10), kMod = int(1E9 + 7);

int l[kN], r[kN];
ll f[kN], inv[kN], ans;
vector<tuple<int, int, int>> v;

ll Pow(ll a, ll b) {
	ll ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % kMod;
		a = a * a % kMod;
		b >>= 1;
	}
	return ans;
}

ll Rev(ll n) {return Pow(n, kMod - 2);}

void pre() {
	inv[0] = inv[1] = f[0] = f[1] = 1;
	for (int i = 2; i < kN; i++) f[i] = f[i - 1] * i % kMod;
	inv[kN - 1] = Rev(f[kN - 1]);
	for (int i = kN - 2; i >= 2; i--) inv[i] = inv[i + 1] * (i + 1) % kMod;
	return ;
}

ll C(int n, int m) {return f[n] * inv[m] % kMod * inv[n - m] % kMod;}

void dfs(int L, int R) {
	if (L > R) return ;
	int xx = lower_bound(v.begin(), v.end(), make_tuple(L, R, 0)) - v.begin();
	if (xx >= int(v.size())) {
			ans = 0;
			return ;
	}
	tuple<int, int, int> tmp = v[xx]; 
	if (get<0>(tmp) != L || get<1>(tmp) != R) ans = 0;
	else {
		int x = get<2>(tmp);	
		ans = ans * C(R - L, x - L) % kMod;
		dfs(L, x - 1);
		dfs(x + 1, R);
	}
	return ;
}

int solve(int n) {
	for (int i = 1; i <= n; i++) scanf("%d", &l[i]);
	for (int i = 1; i <= n; i++) scanf("%d", &r[i]);
	v.resize(n);
	for (int i = 1; i < n; i++) v[i] = {l[i], r[i], i};
	v[0] = {l[n], r[n], n};
	sort(v.begin(), v.end());
	ans = 1;
	dfs(1, n);
	return ans;
}

int main() {
	pre();
	int n, cnt = 1;
	while (scanf("%d", &n) != EOF) printf("Case #%d: %d\n", cnt++, solve(n)); 
} 
