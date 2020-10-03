#include <bits/stdc++.h>
using namespace std;

constexpr uint64_t kMx = uint64_t(UINT_MAX) + 1;

int lg(uint64_t x) {
	return 63 - __builtin_clzll(x);
}

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	int t; cin >> t;
	int cases = 0;
	while (t--) {
		int n; cin >> n;
		vector<pair<uint64_t, uint64_t>> segs, segsr;
		for (int i = 0; i < n; i++) {
			uint64_t x = 0;
			for (int j = 0; j < 4; j++) {
				if (j) cin.ignore(1, '.');
				uint64_t tmp; cin >> tmp;
				x = x << 8 | tmp;
			}
			cin.ignore(1, '/');
			int mask; cin >> mask;
			mask = 32 - mask;
			x &= ~((1ULL << mask) - 1);
			segs.emplace_back(x, x + (1ULL << mask));
		}
		sort(segs.begin(), segs.end());
		uint64_t last = 0;
		for (auto [l, r] : segs) {
			if (last < l) {
				segsr.emplace_back(last, l);
			}
			last = max(last, r);
		}
		if (last != kMx) segsr.emplace_back(last, kMx);
		vector<string> ans;
		auto print = [&](uint64_t l, uint64_t r) {
			while (l != r) {
				int diff_pos = lg(l ^ r);
				if ((l & ((1ULL << (diff_pos + 1)) - 1)) == 0) break;
				auto low = l & -l;
				int mask = lg(low);
				string res;
				for (int j = 0; j < 4; j++) {
					if (j) res += ".";
					res += to_string(l >> (8 * (3 - j)) & 255);
				}
				l += 1ULL << mask;
				mask = 32 - mask;
				res += "/" + to_string(mask);
				ans.push_back(res);
			}
			for (; l < r; l += (1ULL << lg(r - l))) {
				int mask = lg(r - l);
				string res;
				for (int j = 0; j < 4; j++) {
					if (j) res += ".";
					res += to_string(l >> (8 * (3 - j)) & 255);
				}
				mask = 32 - mask;
				res += "/" + to_string(mask);
				ans.push_back(res);
			}
		};
		for (auto [l, r] : segsr) {
			print(l, r);
		}
		cout << "Case #" << ++cases << ":\n";
		cout << ans.size() << '\n';
		for (auto s : ans) cout << s << '\n';
	}
} 
