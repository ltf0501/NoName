#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 1000010;

int z1[kN * 3], z2[kN * 3];
bool vis[kN];

void ZAlg(string str, int *z) {
	int len = int(str.size());
	int l = 0, r = 0;
	for (int i = 0; i < len; i++) {
		if (i > r) {
			l = r = i;
			while (r < len && str[r] == str[r - l]) ++r;
			z[i] = r - l;
			--r;
		} else {
			if (z[i - l] < r - i + 1) {
				z[i] = z[i - l];
			} else {
				l = i;
				while (r < len && str[r] == str[r - l]) ++r;
				z[i] = r - l;
				--r;
			}
		}
	}
}

template<typename T>
tuple<T, T, T> ExtGcd(T a, T b) {
	// ax + by = d, (d, x, y)
	if(!b) return make_tuple(a, 1, 0);
	T d, x, y;
	tie(d, x, y) = ExtGcd(b, a % b);
	return make_tuple(d, y, x - (a / b) * y);
}

int64_t Crt(vector<pair<int, int>> e) {
	int n = int(e.size());
	int64_t mod = e[0].first, x = e[0].second;
	for(int i = 1; i < n; i++) {
		int64_t g = __gcd(int(mod), e[i].first);

		if((e[i].second - x) % g != 0) return -1;

		int64_t m1 = mod / g, m2 = e[i].first / g, t = (e[i].second - x) / g;
		t %= m2;
		if(t < 0) t += m2;
		auto res = ExtGcd(m1, m2);
		int64_t k = t * get<1>(res) % m2;
		x = (k * mod + x) % (mod / g * e[i].first);
		mod = mod * e[i].first / g;
	}
	x %= mod;
	if(x < 0) x += mod;
	return x;
}
int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	string s, t; cin >> s >> t;
	if(s[0] != t[0] || s.back() != t.back()) return cout << -1 << '\n', 0;
	int n = int(t.size());
	if (n == 2) {
		cout << "0\n";
		exit(0);
	}
	// {m, {a_1, a_2, ..., a_n}}
	vector<pair<int, int>> equations;
	int cycle_cnt = 0, min_sz = INT_MAX;
	for (int i = 1; i < n - 1; i++) {
		vector<int> v;
		int j = i;
		if (!vis[j]) ++cycle_cnt;
		int sz = 0;
		while (!vis[j]) {
			v.push_back(j);
			vis[j] = true;
			j = j * 2 % (n - 1);
			++sz;
		}
		if (sz) min_sz = min(min_sz, sz);
		if (v.size()) {
			string s1, s2;
			for (int k : v) {
				s1.push_back(s[k]);
				s2.push_back(t[k]);
			}
			//cerr << s1 << '\n';
			//cerr << s2 << '\n';
			string tmp = s1 + s2 + s2;
			vector<int> offsets;
			ZAlg(tmp, z1);
			string tmp2 = s1 + s1;
			ZAlg(tmp2, z2);
			int min_rot = int(s1.size());
			for (int k = 1; k < int(s1.size()); k++) {
				//cerr << z2[k] << '\n';
				if (z2[k] >= int(s1.size())) {
					min_rot = min(min_rot, k);
				}
			}
			//cerr << "min_rot = " << min_rot << '\n';
			for (int k = int(s1.size()); k < int(tmp.size()); k++) {
				if (z1[k] >= int(s1.size())) {
					offsets.push_back((int(s2.size()) - k + int(s1.size())) % min_rot);
					break;
				}
			}
			if (offsets.empty()) {
				cout << "-1\n";
				exit(0);
			}
			equations.emplace_back(min_rot, offsets.back());
		}
	}
	//for (auto e : equations) {
	//	cerr << e.first << ": " << e.second << '\n';
	//}
	//cerr << cycle_cnt << ' ' << min_sz << '\n';

	int64_t x = Crt(equations);
	cout << x << '\n';
} 
