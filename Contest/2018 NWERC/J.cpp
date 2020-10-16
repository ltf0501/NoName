#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int kN = 1e5 + 10;

int n;
ll a[kN], diff[kN];
int lg[kN];
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%lld", &a[i]);
	for(int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
	sort(a, a + n, greater<ll>());
	for(int i = 0; i < n - 1; i++) diff[i] = a[i] - a[i + 1];

	//for(int i = 0; i < n - 1; i++) printf("%d ", diff[i]); puts("");
	int cur = n - 1;
	for(int i = 1; i < n - 1; i++) 
		if(diff[i] > 0) {cur = i; break;}

	ll ans = 0;
	while(cur < n - 1) {
		ll h = diff[cur];			
		if(h * lg[cur] <= diff[0]) {
			ans += h * (lg[cur] + 1);
			diff[0] -= h * lg[cur];
			diff[cur] = 0;

			while(cur < n - 1 && diff[cur] == 0) cur++;
			if(cur == n - 1) break;
		}
		else {
			ll num = diff[0] / lg[cur];
			ans += 1LL * num * (lg[cur] + 1) + (diff[0] % lg[cur]);
			diff[0] = 0;
			return printf("%lld\n", ans), 0;
		}
	}

	//printf("%lld\n", ans + diff[0]);
	ll num = diff[0] / lg[n - 1];
	ans += 1LL * num * (lg[n - 1] + 1) + (diff[0] % lg[n - 1]);
	printf("%lld\n", ans); 
	return 0;
} 
