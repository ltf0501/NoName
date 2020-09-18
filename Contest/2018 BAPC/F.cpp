#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int kN = 1e5 + 10;
const ll kInf = 2e9 + 10;

int n, M;
int p[kN], c[kN];

bool Check(ll x) {
	ll res = 0;
	for(int i = 0; i < n; i++) {
		if(1LL * p[i] * x - c[i] >= M) return 1;
		res += max<ll>(0, 1LL * p[i] * x - c[i]);
	}
	return res >= M;
}
int main() {
	scanf("%d%d", &n, &M);
	for(int i = 0; i < n; i++) scanf("%d%d", &p[i], &c[i]);
	ll l = 0, r = kInf;
	while(l + 1 < r) {
		ll m = (l + r) >> 1;
		if(Check(m)) r = m;
		else l = m;
	}
	printf("%lld\n", r);
	return 0;
} 
