#include <stdio.h>

typedef long long int ll;
constexpr int kN = int(1E5 + 10), kMod = int(1E9 + 7);
int a[kN];

ll solve() {
	ll ans = 1;
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	if (a[1] != 0) return 0;
	for (int i = 2; i <= n; i++) if (a[i] < a[i - 1]) return 0;
	if (a[n] >= n) return 0;
	for (int i = 2; i <= n; i++) if (a[i] != a[i - 1]) ans = ans * 2 % kMod;
	else ans = ans * (a[i] + 1 - i + 1) % kMod;
	return ans;
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) printf("%lld\n", solve());
} 
