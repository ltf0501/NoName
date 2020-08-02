#include <bits/stdc++.h>
using namespace std;
const int kN = 3e3 + 10;
const int kP = 890501;
const int kMod = 1e9 + 123;
typedef pair<int, int> pii;
#define F first
#define S second

int n, m;

vector<int> g[kN];
vector<pii> edges;
int to(int x, int id) {return x ^ edges[id].F ^ edges[id].S;}

stack<int> s;
int in[kN], dfs_clock;

vector<int> bcc[kN];
int bccno[kN], bcc_cnt;
int component[kN], now;
int ans[kN][kN];

int Dfs(int u, int bad_id = -1, int fa = -1) {
	component[u] = now;
	int lowu = in[u] = ++dfs_clock;
	s.push(u);
	for(int id : g[u]) if(id != bad_id) {
		int v = to(u, id);
		if(v == fa) continue;
		if(!in[v]) lowu = min(lowu, Dfs(v, bad_id, u));
		else lowu = min(lowu, in[v]);
	}

	if(lowu == in[u]) {
		bcc_cnt++;
		while(true) {
			int x = s.top(); s.pop();
			bccno[x] = bcc_cnt;
			bcc[bcc_cnt].push_back(x);
			if(x == u) break;
		}
	}
	return lowu;
}

void Init() {
	memset(in, 0, sizeof(in));
	dfs_clock = 0;
	memset(bccno, 0, sizeof(bccno));
	bcc_cnt = 0;
}

int h[kN];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i++) {
		int x, y; scanf("%d%d", &x, &y);
		g[x].push_back(i), g[y].push_back(i);
		edges.emplace_back(x, y);
	}

	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++) ans[i][j] = -1;

	for(int i = 1; i <= n; i++) {
		if(!in[i]) {
			now++;
			Dfs(i);
		}
	}

	//printf("bccno: ");
	//for(int i = 1; i <= n; i++) printf("%d ", bccno[i]); puts("");
	//printf("component: ");
	//for(int i = 1; i <= n; i++) printf("%d ", component[i]); puts("");

	for(int i = 1; i <= n; i++) {
		for(int j = i + 1; j <= n; j++) {
			if(component[i] != component[j]) ans[i][j] = 0;
			else if(bccno[i] != bccno[j]) ans[i][j] = 1;
		}
	}

	now = 0;
	for(int j = 0; j < m; j++) {
		Init();
		for(int i = 1; i <= n; i++) {
			if(!in[i]) {
				Dfs(i, j);
			}
		}

		for(int i = 1; i <= n; i++) h[i] = (1LL * h[i] * kP + bccno[i]) % kMod;
	}

	for(int i = 1; i <= n; i++) {
		for(int j = i + 1; j <= n; j++) if(ans[i][j] == -1) {
			if(h[i] == h[j]) ans[i][j] = 3;
			else ans[i][j] = 2;
		}
	}

	int sum = 0;
	//for(int i = 1; i <= n; i++) {
	//	for(int j = 1; j <= n; j++) printf("%d ", ans[i][j]); puts("");
	//}
	for(int i = 1; i <= n; i++)
		for(int j = i + 1; j <= n; j++) sum += ans[i][j];
	printf("%d\n", sum);
	return 0;
} 
