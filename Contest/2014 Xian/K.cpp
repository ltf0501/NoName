#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll Cal(ll a, ll b) {
	if(b == 0) return 0;
	return a / b + Cal(b, a % b);
}
int main() { 
	int T; scanf("%d", &T);
	int cas = 0;
	while(T--) {
		ll a, b; scanf("%lld%lld", &a, &b);
		printf("Case #%d: ", ++cas);
		if(a < b) swap(a, b);
		if(a == b && b == 0) puts("1");
		else if(a == b || b == 0) puts("2");
		else printf("%lld\n", 2 + Cal(a, b) - 1);
	}
	return 0;
} 
