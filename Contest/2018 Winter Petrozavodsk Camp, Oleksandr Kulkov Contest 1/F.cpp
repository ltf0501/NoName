bool debug = false;
#include <bits/stdc++.h>
using namespace std;
constexpr int kN = int(1E5 + 10);
#define PB push_back

struct Edge {
	int t, u, v, w;
	void in() {
		scanf("%d%d%d%d", &t, &u, &v, &w);
		return ;
	}
	void out() {
		printf("(%d, %d, %d, %d)\n", t, u, v, w);
		return ;
	}
};

bool cmp(Edge a, Edge b) {
	return a.w == b.w ? a.t > b.t : a.w > b.w;
}

int p1[kN], p2[kN];
vector<int> v[kN], v2[kN];
Edge edge[kN];
bool cand[kN];

int Find1(int n) {return p1[n] == n ? n : p1[n] = Find1(p1[n]);}
int Find2(int n) {return p2[n] == n ? n : p2[n] = Find2(p2[n]);}
void Merge1(int l, int r) {
	if (debug) printf("Merge1(%d, %d)\n", l, r);
	l = Find1(l), r = Find1(r);
	if (l == r) return ;
	p1[r] = l;
	if (int(v[l].size()) < int(v[r].size())) swap(v[l], v[r]);
	for (int i : v[r]) v[l].PB(i);
	return ;
}

void Merge2(int l, int r) {
	if (debug) printf("Merge2(%d, %d)\n", l, r);
	l = Find2(l), r = Find2(r);
	if (l == r) return ;
	p2[r] = l;
	if (int(v2[l].size()) < int(v2[r].size())) swap(v2[l], v2[r]);
	for (int i : v2[r]) v2[l].PB(i);
	return ;
}

void Kill(int n) {
	if (debug) printf("Kill %d\n", n);
	n = Find1(n);
	for (int i : v[n]) cand[i] = false;
	v[n].clear();
	return ;
}

void Kill2(int n) {
	if (debug) printf("Kill2 %d\n", n);
	n = Find2(n);
	for (int i : v2[n]) cand[i] = false;
	v2[n].clear();
	return ;
}


int main() {
	int n, m, l, r, sz, lst = 1;
	vector<int> ans;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) edge[i].in();
	sort(edge + 1, edge + m + 1, cmp);
	if (debug) for (int i = 1; i <= m; i++) edge[i].out();
	
	for (int i = 1; i <= n; i++) p1[i] = p2[i] = i;
	for (int i = 1; i <= n; i++) v[i].PB(i), v2[i].PB(i);
	for (int i = 1; i <= n; i++) cand[i] = true;
	for (int i = 1; i <= m; i++) {
		l = edge[i].u, r = edge[i].v;
		while (edge[lst].t == 1 && edge[lst].w != edge[i].w) {
			Merge2(edge[lst].u, edge[lst].v);
			lst++;
		}
		if (edge[i].t == 1) {
			if (edge[lst].w != edge[i].w) lst = i;
			if (Find2(l) == Find2(r)) {
				Kill2(l), Kill2(r);
			}
			Merge1(l, r);
		}
		else {
			if (Find1(l) == Find1(r)) continue;	
			else {
				Kill(l);
				Kill(r);
				Merge2(l, r);
			}
		}
	}
	
	for (int i = 1; i <= n; i++) if(cand[i]) ans.PB(i);
	assert(!ans.empty());
	sz = int(ans.size());
	printf("%d\n%d", sz, ans[0]);
	for (int i = 1; i < sz; i++) printf(" %d", ans[i]);
	printf("\n");
} 
