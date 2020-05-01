#include <stdio.h>
#include <set>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
constexpr int kN = int(2E5 + 10);
#define PB push_back
typedef long long int ll;

struct seg_tree {
	ll a[kN << 2]; 
	void init(int n, int l, int r) {
		a[n] = 0; 
		if (l < r) {
			int mid = (l + r) >> 1;
			init(n << 1, l, mid);
			init(n << 1 | 1, mid + 1, r);
		}
		return ;
	}
	void add(int n, int l, int r, int L, int R, ll x) {
		if (L <= l && r <= R) a[n] += x;
		else if (L > r || l > R) return ;
		else {
			int mid = (l + r) >> 1;
			add(n << 1, l, mid, L, R, x);
			add(n << 1 | 1, mid + 1, r, L, R, x);
			return ;
		}
	}
	ll ask(int n, int l, int r, int pos) {
		if (l == r) return a[n];
		else {
			int mid = (l + r) >> 1;
			if (pos <= mid) return ask(n << 1, l, mid, pos) + a[n];
			else return ask(n << 1 | 1, mid + 1, r, pos) + a[n];
		}
	}
};

ll a[kN];
set<int> s;
seg_tree seg;

void solve() {
	ll n, d, b = 0, tt; 
	int tmp, xsz;
	vector<ll> x;
	scanf("%lld%lld", &n, &d);
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	s.clear();
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) {
		a[i] -= (i - 1) * d;
		if (a[i] < 0) {
			b -= a[i];
			a[i] = 0;
		}
	}

	a[0] = 0;
	for (int i = 0; i <= n; i++) x.PB(a[i]);
	
	sort(x.begin(), x.end());
	x.resize(unique(x.begin(), x.end()) - x.begin());
	xsz = int(x.size());
	seg.init(1, 0, xsz);
	for (int i = 0; i <= n; i++) a[i] = lower_bound(x.begin(), x.end(), a[i]) - x.begin();
	s.insert(a[0]);
	s.insert(a[1]);
	seg.add(1, 0, xsz, a[0], a[1], 1);
	
	for (int i = 2; i <= n; i++) {
		if (a[0] < a[i]) seg.add(1, 0, xsz, a[0], a[i], 1);
		
		s.insert(a[i]);

		tmp = *(--s.end());
		if (tmp > a[i]) {
			seg.add(1, 0, xsz, max(a[0], a[i] + 1), tmp, -1);
			if (seg.ask(1, 0, xsz, tmp) <= 0) s.erase(tmp);
		}
		b += (x[tmp] - x[a[i]]);
	}

	printf("%lld\n", b);
	return ;
}
int main() {
	int t;
	scanf("%d", &t);
	while (t--) solve();
} 
