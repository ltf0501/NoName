#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
 
tuple<double, int, int, int> p[100010];
int n, s;
 
int64_t Intersect(int a, int b) {
	int64_t up = max(get<1>(p[a]), get<1>(p[b])), down = min(get<1>(p[a]), get<1>(p[b])) + s;
	int64_t left = max(get<2>(p[a]), get<2>(p[b])), right = min(get<2>(p[a]), get<2>(p[b])) + s;

	if(up > down || left > right) return 0;
	return (down - up) * (right - left);
}
 
bool IoU(int a, int b, int thres_i) {
	auto i_area = Intersect(a, b);
	auto u_area = 2LL * s * s - i_area;
	return i_area * 1'000 > u_area * thres_i;
}
 
int main() {
	int t; cin >> t;
	for (int cases = 1; cases <= t; cases++) {
		cin >> n >> s;
		int blk = max(1, s / 11);
		double thres; cin >> thres;
		int thres_i = int(round(thres * 1'000));
		for (int i = 0; i < n; i++) {
			cin >> get<1>(p[i]) >> get<2>(p[i]) >> get<0>(p[i]);
			get<0>(p[i]) *= -1;
			get<3>(p[i]) = i;
		}
		vector<int> ans;
		//unordered_map<int64_t, int> mp;
		__gnu_pbds::cc_hash_table<int64_t, int> mp;
		sort(p, p + n);
		for (int i = 0; i < n; i++) {
			int bx = get<1>(p[i]) / blk;
			int by = get<2>(p[i]) / blk;
			bool del = false;
			[&]() {
				int r = 7;
				for (int j = bx - r; j <= bx + r; j++) {
					for (int k = by - r; k <= by + r; k++) {
					    //if (abs(j - bx) >= 5 && abs(k - by) >= 5) continue;
						int64_t id = j * (1LL << 32) + k;
						if (mp.find(id) != mp.end()) {
							if (IoU(mp[id], i, thres_i)) {
								del = true;
								return;
							}
						}
					}
				}
				int64_t id = bx * (1LL << 32) + by;
				mp[id] = i;
				ans.push_back(get<3>(p[i]));
			}();
		}
		cout << "Case #" << cases << ": " << ans.size() << '\n';
		sort(ans.begin(), ans.end());
		for (int i = 0; i < int(ans.size()); i++) cout << (i ? " " : "") << ans[i] + 1;
		cout << '\n';
	}
}
