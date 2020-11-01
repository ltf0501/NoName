#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int kN = 1e5 + 10;
const ll kInf = 1e18;

int n;
int a[kN];

ll floor(ll a, ll b) {
	if(b < 0) a = -a, b = -b; 
	if(a >= 0) return a / b;
	return -((-a - 1) / b + 1);
}
ll ceil(ll a, ll b) {
	if(b < 0) a = -a, b = -b;
	if(a >= 0) return (a + b - 1) / b;
	return -(-a / b);
}
int main() {
	scanf("%d", &n);
	ll sum = 0;
	for(int i = 0; i < n; i++) scanf("%d", &a[i]), sum += a[i];
	ll ans = kInf;

	for(int i = 0; i < n; i++) {
		if(a[i] == 0) {
			if(sum % 2 == 0) ans = min(ans, sum);
			continue;
		}
		if(a[i] & 1) {
			if(sum & 1) {  // * even
				ll k;
				if(a[i] > 0) {
					k = ceil(a[i] - sum, 2 * a[i]);
				}
				else {
					k = floor(a[i] - sum, 2 * a[i]);
				}
				ans = min(ans, (2 * k - 1) * a[i] + sum);
			}
			else { // * odd
				ll k;
				if(a[i] > 0) {
					k = ceil(-sum, 2 * a[i]);
				}
				else {
					k = floor(-sum, 2 * a[i]);
				}
				ans = min(ans, 2 * k * a[i] + sum);
			} 
		}
		else {
			if(sum & 1) continue;
			else {
				ll k;
				if(a[i] > 0) {
					k = ceil(a[i] - sum, a[i]); 
				}
				else {
					k = floor(a[i] - sum, a[i]);
				}
				ans = min(ans, (k - 1) * a[i] + sum);
			}
		} 
	}
	printf("%lld\n", ans);
	return 0;
} 
