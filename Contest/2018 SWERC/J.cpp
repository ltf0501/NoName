#include <bits/stdc++.h>
using namespace std;

const int kC = 2e6;
const int kSz = 3e5;
const int kN = 17;
typedef unsigned long long uint64;

int n;	
struct rng {
	uint64 s[2];
	uint64 F() {
		uint64 s0 = s[0];
		uint64 s1 = s[1];
		uint64 result = s0 + s1;
		s1 ^= s0;
		s[0] = ((s0 << 55) | (s0 >> 9)) ^ s1 ^ (s1 << 14);
		s[1] = (s1 << 36) | (s1 >> 28);
		return result & ((1ULL << n) - 1);
	}
	rng(uint64 x) {
		s[0] = x;
		s[1] = x ^ 0x7263d9bd8409f526;
	} 
	rng() {}
};
rng rander[4];
vector<pair<int, int>> v[2];

vector<uint64> x[4]; 

vector<pair<int, int>> Do(int id) {
	vector<vector<int>> mp((1 << kN) + 5);

	for(int i = 0; i < kC; i++) {
		uint64 val = rander[id].F();
		x[id].push_back(val);
		mp[val & ((1 << kN) - 1)].push_back(i);
	}
	
	vector<pair<int, int>> res;

	for(int i = 0;; i++) {
		uint64 val = rander[id ^ 1].F();
		x[id ^ 1].push_back(val);

		auto v = mp[val & ((1 << kN) - 1)];
		for(int t : v) res.emplace_back(t, i);

		if(int(res.size()) > kSz) {
			break;
		}
	}
	return res;
}
int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n;
	for(int i = 0; i < 4; i++) {
		uint64 x; cin >> x;
		rander[i] = rng(x);
	}

	v[0] = Do(0), v[1] = Do(2);
	unordered_map<uint64, pair<int, int>>	mp;
	for(auto p : v[0]) {
		uint64 val = x[0][p.first] ^ x[1][p.second];
		assert(!(val & ((1 << kN) - 1)));
		mp[val] = p;
	}
	for(auto p : v[1]) {
		uint64 val = x[2][p.first] ^ x[3][p.second];

		assert(!(val & ((1 << kN) - 1)));
		if(mp.find(val) != mp.end()) {
			auto q = mp[val];
			cout << q.first + 1 << ' ' << q.second + 1 << ' ' << p.first + 1 << ' ' << p.second + 1 << '\n';
				
			return 0;
		}
	}

	assert(0);
	return 0;
} 
