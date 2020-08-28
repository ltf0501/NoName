#include <stdio.h>
#include <utility>
#include <queue>
#include <algorithm>
using namespace std;
#define F first
#define S second

constexpr int kN = int(1E5 + 10);

int len[kN], d[kN], from[kN], p[kN];
bool went[kN];
pair<int, int> a[kN];

int main() {
	int n, k, pos = 1, nxt, ans = 0;
	queue<int> q;
	scanf("%d%d", &n, &k);
	for (int i = 2; i <= n; i++) scanf("%d", &p[i]);
	for (int i = 2; i <= n; i++) d[p[i]]++;
	for (int i = 1; i <= n; i++) from[i] = i;
	for (int i = 1; i <= n; i++) len[i] = 1;
	for (int i = 1; i <= n; i++) if (d[i] == 0) q.push(i);
	while (!q.empty()) {
		nxt = q.front();
		q.pop();
		if (nxt == 1) break;
		d[p[nxt]]--;
		if (d[p[nxt]] == 0) q.push(p[nxt]);
		if (len[nxt] >= len[p[nxt]]) {
			len[p[nxt]] = len[nxt] + 1;
			from[p[nxt]] = from[nxt];
		}
	}
	p[1] = 1;
	for (int i = 1; i <= n; i++) a[i] = {len[i], i};
	sort(a + 1, a + n + 1);
	reverse(a + 1, a + n + 1);
	while (k--) {
		if (pos > n) break;
		if (went[a[pos].S]) {
			pos++;
			k++;
			continue;
		}
		ans += a[pos].F;
		nxt = from[a[pos].S];
		while (!went[nxt]) {
			went[nxt] = true;
			nxt = p[nxt];
		}
		pos++;
	}
	printf("%d\n", ans);
} 
