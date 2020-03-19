#include <bits/stdc++.h>
using namespace std;
const int kN = 2.5e4 + 10;
const int kB = 30;
const int kMod = 998244353;

int fpow(int a, int n) {
	int res = 1;
	while(n) {
		if(n & 1) res = 1LL * res * a % kMod;
		n >>= 1, a = 1LL * a * a % kMod;
	}
	return res;
}
int Inv(int x) {return fpow(x, kMod - 2);}
int Det(vector<vector<int>> v) {
	assert(!v.empty());
	int n = int(v.size());
	int res = 1;
	for(int i = 0; i < n; i++) {
		int p = -1;
		for(int j = i; j < n; j++) {
			if(v[j][i] == 0) continue;
			if(p == -1 || v[j][i] > v[p][i]) p = j;
		}

		if(p == -1) return 0;
		if(p != i) {
			res = kMod - res;
			for(int j = 0; j < n; j++) swap(v[p][j], v[i][j]);
		}
		int f = Inv(v[i][i]);
		for(int j = 0; j < n; j++) if(i != j) {
			int tmp = 1LL * v[j][i] * f % kMod;
			for(int k = 0; k < n; k++) {
				v[j][k] = (v[j][k] - 1LL * tmp * v[i][k] % kMod) % kMod;
				if(v[j][k] < 0) v[j][k] += kMod;
			}
		}
	}
	
	//for(int i = n - 1; i >= 0; i--) {
	//	int f = Inv(v[i][i]);
	//	for(int j = 0; j < i; j++) {
	//		int tmp = 1LL * v[j][i] * f % kMod;
	//		for(int k = 0; k < n; k++) {
	//			v[j][k] = (v[j][k] - 1LL * tmp * v[i][k] % kMod) % kMod;
	//			if(v[j][k] < 0) v[j][k] += kMod;
	//		}
	//	}
	//}
	for(int i = 0; i < n; i++) res = 1LL * res * v[i][i] % kMod;
	return res;
}
int n, m, k;
vector<int> g[kN];

int in[kN], dfs_clock;
stack<int> s;
int bccno[kN], top[kN], bcc_cnt;
int id[kN];
vector<int> bcc[kN];

int dfs(int u, int fa = 0) {
	int lowu = in[u] = ++dfs_clock;
	s.push(u);
	for(int v : g[u]) if(v != fa) {
		if(in[v]) lowu = min(lowu, in[v]);
		else lowu = min(lowu, dfs(v, u));
	}
	if(lowu == in[u]) {
		top[++bcc_cnt] = u;
		int cur = 0;
		while(true) {
			int x = s.top(); s.pop();
			bcc[bcc_cnt].push_back(x);
			bccno[x] = bcc_cnt;
			id[x] = cur++;
			if(x == u) break;
		}
	}
	return lowu;
}
int dp[kN][2];
void solve(int u, int fa = 0) {
	int now = bccno[u], sz = int(bcc[now].size());
	vector<vector<int>> mat(2 * sz);
	for(int i = 0; i < 2 * sz; i++) mat[i].resize(2 * sz);
	for(int x : bcc[now]) {
		int p = 1, q = 0;
		for(int v : g[x]) if(v != fa) {
			if(bccno[v] == bccno[x]) {
				mat[id[v]][id[x]] = mat[id[x]][id[v]] = 1;
			}
			else {
				solve(v, x);
				q = (1LL * q * dp[v][0] + 1LL * p * dp[v][1]) % kMod;
				p = 1LL * p * dp[v][0] % kMod;
			}
		}

		mat[id[x] + sz][id[x] + sz] = p;
		mat[id[x]][id[x] + sz] = 1;
		mat[id[x] + sz][id[x]] = q;
	}
	dp[u][0] = Det(mat);

	for(int i = 0; i < 2 * sz; i++) mat[id[u]][i] = mat[i][id[u]] = 0;
	mat[id[u]][id[u]] = 1;
	dp[u][1] = Det(mat);
}
int main() {
	scanf("%d%d%d", &n, &m, &k);
	//vector<vector<int>> v(n);
	//for(int i = 0; i < n; i++) v[i].resize(n);
	for(int i = 1, x, y; i <= m; i++) {
		scanf("%d%d", &x, &y);
		g[x].push_back(y), g[y].push_back(x);
		//v[x - 1][y - 1] = v[y - 1][x - 1] = 1;
	}
	dfs(1);
	solve(1);
	printf("%d\n", dp[1][0]);
	//printf("%d\n", Det(v));
	return 0;
}
