#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
using namespace std;
#define PB push_back
#define F first
#define S second
typedef long long int ll;
constexpr int kN = int(3E5 + 10);
constexpr ll kInf = ll(2E18 + 10);
struct BIT {
	ll bit[kN];
	void init(int n) {
		for(int i = 1; i <= n + 5; i++) bit[i] = 0;
	}
	void add(int x, ll d) {
		for(int i = x; i < kN; i += (i & -i)) bit[i] += d;
	}
	ll ask(int n, int l, int r, int x) {
		ll res = 0;
		x++;
		for(int i = x; i; i -= (i & -i)) res += bit[i];
		return res;
	}
	void fix(int n, int l, int r, int L, int R, ll x) {
		L++, R++;
		add(L, x), add(R + 1, -x);
	}
};
long long int p[kN], d[kN], l[kN], r[kN], pos[kN];
BIT sg;
void solve (int n) {
	int m, sz, tmp, vp = 0;
	ll temp;
	ll last = 1, nl, nr;
	vector<int> ans;
	vector<pair<ll, ll>> x;
	vector<pair<ll, ll>> dl;
	vector<pair<ll, ll>> work;
	map<pair<ll, ll>, int> s;
	for (int i = 1; i <= n; i++) scanf("%lld%lld", &d[i], &p[i]);
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) scanf("%lld%lld", &l[i], &r[i]);
	for (int i = 1; i <= n; i++) dl.PB({d[i], i});
	for (int i = 1; i <= n; i++) x.PB({d[i], 0});
	for (int i = 1; i <= m; i++) x.PB({l[i], 1});
	for (int i = 1; i <= m; i++) x.PB({r[i], 2});
	for (int i = 1; i <= n; i++) work.PB({p[i] + 1, i});
	sort(dl.begin(), dl.end());
	sort(x.begin(), x.end());
	sort(work.begin(), work.end());
	sz = int(x.size());
	sg.init(sz);
	for (int i = 0; i < sz; i++) {
		if (x[i].S == 1) {
			if (x[i].F > last) {
				s.insert({{last, x[i].F - 1}, i});
				sg.fix(0, 0, sz, i, sz, x[i].F - last);
			}
		}
		else if (x[i].S == 2) last = x[i].F + 1;
		else if (x[i].S == 0) {
			s.insert({{last, x[i].F}, i});
			sg.fix(0, 0, sz, i, sz, x[i].F - last + 1);
			pos[dl[vp].S] = i;
			last = x[i].F + 1;
			vp++;
		}
		else assert(0);
	}
	for (int i = 0; i < n; i++) {
		if (sg.ask(0, 0, sz, pos[work[i].S]) >= work[i].F) {
			ans.PB(work[i].S);
			temp = kInf;
			while (work[i].F > 0) {
				assert(work[i].F < temp);
				temp = work[i].F;
				if(s.empty()) {
					puts("SDADAS");
					return;
				}
				auto u = s.lower_bound({d[work[i].S] + 1, 0});
				if(u == s.begin()) {
					puts("ASFDADASD");
					return;
				}
				u--;
				tmp = u->S;
				nl = (u->F).F;
				nr = (u->F).S;
				if (nr <= d[work[i].S]) {
					if (nr - nl + 1 >= work[i].F) {
						s.erase(u);
						nr -= work[i].F;
						sg.fix(0, 0, sz, tmp, sz, -work[i].F);
						if (nr >= nl) s.insert({{nl, nr}, tmp});
						work[i].F = 0;
					}
					else {
						s.erase(u);
						sg.fix(0, 0, sz, tmp, sz, -(nr - nl + 1));
						work[i].F -= (nr - nl + 1);
					}
				}
				else {
					assert(0);
				}
			}
		}
	}
	sz = int(ans.size());
	printf("%d\n", sz);
	sort(ans.begin(), ans.end());
	if (!ans.empty()) printf("%d", ans[0]);
	for (int i = 1; i < sz; i++) printf(" %d", ans[i]);
	printf("\n");
	return ;
}
int main() {
#ifdef ONLINE_JUDGE
	freopen("intelligent.in", "r", stdin);
	freopen("intelligent.out", "w", stdout);
#endif
	int n;
	while (true) {
		scanf("%d", &n);
		if (n == 0)return 0;
		else solve(n);
	}
}
