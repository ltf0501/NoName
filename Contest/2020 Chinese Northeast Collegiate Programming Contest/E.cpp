#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	int T; scanf("%d", &T);
	while(T--) {
		int n, k;
		scanf("%d%d", &n, &k);
		if(n == 1) {
			puts("1");
			continue;
		}
		if(k == n || k % 2 == 0) {
			puts("-1");
			continue;
		}

		vector<ll> v;
		for(int i = k; i >= 0; i--) {
			ll x = (1LL << (k + 1)) - 1;
			v.push_back(x ^ (1LL << i));
		}

		for(int i = k + 1; i < n; i++) {
			ll x = (1LL << (k - 1)) - 1;
			v.push_back(x ^ (1LL << i));
		}

		for(ll x : v) printf("%lld ", x); puts("");
	}
} 
