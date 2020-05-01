#include <bits/stdc++.h>
using namespace std;
const int kN = 3e3 + 10;
const int kC = 1e6;
typedef pair<int, int> pii;
#define F first
#define S second

struct P {
	int x, y, type;
	bool operator < (const P &r) const {
		return x != r.x ? x > r.x : type < r.type;
	}
};

bool check(int l, int r, int x) {
	if(l <= r) return l <= x && x <= r;
	return x <= r || x >= l;
}
int len(int l, int r) {
	return (r - l + 1 + kC) % kC;
}
int n, sz;
pii a[kN];

int bit[kN];
void add(int x, int d) {
	for(int i = x; i <= sz; i += i & -i) bit[i] += d;
}
int query(int x) {
	int res = 0;
	for(int i = x; i; i -= i & -i) res += bit[i];
	return res;
}
int Cal(vector<P> &p, int s) {
	if(p.empty()) return 0;
	for(auto &t : p) {
		if(t.type == 2) t.x = s - t.x, t.y = (kC - s) - t.y;
	}

	vector<int> v;
	for(auto t : p) v.push_back(t.y);
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
	sz = v.size();
	for(auto &t : p) t.y = lower_bound(v.begin(), v.end(), t.y) - v.begin() + 1;
	sort(p.begin(), p.end());
	
	memset(bit, 0, sizeof(bit));

	for(auto t : p) {
		if(t.type == 1) { // black
			int res = query(t.y);
			int now = 0, tot = 0;
			for(int i = 15; i >= 0; i--) if(now + (1 << i) <= sz) {
				if(tot + bit[now + (1 << i)] <= res) {
					tot += bit[now + (1 << i)];
					now += (1 << i);
				}
			}
			add(1, 1), add(now + 1, -1);
		}
		else { // white
			add(t.y, 1);
		}
	} 
	return query(sz);
}
void Solve() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d%d", &a[i].F, &a[i].S);
	sort(a + 1, a + n + 1, [&](pii x, pii y) {return len(x.F, x.S) < len(y.F, y.S);});

	int ans = 0;

	for(int i = 1; i <= n; i++) {
		int cur = 1;
		vector<P> p;
		for(int j = i + 1; j <= n; j++) if(j != i){
			int mask = 0;
			if(check(a[j].F, a[j].S, a[i].F)) mask |= 1;
			if(check(a[j].F, a[j].S, a[i].S)) mask |= 2;

			if(mask == 3) cur++;
			else if(mask == 1) p.push_back({len(a[i].F, a[j].S), len(a[j].F, (a[i].F - 1 + kC) % kC), 1});
			else if(mask == 2) p.push_back({len(a[j].F, a[i].S), len((a[i].S + 1) % kC, a[j].S), 2});
		}
		cur += Cal(p, len(a[i].F, a[i].S));
		ans = max(ans, cur);
	}
	printf("%d\n", ans);	
}
int main() {
	int T; scanf("%d", &T);
	while(T--) Solve();
	return 0;
}
