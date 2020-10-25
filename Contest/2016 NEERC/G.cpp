#include <bits/stdc++.h>
using namespace std;

enum State { kDraw, kLose, kWin };
const char kRes[] = {'D', 'L', 'W'};

int main() {
freopen("game.in", "r", stdin);	
freopen("game.out", "w", stdout);	
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	int n, m; cin >> n >> m;
	vector<State> state(n + n);
	vector<int> cnt(n + n);
	vector<int8_t> can_win(n + n), can_lose(n + n);
	vector<int> can_lose_list;
	vector<vector<int>> g(n), gr(n + n);
	queue<int> q;
	while (m--) {
		int u, v; cin >> u >> v;
		--u, --v;
		g[u].push_back(v);
		gr[v + n].push_back(u);
		gr[v].push_back(u + n);
	}
	for (int i = 0; i < n; i++) {
		if (g[i].empty()) {
			state[i] = kLose;
			q.push(i);
			state[i + n] = kLose;
			q.push(i + n);
		}
		cnt[i] = cnt[i + n] = int(g[i].size());
	}
	while (!q.empty()) {
		while (!q.empty()) {
			int cur = q.front();
			q.pop();
			assert(state[cur] != kDraw);
			for (int prv : gr[cur]) {
				if (state[prv] != kDraw) continue;
				if (state[cur] == kLose && cur < n) {
					state[prv] = kWin;
					q.push(prv);
				} else if (state[cur] == kWin && cur < n) {
					if (--cnt[prv] <= 0) {
						state[prv] = kLose;
						q.push(prv);
					} else {
						if (!can_lose[prv]) can_lose_list.push_back(prv);
						can_lose[prv] = true;
					}
				} else if (state[cur] == kLose && cur >= n) {
					if (--cnt[prv] <= 0) {
						state[prv] = kWin;
						q.push(prv);
					} else {
						can_win[prv] = true;
					}
				} else if (state[cur] == kWin && cur >= n) {
					if (--cnt[prv] <= 0) {
						state[prv] = can_win[prv] ? kWin : kLose;
						q.push(prv);
					}
				} else {
					assert(false);
				}
			}
		}
		while (!can_lose_list.empty()) {
			int cur = can_lose_list.back();
			can_lose_list.pop_back();
			if (state[cur] != kDraw) continue;
			state[cur] = kLose;
			q.push(cur);
		}
	}
	//for (int i = 0; i < n + n; i++) cerr << cnt[i] << ' ';
	//cerr << '\n';
	assert(q.empty());
	for (int i = 0; i < n; i++) cout << kRes[state[i]];
	cout << '\n';
	for (int i = 0; i < n; i++) cout << kRes[state[i + n]];
	cout << '\n';
#if 0
	for (int i = 0; i < n; i++) {
		if (state[i] == kWin) q.push(i);
	}
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		if (cur < n) {
			for (int prv : gr[cur]) {
				if (state[prv] == kDraw) {
					state[prv] = kLose;
					q.push(prv);
				}
			}
		} else {
			for (int prv : gr[cur]) {
				if (state[prv] != kWin) {
					state[prv] = kWin;
					q.push(prv);
				}
			}
		}
	}
#endif
} 
