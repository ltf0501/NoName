#include <stdio.h>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;
#define PB push_back
#define F first
#define S second
typedef unsigned int u;
constexpr int kN = int(1E5 + 10), kC = int(1E5 + 10);
u a, b, c, ta, tb, tc;
u rng61() {
	u t;
	a = a ^ (a << 16);
	a = a ^ (a >> 5);
	a = a ^ (a << 1);
	t = a;
	a = b;
	b = c;
	c = t ^ a ^ b;
	return c;
}

vector<u> v[kN];
int d[kN];
u ans[kN];

void solve(int n, int m) {
	vector<pair<int, int>> vx;
	u tmp;
	int x, now = -1, cnt = 0, lst = 0;
	for (int i = 1; i <= m; i++) {
		scanf("%d", &x);
		vx.PB({x + 1, i});
	}
	sort(vx.begin(), vx.end());
	for (int i = 0; i < kN; i++) d[i] = 0;
	for (int i = 0; i < n; i++) {
		tmp = rng61();
		d[tmp / kC]++;
	}

	for (int i = 0; i < kN; i++) {
		v[i].clear();
		v[i].shrink_to_fit();
		v[i].reserve(d[i]);
	}
	
	a = ta, b = tb, c = tc;

	for (int i = 0; i < n; i++) {
		tmp = rng61();
		v[tmp / kC].PB(tmp);
	}
	
	for (pair<int, int> i : vx) {
		while (cnt < i.F) {
			lst = cnt;
			cnt += int(v[++now].size());
		}
		nth_element(v[now].begin(), v[now].begin() + (i.F - lst - 1), v[now].end());
		ans[i.S] = v[now][i.F - lst - 1];
	}
	for (int i = 1; i <= m; i++) printf(" %u", ans[i]);
	printf("\n");
	return ;
}

int main() {
	int n, m, cnt = 1;
	while (scanf("%d%d%u%u%u", &n, &m, &a, &b, &c) != EOF) {
		printf("Case #%d:", cnt++);
		ta = a, tb = b, tc = c;
		solve(n, m);
	}
} 
