#include <stdio.h>
typedef long long int ll;
constexpr int kN = int(1E5 + 10), kInf = int(1E9 + 10);

int p[kN];

bool ok(ll x, ll n, ll c, ll t) {
	int now = 0;
	for (int i = 1; i <= n; i++) {
		if (p[i] > t * x) return false;
		if (now + p[i] > t * x) {
			now = 0;
			c--;
		}
		now += p[i];
	}
	return c >= 1;
}

int main() {
	int n, c, t, l, r, mid;
	scanf("%d%d%d", &n, &c, &t);
	for (int i = 1; i <= n; i++) scanf("%d", &p[i]);
	l = 0, r = kInf;
	while (r - l > 1) {
		mid = (l + r) >> 1;
		if (ok(mid, n, c, t)) r = mid;
		else l = mid;
	}
	printf("%d\n", r);
} 
