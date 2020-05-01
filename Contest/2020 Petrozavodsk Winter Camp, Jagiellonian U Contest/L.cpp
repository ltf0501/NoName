#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long int ll;
constexpr int kN = int(1E5 + 10);
constexpr ll kInf = ll(1E16 + 10);
int a[kN];

void solve() {
	int n, k;
	ll ans = 0;
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n - k; i++) ans += a[i];
	ans = max(ans, ll(a[n]));
	printf("%lld\n", ans);
	return ;
}



int main() {
	int t;
	scanf("%d", &t);
	while (t--) solve();
}

