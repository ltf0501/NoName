#pragma GCC optimize("O3")
#pragma GCC tune("avx")
#include <bits/stdc++.h>
using namespace std;
#define PB push_back

constexpr int kN = int(1E5 + 10), kM = int(5E6 + 10), lim = (1 << 30) - 1;

unsigned int x, y, z, w;
int p[kN];
bool b[kN];
int Find(int n) {return p[n] == n ? n : p[n] = Find(p[n]);}

inline unsigned int rng() {
	x ^= x << 11;
	x ^= x >> 4;
	x ^= x << 5;
	x ^= x >> 14;
	w = x ^ y ^ z;
	x = y;
	y = z;
	z = w;
	return z;
}

vector<tuple<unsigned int, unsigned int, unsigned int>> ve[40];

long long int  solve() {
	int n, m, nxt, cnt = 0;
	long long int ans = 0;
	unsigned int l, r, v;
	scanf("%d%d%u%u%u", &n, &m, &x, &y, &z);

	int idx = 1024;
	auto rng61 = [&]() {
		static uint32_t buf[1024];
		auto rng = [&]() {
			x = x ^ (x << 11);
			x = x ^ (x >> 4);
			x = x ^ (x << 5);
			x = x ^ (x >> 14);
			auto w = x ^ y ^ z;
			x = y;
			y = z;
			z = w;
			return z;
		};
		if (idx < 1024) return buf[idx++];
		for (int i = 0; i < 1024; i++) buf[i] = rng();
		idx = 0;
		return buf[idx++];
	};

	for (int i = 1; i <= n; i++) p[i] = i;
	for (int i = 1; i <= n; i++) b[i] = false;
	for (int i = 0; i < 30; i++) ve[i].clear();
	for (int i = 1; i <= m; i++) {
		l = rng61() % n, r = rng61() % n, v = rng61() & lim;
	 	ve[__lg(v)].PB({v, l, r});
	}

	for (int i = 29; i >= 0; i--) {
		sort(ve[i].begin(), ve[i].end(), greater<tuple<int, int, int>>());
		for (tuple<int, int, int> j : ve[i]) {
			l = get<1>(j), r = get<2>(j), v = get<0>(j);
			if (l > r) swap(l, r);
			l++;
			if (!b[l]) {
				b[l] = true;
				ans ^= 1LL * l * v;
				n--;
			}
			while (l <= r) {
				cnt++;
				if (b[l]) l = Find(l);
				if (l <= r) {
					if (!b[l + 1]) {
						p[l++]++;
						b[l] = true;
						ans ^= 1LL * l * v;
						n--;
					}
					else p[l]++;
				}
			}
			if (n == 0) {
				return ans;
			}
		}
	}
	
	return ans;
}


int main() {
	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++) printf("%lld\n", solve());
} 
