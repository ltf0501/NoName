#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>
#include <tuple>
using namespace std;

#define F first
#define S second
#define PB push_back

constexpr int kN = int(1E5 + 10), kInf = int(2E9 + 10);

int x[kN], y[kN], mx[kN], p[kN];
pair<int, int> a[kN], b[kN];

int ABS(int n) {return n >= 0 ? n : -n;}

int dis(int ida, int idb) {
	return ABS(x[ida] - x[idb]) + ABS(y[ida] - y[idb]);
}

int Find(int n) {return p[n] == n ? n : p[n] = Find(p[n]);}

bool Union(int l, int r) {
	l = Find(l), r = Find(r);
	if (l == r) return false;
	p[r] = l;
	return true;
}

int main() {
	int n, ans = kInf;
	vector<tuple<int, int, int>> edges;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", &x[i], &y[i]);
	for (int i = 1; i <= n; i++) a[i] = {x[i] + y[i], i};
	for (int i = 1; i <= n; i++) b[i] = {x[i] - y[i], i};
	sort(a + 1, a + n + 1);
	sort(b + 1, b + n + 1);
	for (int i = 1; i <= n; i++) p[i] = i;
	for (int i = 1; i <= n; i++) {
		edges.PB({dis(i, a[1].S), i, a[1].S});
		edges.PB({dis(i, a[n].S), i, a[n].S});
		edges.PB({dis(i, b[1].S), i, b[1].S});
		edges.PB({dis(i, b[n].S), i, b[n].S});
	}
	sort(edges.begin(), edges.end());
	reverse(edges.begin(), edges.end());
	for (tuple<int, int, int> i : edges) {
		if (Union(get<1>(i), get<2>(i))) n--;
		if (n == 1) {
			printf("%d\n", get<0>(i));
			return 0;
		}
	}
} 
