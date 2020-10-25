#include <bits/stdc++.h>
using namespace std;
const int kN = 1e5 + 10;

static inline char GetRawChar() {
	static char buf[1 << 16], *p = buf, *end = buf;
	if (p == end) {
		if ((end = buf + fread(buf, 1, 1 << 16, stdin)) == buf) return '\0';
		p = buf;
	}
	return *p++;
}

static inline int GetInt() {
	int n = 0;
	char c;
	while ((c = GetRawChar()) && (unsigned)(c - '0') <= 10U) n = n * 10 + (c - '0');
	return n;
}

int sz[kN], p[kN];
int Find(int x) {return p[x] == x ? x : p[x] = Find(p[x]);}
void Union(int x, int y) {
	x = Find(x), y = Find(y);
	if(x == y) return;
	if(sz[x] < sz[y]) swap(x, y);
	sz[x] += sz[y], p[y] = x;
}

int main() {
	int T = GetInt();
	while(T--) {
		int n = GetInt();
		vector<int> a(n + 1), b(n + 1);
		vector<int> v;
		v.reserve(n + n);
		auto GetID = [&](int x) {
			return int(lower_bound(v.begin(), v.end(), x) - v.begin()) + 1;
		};
		for(int i = 1; i <= n; i++) {
			a[i] = GetInt();
			b[i] = GetInt();
			v.push_back(a[i]), v.push_back(b[i]);
		}
		sort(v.begin(), v.end());
		v.resize(unique(v.begin(), v.end()) - v.begin());
		for(int i = 1; i <= n; i++) a[i] = GetID(a[i]);
		for(int i = 1; i <= n; i++) b[i] = GetID(b[i]);

		for(int i = 1; i <= n; i++) p[i] = i, sz[i] = 1;
		for(int i = 1; i <= n; i++) Union(a[i], b[i]);

		int mx = 0;
		for(int i = 1; i <= n; i++) {
			if(p[i] == i) mx = max(mx, sz[i]);
		}
		printf("%d\n", mx); 
	}
	return 0;
} 
