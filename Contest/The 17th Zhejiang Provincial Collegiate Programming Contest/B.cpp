#include <bits/stdc++.h>
using namespace std;

#define F first
#define S second
constexpr int kN = int(1E6 + 10), kInf = int(1E9 + 10);

struct seg_tree {
	int val[kN << 2], idx[kN << 2];
	void pull(int n) {
		if (val[n << 1] <= val[n << 1 | 1]) idx[n] = idx[n << 1];
		else idx[n] = idx[n << 1 | 1];
		val[n] = min(val[n << 1], val[n << 1 | 1]);
		return ;
	}
	void init(int n, int l, int r) {
		val[n] = kInf;
		idx[n] = l;
		if (l < r) {
			int mid = (l + r) >> 1;
			init(n << 1, l, mid);
			init(n << 1 | 1, mid + 1, r);
		}
		return ;
	}
	void fix(int n, int l, int r, int pos, int x) {
		if (l == r) val[n] += x;
		else {
			int mid = (l + r) >> 1;
			if (pos <= mid) fix(n << 1, l, mid, pos, x);
			else fix(n << 1 | 1, mid + 1, r, pos, x);
			pull(n);
		}
	}
	int ask(int n, int l, int r, int x) {
		if (l == r) return idx[n];
		else {
			int mid = (l + r) >> 1;
			if (val[n << 1] <= x) return ask(n << 1, l, mid, x);
			else return ask(n << 1 | 1, mid + 1, r, x);
		}
	}
};

seg_tree sg;
map<int, int> se;
int a[kN];

void solve() {
	int n, c, ans1 = 0, ans2 = 0, id, tmp;
	map<int, int> :: iterator u;
	scanf("%d%d", &n, &c);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	sg.init(1, 1, n);
	for (int i = 1; i <= n; i++) {
		if (sg.val[1] > c - a[i]) sg.fix(1, 1, n, ++ans1, a[i] - kInf);
		else {
			id = sg.ask(1, 1, n, c - a[i]);
			sg.fix(1, 1, n, id, a[i]);
		}
	}
	se.clear();
	for (int i = 1; i <= n; i++) {
		if (se.empty() || se.begin() -> F + a[i] > c) {
			se[a[i]]++;
			ans2++;
		}
		else {
			u = prev(se.upper_bound(c - a[i]));
			tmp = u -> F;
			if (u -> S == 1) se.erase(u);
			else se[tmp]--;
			se[tmp + a[i]]++;
		}
	}
	printf("%d %d\n", ans1, ans2);
	return ;
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) solve();
} 
