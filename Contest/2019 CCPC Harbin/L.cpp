#include <stdio.h>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;
#define PB push_back
typedef long long int ll;
constexpr int kN = int(5E3 + 10), kMod = 998244353, kP[2] = {37, 97};

int pre[kN][kN], a[kN], x[kN], sz[kN];
ll hs[2][kN][kN]; 
bool used[kN];

void solve() {
	int n, q, m, zero;
	ll need[2];
	bool f, ok;
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) used[i] = false;
	sz[0] = 0;

	for (int i = 1; i <= n; i++) if (used[a[i]]) {
		sz[i] = sz[i - 1];
		for (int j = 1; j <= sz[i]; j++) pre[i][j] = pre[i - 1][j];
		for (int j = 1; j <= sz[i]; j++) if (pre[i][j] == a[i]) {
			for (int k = j; k > 1; k--) swap(pre[i][k], pre[i][k - 1]);
			break;
		}
	}
	else {
		used[a[i]] = true;
		sz[i] = sz[i - 1] + 1;
		for (int j = 2; j <= sz[i]; j++) pre[i][j] = pre[i - 1][j - 1];
		pre[i][1] = a[i];
	}

	for (int k = 0; k < 2; k++) for (int i = 1; i <= n; i++) {
		hs[k][i][0] = 0;
		for (int j = 1; j <= sz[i]; j++) hs[k][i][j] = (hs[k][i][j - 1] * kP[k] + pre[i][j]) % kMod;
	}

	while (q--) {
		scanf("%d", &m);
		for (int i = 1; i <= m; i++) scanf("%d", &x[i]);
		zero = 0;
		for (int i = 1; i <= m; i++) if (x[i] == 0) {
			zero = i;
			break;
		}
		if(zero == 1) {
			puts("Yes");
			continue;
		}
		need[0] = need[1] = 0;
		for (int k = 0; k < 2; k++) for (int i = 1; i <= m; i++) {
			if (x[i] == 0) break;
			need[k] = (need[k] * kP[k] + x[i]) % kMod; 
		}
		f = false;
		if (zero) {
			for (int i = 1; i <= n; i++) if (sz[i] == zero - 1) {
				ok = true;
				for (int k = 0; k < 2; k++) if (hs[k][i][zero - 1] != need[k]) {
					ok = false;
					break;
				}
				if (ok) {
					f = true;
					break;
				}
			}
		}
		else {
			for (int i = 1; i <= n; i++) if (sz[i] >= m) {
				ok = true;
				for (int k = 0; k < 2; k++) if (hs[k][i][m] != need[k]) {
					ok = false;
					break;
				}
				if (ok) {
					f = true;
					break;
				}
			}
		}
		if (f) printf("Yes\n");
		else printf("No\n");
	}

	return ;
	
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) solve();
} 
