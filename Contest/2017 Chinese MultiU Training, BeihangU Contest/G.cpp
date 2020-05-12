#include <stdio.h>
#include <math.h>
#include <vector>
using namespace std;
#define PB push_back

constexpr int kN = int(1E5 + 10), kInf = int(1E9 + 10);

struct seg_tree {
	int val[kN << 2], flag[kN << 2];
	void addtag(int n, int x) {
		val[n] += x;
		flag[n] += x;
		return ;
	}
	void push(int n) {
		if (flag[n]) {
			addtag(n << 1, flag[n]);
			addtag(n << 1 | 1, flag[n]);
			flag[n] = 0;
		}
		return ;
	}
	void pull(int n) {
		val[n] = min(val[n << 1], val[n << 1 | 1]);
		return ;
	}
	void init(int n, int l, int r, int a[]) {
		flag[n] = 0;
		if (l == r) val[n] = a[l];
		else {
			int mid = (l + r) >> 1;
			init(n << 1, l, mid, a);
			init(n << 1 | 1, mid + 1, r, a);
			pull(n);
		}
		return ;
	}
	void add(int n, int l, int r, int L, int R, int x) {
		if (L <= l && r <= R) addtag(n, x);
		else if (!(l > R || L > r)) {
			int mid = (l + r) >> 1;
			push(n);
			add(n << 1, l, mid, L, R, x);
			add(n << 1 | 1, mid + 1, r, L, R, x);
			pull(n);
		}
		return ;
	}
	int ask(int n, int l, int r, int L, int R) {
		if (L <= l && r <=  R) return val[n];
		else if (l > R || L > r) return kInf;
		else {
			int mid = (l + r) >> 1;
			push(n);
			return min(ask(n << 1, l, mid, L, R), ask(n << 1 | 1, mid + 1, r, L, R));
		}
	}
};


seg_tree sg;
int dia[kN], l[kN], r[kN], in[kN], t, val[kN], p[kN], L[kN], R[kN];
bool went[kN], rt[kN];
vector<int> graph[kN], ng[kN];

int Find(int n) {
	return p[n] == n ? n : p[n] = Find(p[n]);
}

void dfs(int pos) {
	went[pos] = true;
	in[pos] = ++t;
	l[pos] = t;
	for (int i : graph[pos]) if (!went[i]) {
		val[t + 1] = val[in[pos]] + dia[i] - dia[pos];
		rt[i] = true;
		p[i] = p[pos];
		dfs(i);
	}
	r[pos] = t;
	if (rt[pos]) l[pos] = t + 1;
	for (int i : ng[pos]) if (!went[i]) {
		val[t + 1] = val[in[pos]];
		rt[i] = false;
		p[i] = p[pos];
		dfs(i);
	}
	if (rt[pos]) r[pos] = t;
	return ;
}

void solve(int n, int m, int q) {
	int a, x, y;
	for (int i = 1; i <= n; i++) scanf("%d", &dia[i]);
	for (int i = 1; i <= n; i++) graph[i].clear();
	for (int i = 1; i <= n; i++) ng[i].clear();
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &a, &x, &y);
		if (a == 1) {
			graph[x].PB(y);
			graph[y].PB(x);
		}
		else {
			ng[x].PB(y);
			ng[y].PB(x);
		}
	}
	for (int i = 1; i <= n; i++) dia[i] = __lg(dia[i]);

	t = 0;
	for (int i = 1; i <= n; i++) went[i] = false;
	for (int i = 1; i <= n; i++) if (!went[i]) {
		val[t + 1] = 0;
		p[i] = i;
		L[i] = t + 1;
		rt[i] = true;
		dfs(i);
		R[i] = t;
	}
	sg.init(1, 1, n, val);


	while (q--) {
		scanf("%d%d%d", &a, &x, &y);
		if (a == 1) {
			y = __lg(y);
			if (rt[x]) {
				if (l[x] <= r[x]) sg.add(1, 1, n, l[x], r[x], y - dia[x]);
				sg.add(1, 1, n, in[x], in[x], y - dia[x]);
			}
			else {
				sg.add(1, 1, n, l[x], r[x], dia[x] - y);
				sg.add(1, 1, n, in[x], in[x], y - dia[x]);
			}
			dia[x] = y;
		}
		else {
			int tmp = sg.ask(1, 1, n, in[x], in[x]), tp = p[x];
			printf("%.3lf\n", (tmp - sg.ask(1, 1, n, L[tp], R[tp])) * log(2) + log(y));
		}
	}

	return ;
}

int main() {
	int n, m, q, cnt = 1;
	while (scanf("%d%d%d", &n, &m, &q) != EOF) {
		printf("Case #%d:\n", cnt++);
		solve(n, m, q);
	}
} 
