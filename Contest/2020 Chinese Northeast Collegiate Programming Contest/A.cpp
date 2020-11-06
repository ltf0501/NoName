#include <bits/stdc++.h>
using namespace std;
#define PB push_back
constexpr int kN = 1 << 18;
int p[kN], a[kN], ansp[kN], ansb[kN], ppl[kN], t;
vector<int> graph[kN], same_dis[20];
int Find(int n) {return n == p[n] ? n : p[n] = Find(p[n]);}
void Merge(int l, int r) {
	l = Find(l), r = Find(r);
	if (l != r) p[r] = l;
	return ;
}
void dfs(int pos, int from) {
	//printf("dfs(%d, %d)\n", pos, from);
	++t;
	ansp[t] = pos;
	ansb[t] = from;
	for (int i : graph[pos]) if (i != from) {
		dfs(i, pos);
	}
	return ;
}
void solve() {
	int n, ans = 0, cur;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	memset(ppl, 0, sizeof(ppl));
	t = 0;
	for (int i = 0; i < kN; i++) p[i] = i;
	for (int i = 1; i <= n; i++) ppl[a[i]] = i;
	for (int i = 1; i <= n; i++) graph[i].clear();
	for (int i = 0; i < 20; i++) same_dis[i].clear();
	for (int i = 1; i <= n; i++) same_dis[0].PB(a[i]);
	for (int i = 0; i < 20; i++) {
		for (int j : same_dis[i]) {
			for (int k = 0; k < 18; k++) {
				if (ppl[(1 << k) ^ j]) {
					if (Find((1 << k) ^ j) != Find(j)) {
						graph[ppl[j]].PB(ppl[(1 << k) ^ j]);
						graph[ppl[(1 << k) ^ j]].PB(ppl[j]);
						Merge(j, (1 << k) ^ j);
					}
				}
			}
		}
		for (int j : same_dis[i]) {
			for (int k = 0; k < 18; k++) {
				if (ppl[(1 << k) ^ j]) {
					if (Find((1 << k) ^ j) != Find(j)) {
						graph[ppl[j]].PB(ppl[(1 << k) ^ j]);
						graph[ppl[(1 << k) ^ j]].PB(ppl[j]);
						Merge(j, (1 << k) ^ j);
					}
				}
				else {
					p[(1 << k) ^ j] = j;
					ppl[(1 << k) ^ j] = ppl[j];
					same_dis[i + 1].PB((1 << k) ^ j);
				}
			}
		}
	}
	dfs(1, 1);
	ansb[1] = 1;
	for (int i = 2; i <= n; i++) ans += __builtin_popcount(a[ansp[i]] ^ a[ansb[i]]);
	printf("%d\n", ans);
	printf("%d", ansp[1]); for (int i = 2; i <= n; i++) printf(" %d", ansp[i]); printf("\n");
	printf("%d", ansb[1]); for (int i = 2; i <= n; i++) printf(" %d", ansb[i]); printf("\n");
	return ;
}

int main() {
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++) solve();
} 
