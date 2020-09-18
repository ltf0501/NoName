#include <bits/stdc++.h>
using namespace std;
const int kN = 1e5 + 10;
typedef pair<int, int> pii;
#define F first
#define S second

int n, a, b;
int l[kN], r[kN], t[kN];

int p[kN], sz[kN];
int Find(int x) {return p[x] == x ? x : p[x] = Find(p[x]);}
bool Union(int x, int y) {
	x = Find(x), y = Find(y);
	if(x == y) return 0;
	if(sz[x] < sz[y]) swap(x, y);
	sz[x] += sz[y], p[y] = x;
	return 1;
}
int main() {
	scanf("%d%d%d", &n, &a, &b);
	for(int i = 0; i < n; i++) scanf("%d%d%d", &l[i], &r[i], &t[i]);
	for(int i = 0; i < n; i++) p[i] = i, sz[i] = 1;

	queue<pair<pii, int>> q;
	q.emplace(make_pair(a, b), 0);
	while(!q.empty()) {
		auto tmp = q.front(); q.pop();
		int x, y;
		tie(x, y) = tmp.F;
		int d = tmp.S;
		if(t[x] != t[y]) return printf("%d\n", d), 0;

		if(Union(x, y)) {
			q.emplace(make_pair(l[x], l[y]), d + 1);
			q.emplace(make_pair(r[x], r[y]), d + 1);
		}
	}
	puts("indistinguishable");
	return 0;
} 
