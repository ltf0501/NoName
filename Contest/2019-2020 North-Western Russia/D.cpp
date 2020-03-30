bool debug = false;
#include <stdio.h>
#include <vector>
using namespace std;
typedef long long int ll;
#define PB push_back
constexpr int kN = int(1E5 + 10), kMod = 998244353;

ll Pow(ll a, ll b) {
	ll ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % kMod;
		a = a * a % kMod;
		b >>= 1;
	}
	return ans;
}
ll Rev(ll n) {return Pow(n, kMod - 2);}

void Ntt(vector<ll> &v, bool on, int sz) {
	ll wn, u, t, w, inv;
	for (int i = 1, j = sz >> 1, k; i < (sz - 1); i++) {
		if (i < j) swap(v[i], v[j]);
		k = sz >> 1;
		while (j & k) {
			j ^= k;
			k >>= 1;
		}
		j |= k;
	}
	for (int i = 2; i <= sz; i <<= 1) {
		wn = on ? Pow(3, (kMod - 1) / i) : Pow(3, kMod - 1 - (kMod - 1) / i);
		for (int j = 0; j < sz; j += i) {
			w = 1;
			for (int k = j; k < j + (i >> 1); k++) {
				u = v[k];
				t = w * v[k + (i >> 1)] % kMod;
				v[k] = (u + t) % kMod;
				v[k + (i >> 1)] = (u - t + kMod) % kMod;
				w = w * wn % kMod;
			}
		}
	}
	if (on) {
		inv = Rev(sz);
		for (int i = 0; i < sz; i++) v[i] = v[i] * inv % kMod;
	}
	return ;
}

ll p[kN], mu[kN], k, f[kN], f2[kN], F[kN], G[kN];

void pre() {
	vector<int> v;
	for (int i = 2; i < kN; i++) mu[i] = -3;
	mu[1] = 1;
	for (int i = 2; i < kN; i++) {
		if (mu[i] == -3) {
			mu[i] = kMod - 1;
			v.PB(i);
		}
		for (int j : v) {
			if (i * j >= kN) break;
			if (i % j == 0) {
				mu[i * j] = 0;
				break;
			}
			mu[i * j] = kMod - mu[i];
		}
	}
	return ;
}

int main() {
	int n, tot = 1;
	ll ans = 0;
	vector<ll> v;
	scanf("%d%lld", &n, &k);
	pre();
	while (tot <= n) tot <<= 1;
	tot <<= 1;
	v.resize(tot);
	f[0] = 1;
	v[1] = f[1] = k;
	for (int i = 2; i <= n; i++) v[i] = f[i] = f[i - 2] * k % kMod;
	v[0] = 0;
	Ntt(v, false, tot);
	for (int i = 0; i < tot; i++) v[i] = v[i] * v[i] % kMod;
	Ntt(v, true, tot);
	for (int i = 1; i <= n; i++) f2[i] = (v[i] + f[i]) % kMod;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n / i; j++) G[i * j] += i * f2[j] % kMod * mu[i] % kMod; 
	for (int i = 1; i <= n; i++) G[i] %= kMod;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n / i; j++) F[i * j] += G[i];
	for (int i = 1; i <= n; i++) F[i] %= kMod;
	if (debug) {
		for (int i = 1; i <= n; i++) printf("f[%d] = %lld\n", i, f[i]);
		for (int i = 1; i <= n; i++) printf("f2[%d] = %lld\n", i, f2[i]);
		for (int i = 1; i <= n; i++) printf("G[%d] = %lld\n", i, G[i]);
		for (int i = 1; i <= n; i++) printf("F[%d] = %lld\n", i, F[i]);
	}
	for (int i = 1; i <= n; i++) ans += F[i];
	printf("%lld\n", ans % kMod); 
} 
