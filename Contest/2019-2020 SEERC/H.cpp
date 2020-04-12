#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long int ll;
constexpr int kN = int(2E5 + 10);
int a[kN];
bool t[kN], s[kN];
ll ans[kN], cnt[kN];

int main() {
	int n, npos, tsz = 0, ssz = 0, lpos = 1;
	ll tot = 0, up = 0;
	scanf("%d", &n);
	tot = (n - 1) << 1;
	for (int i = 1; i <= tot; i++) scanf("%d", &a[i]);
	sort(a + 1, a + tot + 1);
	for (int i = 1; i < n; i++) s[i] = t[i] = false;
	for (int i = 1; i <= tot; i++) s[a[i]] = true;
	for (int i = 1; i <= tot; i++) if (a[i] == i) t[i] = true;
	else if (a[i] > i) {
		printf("-1");
		for (int j = 2; j < n; j++) printf(" -1");
		printf("\n");
		return 0;
	}
	else cnt[a[i]]++;

	for (int i = 1; i < n; i++) ans[i] = -1;

	for (int i = 1; i < n; i++) {
		if (s[i]) ssz++;
		if (t[i]) tsz++;
	}
	tot = 0;
	
	npos = n;
	while (up < tsz) {
		npos--;
		up += cnt[npos];
		tot += cnt[npos] * npos;
	}
	ans[tsz] = tot - (up - tsz) * npos;
	
	for (int i = tsz + 1; i <= ssz; i++) {
		while (!s[lpos] || t[lpos]) lpos++;
		cnt[lpos]--;
		if (lpos >= npos) {
			up--;
			tot -= lpos;
		}
		while (up < i) {
			npos--;
			up += cnt[npos];
			tot += cnt[npos] * npos;
		}
		ans[i] = tot - (up - i) * npos;
		lpos++;
	}

	printf("%lld", ans[1]);
	for (int i = 2; i < n; i++) printf(" %lld", ans[i]);
	printf("\n");
} 
