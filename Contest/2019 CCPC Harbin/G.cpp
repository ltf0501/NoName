#pragma GCC optimize("O3")
#include <stdio.h>
#include <bitset>
using namespace std;
constexpr int kC = 64;
typedef long long int ll;
struct F3 {
	bitset<kC> b0, b1, b2;
	F3() {
		b1.reset();
		b2.reset();
		b0 = ~b1;
	}
	F3(ll x) {
		b1 = bitset<kC>(x);
		b2.reset();
		b0 = ~b1;
	}
	void operator += (const F3& a) {
		bitset<kC> t1 = b1, t2 = b2;
		b1 = (b0 & a.b1) | (t1 & a.b0) | (t2 & a.b2);
		b2 = (b0 & a.b2) | (t1 & a.b1) | (t2 & a.b0);
		b0 = ~(b1 | b2);
	}
	void operator -= (const F3& a) {
		bitset<kC> t1 = b1, t2 = b2;
		b1 = (b0 & a.b2) | (t1 & a.b0) | (t2 & a.b1);
		b2 = (b0 & a.b1) | (t1 & a.b2) | (t2 & a.b0);
		b0 = ~(b1 | b2);
	}
};
bool samebit(F3& a, F3& b, int pos) {
	return (a.b1[pos] && b.b1[pos]) || (a.b2[pos] && b.b2[pos]);
}

F3 b[kC], ppl[kC];
ll val[kC], tot;
ll insert(F3 x, ll y) {
	F3 nppl;
	ll top = y;
	int cand;
	for (int i = 0; i < kC; i++) if (!x.b0[i]) {
		if (!b[i].b0[i]) {
			if (samebit(x, b[i], i)) {
				nppl -= ppl[i];
				x -= b[i];
			}
			else {
				nppl += ppl[i];
				x += b[i];
			}
		}
		else {
			ppl[i] = nppl;
			ppl[i].b1[i] = true;
			ppl[i].b0[i] = false;
			b[i] = x;
			val[i] = y;
			tot += y;
			for (int j = i + 1; j < kC; j++) if (!(b[i].b0[j] || b[j].b0[j])) {
				if (samebit(b[i], b[j], j)) {
					b[i] -= b[j];
					ppl[i] -= ppl[j];
				}
				else {
					b[i] += b[j];
					ppl[i] += ppl[j];
				}
			}
			for (int j = 0; j < i; j++) if (!b[j].b0[i]) {
				if (samebit(b[i], b[j], i)) {
					b[j] -= b[i];
					ppl[j] -= ppl[i];
				}
				else {
					b[j] += b[i];
					ppl[j] += ppl[i];
				}
			}
			return tot;
		}
	}
	for (int i = 0; i < kC; i++) if ((!nppl.b0[i]) && top > val[i]) {
		cand = i;
		top = val[i];
	}
	if (top < y) {
		val[cand] = y;
		tot += y - top;
		for (int i = 0; i < kC; i++) if (!ppl[i].b0[cand]) {
			if (samebit(ppl[i], nppl, cand)) {
				ppl[i] -= nppl;
				ppl[i].b1[cand] = true;
				ppl[i].b0[cand] = false;
			}
			else {
				ppl[i] += nppl;
				ppl[i].b2[cand] = true;
				ppl[i].b0[cand] = false;
			}
		}
	}
	return tot;
}

int main() {
	int n;
	ll x, y, lst = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld%lld", &x, &y);
		x ^= lst, y ^= lst;
		printf("%lld\n", lst = insert(x, y));
	}
} 
