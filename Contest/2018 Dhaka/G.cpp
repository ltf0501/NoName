#include <bits/stdc++.h>
using namespace std;
const int kN = 1e5 + 10;
const int kInf = 1e9 + 7;
typedef pair<int, int> pii;
#define F first
#define S second

#define lc (o << 1)
#define rc (o << 1 | 1)
struct Segment_Tree {
	int N;
	vector<int> seg;
	vector<int> id;
	void push_up(int o) {
		seg[o] = min(seg[lc], seg[rc]);
	}
	void Build(int l, int r, int o) {
		if(l == r) {
			seg[o] = kInf;
			return;
		}
		int m = (l + r) >> 1;
		Build(l, m, lc), Build(m + 1, r, rc);
		push_up(o);
	}

	Segment_Tree() {}
	int GetID(int x) {
		return lower_bound(id.begin(), id.end(), x) - id.begin() + 1;
	}
	Segment_Tree(int _N, vector<int> v) {
		N = _N;
		seg.resize((N << 2) + 1);
		Build(1, N, 1);
		id = v;
		sort(id.begin(), id.end());
	}

	void _update(int x, int k, int l, int r, int o) {
		if(l == r) {
			seg[o] = k;
			return;
		}
		int m = (l + r) >> 1;
		if(x <= m) _update(x, k, l, m, lc);
		else _update(x, k, m + 1, r, rc);
		push_up(o);
	}

	int _query(int ql, int qr, int l, int r, int o) {
		if(ql <= l && r <= qr) return seg[o];
		int m = (l + r) >> 1;
		if(qr <= m) return _query(ql, qr, l, m, lc);
		if(ql > m) return _query(ql, qr, m + 1, r, rc);
		return min(_query(ql, qr, l, m, lc), _query(ql, qr, m + 1, r, rc));
	}

	void update(int x, int k) {
		x = GetID(x);
		_update(x, k, 1, N, 1);
	}
	int query(int ql, int qr) {
		ql = lower_bound(id.begin(), id.end(), ql) - id.begin() + 1;
		qr = upper_bound(id.begin(), id.end(), qr) - id.begin();
		//printf("ql = %d, qr = %d, N = %d\n", ql, qr, N);
		if(ql > qr) return kInf;
		return _query(ql, qr, 1, N, 1);
	}
};
int n;
vector<int> g[kN];
int l[kN], r[kN];

vector<int> now;
bool vis[kN];
int sz[kN], mx[kN];
int cen_dep[kN], cen_anc[20][kN], cen_dis[20][kN];

void GetCen(int u) {
	sz[u] = 1, mx[u] = 0, vis[u] = 1;
	now.push_back(u);
	for(int v : g[u]) if(!vis[v]) {
		GetCen(v);
		sz[u] += sz[v], mx[u] = max(mx[u], sz[v]);
	}
}

void GetDis(int u, int dep, int d = 0) {
	vis[u] = 1; now.push_back(u);
	cen_dis[dep][u] = d;
	for(int v : g[u]) if(!vis[v]) {
		GetDis(v, dep, d + 1);
	}
}
Segment_Tree *tree[kN];
void Dfs(int u, int d = 0) {
	GetCen(u);
	int cen = -1;
	int s = now.size();
	for(int w : now) {
		if(max(mx[w], s - sz[w]) * 2 <= s) cen = w;
	}
	for(int w : now) cen_anc[d][w] = cen, vis[w] = 0;
	now.clear();
	cen_dep[cen] = d;

	GetDis(cen, d);

	tree[cen] = new Segment_Tree(int(now.size()), now);
	for(int w : now) {
		tree[cen]->update(w, cen_dis[d][w]);
		vis[w] = 0;
	}
	now.clear();

	vis[cen] = 1;
	for(int v : g[cen]) if(!vis[v]) {
		Dfs(v, d + 1);
	}
}

int Query(int x, int l, int r) {
	int dep = cen_dep[x];
	int res = kInf;
	for(int i = dep; i >= 0; i--) {
		int anc = cen_anc[i][x];
		//printf("fa = %d\n", anc);
		int k = tree[anc]->query(l, r);
		//printf("anc_dis = %d, query = %d\n", cen_dis[i][x], k = tree[anc]->query(l, r));
		res = min(res, cen_dis[i][x] + k);
	}
	return res;
}

void Init() {
	for(int i = 1; i <= n; i++) l[i] = r[i] = -1;
	for(int i = 1; i <= n; i++) g[i].clear();
	now.clear();
	for(int i = 1; i <= n; i++) vis[i] = 0;
	for(int j = 0; j < 16; j++)
		for(int i = 1; i <= n; i++) cen_dis[j][i] = kInf, cen_anc[j][i] = 0;
}
int main() {
	int T; scanf("%d", &T);
	int cas = 0;
	while(T--) {
		printf("Case %d:\n", ++cas);
		scanf("%d", &n);
		Init();
		for(int i = 1; i < n; i++) {
			int x, y; scanf("%d%d", &x, &y);
			g[x].push_back(y), g[y].push_back(x);
		}

		Dfs(1);
		//for(int i = 1; i <= n; i++) {
		//	printf("%d: dep = %d, ", i, cen_dep[i]);
		//	printf("anc: ");
		//	for(int j = cen_dep[i]; j >= 0; j--) printf("%d ", cen_anc[j][i]); puts("");
		//}
		int q; scanf("%d", &q);
		while(q--) {
			int type; scanf("%d", &type);
			if(type == 1) {
				int x; scanf("%d", &x);
				scanf("%d%d", &l[x], &r[x]);
			}
			else if(type == 2) {
				int x; scanf("%d", &x);
				l[x] = r[x] = -1;
			}
			else if(type == 3) {
				int x, m; scanf("%d%d", &x, &m);
				int ans = kInf;
				for(int i = 0; i < m; i++) {
					int c; scanf("%d", &c);
					if(l[c] != -1) ans = min(ans, Query(x, l[c], r[c]));
				}
				printf("%d\n", ans == kInf ? -1 : ans);
			}
		}
		//for(int i = 1; i <= n; i++) free(tree[i]);
	}
	return 0;
} 
