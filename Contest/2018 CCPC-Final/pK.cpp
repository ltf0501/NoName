#include <bits/stdc++.h>
using namespace std;
const int r = (1 << 30) + 3;

int64_t MulMod(int64_t x, int64_t y, int64_t m) {
	return x * y % m;
//	if (double(x) * double(y) < 1E18) return x * y % m;
//	auto t = MulMod((x + x) % m, y >> 1, m);
//	if (y & 1) return (t + x) % m;
//	else return t;
}

int64_t PowMod(int64_t x, int64_t e, int64_t m) {
	if (!e) return 1;
	auto t = PowMod(MulMod(x, x, m), e >> 1, m);
	if (e & 1) return MulMod(t, x, m);
	return t;
}

template <typename T>
tuple<T, T, T> ExtGcd(T a, T b) {
	if(!b) return make_tuple(a, 1, 0);
	T d, x, y;
	tie(d, x, y) = ExtGcd(b, a % b);
	return make_tuple(d, y, x - (a / b) * y);
}
int64_t InvMod(int64_t a, int64_t n) {
	int64_t res = get<1>(ExtGcd(a, n));
	res %= n;
	if(res < 0) res += n;
	return res;
}
int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	int t; cin >> t;
	for (int cases = 1; cases <= t; cases++) {
		int64_t n, c; cin >> n >> c;
		int64_t p = sqrt(n + 0.5);
		while(n % p) p--;
		int64_t q = n / p;

		int64_t a = PowMod(c % p, InvMod(r, p - 1), p);
		int64_t b = PowMod(c % q, InvMod(r, q - 1), q);
		int64_t k = (b - a) * InvMod(p, q) % q;
		int64_t ans = (k * p + a) % n;
		if(ans < 0) ans += n;	
		cout << "Case " << cases << ": " << ans << '\n';
	}
	return 0;
}
