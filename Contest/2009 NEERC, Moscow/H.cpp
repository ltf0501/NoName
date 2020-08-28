#include <stdio.h>
#include <algorithm>
#include <utility>
#include <functional>
#include <queue>
#include <set>
using namespace std;
#define F first
#define S second

constexpr int kN = int(1E5 + 10), kM = int(1E2 + 10);


int stu_pre[kN][kM], fac_pre[kM][kN], fac_rnk[kN][kM], npos[kM], stu_rnk[kM][kN];
bool alive[kM][kN], ok[kN][kM];
queue<int> q[kM], nq[kM];

int main() {
	freopen("harmless.in", "r", stdin);
	freopen("harmless.out", "w", stdout);
	int n, m, k, nxt, ns;
	bool first;
	set<int> s;
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) scanf("%d", &stu_pre[i][j]);
	for (int i = 1; i <= m; i++) for (int j = 1; j <= n; j++) scanf("%d", &fac_pre[i][j]);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) fac_rnk[i][stu_pre[i][j]] = j;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) stu_rnk[j][fac_pre[j][i]] = i;
	
	for (int i = 1; i <= m; i++) for (int j = 1; j <= n; j++) alive[i][j] = true;
	for (int i = 1; i <= m; i++) for (int j = 1; j <= k; j++) ok[fac_pre[i][j]][i] = true;
	for (int i = 1; i <= m; i++) npos[i] = k;
	for (int i = 1; i <= m; i++) {
		function<void(int)> goright = [&](int x) {
			npos[x]++;
			while (!alive[x][npos[x]]) npos[x]++;
			ok[fac_pre[x][npos[x]]][x] = true;
			if (fac_rnk[fac_pre[x][npos[x]]][x] <= i) {
				nq[fac_rnk[fac_pre[x][npos[x]]][x]].push(fac_pre[x][npos[x]]);
				s.insert(fac_rnk[fac_pre[x][npos[x]]][x]);
			}
			return ;
		};
		for (int j = 1; j <= n; j++) if (ok[j][stu_pre[j][i]]) nq[i].push(j);
		if (!nq[i].empty()) s.insert(i);
		while (!s.empty()) {
			ns = *s.begin();
			s.erase(s.begin());
			swap(q[ns], nq[ns]);
			while (!q[ns].empty()) {
				nxt = q[ns].front();
				q[ns].pop();
				if (!alive[stu_pre[nxt][ns]][stu_rnk[stu_pre[nxt][ns]][nxt]]) continue;
				for (int j = ns + 1; j <= m; j++) if (alive[stu_pre[nxt][j]][stu_rnk[stu_pre[nxt][j]][nxt]]) {
					alive[stu_pre[nxt][j]][stu_rnk[stu_pre[nxt][j]][nxt]] = false;
					if (stu_rnk[stu_pre[nxt][j]][nxt] <= npos[stu_pre[nxt][j]]) goright(stu_pre[nxt][j]);
				} else break;
			}
		}
	}

	for (int i = 1; i <= m; i++) {
		first = true;
		for (int j = 1; j <= npos[i]; j++) {
			if (alive[i][j]) {
				if (first) {
					printf("%d", fac_pre[i][j]);
					first = false;
				}
				else printf(" %d", fac_pre[i][j]);
			}
		}
		printf("\n");
	}
} 
