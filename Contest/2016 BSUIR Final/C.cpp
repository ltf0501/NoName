#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
bool Solve(ll n) {
	bool flag = 1;
	ll l = n + 1;
	while(true) {
		//if(l != 0) printf("l = %lld\n", l);
		ll r = l - 1;
		if(flag) {
			l = l / 9 + (l % 9 != 0);
		}
		else {
			l = l / 2 + (l % 2 != 0);
		}
		if(l <= 1 && r >= 1) return flag;
		flag ^= 1;
	}
}
int main() {
	int T; scanf("%d", &T);
	while(T--) {
		ll n; scanf("%lld", &n);
		if(Solve(n)) puts("YES");
		else puts("NO");
	}
	return 0;
}
