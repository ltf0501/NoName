#include <bits/stdc++.h>
using namespace std;
const int kN = 1e5 + 10;
const int kM = 1e2 + 10;
int a[kN];
int dp1[kN][kM], dp2[kN][kM];
int prepos[kN], now[kN];
int pre1[kN][kM], pre2[kN][kM];
int main() {
#ifdef ONLINE_JUDGE
	freopen("funny.in", "r", stdin);
	freopen("funny.out", "w", stdout);
#endif
	int n, k;
	while(~scanf("%d%d", &n, &k) && n + k) {
		vector<int> v;
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), v.push_back(a[i]);
		sort(v.begin(), v.end());
		v.resize(unique(v.begin(), v.end()) - v.begin());
		for(int i = 1; i <= n; i++) 
			a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;

		for(int i = 1; i <= n; i++) now[i] = 0;
		for(int i = 1; i <= n; i++) {
			prepos[i] = now[a[i]];
			now[a[i]] = i;
		}
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= k; j++) dp1[i][j] = dp2[i][j] = 0;
		}

		for(int j = 1; j <= k; j++) {
			for(int i = 1; i <= n; i++) {
				if(dp1[i][j] < dp2[i - 1][j - 1] + 1) {
					dp1[i][j] = dp2[i - 1][j - 1] + 1;
					pre1[i][j] = i - 1;
				}
				if(dp1[i][j] < dp1[prepos[i]][j] + 1) {
					dp1[i][j] = dp1[prepos[i]][j] + 1;
					pre1[i][j] = pre1[prepos[i]][j];
				}
				//dp1[i][j] = max(dp1[i][j], dp2[i - 1][j - 1] + 1);
				//dp1[i][j] = max(dp1[i][j], dp1[prepos[i]][j] + 1);

				if(dp2[i][j] < dp2[i - 1][j]) {
					dp2[i][j] = dp2[i - 1][j];
					pre2[i][j] = pre2[i - 1][j];
				}
				if(dp2[i][j] < dp1[i][j]) {
					dp2[i][j] = dp1[i][j];
					pre2[i][j] = pre1[i][j];
				}
				//dp2[i][j] = max(dp2[i][j], dp2[i - 1][j]);
				//dp2[i][j] = max(dp2[i][j], dp1[i][j]);
				//printf("%d ", pre2[i][j]);
			}
			//puts("");
		}
		vector<int> ans;
		int cur = n;
		for(int i = k; i > 1; i--) {
			cur = pre2[cur][i];
			ans.push_back(cur);
		}
		reverse(ans.begin(), ans.end());
		printf("%d\n", dp2[n][k]);
		for(int x : ans) printf("%d ", x); puts("");
	}
	return 0;
}
