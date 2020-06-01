#include <stdio.h>
#include <utility>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;
#define PB push_back
#define F first
#define S second
constexpr int kN = int(6E5 + 10);

struct Point {
	int x, y, w;
};

struct Query {
	int l, r;
};

struct BIT {
	int val[kN];
	void init() {memset(val, -1, sizeof(val));}
	void fix(int pos, int x) {
		pos++;
		for (; pos < kN; pos += pos & -pos) val[pos] = max(val[pos], x);
		return ;
	}
	int ask(int pos) {
		pos++;
		int ans = -1;
		for (; pos; pos ^= pos & -pos) ans = max(ans, val[pos]);
		return ans;
	}
};

Point r[kN], b[kN];
Query q[kN];
int ans[kN], query[kN];
vector<pair<int, int>> cand;
BIT bit;

void dfs(int L, int R, vector<int>& vb, vector<int>& vr) {
	if (vb.empty() || vr.empty()) return ;
	int mid = (L + R) >> 1, lm = 0, rm = 0;
	vector<int> lvb, lvr, rvb, rvr;
	for (int i : vb) if (b[i].y > mid && b[i].w > b[lm].w) lm = i;
	for (int i : vr) if (r[i].y <= mid && r[i].w > r[rm].w) rm = i;
	if (rm != 0) for (int i : vb) if (b[i].y > mid) cand.PB({i, rm});
	if (lm != 0) for (int i : vr) if (r[i].y <= mid) cand.PB({lm, i});

	for (int i : vb) if (b[i].y <= mid) lvb.PB(i);
	else rvb.PB(i);
	for (int i : vr) if (r[i].y <= mid) lvr.PB(i);
	else rvr.PB(i);

	dfs(L, mid, lvb, lvr);
	dfs(mid + 1, R, rvb, rvr);
	return ;
}

int main() {
	int n, m, pos, sz;
	vector<int> v, vb, vr;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d%d", &r[i].x, &r[i].y, &r[i].w);
	for (int i = 1; i <= n; i++) scanf("%d%d%d", &b[i].x, &b[i].y, &b[i].w);
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) scanf("%d%d", &q[i].l, &q[i].r);

	b[0] = {-1, -1, -1};
	r[0] = {-1, -1, -1};
	memset(ans, -1, sizeof(ans));
	for (int i = 1; i <= n; i++) r[i].x = -r[i].x;
	for (int i = 1; i <= m; i++) q[i].l = -q[i].l;

	v.reserve(n + m);
	for (int i = 1; i <= n; i++) v.PB(r[i].x);
	for (int i = 1; i <= m; i++) v.PB(q[i].l);
	sort(v.begin(), v.end());
	for (int i = 1; i <= n; i++) r[i].x = lower_bound(v.begin(), v.end(), r[i].x) - v.begin();
	for (int i = 1; i <= m; i++) q[i].l = lower_bound(v.begin(), v.end(), q[i].l) - v.begin();

	v.clear();
	v.reserve(n + m);
	for (int i = 1; i <= n; i++) v.PB(b[i].x);
	for (int i = 1; i <= m; i++) v.PB(q[i].r);
	sort(v.begin(), v.end());
	for (int i = 1; i <= n; i++) b[i].x = lower_bound(v.begin(), v.end(), b[i].x) - v.begin();
	for (int i = 1; i <= m; i++) q[i].r = lower_bound(v.begin(), v.end(), q[i].r) - v.begin();

	v.clear();
	v.reserve(n << 1);
	for (int i = 1; i <= n; i++) v.PB(b[i].y);
	for (int i = 1; i <= n; i++) v.PB(r[i].y);
	sort(v.begin(), v.end());
	for (int i = 1; i <= n; i++) b[i].y = lower_bound(v.begin(), v.end(), b[i].y) - v.begin();
	for (int i = 1; i <= n; i++) r[i].y = lower_bound(v.begin(), v.end(), r[i].y) - v.begin();

	vb.resize(n);
	vr.resize(n);
	for (int i = 0; i < n; i++) vb[i] = vr[i] = i + 1;
	dfs(0, (n << 1) - 1, vb, vr);

	sz = int(cand.size());

	for (int i = 1; i <= m; i++) query[i] = i;

	for (int f = 1; f <= 2; f++) {
		sort(query + 1, query + m + 1, [&](int l, int r){return q[l].r < q[r].r;});
		sort(cand.begin(), cand.end(), [&](pair<int, int> l, pair<int, int> r){return b[l.F].x < b[r.F].x;});
		bit.init();
		pos = 0;
		for (int i = 1; i <= m; i++) {
			while (pos < sz && b[cand[pos].F].x < q[query[i]].r) {
				bit.fix(r[cand[pos].S].x, b[cand[pos].F].w + r[cand[pos].S].w);
				pos++;
			}
			ans[query[i]] = max(ans[query[i]], bit.ask(q[query[i]].l));
		}

		for (int i = 1; i <= n; i++) b[i].x = kN - b[i].x - 2;
		for (int i = 1; i <= n; i++) r[i].x = kN - r[i].x - 2;
		for (int i = 1; i <= m; i++) q[i].l = kN - q[i].l - 2;
		for (int i = 1; i <= m; i++) q[i].r = kN - q[i].r - 2;
	}

	for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
} 
