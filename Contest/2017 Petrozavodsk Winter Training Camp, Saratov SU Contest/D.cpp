#include <stdio.h>
#include <algorithm>
#include <stack>
#include <utility>
using namespace std;
#define F first
#define S second

typedef long long int ll;
constexpr int kN = int(2E5 + 10);
constexpr ll kInf = ll(1E16 + 10);

struct seg_tree {
	ll val[kN << 2], flag[kN << 2];
	void init(int n, int l, int r) {
		val[n] = kInf;
		flag[n] = 0;
		if (l < r) {
			int mid = (l + r) >> 1;
			init(n << 1, l, mid);
			init(n << 1 | 1, mid + 1, r);
		}
		return ;
	}
	void addtag(int n, ll x) {
		flag[n] += x;
		val[n] += x;
		return ;
	}
	void push(int n) {
		if (flag[n]) {
			addtag(n << 1, flag[n]);
			addtag(n << 1 | 1, flag[n]);
			flag[n] = 0;
		}
		return ;
	}
	void pull(int n) {
		val[n] = min(val[n << 1], val[n << 1 | 1]);
		return ;
	}
	void set(int n, int l, int r, int pos, ll x) {
		if (l == r) val[n] = x;
		else {
			int mid = (l + r) >> 1;
			push(n);
			val[n] = min(val[n], x);
			if (pos <= mid) set(n << 1, l, mid, pos, x);
			else set(n << 1 | 1, mid + 1, r, pos, x);
		}
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
	}
};

pair<ll, ll> p[kN];
ll dp[kN];
seg_tree sg;

ll solve(int n) {
	stack<pair<int, int>> A;
	int lst, pos = 0;
	for (int i = 1; i <= n; i++) scanf("%lld%lld", &p[i].F, &p[i].S);
	sort(p + 1, p + n + 1);
	sg.init(1, 0, n);
	sg.set(1, 0, n, 0, 0);
	A.push({0, 0});
	p[0] = {0, 0};
	for (int i = 1; i <= n; i++) {
		lst = i;
		while (!A.empty()) {
			if (A.top().F < p[i].S) {
				sg.add(1, 0, n, A.top().S, lst - 1, (p[i].S - A.top().F) << 1);
				lst = A.top().S;
				A.pop();
			}
			else break;
		}
		A.push({p[i].S, lst});
		A.push({0, i});

		while (pos < i) {
			if (dp[pos] < p[i].F) {
				if (pos > 0) sg.add(1, 0, n, 0, pos - 1, dp[pos] - dp[pos - 1]);
				pos++;
			}
			else break;
		}
		sg.add(1, 0, n, 0, pos - 1, p[i].F - max(dp[pos - 1], p[i - 1].F));
		sg.set(1, 0, n, i, (dp[i] = sg.val[1]));
	}
	return dp[n];
}

int main() {
	int n;
	while (scanf("%d", &n) != EOF) printf("%lld\n", solve(n));
} 
