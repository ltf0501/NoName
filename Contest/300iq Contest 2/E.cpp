#pragma GCC optimize("O3")
#include <stdio.h>
#include <bitset>
using namespace std;
typedef long long int ll;
constexpr int kN = int(2E5 + 10), kC = 128, kInf = int(1E9 + 10);

struct Base {
	bitset<kC> b[kC], ppl[kC];
	int val[kC];
	ll tot;
	Base(){
		tot = 0;
		for (int i = 0; i < kC; i++) b[i].reset(), val[i] = 0;
		for (int i = 0; i < kC; i++) ppl[i].reset();
	}
	void insert(bitset<kC> x, int v) {
		int cand, top = v;
		bitset<kC> nppl;
		nppl.reset();
		for (int i = 0; i < kC; i++) if (x[i]) {
			if (b[i][i]) {
				x ^= b[i];
				nppl ^= ppl[i];
			}
			else {
				for (int j = i + 1; j < kC; j++) if (b[j][j] & x[j]) {
					x ^= b[j];
					nppl ^= ppl[j];
				}
				nppl[i] = true;
				ppl[i] = nppl;
				for (int j = 0; j < i; j++) if (b[j][i]) {
					b[j] ^= x;
					ppl[j] ^= ppl[i];
				}
				b[i] = x;
				tot += v; 
				val[i] = v;
				return ;
			}
		}
		for (int i = 0; i < kC; i++) if (nppl[i] && val[i] < top) {
			top = val[i];
			cand = i;
		}
		if(top != v) {
			val[cand] = v;
			tot += v - top;
			for (int i = 0; i < kC; i++) if (ppl[i][cand]) {
				ppl[i][cand] = false;
				ppl[i] ^= nppl;
			}
		}
		return ;
	}
};

int u[kN], v[kN], w[kN];
ll a[kN], p2[60];
Base bs;

bitset<kC> make(int x, int y, ll val) {
	bitset<kC> ans;
	ans.reset();
	x--;
	y--;
	ans[x] = ans[y] = true;
	for (int i = 0; i < 60; i++) if (val & p2[i]) ans[i + 64] = true;
	return ans;
}

int main() {
	int n, q, x;
	bitset<kC> b;
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= q; i++) scanf("%d%d%lld%d", &u[i], &v[i], &a[i], &w[i]);
	for (int i = 0; i < 60; i++) p2[i] = (1ll << i);
	for (int i = 1; i <= q; i++) {
		b = make(u[i], v[i], a[i]);
		x = w[i];
		bs.insert(b, x);
		printf("%lld\n", bs.tot);
	} 
}
