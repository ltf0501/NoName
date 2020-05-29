#include <stdio.h>
#include <algorithm>
#include <stack>
#include <queue>
#include <utility>
using namespace std;
#define F first
#define S second
typedef long long int ll;
constexpr int kN = int(1E5 + 10);
constexpr ll kInf = ll(1E16 + 10);

struct seg_tree {
	pair<ll, int> val[kN << 2];
	ll flag[kN << 2];
	int ff[kN << 2];
	void init(int n, int l, int r) {
		val[n] = {-kInf, l};
		flag[n] = 0;
		ff[n] = 0;
		if (l < r) {
			int mid = (l + r) >> 1;
			init(n << 1, l, mid);
			init(n << 1 | 1, mid + 1, r);
		}
		return ;
	}
	void addtag(int n, ll x) {
		val[n].F += x;
		flag[n] += x;
		return ;
	}
	void ch(int n, int x) {
		val[n].S = ff[n] = x;
		return ;
	}
	void push(int n) {
		if (flag[n]) {
			addtag(n << 1, flag[n]);
			addtag(n << 1 | 1, flag[n]);
			flag[n] = 0;
		}
		if (ff[n]) {
			ch(n << 1, ff[n]);
			ch(n << 1 | 1, ff[n]);
			ff[n] = 0;
		}
		return ;
	}
	void pull(int n) {
		val[n] = max(val[n << 1], val[n << 1 | 1]);
		return ;
	}
	void add(int n, int l, int r, int L, int R, ll x) {
		if (L <= l && r <= R) addtag(n, x);
		else if (!(l > R || L > r)) {
			int mid = (l + r) >> 1;
			push(n);
			add(n << 1, l, mid, L, R, x);
			add(n << 1 | 1, mid + 1, r, L, R, x);
			pull(n);
		}
		return ;
	}
	void change(int n, int l, int r, int L, int R, int x) {
		if (L <= l && r <= R) ch(n, x);
		else if (!(l > R || L > r)) {
			int mid = (l + r) >> 1;
			push(n);
			change(n << 1, l, mid, L, R, x);
			change(n << 1 | 1, mid + 1, r, L, R, x);
			pull(n);
		}
		return ;
	}
	void set(int n, int l, int r, int pos, ll x) {
		if (l == r) val[n].F = x;
		else {
			int mid = (l + r) >> 1;
			push(n);
			if (pos <= mid) set(n << 1, l, mid, pos, x);
			else set(n << 1 | 1, mid + 1, r, pos, x);
			pull(n);
		}
	}
	//pair<ll, int> ask(int n, int l, int r, int L, int R) {
	//	if (L <= l && r <= R) return val[n];
	//	else if (L > r || l > R) return {-kInf, 0};
	//	else {
	//		int mid = (l + r) >> 1;
	//		push(n);
	//		return max(ask(n << 1, l, mid, L, R), ask(n << 1 | 1, mid + 1, r, L, R));
	//	}
	//}
};

seg_tree sg;
ll ans, dp[kN];
int posx, posy, a[kN];

void calc(int n) {
	priority_queue<pair<int, int>> pq;
	stack<pair<int, int>> s;
	int lst;
	for (int i = 1; i <= n; i++) pq.push({a[i], i});
	sg.init(1, 1, n);
	for (int i = 1; i < n; i++) {
		while (pq.top().S <= i) pq.pop();
		lst = i;
		while (!s.empty()) {
			if (s.top().F >= a[i]) {
				//printf("add(%d, %d, %d)\n", s.top().S, lst - 1, s.top().F - a[i]);
				sg.add(1, 1, n, s.top().S, lst - 1, s.top().F - a[i]);
				sg.change(1, 1, n, s.top().S, lst - 1, i);
				lst = s.top().S;
				s.pop();
			}
			else break;
		}
		//printf("set(%d, %d)\n", i, -a[i]);
		sg.set(1, 1, n, i, -a[i]);
		sg.add(1, 1, n, 1, i, a[i]);
		sg.change(1, 1, n, i, i, i);
		s.push({a[i], lst});
		dp[i] = sg.val[1].F + pq.top().F;
		if (ans < dp[i]) {
			ans = dp[i];
			posx = pq.top().S;
			posy = sg.val[1].S;
		}
	}

	//for (int i = 1; i < n; i++) printf("dp[%d] = %lld\n", i, dp[i]);
	//printf("here\n");
	return ;
}


int main() {
	int n;
	ll lans;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	dp[0] = 0;
	posx = 1, posy = 2;
	ans = -kInf;
	for (int i = 1; i <= n; i++) ans = max(ans, dp[i] = max(dp[i - 1], 0ll) + a[i]);
	//printf("here\n");
	calc(n);
	lans = ans;
	reverse(a + 1, a + n + 1);
	calc(n);
	if (lans != ans) {
		posx = n + 1 - posx;
		posy = n + 1 - posy;
	}
	printf("%lld\n%d %d\n", ans, posx, posy);
}
