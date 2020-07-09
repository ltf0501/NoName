#pragma GCC optimize("O3")
#pragma GCC target("avx")
#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 100001;

bool not_prime[kN];
int min_div[kN], prime_id[kN];
vector<int> primes;

int Solve(vector<pair<int, int>> a, vector<pair<int, int>> b) {
	int n = int(a.size());
	sort(b.begin(), b.end());
	vector<bitset<kN>> bs;
	for (int p : primes) {
		if (p * p > n) break;
		bs.emplace_back();
		for (int i = 0; i < n; i++) {
			bs.back()[i] = b[i].second % p != 0;
		}
	}
	int ans = 0;
	for (int i = 0; i < n; i++) {
		int k = i + 1;
		bitset<kN> cur_bs;
		cur_bs.flip();
		if (k != 1) {
			while (not_prime[k]) {
				if (1LL * min_div[k] * min_div[k] > n) break;
				auto d = min_div[k];
				cur_bs &= bs[prime_id[d]];
				do {
					k /= d;
				} while (k % d == 0);
			}
			if (k != 1 && 1LL * k * k <= n) {
				cur_bs &= bs[prime_id[k]];
				k = 1;
			}
		}	
		size_t p = cur_bs._Find_first();
		if (k != 1) {
			while (p < b.size() && b[p].second % k == 0) {
				p = cur_bs._Find_next(p);
			}
		}
		if (p < b.size()) {
			ans = max(ans, a[i].first - b[p].first);
		}
	}
	return ans;
}

int main() {
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	int n; cin >> n;
	for (int i = 2; i <= n; i++) {
		if (not_prime[i]) continue;
		primes.push_back(i);
		prime_id[i] = int(primes.size()) - 1;
		for (int j = i + i; j <= n; j += i) {
			not_prime[j] = true;
			if (!min_div[j] || min_div[j] > i) min_div[j] = i;
		}
	}
	vector<int> a(n + 1), b(n + 1);
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];
	vector<pair<int, int>> aa, bb;
	for (int i = 1; i <= n; i++) {
		aa.clear();
		bb.clear();
		for (int j = i, k = 1; j <= n; j += i, ++k) {
			aa.emplace_back(a[j], k);
			bb.emplace_back(b[j], k);
		}
		cout << max(Solve(aa, bb), Solve(bb, aa)) << ' ';
	}
	cout << '\n';
} 
