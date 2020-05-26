#include <bits/stdc++.h>
using namespace std;
const int kN = 1e2 + 5;
int Query(const vector<int> &v) {
	printf("? ");
	printf("%d ", int(v.size()));
	for(int x : v) printf("%d ", x); puts("");
	fflush(stdout);
	int x;
	scanf("%d", &x);
	return x;
}
int n; 
vector<int> s[kN];
vector<int> anc[kN];
bool vis[kN], vis2[kN];
int fa[kN];
vector<int> g[kN];
int ans[kN];
int cmp(int a, int b) { // 1:a is anc of b, 0: no, -1: b is anc of a
	memset(vis, 0, sizeof(vis));	
	memset(vis2, 0, sizeof(vis2));
	for(int x : s[a]) vis[x] = 1;
	for(int x : s[b]) vis2[x] = 1;
	bool A = 0, B = 0;
	for(int i = 1; i <= n; i++) {
		if(vis[i] && !vis2[i]) A = 1;
		if(!vis[i] && vis2[i]) B = 1;
	}
	if(A && B) return 0;
	if(A) return 1;
	return -1;
}

void dfs(int u, int fa = 0) {
	ans[u] = fa;
	for(int v : g[u])
		if(v != fa) dfs(v, u);
}
int main() {
	scanf("%d", &n);
	vector<int> leaf, other;	
	for(int i = 1; i <= n; i++) {
		vector<int> v;
		for(int j = 1; j <= n; j++)
			if(j != i) v.push_back(j);
		if(Query(v) == n - 1) leaf.push_back(i);
		else other.push_back(i);
	}
	for(int x : leaf) {
		if(x == leaf[0]) s[x] = leaf;
		else s[x].push_back(x);
	}
	for(int a : leaf) {
		if(a == leaf[0]) continue;
		for(int b : other) {
			vector<int> v;
			v.push_back(leaf[0]), v.push_back(a), v.push_back(b);
			if(Query(v) == 3) s[b].push_back(a);
		}
	}
	for(int i = 1; i <= n; i++) sort(s[i].begin(), s[i].end());

	//for(int i = 1; i <= n; i++) {
	//	printf("%d: ", i);
	//	for(int x : s[i]) printf("%d ", x); puts("");
	//}
	//puts("");
	for(int i = 1; i <= n; i++) {
		for(int j = i + 1; j <= n; j++) {
			int res = cmp(i, j);
			if(res == 1) anc[j].push_back(i);
			else if(res == -1) anc[i].push_back(j);
		}
	}

	//for(int i = 1; i <= n; i++) {
	//	printf("%d: ", i);
	//	for(int x : anc[i]) printf("%d ", x); puts("");
	//}
	//puts("");

	for(int i = 1; i <= n; i++) if(i != leaf[0]) {
		int mn = n + 5, id = -1;
		for(int j : anc[i]) {
			if(mn > int(s[j].size())) id = j, mn = int(s[j].size());
		}
		fa[i] = id;
	}
	for(int i = 1; i <= n; i++)
		if(i != leaf[0]) g[i].push_back(fa[i]), g[fa[i]].push_back(i);
	dfs(1);
	printf("! ");
	for(int i = 2; i <= n; i++) printf("%d ", ans[i]); puts(""); fflush(stdout);
	return 0;
} 
