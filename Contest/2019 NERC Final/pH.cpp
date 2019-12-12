#include <bits/stdc++.h>
using namespace std;
const int kN = 8505;
int col[kN];
int vis[kN];
int n;
void gao(vector<int> now, int c) {
	if(now.empty()) return;
	assert(c <= 24);
	//printf("c = %d\n", c);
	for(int x : now) vis[x] = 0;
	set<int> s;
	int sz = int(now.size());
	vector<vector<int>> tmp(n);
	for(int x : now) {
		if(!s.empty()) {
			auto it = s.lower_bound(x);
			if(it != s.end()) tmp[x].push_back(*it);
			if(it != s.begin()) tmp[x].push_back(*prev(it));
			//for(int y : tmp[x]) printf("%d ", y); puts("");
		}
		s.insert(x);
	}

	for(int i = sz - 1; i >= 0; i--) {
		int x = now[i];
		if(!vis[x]) {
			vis[x] = 1;
			col[x] = c;
			for(int y : tmp[x]) vis[y] = -1;
		}
	}

	vector<int> nxt;
	for(int x : now)
		if(vis[x] != 1) nxt.push_back(x);
	gao(nxt, c + 1);
}
int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		vector<int> a(n);
		for(int i = 0; i < n; i++) scanf("%d", &a[i]), a[i]--;
		gao(a, 1);
		for(int i = 0; i < n; i++) printf("%d ", col[i]);
		puts("");
	}
	return 0;
}
