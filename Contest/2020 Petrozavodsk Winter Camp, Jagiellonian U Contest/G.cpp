#include <stdio.h>
#include <math.h>
#include <utility>
#include <algorithm>
using namespace std;
#define F first
#define S second

constexpr int kN = int(1E2 + 10), kInf = int(1E9 + 10);

pair<int, int> p[kN], q[kN];
int a[kN], b[kN];

double dis(pair<int, int> l, pair<int, int> r) {
	int x = (l.F - r.F), y = (l.S - r.S);
	return sqrt(x * x + y * y);
}


void solve() {
	int n, tot = 1;
	double now = kInf, tmp;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", &p[i].F, &p[i].S);
	for (int i = 1; i <= n; i++) scanf("%d%d", &q[i].F, &q[i].S);
	for (int i = 1; i <= n; i++) a[i] = i;
	for (int i = 1; i <= n; i++) tot *= i;
	
	while (tot--) {
		tmp = 0;
		for (int i = 1; i <= n; i++) tmp += dis(p[i], q[a[i]]);
		if (tmp < now) {
			now = tmp;
			for (int i = 1; i <= n; i++) b[i] = a[i];
		}
		next_permutation(a + 1, a + n + 1);
	}
	for (int i = 1; i <= n; i++) printf("2\n%d %d\n%d %d\n", p[i].F, p[i].S, q[b[i]].F, q[b[i]].S);
	return ;
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) solve();
}


