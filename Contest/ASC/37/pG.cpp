#include <bits/stdc++.h>
using namespace std;
 
tuple<int, int, int, bool> p[200001];
int anc[20][200001];
int query(int x, int dis) {
	//cerr << x << ' ' << dis << '\n';
	for (int i = 18; i >= 0; i--) {
		if (dis & (1 << i)) x = anc[i][x];
	}
	return get<2>(p[x]);
}
 
int main() {
	freopen("queue.in", "r", stdin);
	freopen("queue.out", "w", stdout);
	cin.tie(0), ios_base::sync_with_stdio(0);
	int n; cin >> n;
	p[0] = {-1, 0, -1, false};
	for (int i = 1; i <= n; i++) {
		int op; cin >> op;
		if (op == 1) {
			int v, x; cin >> v >> x;
			p[i] = {v, get<1>(p[v]) + 1, x, false};
		} else {
			int v; cin >> v;
			p[i] = p[v];
			get<1>(p[i]) -= 1;
			get<3>(p[i]) = true;
		}
	}
	for (int i = 1; i <= n; i++) anc[0][i] = get<0>(p[i]);
	for(int j = 1; j <= 18; j++)
		for(int i = 0; i <= n; i++) anc[j][i] = anc[j - 1][anc[j - 1][i]]; 
	for (int i = 1; i <= n; i++) {
		if (get<3>(p[i])) cout << query(i, get<1>(p[i])) << '\n';
	}
}
