#include <bits/stdc++.h>
using namespace std;

constexpr int64_t kInf = 1e18;

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	int n;
	int64_t t;
	cin >> n >> t;
	vector<int> xs(n), ys(n);
	string ds(n, 0);
	set<tuple<int, int, int>> st_xs, st_ys;
	for (int i = 0; i < n; i++) {
		cin >> xs[i] >> ys[i] >> ds[i];
		st_xs.emplace(ys[i], xs[i], i);
		st_ys.emplace(xs[i], ys[i], i);
	}
	using P = pair<int, int64_t>;
	vector<int64_t> dist(n, kInf);
	priority_queue<P, vector<P>, greater<P>> pq;
	pq.emplace(dist[0] = 0, 0);
	while (!pq.empty()) {
		auto cur_p = pq.top();
		pq.pop();
		auto d = cur_p.first;
		auto cur = cur_p.second;
		if (d > dist[cur]) continue;
		auto is_lr = [](char c) { return c == 'L' || c == 'R'; };
		auto is_sub = [](char c) { return c == 'L' || c == 'D'; };
		auto &st = is_lr(ds[cur]) ? st_xs : st_ys;
		auto &cord = is_lr(ds[cur]) ? ys : xs;
		auto &cordr = is_lr(ds[cur]) ? xs : ys;
		auto it = st.lower_bound({cord[cur], cordr[cur], 0});
		if (is_sub(ds[cur])) {
			while (it-- != st.begin() && get<0>(*it) == cord[cur]) {
				auto n_d = dist[cur] + abs(cordr[cur] - get<1>(*it));
				if (dist[get<2>(*it)] > n_d) {
					pq.emplace(dist[get<2>(*it)] = n_d, get<2>(*it));
				}
				if (get<2>(*it) != cur && ds[get<2>(*it)] == ds[cur]) break;
			}
		} else {
			for (; it != st.end() && get<0>(*it) == cord[cur]; ++it) {
				auto n_d = dist[cur] + abs(cordr[cur] - get<1>(*it));
				if (dist[get<2>(*it)] > n_d) {
					pq.emplace(dist[get<2>(*it)] = n_d, get<2>(*it));
				}
				if (get<2>(*it) != cur && ds[get<2>(*it)] == ds[cur]) break;
			}
		}
	}
	array<pair<int, int>, 256> to_dir;
	to_dir[uint8_t('L')] = {-1, 0};
	to_dir[uint8_t('R')] = {1, 0};
	to_dir[uint8_t('U')] = {0, 1};
	to_dir[uint8_t('D')] = {0, -1};
	for (int i = 0; i < n; i++) {
		int64_t steps = max<int64_t>(0, t - dist[i]);
		auto dir = to_dir[uint8_t(ds[i])];
		cout << xs[i] + steps * dir.first << ' ' << ys[i] + steps * dir.second << '\n';
	}
} 
