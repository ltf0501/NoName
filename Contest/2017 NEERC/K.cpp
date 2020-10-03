#include <stdio.h>
#include <assert.h>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
#define F first
#define S second
#define PB push_back

typedef unsigned long long int ull;
typedef __int128 ll;

ull b[70];
pair<ull, int> A[1 << 23], B[1 << 24], tb[70];
bool used[70];
ll kLim;

ll Pow(ll x, ll y) {
	ll ans = 1;
	while (y) {
		if (y & 1) ans = ans * x ;
		x = x * x;
		y >>= 1;
	}
	return ans;
}

ull Find(ull x, ull y) {
	ll kMod = kLim;
	while (!(x & 1)) x >>= 1, y >>= 1, kMod >>= 1;
	return (y * Pow(x, (kMod >> 1) - 1)) & (kMod - 1);
}

int main() {
	int n, mid, asz = 1, bsz = 1, idx = 0;
	ull s, lim, x;
	ll now, diff;
	bool f;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%llu", &b[i]);
	scanf("%llu", &s);
	kLim = 1;
	kLim <<= 64;
	if (n > 47) {
		now = 1;
		now <<= n;
		now--;
		lim = (kLim - 1) / now;
		for (int i = 0; i < n; i++) {
			diff = b[i] & -b[i];
			for (ll j = diff; j <= lim; j += diff << 1) {	
				for (ll tx = Find(b[i], j); tx <= kLim; tx += kLim / diff) {
					x = tx;
					assert(b[i] * x == j);
					for (int k = 0; k < n; k++) tb[k] = {b[k] * x, k};
					sort(tb, tb + n);
					now = 0;
					f = true;
					for (int k = 0; k < n; k++) {
						if (tb[k].F <= now) {
							f = false;
							break;
						}
						else now += tb[k].F;
					}
					if (kLim <= now) f = false;
					if (f) {
						s *= x;
						for (int k = n - 1; k >= 0; k--) {
							if (s >= tb[k].F) {
								s -= tb[k].F;
								used[tb[k].S] = true;
							}
						}
						for (int k = 0; k < n; k++) printf("%d", used[k] ? 1 : 0);
						printf("\n");
						return 0;
					}
				}
			}
		}
	}
	else {
		mid = n / 2;
		A[0] = B[0] = {0, 0};
		for (int i = 0; i < mid; i++) {
			for (int j = 0; j < asz; j++) A[j | asz] = {A[j].F + b[i], A[j].S | (1 << i)};
			asz <<= 1;
		}
		for (int i = mid; i < n; i++) {
			for (int j = 0; j < bsz; j++) B[j | bsz] = {B[j].F + b[i], B[j].S | (1 << (i - mid))};
			bsz <<= 1;
		}
		for (int i = 0; i < asz; i++) A[i].F = s - A[i].F;
		sort(A, A + asz);
		sort(B, B + bsz);
		for (int i = 0; i < asz; i++) {
			while (B[idx].F < A[i].F) idx++;
			if (B[idx].F == A[i].F) {
				for (int j = 0; j < mid; j++) printf("%d", (A[i].S & (1 << j)) ? 1 : 0);
				for (int j = mid; j < n; j++) printf("%d", (B[idx].S & (1 << (j - mid))) ? 1 : 0);
				printf("\n");
				return 0;
			}
		}
	}
} 
