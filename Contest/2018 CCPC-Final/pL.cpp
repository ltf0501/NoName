#include <bits/stdc++.h>
using namespace std;

constexpr int kC = 3E8;

bitset<kC + 1> not_prime;

int64_t MulMod(int64_t x, int64_t y, int64_t m) {
	if (double(x) * double(y) < 1E18) return x * y % m;
	auto t = MulMod((x + x) % m, y >> 1, m);
	if (y & 1) return (t + x) % m;
	else return t;
}

int64_t PowMod(int64_t x, int64_t e, int64_t m) {
	if (!e) return 1;
	auto t = PowMod(MulMod(x, x, m), e >> 1, m);
	if (e & 1) return MulMod(t, x, m);
	return t;
}


bool IsPrimeMR(int64_t x) {
	constexpr uint32_t as = 9, a[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
	for (uint32_t i = 0; i < as; i++) {
		if (x == a[i]) return true;
	}
	if (x < a[as - 1]) return false;
	uint64_t t = x - 1;
	int r = 0;
	while ((t & 1) == 0) {
		t >>= 1;
		++r;
	}
	for (uint32_t i = 0; i < as; i++) { 
		bool ok = false;
		int64_t tt = PowMod(a[i], t, x);
		if (tt == 1) continue;
		for (int j = 0; j < r; j++, tt = MulMod(tt, tt, x)) {
			if (tt == x - 1) {
				ok = true;
				break;
			}
		}
		if (!ok) return false;
	}
	return true;
}

bool IsPrimeSqrt(int64_t x) {
	for (int64_t i = 2; i * i <= x; i++) {
		if (x % i == 0) return false;
	}
	return true;
}

#define IsPrime IsPrimeMR

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	vector<int> primes;
	primes.reserve(kC / 20);
	for (int i = 2; i <= kC; i++) {
		if (!not_prime[i]) primes.push_back(i);
		for (int p : primes) {
			if (1LL * i * p > kC) break;
			not_prime[i * p] = true;
			if (i % p == 0) break;
		}
	}
	int t; cin >> t;
	for (int cases = 1; cases <= t; cases++) {
		int64_t n; cin >> n;
		cout << "Case " << cases << ": " ;
		if(n <= 11) {
			cout << "IMPOSSIBLE\n";
			continue;
		}
		if(n & 1) {
			cout << "2 2 2 3 ";
			n -= 9;
			for(int x : primes) {
				if(IsPrime(n - x)) {
					cout << x << ' ' << n - x << '\n';
					break;
				}
			}
		}
		else {
			cout << "2 2 2 2 ";
			n -= 8;
			for(int x : primes) {
				if(IsPrime(n - x)) {
					cout << x << ' ' << n - x << '\n';
					break;
				}
			}
		} 
	}
}
