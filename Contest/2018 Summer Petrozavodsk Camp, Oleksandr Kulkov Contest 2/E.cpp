#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define F first
#define S second
const ll kInf = 1e18;
ll cal1(ll n) {return n * (3 * n - 1) / 2;}
ll cal2(ll n) {return n * (3 * n + 1) / 2;}

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		vector<pair<ll, int>> v;
		ll n; scanf("%lld", &n);
		ll v1 = kInf, v2 = kInf; // v1: +, v2: -
		int cur = 0;

		ll l = 1, r = 1e9;
		while(l < r) {
			ll m = (l + r) >> 1;
			if(cal2(m) <= n) l = m + 1;
			else r = m;
		} 
		if(cal2(l - 1) == n) cur = (l & 1) ? 1 : -1;
		
		for(int i = 0; i < 5; i++) v.emplace_back(cal2(l + i), (l + i) & 1);

		l = 1, r = 1e9;
		while(l < r) {
			ll m = (l + r) >> 1;
			if(cal1(m) <= n) l = m + 1;
			else r = m;
		}
		if(cal1(l - 1) == n) cur = (l & 1) ? 1 : -1;

		for(int i = 0; i < 5; i++) v.emplace_back(cal1(l + i), (l + i) & 1);

		sort(v.begin(), v.end());
		//puts("v:");
		//for(auto p : v) printf("%lld %d\n", p.F, p.S);

		int cnt = 0;
		for(auto p : v) {
			if(p.S == 0) break;
			cnt = 1;
		}

		int ans = (10 - cnt) % 10;
		ans = (ans + 10 + cur) % 10;
		printf("%d ", ans);
	}
	puts("");
	return 0;
} 
