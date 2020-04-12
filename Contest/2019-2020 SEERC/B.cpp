#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long int ll;
constexpr ll kInf = ll(1E16 + 10);
constexpr int kN = int(5E2 + 10);
struct Quest {
	int x, t, y, r;
	void in() {scanf("%d%d%d%d", &x, &t, &y, &r);}
};
bool cmp(Quest a, Quest b) {
	return a.x < b.x;
}
ll dp[kN << 1][kN][2];
Quest quest[kN];
int main() {
	int n, s1, s2, tot, nxtj, nxtk;
	ll ans = kInf;
	bool f = false;
	scanf("%d%d%d", &n, &s1, &s2);
	for (int i = 1; i <= n; i++) quest[i].in();
	tot = s1 + s2;
	sort(quest + 1, quest + n + 1, cmp);
	for (int i = 0; i <= tot; i++) for (int j = 0; j <= s2; j++) dp[i][j][0] = dp[i][j][1] = kInf;
	dp[0][0][0] = dp[0][0][1] = 0; 
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= s1; j++) for (int k = 0; k <= s2; k++) dp[j][k][f] = dp[j][k][!f];
		for (int j = 0; j <= s1; j++) for (int k = 0; k <= s2; k++) {
			if (j < s1) {
				nxtj = j + quest[i].x, nxtk = k;
				if (nxtj > s1) {
					nxtk += nxtj - s1;
					nxtj = s1;
				}
				if (nxtk >= s2) nxtk = s2;
				dp[nxtj][nxtk][f] = min(dp[nxtj][nxtk][f], dp[j][k][!f] + quest[i].t);
			}
			nxtj = j, nxtk = k + quest[i].y;
			if (nxtk >= s2) nxtk = s2;
			dp[nxtj][nxtk][f] = min(dp[nxtj][nxtk][f], dp[j][k][!f] + quest[i].r);
		}
		ans = min(ans, dp[s1][s2][f]);
		f = !f;
	}
	printf("%lld\n", ans == kInf ? -1 : ans);
} 
