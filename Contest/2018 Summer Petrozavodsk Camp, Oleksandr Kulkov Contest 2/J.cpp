#include <stdio.h>
#include <vector>
#include <map>
#include <utility>
#include <assert.h>
using namespace std;
#define PB push_back
#define F first
#define S second

constexpr int kN = 60;
constexpr int kP = 890501;
constexpr int kC = 880301;
constexpr int kMod = 1e9 + 7;

int dep[kN], sz[kN], mxsz[kN];
int Hash[kN];
bool used[kN][kN];
vector<int> graph[kN], emp;
vector<vector<int>> ans;

void dfs_center(int pos, int from = 0) {
	sz[pos] = 1;
	mxsz[pos] = 0;
	for (int i : graph[pos]) if (i != from) dfs_center(i, pos);
	for (int i : graph[pos]) if (i != from) sz[pos] += sz[i];
	for (int i : graph[pos]) if (i != from) mxsz[pos] = max(mxsz[pos], sz[i]);
	return ;
}

void dfs_Hash(int u, int fa = 0) {
	Hash[u] = kP;
	for(int v : graph[u]) if(v != fa) 
		dfs_Hash(v, u), Hash[u] = 1LL * Hash[u] * (Hash[v] ^ kC) % kMod;
}

int get_Hash(int u, int fa = 0) {
	int Hash = kP;
	for(int v : graph[u]) if(v != fa) 
		Hash = 1LL * Hash * (get_Hash(v, u) ^ kC) % kMod;
	return Hash;
}

void init() {
	static int n = int(emp.size()) - 1;
	for (int i = 1; i <= n; i++) emp[i] = i;
	return ;
}

void map_to(int l, int lfrom, int r, int rfrom) {
	emp[l] = r;
	bool used_tmp[kN];
	for (int i = 0; i < kN; i++) used_tmp[i] = false;
	for (int i : graph[l]) if (i != lfrom) {
		used_tmp[i] = true;
		for (int j : graph[r]) if (j != rfrom && !used_tmp[j] && Hash[j] == Hash[i]) {
			used_tmp[j] = true;
			map_to(i, l, j, r);
			break;
		}
	}
	return ;
}

void dfs(int pos, int from = 0) {
	for (int i : graph[pos]) if (i != from) dfs(i, pos);
	map<int, vector<int>> m;
	for (int i : graph[pos]) if (i != from) {
		if (m[Hash[i]].empty()) m.insert({Hash[i], vector<int>()});
		m[Hash[i]].PB(i);
	}
	for (pair<int, vector<int>> i : m) if (int(i.S.size()) > 2) {
		init();
		for (int j = 0; j < int(i.S.size()); j++) {
			map_to(i.S[j], pos, i.S[(j + 1) % int(i.S.size())], pos);
		}
		ans.PB(emp);
		init();
		map_to(i.S[0], pos, i.S[1], pos);
		map_to(i.S[1], pos, i.S[0], pos);
		ans.PB(emp);
	}
	else if (int(i.S.size()) == 2) {
		init();
		map_to(i.S[0], pos, i.S[1], pos);
		map_to(i.S[1], pos, i.S[0], pos);
		ans.PB(emp);
	}

	return ;
}



int main() {
	int n, l, r;
	vector<int> center;
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &l, &r);
		graph[l].PB(r);
		graph[r].PB(l);
	}
	
	dfs_center(1);
	for (int i = 1; i <= n; i++) mxsz[i] = max(mxsz[i], n - sz[i]);
	for (int i = 1; i <= n; i++) if (mxsz[i] * 2 <= n) center.PB(i);

	emp.resize(n + 1);
	dfs_Hash(center[0]);
	dfs(center[0]);

	// special case
	
	if (center.size() == 2) {
		if (get_Hash(center[0], center[1]) == get_Hash(center[1], center[0])) {
			init();
			map_to(center[0], center[1], center[1], center[0]);
			map_to(center[1], center[0], center[0], center[1]);
			ans.PB(emp);
		}
	}



	assert(int(ans.size()) < n);
	if (ans.empty()) {
		init();
		ans.PB(emp);
	}
	printf("%d\n", int(ans.size()));
	for (int i = 0; i < int(ans.size()); i++) {
		for (int j = 1; j < n; j++) printf("%d ", ans[i][j]);
		printf("%d\n", ans[i][n]);
	}
} 
