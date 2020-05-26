#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;

constexpr uint64_t kMod = (1ULL << 61) - 1, kA = 11037;
constexpr int kB = 64;

constexpr uint64_t ModMul(uint64_t a, uint64_t b) {
	uint64_t l1 = uint32_t(a), h1 = a >> 32;
	uint64_t l2 = uint32_t(b), h2 = b >> 32;
	uint64_t l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
	uint64_t ret = (l & kMod) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
	ret = (ret & kMod) + (ret >> 61);
	ret = (ret & kMod) + (ret >> 61);
	return ret - 1;
}

constexpr uint64_t Pow(uint64_t x, uint64_t e) {
	if (!e) return 1;
	auto t = Pow(ModMul(x, x), e >> 1);
	return (e & 1) ? ModMul(t, x) : t;
}

constexpr uint64_t kInvA = Pow(kA, kMod - 2);

using Gp = gp_hash_table<uint64_t, int, hash<uint64_t>, equal_to<uint64_t>, direct_mask_range_hashing<uint64_t>, linear_probe_fn<>, hash_standard_resize_policy<hash_exponential_size_policy<>, hash_load_check_resize_trigger<true>, true>>;

int main() {
	int n, m; cin >> n >> m;
	string s; cin >> s;
	//string s;
	//s.resize(n);
	//for (int i = 0; i < n; i++) s[i] = rand() % 26 + 'a';
	vector<uint64_t> a_pow(n + 1);
	a_pow[0] = 1;
	for (int i = 1; i <= n; i++) {
		a_pow[i] = ModMul(a_pow[i - 1], kA);
	}
	vector<pair<uint64_t, int>> ans_vec;
	for (int i = 1; i < min(n + 1, kB); i++) {
		uint64_t h = 0;
		for (int j = 0; j < i; j++) h = (ModMul(h, kA) + s[j]) % kMod;
		Gp ans, last;
		//ans.resize(n);
		//ans.set_loads({0.25, 0.5});
		//last.resize(n);
		//last.set_loads({0.25, 0.5});
		++ans[h];
		last[h] = i - 1;
		for (int j = i; j < n; j++) {
			h = (h - ModMul(a_pow[i - 1], s[j - i]) + kMod) % kMod;
			h = (ModMul(h, kA) + s[j]) % kMod;
			//cerr << j - i + 1 << ' ' << j << ' ' << h << '\n';
			auto it = last.find(h);
			if (it == last.end() || it->second + i <= j) {
				++ans[h];
				last[h] = j;
			}
		}
		for (auto p : ans) {
			ans_vec.emplace_back(p.first, p.second);
		}
	}
	sort(ans_vec.begin(), ans_vec.end());
	while (m--) {
		string t; cin >> t;	
		int i = int(t.size());
		uint64_t qh = 0;
		for (int j = 0; j < i; j++) qh = (ModMul(qh, kA) + t[j]) % kMod;
		if (i < kB) {
			auto it = lower_bound(ans_vec.begin(), ans_vec.end(), make_pair(qh, 0));
			if (it != ans_vec.end() && it->first == qh) {
				cout << it->second << '\n';
			} else {
				cout << "0\n";
			}
		} else {
			int tmp_ans = 0, last = INT_MIN;
			uint64_t h = 0;
			for (int j = 0; j < i; j++) h = (ModMul(h, kA) + s[j]) % kMod;
			if (h == qh) {
				++tmp_ans;
				last = i - 1;
			}
			for (int j = i; j < n; j++) {
				h = (h - ModMul(a_pow[i - 1], s[j - i]) + kMod) % kMod;
				h = (ModMul(h, kA) + s[j]) % kMod;
				if (h == qh) {
					if (last + i <= j) {
						++tmp_ans;
						last = j;
					}
				}
			}
			cout << tmp_ans << '\n';
		}
	}
} 
