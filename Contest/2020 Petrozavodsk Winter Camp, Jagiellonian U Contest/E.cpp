#include <stdio.h>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;
#define PB push_back

constexpr int kN = int(1E6 + 10), kInf = int(1E9 + 10);

struct seg_tree {
	int val[kN << 4];
	void init(int n, int l, int r) {
		val[n] = -kInf;
		if (l < r) {
			int mid = (l + r) >> 1;
			init(n << 1, l, mid);
			init(n << 1 | 1, mid + 1, r);
		}
		return ;
	}
	void add(int n, int l, int r, int pos, int x) {
		val[n] = max(val[n], x);
		if (l < r) {
			int mid = (l + r) >> 1;
			if (pos <= mid) add(n << 1, l, mid, pos, x);
			else add(n << 1 | 1, mid + 1, r, pos, x);
		}
		return ;
	}
	bool ask(int n, int l, int r, int L, int R, int x) {
		if (L <= l && r <= R) return val[n] >= x;
		else if (l > R || L > r) return false;
		else {
			int mid = (l + r) >> 1;
			return ask(n << 1, l, mid, L, R, x) | ask(n << 1 | 1, mid + 1, r, L, R, x);
		}
	}
};

tuple<int, int, int, int, int, int, int> query[kN];
tuple<int, int, int> circle[kN];
bool ans[kN];
seg_tree seg;

int main() {
	int n, q, xsz, now = 1;
	vector<int> x;
	scanf("%d%d", &n, &q);
	for (int i = 1, cx, cy, r; i <= n; i++) {
		scanf("%d%d%d", &cx, &cy, &r);
		circle[i] = {cy - r, cx, r};
		x.PB(cx);
	}
	for (int i = 1, px, py, qx, qy, y1, y2; i <= q; i++) {
		scanf("%d%d%d%d%d%d", &px, &py, &qx, &qy, &y1, &y2);	
		if (px > qx) swap(px, qx);
		query[i] = {y1, y2, px, py, qx, qy, i};
		x.PB(px);
		x.PB(qx);
	}
	sort(x.begin(), x.end());
	x.resize(unique(x.begin(), x.end()) - x.begin());
	for (int i = 1; i <= n; i++) get<1>(circle[i]) = lower_bound(x.begin(), x.end(), get<1>(circle[i])) - x.begin();
	for (int i = 1; i <= q; i++) {
		get<2>(query[i]) = lower_bound(x.begin(), x.end(), get<2>(query[i])) - x.begin();
		get<4>(query[i]) = lower_bound(x.begin(), x.end(), get<4>(query[i])) - x.begin();
	}
	sort(circle + 1, circle + n + 1);
	sort(query + 1, query + q + 1);
	
	xsz = int(x.size());
	seg.init(1, 0, xsz);
	for (int i = 1; i <= q; i++) {
		while (now <= n && get<0>(circle[now]) <= get<0>(query[i])) {
			seg.add(1, 0, xsz, get<1>(circle[now]), get<0>(circle[now]) + (get<2>(circle[now]) << 1));
			now++;
		}
		ans[get<6>(query[i])] = seg.ask(1, 0, xsz, get<2>(query[i]), get<4>(query[i]), get<1>(query[i]));
	}

	for (int i = 1; i <= q; i++) if (!ans[i]) printf("YES\n");
	else printf("NO\n");
} 
