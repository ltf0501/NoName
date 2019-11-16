#include <bits/stdc++.h>
using namespace std;
 
template <class T>
using MinHeap = priority_queue<T, vector<T>, greater<T>>;
 
const int kN = 1E5 + 10;
 
int ans[kN];
 
int CeilDiv(int a, int b) {
	return (a + b - 1) / b;
}
 
int main() {
	freopen("seaport.in", "r", stdin);
	freopen("seaport.out", "w", stdout);
	cin.tie(0), ios_base::sync_with_stdio(0);
	int n, m, c; cin >> n >> m >> c;
	MinHeap<tuple<int, int, int>> pq_ship[10] = {}; // (time, id, size)
	MinHeap<tuple<int64_t, int, int, int>> pq_crane; // (time, id, speed, mask)
	for (int i = 0; i < n; i++) {
		int d, cc, s; cin >> d >> cc >> s;
		--cc;
		pq_ship[cc].emplace(d, i, s);
	}
	for (int i = 0; i < m; i++) {
		int v, t, mask = 0;
		cin >> v >> t;
		for (int j = 0; j < t; j++) {
			int x; cin >> x;
			--x;
			mask |= 1 << x;
		}
		pq_crane.emplace(0, i, v, mask);
	}
	int num_ships = n;
	while (num_ships) {
		tuple<int64_t, int, int, int> mn_crane{};
		get<1>(mn_crane) = -1;
		tuple<tuple<int, int, int>, int> mn_ship_proc;
		while (get<1>(mn_crane) == -1) {
			auto tmp_mn_crane = pq_crane.top();
			pq_crane.pop();
			mn_ship_proc = {{2E9, 0, 0}, -1};
			for (int i = 0; i < c; i++) {
				if (pq_ship[i].size() && (get<3>(tmp_mn_crane) & (1 << i))) {
					mn_ship_proc = min(mn_ship_proc, {pq_ship[i].top(), i});
				}
			}
			if (get<1>(mn_ship_proc) != -1) {
				mn_crane = tmp_mn_crane;
				pq_ship[get<1>(mn_ship_proc)].pop();
				--num_ships;
			}
		}
		cerr << "MATCH: " << get<1>(mn_crane) << ' ' << get<1>(get<0>(mn_ship_proc)) << endl;
		ans[get<1>(get<0>(mn_ship_proc))] = get<1>(mn_crane);
		pq_crane.emplace(
				max(get<0>(mn_crane), int64_t(get<0>(get<0>(mn_ship_proc))))
					+ CeilDiv(get<2>(get<0>(mn_ship_proc)), get<2>(mn_crane)),
				get<1>(mn_crane),
				get<2>(mn_crane),
				get<3>(mn_crane));
	}
	for (int i = 0; i < n; i++) cout << ans[i] + 1 << '\n';
}
