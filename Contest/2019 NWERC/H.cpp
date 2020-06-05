#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <utility>
#include <math.h>
using namespace std;

#define F first
#define S second
typedef long long int ll;

constexpr int kN = int(1E5 + 10), kInf = int(1E9 + 10);

struct BIT {
	int val[kN];
	void init() {for (int i = 1; i < kN; i++) val[i] = kInf;}
	void add(int pos, int x) {
		for (; pos < kN; pos += pos & -pos) val[pos] = min(val[pos], x);
		return ;
	}
	int ask(int pos) {
		int ans = kInf;
		for (; pos; pos ^= pos & -pos) ans = min(ans, val[pos]);
		return ans;
	}
};

BIT bit;
ll h[kN];
int n;
pair<int, int> a[kN];

double ask(int l, int r, int G) {
	double lhs, rhs;
	if (l == 1) rhs = l;
	else if (G == (h[l] - h[l - 1])) rhs = l - 1;
	else rhs = double(G * r - h[r] - (h[l] - h[l - 1]) * l + h[l]) / (G - (h[l] - h[l - 1]));
	if (r == n) lhs = r;
	else if (G == (h[r + 1] - h[r])) lhs = r + 1;
	else lhs = double(G * l - h[l] - (h[r + 1] - h[r]) * r + h[r]) / (G - (h[r + 1] - h[r]));
	rhs = max(rhs, double(l - 1));
	lhs = min(lhs, double(r + 1));
	return max({r - rhs, lhs - l, double(r - l)});
}

int main() {
	int k, tmp, G;
	double ans, g;
	scanf("%d%d", &n, &k);
	n++;
	for (int i = 1; i <= n; i++) scanf("%lld", &h[i]);
	while (k--) {
		scanf("%lf", &g);
		G = int(round(g * 10));
		for (int i = 1; i <= n; i++) a[i] = {h[i] - i * G, i};
		sort(a + 1, a + n + 1);
		bit.init();
		ans = -kInf;
		for (int i = 1; i <= n; i++) {
			tmp = bit.ask(a[i].S);
			if (tmp != kInf) ans = max(ans, ask(tmp, a[i].S, G));
			bit.add(a[i].S, a[i].S);
		}
		if (ans < 0) printf("-1\n");
		else printf("%.20lf\n", ans);
	}
}
