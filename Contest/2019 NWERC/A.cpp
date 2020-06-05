#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 300010;

int score[kN];
int64_t a[kN], cnt[kN], sum[kN];

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	int n, w; cin >> n >> w;
	cnt[0] = n;
	for (int t = 0; t < w; t++) {
		int k; cin >> k;
		map<int, vector<int>> mp;
		for (int i = 0; i < k; i++) {
			int c; cin >> c;
			--c;
			mp[score[c]].push_back(c);
		}
		for (auto [s, v] : mp) {
			for (int x : v) {
				sum[x] -= 1LL * cnt[score[x] + 1] * (w - t);
			}
			for (int x : v) {
				sum[x] += a[score[x]];
				++score[x];
				sum[x] -= a[score[x]];
			}
		}
		for (auto [s, v] : mp) {
			cnt[s] -= int(v.size());
			cnt[s + 1] += int(v.size());
			a[s] += int64_t(v.size()) * (w - t);
		}
	}
	for (int i = 0; i < n; i++) {
		sum[i] += a[score[i]];
		cout << fixed << setprecision(10) << 1 + double(sum[i]) / w << '\n';
	}
}
