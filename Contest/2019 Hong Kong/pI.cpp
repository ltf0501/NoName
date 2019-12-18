#include <bits/stdc++.h>
using namespace std;
 
constexpr int kN = 200010;
 
using TP = tuple<int64_t, int>;
priority_queue<TP, vector<TP>, greater<TP>> pq[kN];
int64_t tag[kN], id2tag[kN][3];
int p_cnt[kN], id2pos[kN][3];
int64_t need[kN];
map<pair<int, int>, int> mp;
 
int main() {
	cin.tie(nullptr); ios_base::sync_with_stdio(false);
	int n, m; cin >> n >> m;
	int last = 0, id = 0;
	for (int t = 0; t < m; t++) {
		int op; cin >> op;
		if (op == 1) {
			id++;
			cin >> need[id] >> p_cnt[id];
			need[id] ^= last;
			for (int i = 0; i < p_cnt[id]; i++) {
				cin >> id2pos[id][i];
				int q = id2pos[id][i] ^= last;
				pq[q].emplace((need[id] + p_cnt[id] - 1) / p_cnt[id] + tag[q], id);
				id2tag[id][i] = tag[q];
				mp[{id, q}] = i;
			}
		} else {
			int x, y; cin >> x >> y;
			x ^= last;
			y ^= last;
			tag[x] += y;
			vector<int> ans;
			while (pq[x].size() && get<0>(pq[x].top()) <= tag[x]) {
				auto cur = pq[x].top();
				pq[x].pop();
				int p = get<1>(cur);
				if (need[p] <= 0) continue;
				for (int i = 0; i < p_cnt[p]; i++) {
					int q = id2pos[p][i];
					need[p] -= tag[q] - id2tag[p][i];
				}
				if (need[p] <= 0) ans.push_back(p);
				else {
					for (int i = 0; i < p_cnt[p]; i++) {
						int q = id2pos[p][i];
						pq[q].emplace((need[p] + p_cnt[p] - 1) / p_cnt[p] + tag[q], p);
						id2tag[p][i] = tag[q];
					}
				}
			}
			sort(ans.begin(), ans.end());
			cout << ans.size();
			for (int xx : ans) cout << ' ' << xx;
			cout << '\n';
			last = int(ans.size());
		}
		//cerr << "CURRENT: ";
		//for (int i = 1; i <= 3; i++) cerr << need[i] << ' ';
		//cerr << '\n';
	}
}
