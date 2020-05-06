#include <bits/stdc++.h>
using namespace std;

int64_t ans_arr[2][100010];
bool vis[100010];

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	int xx, yy; cin >> xx >> yy;
	int n; cin >> n;
	vector<int> x(n), y(n);
	vector<pair<int, int>> events;
	unordered_map<int, vector<int>> mp;
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> y[i];
		events.emplace_back(y[i], x[i]);
	}
	{
		memset(vis, 0, sizeof(vis));
		sort(events.begin(), events.end());
		int p = 0, cnt = 0;
		for (int i = 1; i < yy; i++) {
			while (p < int(events.size()) && events[p].first < i) {
				if (!vis[events[p].second]) {
					vis[events[p].second] = true;
					++cnt;
				}
				++p;
			}
			ans_arr[0][i] = ans_arr[0][i - 1] + cnt;
		}
	}
	for (auto &p : events) p.first = yy - p.first - 1;
	{
		memset(vis, 0, sizeof(vis));
		sort(events.begin(), events.end());
		int p = 0, cnt = 0;
		for (int i = 1; i < yy; i++) {
			while (p < int(events.size()) && events[p].first < i) {
				if (!vis[events[p].second]) {
					vis[events[p].second] = true;
					++cnt;
				}
				++p;
			}
			ans_arr[1][i] = ans_arr[1][i - 1] + cnt;
		}
	}
	int64_t ans = INT64_MAX;
	for (int i = 0; i < yy; i++) ans = min(ans, ans_arr[0][i] + ans_arr[1][yy - i - 1]);
	ans = xx - 1 + ans * 2;
	cout << ans << '\n';
} 
